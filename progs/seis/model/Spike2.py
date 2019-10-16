#!/usr/bin/env @Python3_EXECUTABLE@
import argparse
import genericIO
import KirchTime
import Hypercube


def migrateIt(args):
    """Function for Kirchhoff time migration"""
    inputIO = genericIO.io()
    outputIO = genericIO = io()
    if args.inputIO:
        inputIO = genericIO.io(args.inputIO)
    if args.outputIO:
        outputIO = genericIO.io(args.outputIO)
    vel3d = KirchTime.vel3d(inputIO.getRegFile("velocity"))
    data = KirchTime.data5DReg(file=inputIO.getRegFile(args.data))
    hyperD = data.getHyper()
    aX = hyperD.getAxis(4)
    aY = hyperD.getAxis(5)
    if args.nx:
        aX.n = args.nx
    if args.ox:
        aX.o = args.ox
    if args.dx:
        aX.d = args.dx
    if args.ny:
        aY.n = args.ny
    if args.oy:
        aY.o = args.oy
    if args.dy:
        aY.d = args.dy

    image = KirchTime.KirchTime.data5DReg(data=data, aX=aX, aY=aY)
    imageF = outputIO.getRegFile(
        args.image,
        fromHyper=image.getHyper(),
        storage="float",
        usage="output")
    image.setFile(imageF)
    maxsize = args.maxsize * 1024 * 1024 * 1024
    data.checkLogic(vel3d)
    maxsize -= vel3d.readVelocity(image.getHyper(), maxsize)
    kir = kirchTime.kirchTime(vel3d, data, maxsize, args.aper)
    kir.migrateData(image)
    image.getFile().close()


def modelIt(args):
    """Function for Kirchhoff time modeling"""
    inputIO = genericIO.io()
    outputIO = genericIO.io()
    if args.inputIO:
        inputIO = genericIO.io(args.inputIO)
    if args.outputIO:
        outputIO = genericIO.io(args.outputIO)
    vel3d = KirchTime.vel3d(inputIO.getRegFile("velocity"))
    imageF = inputIO.getRegFile(args.image)
    image = KirchTime.data3DReg(imageF)
    hyperI = image.getHyper()
    aX = hyperI.getAxis(2)
    aY = hyperI.getAxis(3)
    aOX = Hypercube.axis(n=1, d=.1)
    aOY = Hypercube.axis(n=1, d=.1)
    if args.nx:
        aX.n = args.nx
    if args.ox:
        aX.o = args.ox
    if args.dx:
        aX.d = args.dx
    if args.ny:
        aY.n = args.ny
    if args.oy:
        aY.o = args.oy
    if args.dy:
        aY.d = args.dy
    if args.nox:
        aOX.n = args.nox
    if args.oox:
        aOX.o = args.oox
    if args.dox:
        aOX.d = args.dox
    if args.noy:
        aOY.n = args.noy
    if args.ooy:
        aOY.o = args.ooy
    if args.doy:
        aOY.d = args.doy
    data = KirchTime.data5DReg(image=image, aOX=aOX, aOY=aOY, aX=aX, aY=aY)
    dataF = outputIO.getRegFile(
        args.data,
        fromHyper=data.getHyper(),
        storage="float",
        usage="output")
    data.setFile(dataF)
    print("w1")
    wave = inputIO.getVector(args.wavelet)
    print("w1")

    maxsize = args.maxsize * 1024 * 1024 * 1024
    print("w1")

    data.checkLogic(vel3d)
    print("w1")

    maxsize -= vel3d.readVelocity(image.getHyper(), maxsize)
    print("w1")

    kir = KirchTime.kirchTime(vel3d, data, maxsize, args.aper)
    print("w1")

    kir.modelData(image, wave)
    data.getFile().close()
parser = argparse.ArgumentParser(
    description="Kirchhoff 3D migration / modeling")
subParser = parser.add_subparsers(help="sub command help")
modes = genericIO.ioModes.getIOs()
defType = genericIO.ioModes.getDefaultType()


def jointArguments(parser):
    """Arguments for both options"""
    parser.add_argument(
        "-inputIO",
        type=str,
        choices=modes, default=defType,
        help="Input file types")
    parser.add_argument(
        "-outputIO",
        type=str,
        choices=modes, default=defType,
        help="Output file types")
    parser.add_argument(
        "-datapath",
        type=str,
        help="Location for binary (for some IOs)")
    parser.add_argument(
        "-nx",
        type=int,
        help="Number of cmps in x for output")
    parser.add_argument(
        "-ox",
        type=float,
        help="First  cmp x location for output")
    parser.add_argument(
        "-dx",
        type=float,
        help="Sampling of cmps in x for output")
    parser.add_argument(
        "-ny",
        type=int,
        help="Number of cmps in y for output")
    parser.add_argument(
        "-oy",
        type=float,
        help="First  cmp y location for output")
    parser.add_argument(
        "-dy",
        type=float,
        help="Sampling of cmps in y for output")
    parser.add_argument(
        "-maxsize",
        type=int,
        default=24,
        help="Amount of memory to use in GB")

modelParser = subParser.add_parser("model")
modelParser.add_argument(
    "velocity",
    type=str,
    help="VRMS (nt,ncmpx,ncmpy) [input]")
modelParser.add_argument(
    "wavelet",
    type=str,
    help="Wavelet to convovle data with")


modelParser.add_argument(
    "image",
    type=str,
    help="Image (nt,ncmpx,ncmpy) [input]")
modelParser.set_defaults(func=modelIt)
modelParser.add_argument(
    "data", type=str, help="data (nt,offx,offy,ncmpx,ncmpy [output]")
modelParser.add_argument("aper", type=float, help="Aperture ofr migration")


modelParser.add_argument(
    "-nox",
    type=int,
    help="Number of offset in x for output")
modelParser.add_argument(
    "-oox",
    type=float,
    help="First  offset x location for output")
modelParser.add_argument(
    "-dox",
    type=float,
    help="Sampling of offset in x for output")
modelParser.add_argument(
    "-noy",
    type=int,
    help="Number of offset in x for output")
modelParser.add_argument(
    "-ooy",
    type=float,
    help="First  offset y location for output")
modelParser.add_argument(
    "-doy",
    type=float,
    help="Sampling of offset in y for output")


migrateParser = subParser.add_parser("migrate")
migrateParser.add_argument("velocity", help="VRMS (nt,ncmpx,ncmpy) [input]")

migrateParser.add_argument(
    "data", type=str, help="Image (nt,offx,offy,ncmpx,ncmpy) [input]")
migrateParser.add_argument(
    "image", type=str, help="data (nt,offx,offy,ncmpx,ncmpy [output]")
migrateParser.add_argument("aper", type=float, help="Aperture ofr migration")
migrateParser.set_defaults(func=migrateIt)


migrateParser = jointArguments(migrateParser)
modelParser = jointArguments(modelParser)
args = parser.parse_args()


paramArgs = genericIO.argParseParams(vars(args))

args.func(args)
