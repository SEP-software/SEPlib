import pySEPUtil
import Hypercube

"""Class to perform Filtering"""


class FilterFloat1D:

    def __init__(self, filt, **kw):
        """Create filter object

        filt - Filter


        """

        self.cppMode = pySEPUtil.floatfilter1D(iaxes, filt)

    def loopData(self, ind, outd):
        """Loop through data applying NMO

            ind  - Input dataset
            outd - Ouput dataset"""
        self.cppMode.loopData(ind.cppMode, outd.cppMode)

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return self.cppMode
