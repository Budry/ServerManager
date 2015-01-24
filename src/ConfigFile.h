/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#ifndef SERVER_MANAGER_CONFIG_FILE_H
#define SERVER_MANAGER_CONFIG_FILE_H

#include <string>

namespace ServerManager {
  class ConfigFile {
    public:
      ConfigFile(std::string);
      std::string readString(std::string, std::string, std::string);
    private:
      std::string pathName;
  };
}

#endif