import pySEPUtil

"""Class to do piping incore"""


class PipeReg:

    def __init__(self, ops, inF, outF. **kw):
        """Create piping operator

                ops - A list of the operator to pipe
                inF - Input file
                outF -Output File

           Optional:
                memory - Memory to use in GBs


        """
        mem = 20
        if "memory" in kw:
            mem = kw["memory"]

        mem = mem * 1024 * 1024 * 1024
        opC = []
        for o in ops:
            opC.append(o.cppMode)

        self.cppMode = pySEPUtil.blockIORegPipe(inF.cppMode, outF.cppMode, opC)
        self.inF = inF
        self.outF = outF
        self.ops = ops

    def loopData(self):
        """Loop through data """
        self.cppMode.loopData(self.inF.cppMode, self.outF.cppMode)

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return self.cppMode
