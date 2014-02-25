/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */


#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "./Manager.h"
#include "./Configuration.h"

using namespace ServerManager;

Manager::Manager(){}

void Manager::setConfiguration(Configuration config)
{
	this->config = config;
}

string Manager::getList()
{
	ifstream file(this->config.hosts.c_str());
	if (file.good()) {
		string content(
			(istreambuf_iterator<char>(file)),
			(istreambuf_iterator<char>())
		);
		file.close();

		return content;
	} else {
		file.close();
		throw "Invalid hosts file";	
	}
}

string Manager::create(string hostName)
{
	string result;
	result.append("Stoping nginx");
	system("nginx -s stop");
	ofstream hostsFile(this->config.hosts.c_str(), ios_base::app | ios_base::out);
	if (hostsFile.good()) {
		hostsFile << endl << "127.0.0.1\t" << hostName << this->config.ext;
		result.append("\nAdded virtual host into hosts file");
		hostsFile.close();
	} else {
		hostsFile.close();
		throw "Invalid hosts file";
	}
	string path = this->config.nginx;
	path.append("/");
	path.append(hostName);
	path.append(".conf");
	ofstream nginxConfig(path.c_str());
	if (nginxConfig.good()) {
		nginxConfig << "server {" << endl 
			<< "\tlisten 80;" << endl 
			<< "\tserver_name " << hostName << this->config.ext << ";" << endl 
			<< "\troot " << this->config.htdocs << "/" << hostName << "/" << this->config.root << ";" << endl
			<< endl
			<< "\terror_log " << this->config.htdocs << "/" << hostName << "/log/" << hostName << "_error.log;" << endl
			<< "\taccess_log " << this->config.htdocs << "/" << hostName << "/log/" << hostName << "_accesslog.log;" << endl
			<< endl
			<< "\tinclude common/common.conf;" << endl
			<< "\tinclude common/php.conf;" << endl
			<< "\tinclude common/nette.conf;" << endl
			<< "}";
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
		throw "Nginx config file has not been created";
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
		throw "Project path has not been removed";
	}
	if (system(rmNginxConf.c_str()) == 0) {
		result.append("\nNginx configuration has been removed");
	} else {
		throw "Nginx configuration has not been removed";
	}
	ifstream ihostFile(this->config.hosts.c_str());
	if (ihostFile.good()) {
		string line;
		string newContent = "";
		while(getline(ihostFile, line)) {
			if (line.compare("127.0.0.1\t" + hostName + this->config.ext) != 0 && !line.empty())  {
				newContent.append(line + "\n");
			}
		}
		ofstream ohostFile(this->config.hosts.c_str()/*, ios_base::app | ios_base::out*/);
		ohostFile << newContent;
		result.append("\nVirtual host has been removed from hosts file");
		ihostFile.close();
		ohostFile.close();
	} else {
		throw "Invalid hosts file";
		ihostFile.close();
	}
	result.append("\nStarting nginx");
	system("nginx");

	return result;
}
