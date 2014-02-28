/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "./ArgumentParser.h"

using namespace ServerManager;
using namespace std;

ArgumentParser::ArgumentParser(int argc, char** argv)
{
	int i,start;
	if (argc >= 2) {
		this->action = argv[1];
		if (this->action.compare("list") == 0) {
			if ((argc - 2) % 2 != 0) {
				throw "Missing option value";
			}
			start = 2;
		} else {
			if (argc >= 3) {
				if ((argc - 3) % 2 != 0) {
					throw "Missing option value";
				}
				this->param = argv[2];
				start = 3;
			} else {
				throw "Invalid arguments";
			}
		}
		for (i = start; i < argc; i++) {
			this->argv.push_back(argv[i]);
		}
	} else {
		throw "Invalid arguments";
	}
}

string ArgumentParser::getAction()
{
	return this->action;
}

string ArgumentParser::getParam()
{
	return this->param;
}

string ArgumentParser::getOption(string key)
{
	unsigned int i;
	for(i = 0; i < this->argv.size(); i++) {
		if (this->argv[i].compare(key) == 0) {
			return this->argv[i + 1];
		}
	}

	return "";
}
