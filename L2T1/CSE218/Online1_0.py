import math

def function(x):
    result = -2*x**4 + 2*x**3 - 16*x**2 - 60*x + 100
    return result

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

def inverseMethod(func, first, second, third, error, maxIter):
    x0 = first
    x1 = second
    x2 = third
    
    countIter = 0
    while(countIter < maxIter):
        
        if(func(x0) == 0):
            xNew = x0
            break
        elif(func(x1) == 0):
            xNew = x1
            break
        elif(func(x2) == 0):
            xNew = x2
            break
        elif(func(x0) == func(x1) or func(x1) == func(x2) or func(x0) == func(x2)):
            break
        else:
            xNew = ( func(x1)*func(x2)*x0 )/( (func(x0) - func(x1)) * (func(x0) - func(x2)) ) 
            xNew += ( func(x0)*func(x2)*x1 )/( (func(x1) - func(x0)) * (func(x1) - func(x2)) ) 
            xNew += ( func(x0)*func(x1)*x2 )/( (func(x2) - func(x0)) * (func(x2) - func(x1)) )                
                   
            x0, x1, x2 = x1, x2, xNew
        
        countIter += 1
        
    return xNew, countIter

X0, X1, X2 = 0, 1, 2

print("Secant = ", secantMethod(function, X0, X1, 0.001, 30))
print("FalsePos = ", falsePosMethod(function, 0, 2, 0.001, 30))
print("Inverse Quad = ", inverseMethod(function, X0, X1, X2, 0.001, 50))    
