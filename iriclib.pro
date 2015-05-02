######################################################################
# Automatically generated by qmake (2.01a) ? 10 29 11:45:42 2008
######################################################################

TEMPLATE = lib
TARGET = iriclib
DEPENDPATH += .
win32 {
	INCLUDEPATH += "E:/iricdev_2013/lib/install/cgnslib-3.2.1/debug/include"
}
unix {
	INCLUDEPATH += /usr/include
}
CONFIG += dll

DEFINES += IRICLIBDLL_LIBRARY

# Input
HEADERS += iriclib.h \
	iriclib_bstream.h \
	iriclib_polygon.h \
	iriclib_riversurvey.h \
	iriclib_pointmap.h \
	iriclib_f.h

SOURCES += iriclib.c \
	iriclib_bstream.cpp \
	iriclib_geo.cpp \
	iriclib_polygon.cpp \
	iriclib_riversurvey.cpp \
	iriclib_pointmap.cpp

QT =

win32 {
	CONFIG(debug, debug|release) { 
		# cgnslib
		LIBS += -L"E:/iricdev_2013/lib/install/cgnslib-3.2.1/debug/lib"
	} else { 
		# cgnslib
		LIBS += -L"E:/iricdev_2013/lib/install/cgnslib-3.2.1/release/lib"
	}
	LIBS += -lcgnsdll
}
unix {
	LIBS += -lcgns
	LIBS += -lhdf5
}

#installation settings

unix {
  inst_headers.path = /usr/local/iRIC/include
  inst_headers.files = iriclib.h iriclib_global.h iriclib_f.h
	INSTALLS += inst_headers

	target.path = /usr/local/iRIC/lib
	INSTALLS += target
}

