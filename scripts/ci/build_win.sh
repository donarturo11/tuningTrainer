#!/usr/bin/env bash

SOURCE_DIR="/c/Users/art/Documents/GitHub/tuningTrainer/"
BUILD_DIR="/src/tuningTrainer-build"

CXX_FLAGS+="${CXX_FLAGS}"

#CXX_FLAGS+=" -Wl,-S -mwindows -mconsole"
CXX_FLAGS+=" -Wl,-S -mwindows"


mkdir ${BUILD_DIR} || rm -Rv ${BUILD_DIR}

echo "CXX_FLAGS=${CXX_FLAGS}"
cmake -S ${SOURCE_DIR} \
      -B ${BUILD_DIR} \
      -DCMAKE_BUILD_TYPE=Release \
      -G "Unix Makefiles" \
      -D BUILD_LIBRARY_TYPE:STRING="Static" \
      -DMINGW_ROOT="/c/msys64" \
      -DCMAKE_INSTALL_PREFIX=${BUILD_DIR}/tuningTrainer-win \
      -DCMAKE_CXX_FLAGS="${CXX_FLAGS}"

cd ${BUILD_DIR}
make #VERBOSE=1
make install

#windeployqt ${BUILD_DIR}/tuningTrainer-win/bin
