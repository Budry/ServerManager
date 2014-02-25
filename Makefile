##
# This file is part of ServerManager the package.
#
# (c) Ondřej Záruba <zarubaondra@gmail.com>
#
# For the full copyright and license information, please view the license.md
# file that was distributed with this source code.
##

CC = g++
CFLAGS = -Wall -Wextra -pedantic
TEST_DIR = tests/
SOURCES = ./src/ServerManager/main.cpp \
		  ./src/ServerManager/ConfigParser.cpp \
		  ./src/ServerManager/ArgumentParser.cpp \
		  ./src/ServerManager/Manager.cpp \
		  ./src/ServerManager/Configurator.cpp

build: $(SOURCES)
	$(CC) $(CFLAGS) -o build/server-manager $(SOURCES)
