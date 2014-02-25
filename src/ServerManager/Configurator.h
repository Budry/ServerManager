/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_CONFIGURATOR
#define SERVERMANAGER_CONFIGURATOR

#include "./Configuration.h"
#include "./ArgumentParser.h"

using namespace ServerManager;

namespace ServerManager
{
	class Configurator
	{
		public:
			Configurator();
			Configuration applyOptions(Configuration config, ArgumentParser* args);
	};
}

#endif
