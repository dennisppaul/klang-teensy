#! /bin/zsh

M_PATH=`pwd`
KLST_ARDUINO_SRC_PATH=../klangstrom/klangstrom/platforms/klangstrom-arduino/libraries/Klangstrom/src/
M_SRC_PATH=src
M_TEMPLATE_PATH=template

if [ -d "$M_SRC_PATH" ]; then
	rm -rf "$M_SRC_PATH"
fi
mkdir -p "$M_SRC_PATH"

cp -r "$KLST_ARDUINO_SRC_PATH" "$M_SRC_PATH"
cp -r "$M_TEMPLATE_PATH" "$M_SRC_PATH"
rm "$M_SRC_PATH"/Klangstrom.h
