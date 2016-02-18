CONFIG -= qt android_install

OTHER_FILES += \
    $$PWD/AndroidManifest.xml \
    $$PWD/build.gradle \
    $$PWD/gradle/wrapper/gradle-wrapper.properties

templates.files = $$PWD/AndroidManifest.xml $$PWD/build.gradle $$PWD/gradle
templates.path = $$[QT_INSTALL_PREFIX]/src/qmlandroid/templates
INSTALLS += templates
