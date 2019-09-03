import pySEPUtil
import Hypercube
import Vel3D

class data3DReg:

    def __init__(self, myf):
        """initialize data3DReg
            myf  to build object from
        """
        self.cppMode = pySEPUtil.data3DReg(myf.cppMode)

    def getHyper(self):
        """Returm hypercube"""
        return Hypercube.hypercube(hypercube=self.cppMode.getHyper())

    def read(self):
        """Read file"""
        return self.cppMode.read()


class data5DReg:
    """5-D data object"""

    def __init__(self, **kw):
        """initialize object one of two ways

        Method 1:
            data  data object
            aX CMP-X axis
            aY CMP-Y axis

        Method 2:
            image image object
            aX CMP-X axis
            aY CMP-Y axis
            aOX Offset-X axis
            aOY Offset-y axis

        Method 3:
            file
        """

        if "data" in kw and "aX" in kw and "aY" in kw:
            if not isinstance(kw["data"], data5DReg):
                raise Exception("data must be a data5DRweg object")
            self.cppMode = pySEPUtil.data5DReg(
                kw["data"].cppMode, kw["aX"].getCpp(), kw["aY"].getCpp())
        elif "image" in kw and "aX" in kw and "aY" in kw and "aOX" in kw and "aOY" in kw:
            if not isinstance(kw["image"], data3DReg):
                raise Exception("data must be a data3DReg object")
            self.cppMode = pySEPUtil.data5DReg(
                kw["image"].cppMode, kw["aOX"].getCpp(), kw["aOY"].getCpp(), kw["aX"].getCpp(), kw["aY"].getCpp())
        elif "file" in kw:
            self.file = file
            self.cppMode = pySEPUtil.data5DReg(kw["file"].cppMode)
        else:
            raise Exception("Now valid initialization method")

    def setFile(self, file):
        """Set file associated with structure
            file to associate
        """
        self.file = file.cppMode
        self.cppMode.setFile(file.cppMode)

    def getHyper(self):
        """Returm hypercube"""
        return Hypercube.hypercube(hypercube=self.cppMode.getHyper())

    def getFile(self):
        """Returm file associated with object"""
        return self.file

    def checkLogic(self, vel):
        """Make sure velocity model contains image"""
        self.cppMode.checkLogic(vel.cppMode)

    def readWindow(self, nw, fw, vec):
        """Read a window of the dataset

            nw,fw - Windowing parameters for read
            vec   - Vector to store into
        """
        self.cppMode.readWindow(nw, fw, vel.cppMode)

    def writeWindow(self, nw, fw, vec):
        """Write a window of the dataset

            nw,fw - Windowing parameters for read
            vec   - Vector to read from
        """
        self.cppMode.writeWindow(nw, fw, vel.cppMode)


class kirchModel:
    """Modeling operator for a sub-volume"""

    def __init__(self, inp, vel, wave, aper, mem):
        """Initialize modeling opreator
          inp Data5D object
          vel Vel3D object
          wave wavelet
          aper Aperture
          mem  Memory to use """
        self.cppMode = pySEPUtil.model(
            inp.cppMode, vel.cppmode, wave.cppMode, aper, mem)

    def apply(self, wavelet, image):
        self.cppMode.apply(wavelet, image)


class kirchMigrate:
    """Class to migrate a sub-volume"""

    def __init__(self, inp, vel, aper, mem):
        """Initialize migration opreator
          inp Data5D object
          vel Vel3D object
          aper Aperture
          mem  Memory to use """
        self.cppMode = pySEPUtil.migrate(inp.cppMode, vel.cppmode, aper, mem)

    def apply(self, wavelet, image):
        self.cppMode.apply(wavelet, image)


class kirchTime:
    """Looping operator for modeling/migration"""

    def __init__(self, vel, data, mem, aper):
        """Initalize Kirchhoff looping operator
            vel  Velocity
            data Data object
            mem Memory
            aper Aperture"""
        self.cppMode = pySEPUtil.kirchhoffTime(
            vel.cppMode, data.cppMode, mem, aper)

    def modelData(self, image, wave):
        """Model data (loop through dataset)"""
        self.cppMode.modelData(image.cppMode, wave.cppMode)

    def migrateData(self, image):
        """Migrate data (loop through dataset)"""
        self.cppMode.migrateData(image.cppMode)
