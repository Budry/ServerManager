/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#include <iostream>
#include "ConfigFile.h"

using namespace ServerManager;

int main(int argc, char *argv[]) {
  ConfigFile *config = new ConfigFile();
  std::cout << config->readString("section", "key", "omg");
}