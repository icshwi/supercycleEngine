# .cmd
# ====
epicsEnvSet("TOP", "$(E3_CMD_TOP)/..")

iocshLoad("$(TOP)/iocsh/mtcai.iocsh")
iocshLoad("$(TOP)/iocsh/tsi.iocsh")

epicsEnvSet("PEVG", "MTCA5U-EVG:")

require mrfioc2, 2.2.0-rc7

iocshLoad("$(TOP)/iocsh/evmi.iocsh", "P=MTCA5U, DEV=EVG, PCIID=$(MTCA_5U_PCIID7)")

iocInit()

iocshLoad("$(TOP)/iocsh/evgr.iocsh", "P=$(PEVG), INTREF=")

dbl > "${PEVG}.pvlist"

#EOF
