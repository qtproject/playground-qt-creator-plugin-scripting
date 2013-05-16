TEMPLATE = lib
QT += script

DEFINES += SCRIPTING_LIBRARY

# Scripting files

SOURCES += scriptingplugin.cpp \
    scriptrunner.cpp \
    scriptmanager.cpp \
    runscriptlocatorfilter.cpp \
    objects/console.cpp \
    objects/editors.cpp \
    objects/editor.cpp \
    objects/basetexteditor.cpp \
    objects/cppeditor.cpp \
    utils/signalwaiter.cpp \
    objects/texteditor.cpp \
    wrappers/scriptwrappers.cpp \
    wrappers/enumwappers.cpp \
    utils/dialogs.cpp \
    objects/cppfunction.cpp \
    objects/cppargument.cpp \
    objects/mark.cpp \
    utils/position.cpp \
    utils/utils.cpp \
    objects/cppclass.cpp \
    wrappers/qfileinfoprototype.cpp

HEADERS += scriptingplugin.h \
    scripting_global.h \
    scriptingconstants.h \
    scriptrunner.h \
    scriptmanager.h \
    runscriptlocatorfilter.h \
    objects/console.h \
    objects/editors.h \
    objects/editor.h \
    objects/basetexteditor.h \
    objects/cppeditor.h \
    utils/signalwaiter.h \
    objects/texteditor.h \
    wrappers/scriptwrappers.h \
    objects/enums.h \
    wrappers/enumwappers.h \
    utils/dialogs.h \
    objects/cppfunction.h \
    objects/cppargument.h \
    objects/mark.h \
    utils/position.h \
    utils/utils.h \
    objects/cppclass.h \
    wrappers/qfileinfoprototype.h

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):error("Please set the environment variable QTC_SOURCE")

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):error("Please set the environment variable QTC_BUILD")

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\Nokia\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/Nokia/qtcreator" or "~/.local/share/Nokia/qtcreator" on Linux
##    "~/Library/Application Support/Nokia/Qt Creator" on Mac
USE_USER_DESTDIR = yes

PROVIDER = KDAB

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

OTHER_FILES += \
    examples/* \
    tests/mark/test.cpp \
    tests/mark/mark.qs \
    tests/runtests.qs \
    tests/positions/test.cpp \
    tests/positions/positions.qs \
    tests/test.js \
    tests/class/class.qs \
    tests/class/test.h \
    tests/qfileinfo/qfileinfo.qs \
    tests/qfileinfo/test.cpp




