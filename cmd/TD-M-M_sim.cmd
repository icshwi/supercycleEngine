#!../bin/linux-x86_64/supercycleEngine

< envPaths
cd "${TOP}"

# Init environment
iocshLoad("iocsh/mtcai.iocsh")
iocshLoad("iocsh/tsi.iocsh")

# Maintenance
epicsEnvSet("LOCATION", "MBL-070ROW:CNPW-U-017")
epicsEnvSet("FBS",      "=ESS.INFR.K01.K01")

epicsEnvSet("PSCE",     "TD-M:TS-SCE-01:")
epicsEnvSet("PEVG",     "TD-M:TS-EVG-01:")

epicsEnvUnset("PEVG")
epicsEnvSet("PEVG",     "MTCA5U-EVG:")

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances

dbLoadRecords("db/devg.db",   "P=$(PEVG)")
iocshLoad("iocsh/scei.iocsh", "P=$(PSCE), PG=$(PEVG)")

iocInit
