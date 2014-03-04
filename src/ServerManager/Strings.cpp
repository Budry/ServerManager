/*
 * This file is part of ServerManager package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include <string>
#include "Strings.h"

using namespace ServerManager;
using namespace std;

Strings::Strings() {}

string Strings::replace(string search, string replace, string original)
{
	string result = original;
	size_t start;
	while ((start = result.find(search)) != string::npos) {
		size_t length = search.length();
		result.replace(start, length, replace);
	}

	return result;
}
