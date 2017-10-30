import os
import sys

flags = sys.getdlopenflags()
dll_load_flags = os.RTLD_NOW | os.RTLD_GLOBAL
sys.setdlopenflags(dll_load_flags)
import mpiProxy
sys.setdlopenflags(flags)

class TestClass(object):

  def __init__(self):
      self.proxy = mpiProxy.MpiProxy()

  def doWork(self):
    self.proxy.ImportantFunction()

with mpiProxy.MpiProxy() as proxy:
  proxy.ImportantFunction()