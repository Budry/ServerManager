/*
 * This file is part ServerManager of package
 *
 * (c) Ondřej Záruba <zarubaondra@gmail.com>
 *
 * For the full copyright and license information, please view the license.md
 * file that was distributed with this source code.
 */

#ifndef SERVERMANAGER_MAIN
#define SERVERMANAGER_MAIN

#include <string>
#include <vector>

using namespace std;

const char* HELP = "ServerManager v1.0.0\n" \
					"======================\n" \
					"Usages:\n" \
					"\tserver-manager list\t\t\t\t- Displays list of create virtual hosts\n" \
					"\tserver-manager create <host-name> [options]\t- Create a new virtual host with name <host-name>\n" \
					"\tserver-manager remove <host-name> [options]\t- Remove virtual hosts <host-name> with all files\n" \
					"Options:\n" \
					"\t--root\t- Set application root dir (for example www/)\n" \
					"\t--ext\t- Set virtual host extension (example: project.lc or projec.dev)\n" \
					"\t--htdoc\t- Set htdocs directoryr\n" \
					"\t--nginx\t- Set path to nginx configuration (sites-enabled)\n" \
					"\t--hosts\t- Set path to hosts file (example: /etc/hosts)\n";

string formateError(string message);
string formateThrow(string message);
string formateSuccess(string message);
string formateProcess(string message);

#endif
