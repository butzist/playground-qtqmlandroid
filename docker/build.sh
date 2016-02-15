#!/bin/bash

rm -fr tools

qmake qtqmlandroid.pro
make -j2
sudo make install

pushd examples/android/catalog/
qmake catalog.pro
make -j2
make install INSTALL_ROOT=QtQml-Catalog
androiddeployqt --input android-libcatalog.so-deployment-settings.json --output QtQml-Catalog --verbose --gradle QtQml-Catalog
popd

cp examples/android/catalog/PACKAGE/build/outputs/apk/QtQml-Catalog-debug.apk .
