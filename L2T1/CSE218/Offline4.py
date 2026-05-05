import numpy as np
import matplotlib.lines as ml
import matplotlib.pyplot as pp


def curveFit(deg, dataX, dataY):
    size = deg + 1
    leftMatrix = np.zeros(size * size).reshape(size, size)
    rightMatrix = np.zeros(size)

    for row in range(size):
        for col in range(size):
            power = row + col
            leftMatrix[row][col] = np.power(dataX, power).sum()

    for row in range(size):
        power = row
        temp = np.power(dataX, power) * dataY
        rightMatrix[row] = temp.sum()

    a = np.linalg.solve(leftMatrix, rightMatrix)
    return a


def yFunc(x, a):
    y = 0
    for i in range(a.size):
        y += pow(x, i)*a[i]
    return y


def plotCurve(a, dataX, y):
    maxX = np.amax(dataX)
    minX = np.amin(dataX)

    dataX = np.arange(minX, maxX, 0.01)
    dataY = y(dataX, a)

    pp.plot(dataX, dataY, 0.01)


def regCo(dataX, dataY, a):

    tempY = coorY - coorY.mean()
    St = np.power(tempY, 2).sum()
    tempY = coorY - yFunc(dataX, a)
    Sr = np.power(tempY, 2).sum()
#    print("St, Sr =", St, Sr)

    coEff = pow(( (St - Sr) / St), 0.5)
    print("Correlation Coefficient = ", coEff)


#   main method -----------------------------------------------------------------
if __name__ == "__main__":

    file = open("data.txt", "r")
    dataSet = file.readlines()
    coorX, coorY = [], []
    pp.figure(figsize=(12, 8))

    for line in dataSet:
        tempX, tempY = line.split(" ")
        coorX.append(float(tempX))
        coorY.append(float(tempY))

    coorX = np.array(coorX)
    coorY = np.array(coorY)
    point = pp.scatter(coorX, coorY, 1.5, color="grey", label="Given point")

    maxDegree = 3
    for DEGREE in range(1, maxDegree + 1):
        a = curveFit(DEGREE, coorX, coorY)
        plotCurve(a, coorX, yFunc)
        print("\nValue of a for degree", DEGREE, ":")
        print("a =", a)
        regCo(coorX, coorY, a)

    pp.grid()
    pp.title("Graph Fitting of Degree 3")
    pp.xlabel("Value of X")
    pp.ylabel("Value of Y")

    deg1 = ml.Line2D([], [], color="blue", markersize=18, label="Degree 1")
    deg2 = ml.Line2D([], [], color="green", markersize=18, label="Degree 2")
    deg3 = ml.Line2D([], [], color="purple", markersize=18, label="Degree 3")

    pp.legend(handles=[deg1, deg2, deg3, point], prop={'size': 18})
    pp.savefig("graphFitting.png")
    pp.show()
