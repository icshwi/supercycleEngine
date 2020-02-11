#!../../bin/linux-x86_64/supercycleEngine

#- You may have to change supercycleEngine to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=jerzy")
dbLoadRecords("db/testProc.db")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=jerzy"
