#!/bin/bash

CONFIG_PATH="${HOME}/.server-manager"
USER_BIN="/usr/local/bin/"
COMMAND_NAME="server-manager"

if [ -f ${CONFIG_PATH} ] 
then
	echo "ServerManager need ~/.server-manager file for store default configuration. Do we can overwrite it? (Y/n):"
	read rewrite
	if [ "$rewrite" = "y" ]
	then
		cp .server-manager_default ${CONFIG_PATH}
	fi
else
	cp .server-manager_default ${CONFIG_PATH}
fi

chmod -R 0777 ${CONFIG_PATH}

if [ $1 ]
then
	COMMAND_NAME=$1
fi

mkdir -p build/
COMMAND=${USER_BIN}${COMMAND_NAME}

make -B

if [ -f ${COMMAND} ]
then
	echo "Binnary file ${COMMAND} already exist. Do we can overwrite it? (Y/n):"
	read rewrite
	if [ "$rewrite" = "y" ]
	then
		cp build/server-manager ${COMMAND} -f
	else
		rm ${CONFIG_PATH} -rf
		echo "Install terminated"
		exit 1
	fi
else
	cp build/server-manager ${COMMAND}
fi

rm -rf build/server-manager
echo "ServerManager has been installed successfully"

exit 0
