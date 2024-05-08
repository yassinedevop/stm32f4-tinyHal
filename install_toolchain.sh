#!/bin/bash

# variables
toolchain="gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2"
path="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/"

# get the latest version of the ARM toolchain
wget --progress=bar -c $path$toolchain

# extract the tarball 
echo "Extracting the tarball..."
# extract the tarball
tar -xvf $toolchain > /dev/null

#  move the toolchain to /usr/share
echo "moving toolchain to /usr/share"
sudo mv gcc-arm-none-eabi-10.3-2021.10 /usr/share/
echo "Toolchain moved to /usr/share"

# symlinking
echo "Creating symlinks..."
sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/*  /usr/bin
echo "Done!"


# clean up
echo "Would you like to clean up the files?"
read -p "y/n: " clean
if [ "$clean" == "y" ]; then
    rm -rf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 gcc-arm-none-eabi-10.3-2021.10
    echo "Files cleaned up!"
fi

# check if the toolchain is installed
arm-none-eabi-gcc --version

