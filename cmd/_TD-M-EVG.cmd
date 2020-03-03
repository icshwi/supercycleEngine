# .cmd
# ====
epicsEnvSet("TOP", "$(E3_CMD_TOP)/..")
iocshLoad("$(TOP)/iocsh/tsi.iocsh")

epicsEnvSet("AS", "MTCA5U")
epicsEnvSet("DS", "EVG")
epicsEnvSet("PEVG", "$(AS):$(DS)-01:")

require mrfioc2, 2.2.0-rc7

iocshLoad("$(TOP)/iocsh/evmi.iocsh", "AS=$(AS), DS=$(DS), PCIID=$(MTCA_5U_PCIID7)")

iocInit()

iocshLoad("$(TOP)/iocsh/evgr.iocsh", "P=$(PEVG), INTREF=")

dbl > "${PEVG}.pvlist"

#EOF
