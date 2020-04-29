require "mrfioc2"           "master"
require "supercycleEngine"  "master"

epicsEnvSet "PSCE"          "TD-M:TS-SCE-01"
epicsEnvSet "PEVG"          "TD-M:TS-EVG-01"

epicsEnvSet "DBUFL"         "../reftabs/init/databuffer-ess.json"
epicsEnvSet "MEVTSL"        "../reftabs/init/mevts-ess.json"
epicsEnvSet "SCTROOT"       "../reftabs/supercycles/"

# Load environment
iocshLoad "$(mrfioc2_DIR)/mtca.iocsh"
iocshLoad "$(mrfioc2_DIR)/ts.iocsh"
# Load record instances
iocshLoad "$(mrfioc2_DIR)/evm.iocsh"                "P=$(PEVG), OBJ=EVG,   PCIID=$(MTCA_5U_PCIID7), U=:EVRU-, D=:EVRD-"
iocshLoad "$(supercycleEngine_DIR)/sce.iocsh"       "P=$(PSCE), PG=$(PEVG)"

iocInit

iocshLoad "$(mrfioc2_DIR)/evgr.iocsh"               "P=$(PEVG), INTRF=, INTPPS="
iocshLoad "$(mrfioc2_DIR)/evgasynr.iocsh"           "P=$(PEVG), U=:EVRU-"
iocshLoad "$(supercycleEngine_DIR)/evgseqr.iocsh"   "P=$(PEVG)"

dbl > "TD-M-M.pvlist"
