QT += quick-private network positioning-private location-private locationlabs-private qml-private core-private gui-private

TARGET = locationlabsplugin
TARGETPATH = Qt/labs/location
IMPORT_VERSION = 5.11

SOURCES += \
           locationlabs.cpp

#CONFIG += no_cxx_module
load(qml_plugin)

OTHER_FILES += \
    plugin.json \
    qmldir
