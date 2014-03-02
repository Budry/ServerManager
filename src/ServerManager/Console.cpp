/*
 * This file is part of ServerManager package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <string>
#include <fstream>
#include "./Console.h"

using namespace ServerManager;
using namespace std;

Console::Console(string command)
{
	this->command = command + " 2>&1";
}

void Console::addCommand(string command)
{
	if (this->command.empty()) {
		this->command.append(command);
	} else {
		this->command.append(" && " + command);
	}
}

string Console::exec()
{
	string result;
	const int BUFFER_MAX = 4096;
	FILE* stream;
	char buffer[BUFFER_MAX];
	stream = popen(this->command.c_str(), "r");
	if (stream != NULL) {
		while(!feof(stream)) {
			if (fgets(buffer, BUFFER_MAX, stream) != NULL) {
				result.append(buffer);
			}
		}
	}

	return result;
}
