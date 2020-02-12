#!../../bin/linux-x86_64/supercycleEngine

#- You may have to change supercycleEngine to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

# Naming: AS:DS-ID
epicsEnvSet("AS",        "TD-M")                # Area Structure
 # SCE IOC
epicsEnvSet("DSSCE",     "TS-SCE")              # Device Structure SCE
epicsEnvSet("PSCE01",    "$(AS):$(DSSCE)-01:")  # Prefix of the SCE 01

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=jerzy")
dbLoadRecords("db/engineCycle.db", "P=$(PSCE01)")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=jerzy"
