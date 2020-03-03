# .cmd
# ====
epicsEnvSet("TOP", "$(E3_CMD_TOP)/../..")
iocshLoad("$(TOP)/iocsh/env-init.iocsh")

#epicsEnvSet("LOCATION","MBL-070ROW:CNPW-U-017:AMC2")

epicsEnvSet("IOC", "MTCA5U")
epicsEnvSet("DEV", "EVG")

require mrfioc2, 2.2.0-rc7

iocshLoad("$(TOP)/iocsh/evm-mtca-init.iocsh", "IOC=$(IOC), DEV=$(DEV), PCIID=$(MTCA_5U_PCIID7)")

iocInit()

iocshLoad("$(TOP)/iocsh/evg-run.iocsh", "IOC=$(IOC), DEV=$(DEV), INTREF=''")

dbl > "${IOC}-${DEV}.pvlist"

#EOF
