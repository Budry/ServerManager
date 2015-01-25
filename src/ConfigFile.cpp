/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#include <fstream>
#include <regex>
#include "ConfigFile.h"

using namespace ServerManager;

ConfigFile::ConfigFile(std::string path) {
  this->pathName = path;
}

std::string ConfigFile::get(std::string section, std::string key) {
  std::ifstream fileStream(this->pathName.c_str());
  if (!fileStream.good()) {
    return "";
  }
  std::string line;
  bool isEnd = false;
  bool inSection = false;

  std::regex sectionPattern("^\\[(.*)\\]$");
  std::cmatch match;

  while (getline(fileStream, line) && !isEnd) {
    if (std::regex_match(line.c_str(), match, sectionPattern)) {
      if (section.compare(match[1]) == 0) {
        inSection = true;
        continue;
      } else {
        isEnd = inSection;
      }
    }
    if (inSection) {
      std::string delimiter = "=";
      std::string keyOrig = line.substr(0, line.find(delimiter));
      if (keyOrig.compare(key) == 0) {
        return line.substr(line.find(delimiter) + 1, line.size());
      }
    }
  }

  return "";
}