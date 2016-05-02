#!/bin/bash

CONFIG_PATH="${HOME}/.server-manager/"
USER_BIN="/usr/local/bin/"
COMMAND_NAME="server-manager"

if [ -d ${CONFIG_PATH} ]
then
	echo "ServerManager need ~/.server-manager/ directory for store default configuration. Do we can overwrite it? (Y/n):"
	read rewrite
	if [ "$rewrite" = "y" ] || [ "$rewrite" = "Y" ]
	then
		rm ${CONFIG_PATH} -rf
		cp .server-manager/ ${CONFIG_PATH} -r
		sed -i "s/<username>/${SUDO_USER}/g" ${CONFIG_PATH}/.server-manager
	fi
else
	cp .server-manager/ ${CONFIG_PATH} -r
	sed -i "s/<username>/${SUDO_USER}/g" ${CONFIG_PATH}/.server-manager
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
	if [ "$rewrite" = "y" ] || [ "$rewrite" = "Y" ]
	then
		rm ${COMMAND} -rf
		cp build/server-manager ${COMMAND}
	else
		echo "Install terminated"
		exit 1
	fi
else
	cp build/server-manager ${COMMAND}
fi

rm -rf build/server-manager
echo "ServerManager has been installed successfully"

exit 0
