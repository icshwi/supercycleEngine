#!../../bin/linux-x86_64/supercycleEngine

#- You may have to change supercycleEngine to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

# Naming: AS:DS-ID
epicsEnvSet("AS",        "TD-M")
epicsEnvSet("DSSCE",     "TS-SCE")
epicsEnvSet("PSCE01",    "$(AS):$(DSSCE)-01:")

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=jerzy")
dbLoadRecords("db/engine.db", "P=$(PSCE01)")

var iodebug 3

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=jerzy"
