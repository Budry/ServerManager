/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#include "./Configurator.h"
#include "./ArgumentParser.h"
#include "./Configuration.h"

using namespace ServerManager;

Configurator::Configurator() {}

Configuration Configurator::applyOptions(Configuration config, ArgumentParser* args)
{
	if (!args->getOption("--root").empty()) {
		config.root = args->getOption("--root");
	} else if (!args->getOption("--extension").empty()) {
		config.extension = args->getOption("--extension");
	} else if (!args->getOption("--htdocs").empty()) {
		config.htdocs = args->getOption("--htdocs");
	} else if (!args->getOption("--nginx").empty()) {
		config.nginx = args->getOption("--nginx");
	} else if (!args->getOption("--hosts").empty()) {
		config.htdocs = args->getOption("--hosts");
	}

	return config;
}
