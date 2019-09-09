import pySEPUtil
import Hypercube
import Vel3d

"""Class to perform NMO"""


class NMO:

    def __init__(self, vel, **kw):
        """Create NMO object

        vel - Vel3D object

        Regular cube:

        iOffsetXAxis - Axis index associated with  offset x axis on a regular cube
        iOffsetYAxis - Axis index associated with  offset y axis on a regular cube (optional)
        iCmpXAxis - Axis index associated with  CMP x axis on a regular cube
        iCmpYAxis - Axis index associated with  CMP y axis on a regular cube (optional)
        timeAxis - Time axis
        stretchMute - Whether or not to do stretch mute (optional). Defaults to yes
        smute - Stretch mute parameter (optional)
        doInverse - Whether or not do inverse stretch mute (defaults to fault)

        """

        if isinstance(vel) != Vel3d.vel3d:
            raise Exception("Velocity must be inherited from Vel3d.vel3d")
        if "iOffsetXAxis" in kw:
            if not "iCmpXAxis" in kw or not "timeAxis" in kw:
                raise Exception(
                    "If specifying iOffsetXAxis your must also specify iCmpYAxis and timeAxis")
            if "iOffsetYAxis" in kw:
                if not "iCmpYAxis" in kw:
                    raise Exception(
                        "If specifying ioffsetYAxis you must supply iCmpYAxis")
                ioffA = [int(kw["iOffsetAxis"]), int(kw["iOffsetYAxis"])]
                self.cppMode = pySepUtil.nmoRegCube(
                    vel.cppMode, kw["timeAxis"].getCpp(), ioffA, kw["iCmpXAxis"], kw["iCmpYAxis"])
            else:
                ioffA = [int(kw["iOffsetAxis"])]
                self.cppMode = pySepUtil.nmoRegCube(
                    vel.cppMode, kw["timeAxis"].getCpp(), ioffA, kw["iCmpXAxis"], -1)
        if "smute" in kw:
            self.cppMode.setSmute(kw["smute"])
        if "stretchMute" in kw:
            self.cppMode.stretchMute(kw["stretchMute"])
        if "doInverse" in kw:
            self.cppMode.doInverse(kw["doInverse"])

    def nmoIt(self, inp, out):
        """Perform nmo (or inverse nmo)

        inp - regspace (input)
        out - regspace (output)
        """
        self.cppMode.nmoIt(inp, out)

    def loopData(self, ind, outd):
        """Loop through data applying NMO

            ind  - Input dataset
            outd - Ouput dataset"""
        self.cppMode.loopData(ind.cppMode, outd.cppMode)

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return self.cppMode
