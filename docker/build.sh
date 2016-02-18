#!/bin/bash

unset QMAKESPEC

qmake qtqmlandroid.pro
make -j2

pushd examples/android/catalog/
qmake catalog.pro
make -j2
make install INSTALL_ROOT=QtQml-Catalog
androiddeployqt --input android-libcatalog.so-deployment-settings.json --output QtQml-Catalog --verbose --gradle QtQml-Catalog
popd

cp examples/android/catalog/QtQml-Catalog/build/outputs/apk/QtQml-Catalog-debug.apk .
