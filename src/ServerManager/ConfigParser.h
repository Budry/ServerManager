/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_CONFIGPARSER
#define SERVERMANAGER_CONFIGPARSER

#include <string>
#include "./Configuration.h"

using namespace ServerManager;
using namespace std;

namespace ServerManager
{
	class ConfigParser
	{
		public:
			ConfigParser();
			Configuration getConfiguration();
		private:
			string configFile;
	};
}

#endif
