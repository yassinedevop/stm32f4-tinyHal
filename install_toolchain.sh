#!/bin/bash

# check if the toolchain is already installed
if [ -x "$(command -v arm-none-eabi-gcc)" ]; then
    echo "Toolchain is already installed."
    exit 0
fi

# variables
toolchain="gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2"
path="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/"

# get the latest version of the ARM toolchain
wget --progress=bar -c $path$toolchain

# extract the tarball 
echo "Extracting the tarball..."
# extract the tarball
tar -xvf $toolchain > /dev/null

# ask to move the toolchain to /opt/
echo "Do you want to move the toolchain to /opt/ ?"
read -p "y/n: " move
if [ "$move" == "y" ]; then
    sudo mv gcc-arm-none-eabi-10.3-2021.10 /opt/
    echo "Toolchain moved to /opt/"
fi
# ask to copy the toolchain to /usr/bin/
echo "Do you want to copy the toolchain to /usr/bin/ ?"
read -p "y/n: " copy
if [ "$copy" == "y" ]; then
    sudo cp gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-* /usr/bin/
    echo "Toolchain copied to /usr/bin/"
fi

# clean up
rm -rf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 gcc-arm-none-eabi-10.3-2021.10

# check if the toolchain is installed
arm-none-eabi-gcc --version

