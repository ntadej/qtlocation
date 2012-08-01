TEMPLATE = app
!no_system_tests:CONFIG += testcase
TARGET=tst_qgeosatelliteinfosource

SOURCES += tst_qgeosatelliteinfosource.cpp \
            testqgeosatelliteinfosource.cpp \
            ../utils/qlocationtestutils.cpp

HEADERS += testqgeosatelliteinfosource_p.h \
            ../utils/qlocationtestutils_p.h

QT += location testlib

# Define whether a satellite source is available.  This must match the logic in
# src/location/location.pro or the test will fail on some platforms.
maemo6|meego:DEFINES += SATELLITE_SOURCE_AVAILABLE
config_locationd:!simulator:DEFINES += SATELLITE_SOURCE_AVAILABLE
simulator:DEFINES += SATELLITE_SOURCE_AVAILABLE
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
