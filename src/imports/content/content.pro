TARGET = qtqmlandroidcontentplugin
TARGETPATH = android/content
IMPORT_VERSION = 0.21

QT += qmlandroid-private

SOURCES += \
    $$PWD/qtqmlandroidcontentplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
