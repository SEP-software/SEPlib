import pyHypercube


class axis:

    def __init__(self, **kw):
        """Axis
                defaults to n=1, o=0., d=1."""
        self.n = 1
        self.o = 0.
        self.d = 1.
        self.label = ""
        self.unit = ""
        if "n" in kw:
            self.n = kw["n"]
        if "o" in kw:
            self.o = kw["o"]
        if "d" in kw:
            self.d = kw["d"]
        if "label" in kw:
            self.label = kw["label"]
        if "unit" in kw:
            self.unit = kw["unit"]
        if "axis" in kw:
            self.n = kw["axis"].n
            self.o = kw["axis"].o
            self.d = kw["axis"].d
            self.label = kw["axis"].label
            self.unit = kw["axis"].unit

    def getCpp(self):
        """Return a c++ version of the python representation"""
        return pyHypercube.axis(self.n, self.o, self.d, self.label,self.unit)


class hypercube:

    def __init__(self, **kw):
        """initialize with
          - axes=[] A list of Hypercube.axis
          - ns=[] An list of integers (optionally lists of os,ds,labels)
          - hypercube From another hypercube"""
        isSet = False
        self.axes = []
        if "axes" in kw:
            for ax in kw["axes"]:
                self.axes.append(axis(n=ax.n, o=ax.o, d=ax.d, label=ax.label))
                isSet = True
        elif "ns" in kw:
            for n in kw["ns"]:
                self.axes.append(axis(n=n))
                isSet = True
        if "os" in kw:
            for i in range(len(kw["os"]) - len(self.axes)):
                self.axes.append(axis(1))
            for i in range(len(kw["os"])):
                self.axes[i].o = kw["os"][i]
        if "ds" in kw:
            for i in range(len(kw["ds"]) - len(self.axes)):
                self.axes.append(axis(1))
            for i in range(len(kw["ds"])):
                self.axes[i].d = kw["ds"][i]
        if "labels" in kw:
            for i in range(len(kw["labels"]) - len(self.axes)):
                self.axes.append(axis(1))
            for i in range(len(os)):
                self.axes[i].label = kw["labels"][i]
        if "hypercube" in kw:
            for i in range(kw["hypercube"].getNdim()):
                a = axis(axis=kw["hypercube"].getAxis(i + 1))
                self.axes.append(a)
        self.buildCpp()

    def getNdim(self):
        """Return the number of dimensions"""
        return len(self.axes)

    def getAxis(self, i):
        """Return an axis"""
        return self.axes[i - 1]

    def getN123(self):
        """Get the number of elements"""
        n123 = 1
        for ax in self.axes:
            n123 = n123 * ax.n
        return n123

    def getNs(self):
        """Get a list of the sizes of the axes"""
        ns = []
        for a in self.axes:
            ns.append(a.n)
        return ns

    def getCpp(self):
        """Get the c++ representation"""
        return self.cppMode

    def addAxis(self, axis):
        """Add an axis to the hypercube"""
        self.axes.append(axis)
        self.cppMode.addAxis(axis.getCpp())

    def buildCpp(self):
        """Internal function to build c++ version"""
        ax1 = self.axes[0].getCpp()
        if len(self.axes) > 1:
            ax2 = self.axes[1].getCpp()
            if len(self.axes) > 2:
                ax3 = self.axes[2].getCpp()
                if len(self.axes) > 3:
                    ax4 = self.axes[3].getCpp()
                    if len(self.axes) > 4:
                        ax5 = self.axes[4].getCpp()
                        if len(self.axes) > 5:
                            ax6 = self.axes[5].getCpp()
                            self.cppMode = pyHypercube.hypercube(
                                ax1, ax2, ax3, ax4, ax5, ax6)
                        else:
                            self.cppMode = pyHypercube.hypercube(
                                ax1, ax2, ax3, ax4, ax5)
                    else:
                        self.cppMode = pyHypercube.hypercube(
                            ax1, ax2, ax3, ax4)
                else:
                    self.cppMode = pyHypercube.hypercube(ax1, ax2, ax3)
            else:
                self.cppMode = pyHypercube.hypercube(ax1, ax2)
        else:
            self.cppMode = pyHypercube.hypercube(ax1)
