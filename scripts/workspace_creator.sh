#!/usr/bin/env bash
GENERATOR="CodeLite - Ninja"
SRC_PATH=tuningTrainer
BLD_PATH=${SRC_PATH}/build.debug
[[ -x ${BLD_PATH} ]] && rm -Rf ${BLD_PATH}
mkdir -v ${BLD_PATH}
cmake -G "${GENERATOR}" \
      -S ${SRC_PATH} \
      -B ${BLD_PATH} \
      -DCMAKE_BUILD_TYPE=Debug
