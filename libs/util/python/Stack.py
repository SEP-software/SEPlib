import pySEPUtil
import Hypercube

"""Class to perform Stacking"""


class StackFloat:

    def __init__(self, iaxes, **kw):
        """Create Stack object

        iaxes - Axes to stack over


        adj [true] - Whether or not to run adjoint
        """

        adj = True
        if "adj" in kw:
            adj = kw["adj"]

        self.cppMode = pySEPUtil.floatStackSpreadReg(iaxes, adj)

    def loopData(self, ind, outd):
        """Loop through data applying NMO

            ind  - Input dataset
            outd - Ouput dataset"""
        self.cppMode.loopData(ind.cppMode, outd.cppMode)

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return self.cppMode
