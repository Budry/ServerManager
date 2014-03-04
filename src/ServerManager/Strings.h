/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_STRINGS
#define SERVERMANAGER_STRINGS

#include <string>

using namespace std;

namespace ServerManager
{
	class Strings
	{
		public:
			Strings();
			string replace(string search, string replace, string original);
	};
}

#endif
