#!/usr/bin/env bash
export QT5_PATH="${HOME}/Qt5.12.12/5.12.12/clang_64"
mkdir build/ || rm -Rfv build/ && mkdir build/
cd build/
cmake .. \
      -DQt5_PATH="${QT5_PATH}"
make
make install
${QT5_PATH}/bin/macdeployqt tuningTrainer.app
