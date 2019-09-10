import pySEPUtil
import Hypercube


class vel3d:

    def __init__(self):
        """Vel3d """
        self.x = 1


class vel3dFromFile(vel3d):

    def __init__(self, velFile):
        """Create a vel3DFromFile object"""
        self.cppMode = pySEPUtil.vel3DFromFile(velFile.cppMode)

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return self.cppMode

    def readVelocity(self, hyper, mem):
        """Read velocity spanning hypercube update amount of memory used

            hyper - Hypercube describing domain to read in
            mem   - Memory used to this point

            @return new memory used"""
        return self.cppMode.readVelocity(hyper.getCpp(), mem)
