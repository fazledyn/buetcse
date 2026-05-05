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


def Substitution(L, U, B):
    Y = np.array([[0.0] for i in range(matSize)])
    X = np.array([[0.0] for i in range(matSize)])
#   Y er matrix
#    matY[0] = B[0]
    for row in range(matSize):
        sum = 0
        for col in range(row):
            sum += L[row][col]*Y[col]
        Y[row] = B[row] - sum
#   X er matrix
    for row in range(matSize-1, -1, -1):
        sum = 0
        for col in range(matSize-1, row, -1):
            sum += U[row][col]*X[col]
        X[row] = (Y[row] - sum)/U[row][row]

    return X, Y


def noUniqueSolution(mat, matSize):
    temp = np.array([0.0] for a in range(matSize))
    if temp in mat:
        return True


#              MAIN METHOD
inFile = open("in1.txt", "r")
matSize = int(inFile.readline())

matA = np.array([[0.0]*matSize for i in range(matSize)])
matB = np.array([0.0]*matSize)

for i in range(matSize):
    matA[i] = [float(x) for x in inFile.readline().split(" ")]

for i in range(matSize):
    matB[i] = float(inFile.readline())

inFile.close()
matB = matB.reshape(matSize, 1)

L, U = LUDecompose(matA, matSize)
matX, matY = Substitution(L, U, matB)

outFile = open("out1.txt", "w")

#   printing L in file
for row in range(matSize):
    for col in range(matSize):
        if L[row][col] == int(L[row][col]):
            outFile.write(str(int(L[row][col])) + " ")
        else:
            outFile.write(str("{0:.4f}".format(L[row][col])) + " ")
    outFile.write("\n")

#   printing U in file
outFile.write("\n")
for row in range(matSize):
    for col in range(matSize):
        if U[row][col] == int(U[row][col]):
            outFile.write(str(int(U[row][col])) + " ")
        else:
            outFile.write(str("{0:.4f}".format(U[row][col])) + " ")
    outFile.write("\n")

#   printing solution
outFile.write("\n")
if noUniqueSolution(U, matSize):
    outFile.write("No unique solution")
    exit()
else:
    #   printing Y in file
    for row in range(matSize):
        if matY[row][0] == int(matY[row][0]):
            outFile.write(str(int(matY[row][0])))
        else:
            outFile.write(str("{0:.4f}".format(matY[row][0])) + " ")
        outFile.write("\n")

    #   printing X in file
    outFile.write("\n")
    for row in range(matSize):
        if matX[row][0] == int(matX[row][0]):
            outFile.write(str(int(matX[row][0])))
        else:
            outFile.write(str("{0:.4f}".format(matX[row][0])) + " ")
        outFile.write("\n")
    outFile.close()
