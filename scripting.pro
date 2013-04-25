TARGET = Scripting
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
    scriptwrappers.cpp \
    enumwappers.cpp \
    utils/dialogs.cpp \
    objects/cppfunction.cpp \
    objects/cppargument.cpp

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
    scriptwrappers.h \
    objects/enums.h \
    enumwappers.h \
    utils/dialogs.h \
    objects/cppfunction.h \
    objects/cppargument.h

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=/d/dev/qt-creator/src

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=/d/dev/qt-creator/build-Debug

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\Nokia\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/Nokia/qtcreator" or "~/.local/share/Nokia/qtcreator" on Linux
##    "~/Library/Application Support/Nokia/Qt Creator" on Mac
USE_USER_DESTDIR = yes

PROVIDER = KDAB

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)
include($$QTCREATOR_SOURCES/src/shared/scriptwrapper/scriptwrapper.pri)
include($$QTCREATOR_SOURCES/src/plugins/coreplugin/coreplugin.pri)
include($$QTCREATOR_SOURCES/src/plugins/locator/locator.pri)
include($$QTCREATOR_SOURCES/src/plugins/projectexplorer/projectexplorer.pri)
include($$QTCREATOR_SOURCES/src/plugins/texteditor/texteditor.pri)
include($$QTCREATOR_SOURCES/src/plugins/cppeditor/cppeditor.pri)

LIBS += -L$$IDE_PLUGIN_PATH/Nokia




