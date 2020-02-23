#!../../bin/linux-x86_64/supercycleEngine

#- You may have to change supercycleEngine to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

# Init environment
iocshLoad("iocsh/TD-M.iocsh")

epicsEnvUnset("PEVG01")
epicsEnvSet("PEVG01", "MTCA5U-EVG:")

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances

dbLoadRecords("db/devg.db",     "P=$(PEVG01)")
dbLoadRecords("db/engine.db",   "P=$(PSCE01),   PEVG=$(PEVG01), ENEVG=")

var iodebug 3

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=jerzy"
