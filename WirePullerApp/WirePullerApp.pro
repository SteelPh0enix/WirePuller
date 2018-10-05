TEMPLATE = subdirs

include(configuration.pri)

SUBDIRS += \
    src/main


ENABLE_TEST {
    SUBDIRS += src/test
}
