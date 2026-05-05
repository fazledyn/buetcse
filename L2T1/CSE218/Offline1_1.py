import math
import matplotlib.pyplot as pp
import numpy as np

# defining own function
def myLog(x, n):
    sumLog = 0
    temp = 0
    i = 1
    while(i <= n):
        temp = (math.pow(x, i)/i)*math.pow((-1), (i+1))
        sumLog += temp
        i = i+1

    return sumLog

# ######################################
# ######### Problem 1(a) ###############
# ######################################

print(" - - Solution for Problem 1(a) - - ")

x = float(input("Enter x : "))
n = int(input("Enter n : "))

print("The value of ln(1+x) using myLog is :", myLog(x, n))

# ######################################
# ######### Problem 1(b) ###############
# ######################################

print("")
print(" - - Solution for Problem 1(b) - - ")
print("The graph for 1(b)")

SetX = np.arange(-0.9, 0.9, 0.1)
SetY = [np.log(1+a) for a in SetX]
line1, = pp.plot(SetX, SetY, label = "Built-in Log")

pp.grid()
pp.title("Graph of ln(1+x)")
pp.xlabel("x")
pp.ylabel("y = ln(1+x)")
pp.legend(handles = [line1], fontsize = 14)
pp.savefig("Problem_1(b).jpg")
pp.show()

# ######################################
# ######### Problem 1(c) ###############
# ######################################

print("")
print(" - - Solution for Problem 1(c) - - ")

SetmyY1 = [myLog(a, 1) for a in SetX]
SetmyY2 = [myLog(a, 3) for a in SetX]
SetmyY3 = [myLog(a, 5) for a in SetX]
SetmyY4 = [myLog(a, 20) for a in SetX]
SetmyY5 = [myLog(a, 50) for a in SetX]

print("The graph for 1(c) : ")

line1, = pp.plot(SetX, SetY, label = "Built-in Log")
line2, = pp.plot(SetX, SetmyY1, label = "Iter 1")
line3, = pp.plot(SetX, SetmyY2, label = "Iter 3")
line4, = pp.plot(SetX, SetmyY3, label = "Iter 5")
line5, = pp.plot(SetX, SetmyY4, label = "Iter 20", linestyle = "--")
line6, = pp.plot(SetX, SetmyY5, label = "Iter 50")

pp.grid()
pp.title("Comparison of ln(1+x) function")
pp.xlabel("x")
pp.ylabel("y = myLog(1+x)")
pp.legend(handles = [line1, line2, line3, line4, line5, line6], fontsize = 14)
pp.savefig("Problem_1(c).jpg")
pp.show()

# ######################################
# ######### Problem 1(d) ###############
# ######################################

print("")
print(" - - Solution for Problem 1(d) - - ")

def errorCalc(x, n):
    realVal = math.log(1 + x)
    apprVal = myLog(x, n)
    error = abs(realVal - apprVal)/abs(realVal)
    errorPercentage = error * 100

    return errorPercentage

#########################################

xAxis = range(50)
yAxis = [errorCalc(0.5, a+1) for a in range(50) ]

print("The graph for 1(d) : ")

errorLine, = pp.plot(xAxis, yAxis, label = "Error percentage")

pp.grid()
pp.xlabel("Number of terms")
pp.ylabel("Error percentage (%)")
pp.legend(handles=[errorLine], fontsize = 14)
pp.savefig("Problem_1(d).jpg")

pp.show()