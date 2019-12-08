#!/bin/sh
set -e

# Set the versions we will be using.
binutils_version="2.33.1"
gcc_version="9.2.0"

# This script expects the target triplet (e.g. i786-pc-elf) as command line argument.
target=i686-elf

# The tools will be installed in ~/cross/$target.
prefix=~/cross

# First check whether the toolchain was already built on a previous run of this script.
if [ ! -d $prefix/bin ]
then
	mkdir -p /tmp/toolchain
	cd /tmp/toolchain

	# Download gcc sources if they are not yet downloaded.
	if [ ! -f gcc-$gcc_version.tar.xz ]
	then
		wget -c -O gcc-$gcc_version.tar.xz ftp://ftp.gnu.org/gnu/gcc/gcc-$gcc_version/gcc-$gcc_version.tar.xz
		tar -xf gcc-$gcc_version.tar.xz
	fi

	# Download binutils sources if they are not yet downloaded.
	if [ ! -f binutils-$binutils_version.tar.xz ]
	then
		wget -c -O binutils-$binutils_version.tar.xz ftp://ftp.gnu.org/gnu/binutils/binutils-$binutils_version.tar.xz
		tar -xf binutils-$binutils_version.tar.xz
	fi

	# Create build paths.
	mkdir -p /tmp/toolchain/build-binutils
	mkdir -p /tmp/toolchain/build-gcc
	mkdir -p /tmp/toolchain/build-newlib

	# Build binutils.
	cd /tmp/toolchain/build-binutils
	sudo rm -rf *
	/tmp/toolchain/binutils-$binutils_version/configure --target=$target --prefix=$prefix --disable-nls --disable-werror 2>&1
	echo "Building bin utils... (may take a while)"
	make -s 2>&1
	make install 2>&1
	sudo rm -rf *

	# Build gcc and libgcc.
	cd /tmp/toolchain/build-gcc
	/tmp/toolchain/gcc-$gcc_version/configure --target=$target --prefix=$prefix --disable-nls --enable-languages=c --without-headers 2>&1
	echo "Building gcc... (may take a while)"
	make -s all-gcc 2>&1
	make -s all-target-libgcc 2>&1
	make install-gcc 2>&1
	make install-target-libgcc 2>&1

	rm -rf /tmp/toochain
fi