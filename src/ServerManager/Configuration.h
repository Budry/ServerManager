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
		string tld;
		string htdocs;
		string nginx;
		string hosts;
		string log;
		string systemTemplate;
		string serverTemplate;
		string project;
	} Configuration;
}

#endif
