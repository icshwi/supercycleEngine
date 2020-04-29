require "supercycleEngine" "develop"

epicsEnvSet "PSCE"      "TD-M:TS-SCE-01"
epicsEnvSet "PEVG"      "TD-M:TS-EVG-01"

epicsEnvUnset "PEVG"
epicsEnvSet "PEVG"      "MTCA5U-EVG"

epicsEnvSet "DBUFL"     "../reftabs/init/databuffer-ess.json"
epicsEnvSet "MEVTSL"    "../reftabs/init/mevts-ess.json"
epicsEnvSet "SCTROOT"   "../reftabs/supercycles/"

# Load record instances
dbLoadRecords "db/devg.db" "P=$(PEVG)"
iocshLoad     "$(supercycleEngine_DIR)/sce.iocsh"   "P=$(PSCE), PG=$(PEVG)"

iocInit
