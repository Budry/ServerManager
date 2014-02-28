/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_ARGUMENTPARSER
#define SERVERMANAGER_ARGUMENTPARSER

#include <string>
#include <vector>
#include "./Configuration.h"

using namespace ServerManager;
using namespace std;

namespace ServerManager
{
	class ArgumentParser
	{
		public:
			ArgumentParser(int argc, char** argv);
			string getAction();
			string getParam();
			string getOption(string key);
		private:	
			vector<string> argv;
			string param;
			string action;
	};
}

#endif
