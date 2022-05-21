#!/usr/bin/env bash
export QT5_PATH="${HOME}/Qt5.12.12/5.12.12/clang_64"
mkdir build/ || rm -Rf build/
cd build/
cmake ..  -DQt5_PATH="${QT5_PATH}"
make
make install DESTDIR=tuningTrainer-bin
mkdir tuningTrainer.app || rm -Rf tuningTrainer.app
mkdir -p tuningTrainer.app/Contents/MacOS/
cp tuningTrainer-bin/usr/local/bin/tuningTrainer tuningTrainer.app/Contents/MacOS/
${QT5_PATH}/bin/macdeployqt tuningTrainer.app