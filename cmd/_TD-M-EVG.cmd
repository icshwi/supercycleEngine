# .cmd
# ====
epicsEnvSet("TOP", "$(E3_CMD_TOP)/..")

iocshLoad("$(TOP)/iocsh/mtcai.iocsh")
iocshLoad("$(TOP)/iocsh/tsi.iocsh")

epicsEnvSet("IOC", "MTCA5U")
epicsEnvSet("DEV", "EVG")
epicsEnvSet("PEVG", "$(IOC)-$(DEV):")

require mrfioc2, 2.2.0-rc7

iocshLoad("$(TOP)/iocsh/evmi.iocsh", "IOC=$(IOC), DEV=$(DEV), PCIID=$(MTCA_5U_PCIID7)")

iocInit()

iocshLoad("$(TOP)/iocsh/evgr.iocsh", "P=$(PEVG), INTREF=")

dbl > "${PEVG}.pvlist"

#EOF
