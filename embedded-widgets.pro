include($$(cetoni_repository)/build/qt/qtprojectsettings/common.pri)
src_dir = src
skin_dir = skins

QT += core \
    gui \
    svg

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TEMPLATE = lib
TARGET = $$uslQtLibraryTarget(embedded-widgets, d)
INCLUDEPATH += .

win32 {
isEmpty( DLLDESTDIR ) {
    DLLDESTDIR = $$usrlibs
    CONFIG += dll
}
} # win32
unix:DESTDIR = $$usrlibs

include($$src_dir/scrolldial/scrolldial.pri)
include($$src_dir/common/common.pri)
include($$src_dir/5waybutton/5waybutton.pri)
include($$src_dir/6waybutton/6waybutton.pri)
include($$src_dir/svgspinbutton/svgspinbutton.pri)
include($$src_dir/multislider/multislider.pri)
include($$src_dir/scrollwheel/scrollwheel.pri)
include($$src_dir/svgbutton/svgbutton.pri)
include($$src_dir/svgdialgauge/svgdialgauge.pri)
include($$src_dir/svgslideswitch/svgslideswitch.pri)
include($$src_dir/svgtoggleswitch/svgtoggleswitch.pri)
include($$src_dir/basicgraph/basicgraph.pri)


RESOURCES += $$skin_dir/thermometer_svgdialgauge.qrc \
    $$skin_dir/tachometer_svgdialgauge.qrc \
    $$skin_dir/amperemeter_svgdialgauge.qrc \
    $$skin_dir/beryl_5waybutton.qrc \
    $$skin_dir/beryl_multislider.qrc \
    $$skin_dir/beryl_svgslideswitch.qrc \
    $$skin_dir/beryl_svgbutton.qrc \
    $$skin_dir/beryl_svgtoggleswitch.qrc \
    $$skin_dir/berylsquare_svgtoggleswitch.qrc \
    $$skin_dir/berylsquare_svgbutton.qrc \
    $$skin_dir/beryl_scrollwheel.qrc \
    $$skin_dir/beryl_scrolldial.qrc \
    $$skin_dir/metallicbrush_svgbutton.qrc \
    $$skin_dir/metallicbrush_svgslideswitch.qrc \
    $$skin_dir/dark_5waybutton.qrc \
    $$skin_dir/black_5waybutton.qrc \
    $$skin_dir/black_svgspinbutton.qrc \
    $$skin_dir/black_6waybutton.qrc \
    $$skin_dir/black2_6waybutton.qrc
