/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_CONFIGURATION
#define SERVERMANAGER_CONFIGURATION

#include <string>

using namespace std;

namespace ServerManager
{
	typedef struct {
		string root;
		string extension;
		string htdocs;
		string nginx;
		string hosts;
	} Configuration;
}

#endif
