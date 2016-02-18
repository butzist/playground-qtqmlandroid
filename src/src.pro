TEMPLATE = subdirs
SUBDIRS += \
    imports \
    qmlandroid \
    templates \
    java

imports.depends = qmlandroid
