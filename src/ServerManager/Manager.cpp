/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "./Manager.h"
#include "./Configuration.h"

using namespace ServerManager;
using namespace std;

Manager::Manager(){}

void Manager::setConfiguration(Configuration config)
{
	this->config = config;
}

void Manager::appendLine(string* result,string key, string line)
{
	if (key.compare("127.0.0.1") == 0) {
		(*result).append(line + "\n");
	}
}

string Manager::getServerConfig(string hostName)
{
	string config = "server {\n" \
					 "\tlisten 80;\n" \
					 "\tserver_name " + hostName + this->config.tld + ";\n" \
					 "\troot " + this->config.htdocs + "/" + hostName + "/" + this->config.root + ";\n" \
					 "\n" \
					 "\terror_log " + this->config.htdocs + "/" + hostName + "/log/" + hostName + "_error.log;\n" \
					 "\taccess_log " + this->config.htdocs + "/" + hostName + "/log/" + hostName + "_accesslog.log;\n" \
					 "\n" \
					 "\tinclude common/common.conf;\n" \
					 "\tinclude common/php.conf;\n" \
					 "\tinclude common/nette.conf;\n" \
					 "}\n";

	return config;
}

string Manager::getHostConfig(string hostName, string delimiter = "\t")
{
	string host = "127.0.0.1" + delimiter + hostName + this->config.tld;

	return host;
}

bool Manager::search(string hostName)
{
	string result;
	FILE* stream;
	char buffer[256];
	string cmd = "cat " + this->config.hosts + " | grep " + hostName  + " 2>&1";
	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, 256, stream) != NULL) {
				result.append(buffer);
			}
		}
		pclose(stream);
	}

	return !result.empty();
}

string Manager::getList()
{
	ifstream file(this->config.hosts.c_str());
	string line;
	string result;
	if (file.good()) {
		while(getline(file, line)) {
			istringstream line_string(line);
			string key;
			if (line.find(" ") != std::string::npos) {
				if (getline(line_string, key, ' ')) {
					this->appendLine(&result, key, line);
				}
			} else {
				if (getline(line_string, key, '\t')) {
					this->appendLine(&result, key, line);
				}
					
			}
		}
		file.close();

		return result;
	} else {
		file.close();
		throw "Invalid path to hosts file or you don't run as administrator(sudo)";
	}
}

string Manager::create(string hostName)
{
	string result;
	result.append("Stoping nginx");
	system("nginx -s stop");
	ofstream hostsFile(this->config.hosts.c_str(), ios_base::app | ios_base::out);
	if (hostsFile.good()) {
		hostsFile << endl << this->getHostConfig(hostName);
		result.append("\nAdded virtual host into hosts file");
		hostsFile.close();
	} else {
		hostsFile.close();
		throw "Invalid path to hosts file or you don't run as administrator(sudo)";
	}
	string path = this->config.nginx;
	path.append("/");
	path.append(hostName);
	path.append(".conf");
	ofstream nginxConfig(path.c_str());
	if (nginxConfig.good()) {
		nginxConfig << this->getServerConfig(hostName);
		if(nginxConfig.good()) {
			result.append("\nAdded virtual host nginx configuration");
		}
		string mkdirLog = "mkdir -p " + this->config.htdocs + "/" + hostName + "/log";
		string mkdirRoot = "mkdir -p " + this->config.htdocs + "/" + hostName + "/" + this->config.root;
		if (system(mkdirLog.c_str()) == 0 && system(mkdirRoot.c_str()) == 0) {
			result.append("\nCreated base project directories: ");
			result.append("\n\t-" + this->config.htdocs + "/" + hostName + "/log");
			result.append("\n\t-" + this->config.htdocs + "/" + hostName + "/" + this->config.root);
		}
		nginxConfig.close();
	} else {
		nginxConfig.close();
		throw "Invalid path to nginx sites-enabled directory or you don't run as administrator(sudo)";
	}
	result.append("\nStarting nginx");
	system("nginx");
	result.append("Set chmod");
	string chmodCmd = "chmod -R 0777 " + this->config.htdocs + "/" + hostName;
	system(chmodCmd.c_str());

	return result;
}

string Manager::remove(string hostName)
{
	string result;
	result.append("Stoping nginx");
	system("nginx -s stop");
	string rmProject = "rm -rf " + this->config.htdocs + "/" + hostName;
	string rmNginxConf = "rm -rf " + this->config.nginx + "/" + hostName + ".conf";
	if (system(rmProject.c_str()) == 0) {
		result.append("\nProject directory has been removed");
	} else {
		throw "Invalid path to host(project) directory or you don't run as administrator(sudo)";
	}
	if (system(rmNginxConf.c_str()) == 0) {
		result.append("\nNginx configuration has been removed");
	} else {
		throw "Invalid path to nginx sites-enabled directory or you don't run as administrator(sudo)";
	}
	ifstream ihostFile(this->config.hosts.c_str());
	if (ihostFile.good()) {
		string line;
		string newContent = "";
		while(getline(ihostFile, line)) {
			if (line.compare(this->getHostConfig(hostName)) != 0 && !line.empty() && line.compare(this->getHostConfig(hostName, " ")) != 0)  {
				newContent.append(line + "\n");
			}
		}
		ofstream ohostFile(this->config.hosts.c_str());
		ohostFile << newContent;
		result.append("\nVirtual host has been removed from hosts file");
		ihostFile.close();
		ohostFile.close();
	} else {
		throw "Invalid path to hosts file or you don't run as administrator(sudo)";
		ihostFile.close();
	}
	result.append("\nStarting nginx");
	system("nginx");

	return result;
}
