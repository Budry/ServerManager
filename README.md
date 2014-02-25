# ServerManager

## Installation

Run

```shell
$ sudo sh install.sh [command-name]
```
Default command name is ```server-manager``` but you can change this if run installation script with command name argument.

## Usages

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
* ```--root```		- Path to server root
* ```--tld```		- Set server tld
* ```--htdocs```	- Set path to htdocs directory
* ```--nginx```		- Set path to nginx sites-enabled directory
* ```--hosts```		- Set path to hosts file *(/etc/hosts)*

**All default configuration are in ```/home/user/.server-manager``` file and you can change it.**
