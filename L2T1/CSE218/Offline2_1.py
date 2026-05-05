import numpy as np


def LUDecompose(A, matSize):
    matUpper = np.array([[0.0]*matSize for i in range(matSize)])
    matLower = np.array([[0.0]*matSize for i in range(matSize)])

    for row in range(matSize):
        for col in range(row, matSize):
            sum = 0
            for temp in range(row):
                sum += (matLower[row][temp] * matUpper[temp][col])

            matUpper[row][col] = (A[row][col] - sum)

        for col in range(row, matSize):
            if(row == col):
                matLower[row][col] = 1
            else:
                sum = 0
                for temp in range(col):
                    sum += matLower[col][temp] * matUpper[temp][row]

                matLower[col][row] = int((A[col][row] - sum)/matUpper[row][row])

    return matLower, matUpper


file = open("in1.txt", "r")
matSize = int(file.readline())

matA = np.array([[0.0]*matSize for i in range(matSize)])
matB = np.array([0.0]*matSize)

for i in range(matSize):
    matA[i] = [float(x) for x in file.readline().split(" ")]

for i in range(matSize):
    matB[i] = float(file.readline())

matB = matB.reshape(3,1)

print("A = ", matA)
print("B = ", matB)

L, U = LUDecompose(matA, matSize)

print("L = ", L)
print("U = ", U)


