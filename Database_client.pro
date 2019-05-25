TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += \
    -lsqlite3\
    -lpthread\
    -lboost_system

SOURCES += \
        database_client.cpp \
        main.cpp \
        query.cpp

HEADERS += \
    database_client.h \
    query.h
