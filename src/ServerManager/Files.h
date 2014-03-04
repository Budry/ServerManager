/*
 * This file is part of ServerManager package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_FILES
#define SERVERMANAGER_FILES

#include <string>

using namespace std;

namespace ServerManager
{
	class Files
	{
		public:
			Files();
			string getString(string path);
	};
}

#endif
