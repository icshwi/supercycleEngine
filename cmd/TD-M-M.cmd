#!../bin/linux-x86_64/supercycleEngine

< envPaths
cd "${TOP}"

# Maintenance
epicsEnvSet("LOCATION", "MBL-070ROW:CNPW-U-017")
epicsEnvSet("FBS",      "=ESS.INFR.K01.K01")
epicsEnvSet("PSCE",     "TD-M:TS-SCE-01:")
epicsEnvSet("PEVG",     "TD-M:TS-EVG-01:")

epicsEnvUnset("PEVG")
epicsEnvSet("PEVG", "MTCA5U-EVG:")

# Init environment
iocshLoad("iocsh/MTCA.iocsh")
iocshLoad("iocsh/TS.iocsh")

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances

#dbLoadRecords("db/devg.db",         "P=$(PEVG)")
dbLoadRecords("db/engine.db",       "P=$(PSCE),   PEVG=$(PEVG)")
dbLoadRecords("db/engineCtrl.db",   "P=$(PSCE)")

#mapStrOut "databufferLink" "../reftabs/init/databuffer-ess.json"
#mapStrOut("databufferLink", "../reftabs/init/mevts-ess.json")
#mapStrOut("databufferLink", "../reftabs/init/d-ess.json")

var iodebug 4
#var PscUs 888

iocInit

iocshLoad("iocsh/evg.iocsh", "P=$(PEVG), INTREF=")
