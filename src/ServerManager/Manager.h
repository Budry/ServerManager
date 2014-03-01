/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_SERVERMANAGER
#define SERVERMANAGER_SERVERMANAGER

#include <string>
#include "./Configuration.h"

using namespace ServerManager;
using namespace std;

namespace ServerManager
{
	class Manager
	{
		public:
			Manager();
			void setConfiguration(Configuration config);
			string getList();
			string create(string hostName);
			string remove(string hostName);
			bool search(string hostName);
		private:
			void appendLine(string* result, string key, string line);
			Configuration config;
	};
}

#endif
