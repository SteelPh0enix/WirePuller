TEMPLATE = subdirs

include(configuration.pri)

SUBDIRS += \
    src/main \
    src/test

message($$ROOT_DIR)
