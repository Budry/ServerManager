/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#include <iostream>
#include <regex>
#include <map>
#include "Input.h"

using namespace ServerManager;

Input::Input(int argc, const char *argv[]) {
  if (argc < 2) {
    throw "Invalid arguments! See --help or help.";
  }
  this->command = argv[1];
  if (this->command.compare("--help") == 0) {
    this->command = "help";
  }

  int i = 0;
  if (this->command.compare("help") == 0 || this->command.compare("list") == 0) {
    i = 2;
  } else if (this->command.compare("create") == 0) {
    if (argc < 3) {
      throw "Invalid arguments! See --help or help.";
    }
    this->hostName = argv[2];
    i = 3;
  } else if (this->command.compare("remove") == 0) {
    if (argc < 3) {
      throw "Invalid arguments! See --help or help.";
    }
    this->hostName = argv[2];
    i = 3;
  } else if (this->command.compare("search") == 0) {
    if (argc < 3) {
      throw "Invalid arguments! See --help or help.";
    }
    this->hostName = argv[2];
    i = 3;
  } else {
    throw "Invalid command!. See --help or help.";
  }

  std::regex optionPattern("^--([a-zA-Z0-9]+)$");
  std::cmatch match;
  for (; i < argc; i++) {
    if (std::regex_match(argv[i], match, optionPattern)) {
      if (i + 1 < argc) {
        this->options[match[1]] = argv[i + 1];
      } else {
        this->options[match[1]] = "";
      }
    }
  }
}

std::string Input::getOption(std::string name) {
  if (this->options.find(name) == this->options.end() ) {
    return "";
  } else {
    return this->options.find(name)->second;
  }
}

std::string Input::getCommand() {
  return this->command;
}

std::string Input::getHostName() {
  return this->hostName;
}