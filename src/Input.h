/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#ifndef SERVER_MANAGER_INPUT_H
#define SERVER_MANAGER_INPUT_H

#include <vector>
#include <map>

namespace ServerManager {
  class Input {
    public:
      Input(int, const char *[]);
      std::string getOption(std::string, std::string);
      std::string getCommand();
      std::string getHostName();
    private:
      std::string command;
      std::string hostName;
      std::map<std::string, std::string> options;
  };
}

#endif