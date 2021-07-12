#! /bin/zsh

M_PATH=`pwd`
KLST_ARDUINO_SRC_PATH=../klangstrom/klangstrom/platforms/klangstrom-arduino/libraries/Klangstrom/src/
M_SRC_PATH=src
M_TEMPLATE_PATH=template

echo 
echo "###"
echo "### +++ Klang Teensy Audio Library +++ "
echo "###"
echo "### cleaning up source folder"

if [ -d "$M_SRC_PATH" ]; then
	rm -rf "$M_SRC_PATH"
fi
mkdir -p "$M_SRC_PATH"

echo "### copying source files from klangstrom project"

cp -r "$KLST_ARDUINO_SRC_PATH" "$M_SRC_PATH"

echo "### cleaning up source files"

rm "$M_SRC_PATH"/Klangstrom.h

echo "### copying template files"

cp -r "$M_TEMPLATE_PATH"/ "$M_SRC_PATH"

echo "###"
echo
