import numpy as np


def optimal(t, TOTAL_VAR):
    count = 0
    row = 0
    for col in range(1, TOTAL_VAR + 1):
        if t[row][col] >= 0.0:
            count += 1
    if count == TOTAL_VAR:
        return True
    else:
        return False


def printMatrix(t, hLabel, vLabel):
    ROW, COL = t.shape
    for col in range(COL):
        print("\t", hLabel[col], end="\t")
    print()
    for row in range(ROW):
        print(vLabel[row], end = "")
        for col in range(COL):
            print("\t", round(t[row][col], 2), end="")
        print()


#   main method here
if __name__ == "__main__":

    np.set_printoptions(formatter = {'float': '{: 0.2f}'.format})

    inFile = open("in2.txt", "r")
    funcCoEff = np.array([float(x) for x in inFile.readline().split(" ")])
    VAR_NO = funcCoEff.size

    lines = inFile.readlines()
    data = []
    for line in lines:
        data += [float(x) for x in line.split(" ")]

    data = np.array(data)
    CONS_NO = int(data.size / (VAR_NO + 1))
    data = data.reshape(CONS_NO, VAR_NO + 1)

    ROW = CONS_NO + 1
    COL = CONS_NO + VAR_NO + 3

    SOLN_COL = COL - 2
    SLACK_COL_INIT = VAR_NO + 1
    INTERCEPT_COL = COL - 1

    table = np.zeros((ROW, COL))
    table[0][0] = 1
    horLabel = [""] * (CONS_NO + VAR_NO + 3)
    verLabel = [""] * (CONS_NO + 1)
    verLabel[0] = " Z"
    horLabel[0] = " Z"

    for i in range(VAR_NO):
        table[0][i + 1] = -funcCoEff[i]
        horLabel[i + 1] = "x" + str(i + 1)

    for row in range(CONS_NO):
        table[row + 1][SLACK_COL_INIT + row] = 1
        horLabel[VAR_NO + row + 1] = "S" + str(row + 1)
        verLabel[row + 1] = "S" + str(row + 1)

    horLabel[COL - 2] = "Sol."
    horLabel[COL - 1] = "Int."

    for row in range(CONS_NO):
        for col in range(VAR_NO):
            table[row + 1][col + 1] = data[row][col]
        table[row + 1][SOLN_COL] = data[row][VAR_NO]

    print("Data load er por")
    printMatrix(table, horLabel, verLabel)

    pRow, pCol = 2, 1
    TOTAL_VAR = COL - 2

    iterCount = 1
    while not optimal(table, TOTAL_VAR):

        print("Iteration -", iterCount)
        print("pivot col = ", pCol)

        for row in range(1, ROW):
            if table[row][pCol] == 0:
                table[row][INTERCEPT_COL] = float("inf")
            else:
                table[row][INTERCEPT_COL] = table[row][INTERCEPT_COL - 1]/table[row][pCol]

        print("intercept ber korar por")
        printMatrix(table, horLabel, verLabel)

        for row in range(1, ROW):
            if table[pRow][INTERCEPT_COL] > table[row][INTERCEPT_COL] > 0.0:
                pRow = row

        verLabel[pRow] = horLabel[pCol]
        pivotElement = table[pRow][pCol]
        print("pivot position = ", pRow, ",", pCol)
        print("pivot element = ", round(pivotElement, 2))

        for col in range(0, COL):
            table[pRow][col] = table[pRow][col] / pivotElement

        print("pivot element diye vag korar por")
        printMatrix(table, horLabel, verLabel)

        for row in range(ROW):
            if row == pRow:
                continue
            else:
                table[row] = table[row] - table[pRow] * table[row][pCol]

        print("row operation korar por")
        printMatrix(table, horLabel, verLabel)

        iterCount += 1

        for col in range(1, VAR_NO + 1):
            if table[0][col] < table[0][pCol]:
                pCol = col

        print(" -" * 40)

    print("last table : ")
    printMatrix(table, horLabel, verLabel)
    print(" -" * 40)
    print(" -" * 40)
    print("Final Result :")

    for row in range(VAR_NO + 1):
        for col in range(ROW):
            if horLabel[row] == verLabel[col]:
                print(verLabel[col], " = ", round(table[col][COL - 2], 2) )

    for i in range(VAR_NO + 1):
        if horLabel[i] not in verLabel:
            print(horLabel[i], " = ", 0.0)
