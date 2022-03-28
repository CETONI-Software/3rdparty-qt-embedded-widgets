INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += $$PWD/qtscrollwheel.h
SOURCES += $$PWD/qtscrollwheel.cpp

QT += svg

isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets
}
