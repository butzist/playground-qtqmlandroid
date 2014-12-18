TEMPLATE = app
TARGET = qtandroid
QT += androidextras qml core-private # qjnihelpers
CONFIG += c++11

SOURCES += \
    main.cpp

RESOURCES += \
    qtandroid.qrc

include(src/android/android.pri)

OTHER_FILES += \
    qml/main.qml \
    qml/AwesomeView.qml \
    qml/ButtonView.qml \
    qml/InputView.qml \
    qml/ModelView.qml \
    qml/PickerView.qml \
    qml/ProgressView.qml

DISTFILES += \
    src/java/build.gradle \
    src/java/gradle/wrapper/gradle-wrapper.properties
