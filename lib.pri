#
# HALCON
#
INCLUDEPATH   += "$$(HALCONROOT)/include"
INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"
LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                   "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"

#
# OPENCV
#
INCLUDEPATH += C:\opencv-3.4.0/build/install/include
Debug: {
LIBS += -lC:\opencv-3.4.0/build/install/x64/vc15/lib/opencv_world340d
}
Release: {
LIBS += -lC:\opencv-3.4.0/build/install/x64/vc15/lib/opencv_world340
}

#
# OPENCV
#
# read librarias from the lib folder for linux or windows
LIBS += -L$$PWD/lib/ -lsnap7

DEPENDPATH += $$PWD/.
