import os
import sys

flags = sys.getdlopenflags()
dll_load_flags = os.RTLD_NOW | os.RTLD_GLOBAL
sys.setdlopenflags(dll_load_flags)
import mpiProxy
sys.setdlopenflags(flags)

proxy = mpiProxy.MpiProxy()
proxy.ImportantFunction()