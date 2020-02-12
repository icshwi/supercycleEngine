TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================
USR_CXXFLAGS += -std=c++11 -g -Wall -Wextra

# ============================
# Build an IOC support library

#LIBRARY_IOC += aiSecond

#DBD += aiSecond.dbd
#aiSecond_SRCS += devAiSecond.c
#aiSecond_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = supercycleEngine
# supercycleEngine.dbd will be created and installed
DBD += supercycleEngine.dbd

# supercycleEngine.dbd will be made up from these files:
supercycleEngine_DBD += base.dbd
supercycleEngine_DBD += engine.dbd

# Include dbd files from all support applications:
#supercycleEngine_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#supercycleEngine_LIBS += xxx

# supercycleEngine_registerRecordDeviceDriver.cpp derives from supercycleEngine.dbd
supercycleEngine_SRCS += supercycleEngine_registerRecordDeviceDriver.cpp
 # SRC libraries
supercycleEngine_SRCS += cmnbase.cpp
supercycleEngine_SRCS += dbuf.cpp
supercycleEngine_SRCS += engine.cpp
supercycleEngine_SRCS += json.cpp
supercycleEngine_SRCS += csv.cpp
supercycleEngine_SRCS += ioblock.cpp
#supercycleEngine_SRCS += sequence.cpp
 # Device Support
supercycleEngine_SRCS += devEngineCycle.cpp

# Build the main IOC entry point on workstation OSs.
supercycleEngine_SRCS_DEFAULT += supercycleEngineMain.cpp
supercycleEngine_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#supercycleEngine_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
supercycleEngine_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================
USR_SYS_LIBS += jsoncpp

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

