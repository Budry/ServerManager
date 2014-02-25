#!/bin/bash

CONFIG_PATH="${HOME}/.server-manager"
USER_BIN="/usr/local/bin/"
COMMAND_NAME="server-manager"

if [ -f ${CONFIG_PATH} ] 
then
	echo "File '~/.server-manager' already exist!"
	exit 1
else
	cp .server-manager_default ${CONFIG_PATH}
fi

if [ $1 ]
then
	COMMAND_NAME=$1
fi

COMMAND=${USER_BIN}${COMMAND_NAME}

make -B

if [ -f ${COMMAND} ]
then
	echo "Command ${COMMAND} already exist!"
	exit 1
else
	cp build/server-manager ${COMMAND}
fi

rm -rf build/server-manager
