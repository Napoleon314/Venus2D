#-------------------------------------------------
#
# Project created by QtCreator 2012-11-01T22:29:03
#
#-------------------------------------------------

QT       += core gui
QT       += qt3support
QT       += opengl

TARGET = Olympus
TEMPLATE = app


SOURCES += \
    ../../../Tools/Olympus/MainWindow.cpp \
    ../../../Tools/Olympus/Main.cpp \
    ../../../Tools/Olympus/RollupBar.cpp \
    ../../../Tools/Olympus/CenterView.cpp \
    ../../../Tools/Olympus/Console.cpp \
    ../../../Tools/Olympus/SceneEditor.cpp \
    ../../../Tools/Olympus/NewDialog.cpp \
    ../../../Tools/Olympus/MaterialEditor.cpp \
    ../../../Tools/Olympus/MaterialDoc.cpp \
    ../../../Tools/Olympus/PropertyList.cpp

HEADERS  += \
    ../../../Tools/Olympus/MainWindow.h \
    ../../../Tools/Olympus/RollupBar.h \
    ../../../Tools/Olympus/CenterView.h \
    ../../../Tools/Olympus/Console.h \
    ../../../Tools/Olympus/SceneEditor.h \
    ../../../Tools/Olympus/NewDialog.h \
    ../../../Tools/Olympus/MaterialEditor.h \
    ../../../Tools/Olympus/MaterialDoc.h \
    ../../../Tools/Olympus/PropertyList.h

RESOURCES += \
    ../../../Tools/Olympus/Olympus.qrc


win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../SDK/Windows/VC100/Win32/Debug/ -lVenusEditor
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../SDK/Windows/VC100/Win32/Release/ -lVenusEditor
else:macx: LIBS += -L$$PWD/../../../SDK/Macosx/Debug/ -lVenusEditor
else:unix:!macx:!symbian: LIBS += -L$$PWD/../../../SDK/Linux/i386/Debug/ -lVenusEditor
#else:unix:!macx:!symbian: LIBS += -L$$PWD/../../../SDK/Linux/amd64/Debug/ -lVenusEditor

INCLUDEPATH += $$PWD/../../../SDK/Include
DEPENDPATH += $$PWD/../../../SDK/Include

FORMS += \
    ../../../Tools/Olympus/NewDialog.ui
