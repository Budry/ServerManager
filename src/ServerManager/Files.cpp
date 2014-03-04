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
#include "Files.h"

using namespace ServerManager;
using namespace std;

Files::Files() {}

string Files::getString(string path)
{
	ifstream file(path.c_str());
	if (!file.good()) {
		throw "Invalid file";
	}
	string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	file.close();

	return content;
}
