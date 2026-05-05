import numpy as np
import matplotlib.pyplot as pp


# ################################
# ######## Problem 2(a) ##########
# ################################

print("")
print(" - - Graph drawing for Problem - 2(a) - - ")

def Kfunc(x):
    P = 3
    func = (x/(1-x) * np.sqrt((2*P)/(2+x)))-0.05
#    print(x, "gives", func)
    return func


setX = np.arange(0, 0.1, 0.001)
setY = Kfunc(setX)

Y1 = 0

pp.figure(figsize=(10,8))
pp.axhline(y = 0, color="black")
pp.axvline(x = 0, color="black")
pp.plot(setX, setY, color = "orange")

index = np.argwhere(np.diff(np.sign(setY - Y1))).flatten()
pointX = setX[index]
pointY = setY[index]
print("The intersecting point is appr. :", pointX, pointY)
pp.scatter(pointX, pointY, 50, color = "red")
pp.text(pointX + 0.003, pointY + 0.005, '({}, {})'.format(pointX, pointY), fontsize = 15)

pp.grid()
pp.xlabel("Value of x", fontsize = 16)
pp.ylabel("Value of Kfunc(x)", fontsize = 16)
pp.savefig("Problem_2(a).pdf")
pp.show()
print("")

# ################################
# ######## Problem 2(b) ##########
# ################################

print(" - - Solution for Problem 2(b) - - ")
print(" - - Secant Method Application - - ")
print("")

def secantMethod(func, first, second, error, maxIter):
    
    x0 = first
    x1 = second
    countIter = 0;
    
    while (countIter < maxIter):
        x2 = ( x1 - (func(x1) * (x0 - x1)) / (func(x0) - func(x1)) )
        countIter = countIter+1
        x0, x1 = x1, x2
        
        if(abs(x1 - x0) < error):
            break
     
    return x1, countIter

secantAns, secantIter = secantMethod(Kfunc, -0.5, 0.5, 0.005, 10)
print("Secant Ans = ", secantAns)
print("Iteration no = ", secantIter)
print("")

print(" - - False Position Method Application - - ")

def falsePosMethod(func, xLow, xHigh, error, maxIter):
    
    if(func(xLow) * func(xHigh) >= 0):
        print("Assume correct upper and lower bound")
        return -1, -1
    
    else:
        falsePosIter = 0
        xPrev = -1
        relError = 100
        while((falsePosIter < maxIter) and (relError > error)):
            
            xTemp = xHigh - func(xHigh)*(xLow - xHigh)/(func(xLow) - func(xHigh))
            falsePosIter += 1
            
            if(func(xTemp) * func(xLow) < 0):
                xHigh = xTemp
                
            elif(func(xTemp) * func(xLow) > 0):
                xLow = xTemp
            
            relError = abs(xTemp - xPrev) / abs(xTemp)
            xPrev = xTemp
            #     storing the current term for future use
    return xTemp, falsePosIter

falsePosAns, falsePosIter = falsePosMethod(Kfunc, -0.5, 0.5, 0.005, 7)
print("FalsePos Ans = ", falsePosAns)
print("Iteration no = ", falsePosIter)

