# This file is part of the ServerManager package.
# (c) Ondřej Záruba <zarubaondra@gmail.com>
#
# For the full copyright and license information, please view
# the license.md file that was distributed with this source code.

CC = g++

CFLAGS = -std=c++11 -Wall -Wextra -pedantic

SOURCES := $(wildcard src/*.cpp)

build: $(SOURCES)
	$(CC) $(CFLAGS) -o build/server-manager $(SOURCES)