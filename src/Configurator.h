/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#ifndef SERVER_MANAGER_CONFIGURATOR_H
#define SERVER_MANAGER_CONFIGURATOR_H

#include "Input.h"
#include "ConfigFile.h"

namespace ServerManager {
  class Configurator {
    public:
      Configurator(Input*, ConfigFile*);
      std::string getHostsPath();
      std::string getNginxPath();
      std::string getTemplate();
      std::string getTld();
      std::string getHtdocs();
      std::string getRoot();
      std::string getLogDir();
    private:
      Input *input;
      ConfigFile *config;
  };
}

#endif