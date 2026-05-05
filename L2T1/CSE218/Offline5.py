import numpy as np
import matplotlib.pyplot as pp
import matplotlib.patches as patch


#   constants   #
COLOR_TRAPEZOID = "green"
COLOR_ONE_THIRD = "cyan"
COLOR_THREE_EIGHTH = "orange"
DECIMAL_PRECISION = 6


def Sub(a, b):
    return round((a - b), DECIMAL_PRECISION)


def Trapezoid(start, end, x, y):

    a, b = x[start], x[end]
    I = (b - a)/2
    I *= y[start] + y[end]
    return I


def OneThird(start, end, x, y):

    a, b = x[start], x[end]
    I = y[start] + 4 * y[start + 1] + y[start + 2]
    I *= (b - a)/6
    return I


def ThreeEighth(start, end, x, y):

    a, b = x[start], x[end]
    I = y[start] + 3 * y[start + 1] + 3 * y[start + 2] + y[start + 3]
    I *= (b - a)/8
    return I


def colorGraph(plt, coorx, coory, start, end, color):
    polyx = coorx[start:end+1]
    polyy = coory[start:end+1]
    plt.fill_between(polyx, polyy, color=color)


if __name__ == "__main__":

    file = open("input.txt", "r")
    sampleSize = file.readline()
    sampleSize = int(sampleSize)

    x, y = [], []
    dataSet = file.readlines()

    for line in dataSet:
        tempX, tempY = line.split(" ")
        x.append(float(tempX))
        y.append(float(tempY))

    file.close()
    x = np.array(x)
    y = np.array(y)

    iValue = 0.0
    i = 0
    segTrapezoid, segOneThird, segThreeEighth = 0, 0, 0

    while i < sampleSize - 1:
        k, sameSegment = i, 1

        while k < sampleSize - 2 and Sub(x[k+2], x[k+1]) == Sub(x[k+1], x[k]):
            sameSegment += 1
            k += 1

        #   3/8
        if sameSegment % 3 == 0:
            iValue += ThreeEighth(i, i + 3, x, y)
            colorGraph(pp, x, y, i, i+3, COLOR_THREE_EIGHTH)
            segThreeEighth += 3
            i += 3
        #   1/3
        elif sameSegment % 2 == 0:
            iValue += OneThird(i, i + 2, x, y)
            colorGraph(pp, x, y, i, i+2, COLOR_ONE_THIRD)
            segOneThird += 2
            i += 2
        #   3/8 + 1/3
        elif sameSegment % 3 == 2:
            iValue += ThreeEighth(i, i+3, x, y)
            colorGraph(pp, x, y, i, i+3, COLOR_THREE_EIGHTH)
            iValue += OneThird(i+3, i+5, x, y)
            colorGraph(pp, x, y, i+3, i+5, COLOR_ONE_THIRD)
            segThreeEighth += 3
            segOneThird += 2
            i += 5
        #   3/8 + 1/3 + 1/3
        elif sameSegment % 3 == 1 and sameSegment % 2 == 1 and sameSegment > 3:
            iValue += ThreeEighth(i, i+3, x, y)
            colorGraph(pp, x, y, i, i+3, COLOR_THREE_EIGHTH)
            iValue += OneThird(i+3, i+5, x, y)
            colorGraph(pp, x, y, i+3, i+5, COLOR_ONE_THIRD)
            iValue += OneThird(i+5, i+7, x, y)
            colorGraph(pp, x, y, i+5, i+7, COLOR_ONE_THIRD)
            segOneThird += 4
            segThreeEighth += 3
            i += 7
        #   trapezoid
        else:
            iValue += Trapezoid(i, i + 1, x, y)
            colorGraph(pp, x, y, i, i+1, COLOR_TRAPEZOID)
            segTrapezoid += 1
            i += 1

    # graph printing
    patchOneThird = patch.Patch(color=COLOR_ONE_THIRD, label="One Third")
    patchThreeEighth = patch.Patch(color=COLOR_THREE_EIGHTH, label="Three Eighth")
    patchTrapezoid = patch.Patch(color=COLOR_TRAPEZOID, label="Trapezoid")
    pp.legend(handles=[patchThreeEighth, patchOneThird, patchTrapezoid])

    pp.plot(x, y)
    pp.scatter(x, y)
    pp.grid()
    pp.xlabel("x")
    pp.ylabel("f(x)")
    pp.show()

    #   output printing
    print("Trapezoid:", segTrapezoid, "intervals")
    print("1/3 rule:", segOneThird, "intervals")
    print("3/8 rule:", segThreeEighth, "intervals")
    print()
    #    print("Integral value:", "{0:.5f}".format(iValue) )
    print("Integral value:", iValue)
