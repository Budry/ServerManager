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
#include "./Console.h"
#include "./Files.h"
#include "./Strings.h"

using namespace ServerManager;
using namespace std;

Manager::Manager(){}

void Manager::setConfiguration(Configuration config)
{
	this->config = config;
}

string Manager::search(string hostName)
{
	string cmd = "cat " + this->config.hosts + " | grep " + hostName;
	Console console(cmd);

	return console.exec();
}

string Manager::getList()
{
	ifstream file(this->config.hosts.c_str());
	string line, result;
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
	Console console("nginx -s stop");
	if (console.exec().empty()) {
		result.append("Stoping nginx");
	}
	ofstream hostsFile(this->config.hosts.c_str(), ios_base::app | ios_base::out);
	if (hostsFile.good()) {
		hostsFile << endl << this->getHostConfig(hostName);
		result.append("\nAdded virtual host into hosts file");
		hostsFile.close();
	} else {
		hostsFile.close();
		throw "Invalid path to hosts file or you don't run as administrator(sudo)";
	}
	string path = this->config.nginx + "/" + hostName + ".conf";
	ofstream nginxConfig(path.c_str());
	if (nginxConfig.good()) {
		nginxConfig << this->getServerConfig(hostName);
		if (nginxConfig.good()) {
			result.append("\nAdded virtual host nginx configuration");
		}
		if (!this->config.project.empty()) {
			Console testGitRepository("git ls-remote " + this->config.project + " --exit-code");
			if (testGitRepository.exec().empty()) {
					Console cloneGitRepository("git clone " + this->config.project + " " + this->config.htdocs + "/" + hostName);
					cloneGitRepository.exec();
					result.append("\nCreated project from git repository");
			} else {
				nginxConfig.close();
				throw "Check if repository of project is valid: " + this->config.project;
			}
		} else {
			Console mkdirLog("mkdir -p " + this->config.htdocs + "/" + hostName + "/" + this->config.log);
			Console mkdirRoot("mkdir -p " + this->config.htdocs + "/" + hostName + "/" + this->config.root);
			if (mkdirLog.exec().empty() && mkdirRoot.exec().empty()) {
				result.append("\nCreated base project directories: ");
				result.append("\n\t-" + this->config.htdocs + "/" + hostName + "/" + this->config.log);
				result.append("\n\t-" + this->config.htdocs + "/" + hostName + "/" + this->config.root);
			}
		}
		nginxConfig.close();
	} else {
		nginxConfig.close();
		throw "Invalid path to nginx sites-enabled directory or you don't run as administrator(sudo)";
	}
	Console nginxStart("nginx");
	if (nginxStart.exec().empty()) {
		result.append("\nStarting nginx");
	}
	Console chmodCmd("chmod -R 0777 " + this->config.htdocs + "/" + hostName);
	if (chmodCmd.exec().empty()) {
		result.append("\nSet chmod");
	}

	return result;
}

string Manager::remove(string hostName)
{
	string result;
	Console console("nginx -s stop");
	if (console.exec().empty()) {
		result.append("Stoping nginx");
	}
	Console rmProject("rm -rf " + this->config.htdocs + "/" + hostName);
	Console rmNginxConf("rm -rf " + this->config.nginx + "/" + hostName + ".conf");
	if (rmProject.exec().empty()) {
		result.append("\nProject directory has been removed");
	} else {
		throw "Invalid path to host(project) directory or you don't run as administrator(sudo)";
	}
	if (rmNginxConf.exec().empty()) {
		result.append("\nNginx configuration has been removed");
	} else {
		throw "Invalid path to nginx sites-enabled directory or you don't run as administrator(sudo)";
	}

	ifstream ihostFile(this->config.hosts.c_str());
	if (ihostFile.good()) {
		ihostFile.close();
		Console rmHost("sed --in-place /" + hostName + "/d " + this->config.hosts.c_str());
		if (rmHost.exec().empty()) {
			result.append("\nVirtual host/s has been removed from hosts file");
		}
	} else {
		ihostFile.close();
		throw "Invalid path to hosts file or you don't run as administrator(sudo)";
	}
	Console nginxStart("nginx");
	if (nginxStart.exec().empty()) {
		result.append("\nStarting nginx");
	}

	return result;
}

void Manager::appendLine(string* result,string key, string line)
{
	if (key.compare("127.0.0.1") == 0) {
		(*result).append(line + "\n");
	}
}

string Manager::getServerConfig(string hostName)
{
	Files files;
	Strings strings;
	string content = files.getString(this->config.serverTemplate);
	string config = strings.replace("%hostName%", hostName, content);
	config = strings.replace("%tld%", this->config.tld, config);
	config = strings.replace("%htdocs%", this->config.htdocs, config);
	config = strings.replace("%root%", this->config.root, config);
	config = strings.replace("%log%", this->config.log, config);

	return config;
}

string Manager::getHostConfig(string hostName)
{
	Files files;
	Strings strings;
	string content = files.getString(this->config.systemTemplate);
	string host = strings.replace("%hostName%", hostName, content);
	host = strings.replace("%tld%", this->config.tld, host);

	return host;
}
