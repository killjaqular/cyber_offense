import sys

class RunningEnvironment:
    def __init__(self):
        self.isInDebugger  = None
        self.isInVM        = None
        self.isCompromised = None

    def checkDebugger(self):
        gettrace = getattr(sys, 'gettrace', None)

        if gettrace is None:
            self.isInDebugger = False
        elif gettrace():
            self.isInDebugger = True
        else:
            self.isInDebugger = False

        self.isCompromised = self.isInDebugger

        return self.isInDebugger

    def getBasePrefixCompat():
        return getattr(sys, "base_prefix", None) or\
               getattr(sys, "real_prefix", None) or\
               sys.prefix

    def checkVM(self):
        self.isInVM = RunningEnvironment.getBasePrefixCompat() != sys.prefix
        self.isCompromised = self.isInVM

        return self.isInVM
