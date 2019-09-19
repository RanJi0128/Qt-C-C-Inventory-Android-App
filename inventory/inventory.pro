

QT += sql core widgets androidextras

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += consumptask.cpp \
        advancedoption.cpp \
        consumptaskcreate.cpp \
        consumptaskmenu.cpp \
        customkeyboard.cpp \
        database.cpp \
        downloadstate.cpp \
        generaloption.cpp \
        inventorytask.cpp \
        inventorytaskcreate.cpp \
        inventorytaskmenu.cpp \
        languageoption.cpp \
        main.cpp \
        mainwindow.cpp \
        options.cpp \
        shippingtask.cpp \
        shippingtaskcreate.cpp \
        shippingtaskmenu.cpp \
        stateoption.cpp \
        usermanger.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += consumptask.h \
    advancedoption.h \
    consumptaskcreate.h \
    consumptaskmenu.h \
    customkeyboard.h \
    database.h \
    downloadstate.h \
    generaloption.h \
    include.h \
    inventorytask.h \
    inventorytaskcreate.h \
    inventorytaskmenu.h \
    languageoption.h \
    mainwindow.h \
    options.h \
    shippingtask.h \
    shippingtaskcreate.h \
    shippingtaskmenu.h \
    stateoption.h \
    usermanger.h

DISTFILES +=android/AndroidManifest.xml \
    android/assets/drop-arrow.png \
    android/assets/hide.png \
    android/assets/style.qss \
    android/assets/times.png \
    android/assets/unhide.png \
    android/src/com/jni/systeminfo/AppActivity.java \
    android/src/com/jni/systeminfo/BatteryLevelListener.java \
    android/src/com/jni/systeminfo/DeviceInformation.java \
    android/libs/jcifs-1.3.19.jar \
    android/src/com/jni/systeminfo/NetworkManager.java \
    android/assets/db/inventory.db \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/com/jni/systeminfo/OpenOtherApp.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
