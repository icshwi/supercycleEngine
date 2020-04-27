# .cmd
require "iocstats"
require "mrfioc2"
require "supercycleEngine"

epicsEnvSet "DBUFL"         "$(reftabs_DIR)/init/databuffer-ess.json"
epicsEnvSet "MEVTSL"        "$(reftabs_DIR)/init/mevts-ess.json"
epicsEnvSet "SCTROOT"       "$(reftabs_DIR)/supercycles/"

# Load environment
iocshLoad "$(mrfioc2_DIR)/mtca.iocsh"
iocshLoad "$(mrfioc2_DIR)/ts.iocsh"
# Load record instances
iocshLoad "$(mrfioc2_DIR)/evm.iocsh"                "P=$(PEVG), OBJ=EVG,   PCIID=$(PCI_SLOT), U=:EVRU-, D=:EVRD-"
iocshLoad "$(supercycleEngine_DIR)/sce.iocsh"       "P=$(PSCE), PG=$(PEVG)"

iocInit

iocshLoad "$(mrfioc2_DIR)/evgr.iocsh"               "P=$(PEVG), INTRF=, INTPPS="
iocshLoad "$(mrfioc2_DIR)/evgasynr.iocsh"           "P=$(PEVG), U=:EVRU-"
iocshLoad "$(supercycleEngine_DIR)/evgseqr.iocsh"   "P=$(PEVG)"

# EOF
