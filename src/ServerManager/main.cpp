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
		config = configurator->applyOptions(config, argsParser);
		if (argsParser->getAction().compare("list") == 0) {
			cout << formateSuccess("List of virtual hosts:") << endl;
			manager->setConfiguration(config);
			cout << formateProcess(manager->getList()) << endl;
		} else if (argsParser->getAction().compare("create") == 0) {
			cout << formateProcess("Creating virtual host:") << endl;
			manager->setConfiguration(config);
			cout << formateSuccess(manager->create(argsParser->getParam())) << endl;
		} else if (argsParser->getAction().compare("remove") == 0) {
			cout << formateProcess("Removing virtual host:") << endl;
			manager->setConfiguration(config);
			cout << formateSuccess(manager->remove(argsParser->getParam())) << endl;
		} else if (argsParser->getAction().compare("search") == 0) {
			manager->setConfiguration(config);
			cout << formateSuccess("Host ");
			cout <<	formateProcess(argsParser->getParam());
			cout << formateSuccess(" has been found in:") << endl;
			cout << formateProcess(manager->search(argsParser->getParam())) << endl;
		} else {
			cout << formateProcess(HELP) << endl;
		}	
	} catch(const char* e) {
		cerr << formateThrow(e) << endl;
	}

	return 0;
}

string formateThrow(string message)
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

string formateError(string message)
{
	string formated = "\033[0;31m";
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
