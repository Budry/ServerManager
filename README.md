# ServerManager

Simply server manager for manage virtual hosts in nginx.

## Requirements

* ngnix configuration by this [manual](https://gist.github.com/jsifalda/3331643)

## Installation

1. Run  ```$ sudo sh install.sh [command-name]```
2. Default command name is ```server-manager``` but you can change this if run installation script with command name argument.
3. And next you must edit ```/home/user/.server-manager``` config file and fill your paths and configuration.

*If you want set directory automatically use ```htdocs=pwd```*

## Usages

**Important! Server manager must be run with sudo**

```shell
$ sudo server-mamager list
$ sudo server-manager create <host-name> [options]
$ sudo server-manager remove <host-name> [options]
```

### Actions:
* ```list```				- Display list of created virtual hosts
* ```create <host-name>```	- Create a new virtual host with <host-name> name
* ```remove <host-name>```	- Remove virtual host and all project files

### Options:

*Options has a higher priority than configuration in config file*

* ```--root```		- Path to server root
* ```--tld```		- Set server tld
* ```--htdocs```	- Set path to htdocs directory
* ```--nginx```		- Set path to nginx sites-enabled directory
* ```--hosts```		- Set path to hosts file *(/etc/hosts)*

**All default configuration are in ```/home/user/.server-manager``` file and you can change it.**
