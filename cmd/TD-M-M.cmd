#!../bin/linux-x86_64/supercycleEngine

< envPaths
cd "${TOP}"

# Init environment
iocshLoad("iocsh/mtcai.iocsh")
iocshLoad("iocsh/tsi.iocsh")

epicsEnvSet("PSCE",     "TD-M:TS-SCE-01:")
epicsEnvSet("PEVG",     "TD-M:TS-EVG-01:")

epicsEnvUnset("PEVG")
epicsEnvSet("PEVG", "MTCA5U-EVG:")

## Register all support components
dbLoadDatabase "dbd/supercycleEngine.dbd"
supercycleEngine_registerRecordDeviceDriver pdbbase

## Load record instances

#dbLoadRecords("db/devg.db",         "P=$(PEVG)")
dbLoadRecords("db/engine.db",       "P=$(PSCE), PEVG=$(PEVG), EVT_CEND=$(EVT_CEND)")
dbLoadRecords("db/engineCtrl.db",   "P=$(PSCE)")

#mapStrOut "databufferLink" "../reftabs/init/databuffer-ess.json"
#mapStrOut("databufferLink", "../reftabs/init/mevts-ess.json")
#mapStrOut("databufferLink", "../reftabs/init/d-ess.json")

var iodebug 4
#var PscUs 888

iocInit

#iocshLoad("iocsh/evgr.iocsh", "P=$(PEVG), INTREF=")
