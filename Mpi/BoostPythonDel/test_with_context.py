import os
import sys

flags = sys.getdlopenflags()
dll_load_flags = os.RTLD_NOW | os.RTLD_GLOBAL
sys.setdlopenflags(dll_load_flags)
import mpiProxy
sys.setdlopenflags(flags)

with mpiProxy.MpiProxy() as proxy:
  proxy.ImportantFunction()