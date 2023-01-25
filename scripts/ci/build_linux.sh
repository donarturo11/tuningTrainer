#!/usr/bin/env bash

export SOURCE_DIR=${HOME}/git/tuningTrainer
export BUILD_DIR=${HOME}/src/tuningTrainer-build
export CMAKEARGS=""

CMAKEARGS+=" -DCMAKE_INSTALL_PREFIX=tuningTrainer-linux"
CMAKEARGS+=" -DCMAKE_BUILD_TYPE=Debug"
if [[ -x $BUILD_DIR ]]; then
	rm -Rv $BUILD_DIR
fi

cmake -S $SOURCE_DIR -B $BUILD_DIR $CMAKEARGS
cd $BUILD_DIR
make
make install
