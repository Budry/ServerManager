# ServerManager

Simply server manager for manage virtual hosts in nginx and Linux.

## Requirements

* ngnix configuration by this [manual](https://gist.github.com/jsifalda/3331643)

## Installation

1. Run  ```$ sudo sh install.sh [command-name]```
2. Default command name is ```server-manager``` but you can change this if run installation script with command name argument.
3. And next you must edit ```/home/user/.server-manager/.server-manager``` config file and fill your paths and configuration.

You can update base templates or create custom in ```~/.server-manager/templates```. This files are templates for configuration.
For more info see [Template](#Templates)

*If you want set directory automatically use ```htdocs=pwd```*

## Usages

**Important! Server manager must be run with sudo**

```shell
$ sudo server-mamager list [options]
$ sudo server-manager create <host-name> [options]
$ sudo server-manager remove <host-name> [options]
$ sudo server-manager search <host-name> [options]
```

### Actions:
* ```list```				- Display list of created virtual hosts
* ```create <host-name>```	- Create a new virtual host with <host-name> name
* ```remove <host-name>```	- Remove virtual host and all project files
* ```search <host-name>```	- Search if host with <host-name> exist

### Options:

*Options has a higher priority than configuration in config file*

* ```--root```				- Path to server root
* ```--tld```				- Set server tld
* ```--htdocs```			- Set path to htdocs directory
* ```--nginx```				- Set path to nginx sites-enabled directory
* ```--hosts```				- Set path to hosts file *(/etc/hosts)*
* ```--systemTemplate```	- Set template for host in system hosts file
* ```--serverTemplate```	- Set template for server (apache/nginx/...) configuration

**All default configuration are in ```/home/user/.server-manager``` file and you can change it.**

### Templates

You can edit templates for system hosts and server virtual host configuration. You can create custom template too.
In tempaltes you can use keywords: ```%hostName```, ```%tld%```, ```%root%```, ```%htdocs%```. This keywords will be
replaced by section in configuration file or by [options](#Options) with same name.

If you can add custom template you must edit in config file section ```serverTemplate``` or ```systemTemplate``` or you can use
options ```--serverTemplate <path>``` and ```---systemTemplate <path>```.
