/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "./main.h"
#include "./Configuration.h"
#include "./ConfigParser.h"
#include "./ArgumentParser.h"
#include "./Manager.h"
#include "./Configurator.h"

using namespace std;
using namespace ServerManager;

int main(int argc, char** argv)
{
	try {
		ConfigParser* parser = new ConfigParser();
		Configuration config = parser->getConfiguration();
		ArgumentParser* argsParser = new ArgumentParser(argc, argv);
		Configurator* configurator = new Configurator();
		Manager* manager = new Manager();
		if (argsParser->getAction().compare("list") == 0) {
			manager->setConfiguration(config);
			cout << formateSuccess("List of virtual hosts:") << endl;
			cout << formateProcess(manager->getList()) << endl;
		} else if (argsParser->getAction().compare("create") == 0) {
			if (argsParser->getParam().empty()) {
				throw "Missing host name";
			}
			cout << formateProcess("Creating virtual host:") << endl;
			config = configurator->applyOptions(config, argsParser);
			manager->setConfiguration(config);
			cout << formateSuccess(manager->create(argsParser->getParam())) << endl;
		} else if (argsParser->getAction().compare("remove") == 0) {
			cout << formateProcess("Removing virtual host:") << endl;
			config = configurator->applyOptions(config, argsParser);
			manager->setConfiguration(config);
			cout << formateSuccess(manager->remove(argsParser->getParam())) << endl;		
		} else {
			cout << formateProcess(HELP) << endl;
		}	
	} catch(const char* e) {
		cerr << formateError(e) << endl;
	}

	return 0;
}

string formateError(string message)
{
	string formated = "\033[0;41m";
	formated.append(message);
	formated.append("\033[0m");

	return formated;
}

string formateSuccess(string message)
{
	string formated = "\033[0;32m";
	formated.append(message);
	formated.append("\033[0m");

	return formated;
}

string formateProcess(string message)
{
	string formated = "\033[0;33m";
	formated.append(message);
	formated.append("\033[0m");

	return formated;
}
