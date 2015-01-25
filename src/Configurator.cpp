/**
 * This file is part of the ServerManager package.
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view
 * the license.md file that was distributed with this source code.
**/

#include <limits.h>
#include <unistd.h>
#include <cstdlib>
#include "Configurator.h"

using namespace ServerManager;

Configurator::Configurator(Input *input, ConfigFile *config) {
  this->input = input;
  this->config = config;
}

std::string Configurator::getHostsPath() {
  std::string key = "hosts";
  return this->input->getOption(key, this->config->get("core", key));
}

std::string Configurator::getNginxPath() {
  std::string key = "nginx";
  return this->input->getOption(key, this->config->get("core", key));
}

std::string Configurator::getTemplate() {
  std::string key = "template";
  return this->input->getOption(key, this->config->get("core", key));
}

std::string Configurator::getTld() {
  std::string templateName = this->getTemplate();
  std::string key = "tld";
  return this->input->getOption(key, this->config->get(templateName, key));
}

std::string Configurator::getHtdocs() {
  std::string templateName = this->getTemplate();
  std::string key = "htdocs";
  std::string value = this->input->getOption(key, this->config->get(templateName, key));
  if (value.compare("pwd") == 0) {
    value = getcwd(NULL, PATH_MAX + 1);
  }

  return value;
}

std::string Configurator::getRoot() {
  std::string templateName = this->getTemplate();
  std::string key = "root";
  return this->input->getOption(key, this->config->get(templateName, key));
}

std::string Configurator::getLogDir() {
  std::string templateName = this->getTemplate();
  std::string key = "log";
  return this->input->getOption(key, this->config->get(templateName, key));
}