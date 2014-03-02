/*
 * This file is part of ServerManager package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_CONSOLE
#define SERVERMANAGER_CONSOLE

#include <string>

using namespace std;

namespace ServerManager
{
	class Console
	{
		public:
			Console(string command);
			void addCommand(string command);
			string exec();
		private:
			string command;
	};
}

#endif
