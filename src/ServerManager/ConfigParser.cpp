/*
 * This file is part of ServerManager package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <limits.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "./ConfigParser.h"
#include "./Configuration.h"

using namespace ServerManager;
using namespace std;

ConfigParser::ConfigParser()
{
	string path = getenv("HOME");
	path.append("/.server-manager/.server-manager");
	this->configFile = path;
}

Configuration ConfigParser::getConfiguration()
{
	Configuration cfg;
	ifstream file(this->configFile.c_str());
	if (!file.good()) {
		throw "Missing config file ~/.server-manager/.server-manager";
	}
	string line;
	while(getline(file, line)) {
		istringstream line_string(line);
		string key;
		if (getline(line_string, key, '=')) {
			string value;
			if (getline(line_string, value)) {
				if (key.compare("root") == 0) {
					cfg.root = value;
				} else if (key.compare("tld") == 0) {
					cfg.tld = value;
				} else if (key.compare("htdocs") == 0) {
					if (value.compare("pwd") == 0) {
						cfg.htdocs = getcwd(NULL, PATH_MAX + 1);
					} else {
						cfg.htdocs = value;
					}
				} else if (key.compare("nginx") == 0) {
					cfg.nginx = value;
				} else if (key.compare("hosts") == 0) {
					cfg.hosts = value;
				} else if (key.compare("log") == 0) {
					cfg.log = value;
				} else if (key.compare("systemTemplate") == 0) {
					cfg.systemTemplate = value;
				} else if (key.compare("serverTemplate") == 0) {
					cfg.serverTemplate = value;
				} else if (key.compare("project") == 0) {
					cfg.project = value;
				} else {
					throw "Unsupported option";
				}
			}
		}
	}
	file.close();

	return cfg;
}
