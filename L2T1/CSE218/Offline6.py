import numpy as np
import matplotlib.pyplot as pp

# constants    - you may change here
X_MIN, X_MAX = 0, 10
X_INIT, Y_INIT = 0, 4


def myArange(start, end, step):
    val = np.arange(start, end, step)
    for i in range(len(val)):
        val[i] = round(val[i], 7)

    return val


def f(x, y):
    return (x + 20 * y) * np.sin(x * y)


def Euler(func, x0, y0, h):
    return y0 + func(x0, y0) * h


def Heun(func, x0, y0, h):
    return RK2nd(func, x0, y0, 0.5, h)


def Midpoint(func, x0, y0, h):
    return RK2nd(func, x0, y0, 1, h)


def Ralston(func, x0, y0, h):
    return RK2nd(func, x0, y0, 2 / 3, h)


def RK2nd(func, x0, y0, a2, h):
    a1, p1, q11 = 1 - a2, 0.5 * a2, 0.5 * a2

    k1 = func(x0, y0)
    k2 = func(x0 + p1 * h, y0 + q11 * k1 * h)

    return y0 + (a1 * k1 + a2 * k2) * h


def RK4th(func, x0, y0, h):
    k1 = func(x0, y0)
    k2 = func(x0 + 0.5 * h, y0 + 0.5 * k1 * h)
    k3 = func(x0 + 0.5 * h, y0 + 0.5 * k2 * h)
    k4 = func(x0 + h, y0 + k3 * h)

    return y0 + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4)


def PlotMethod(x0, y0):
    methodName = ["Euler's Method", "Heun's Method", "Midpoint Method", "Ralston Method", "RK4th Method"]
    stepSize = [0.5, 0.1, 0.05, 0.01]

    for method in methodName:

        if method == "Euler's Method":
            methodFunc = Euler
        elif method == "Heun's Method":
            methodFunc = Heun
        elif method == "Midpoint Method":
            methodFunc = Midpoint
        elif method == "Ralston Method":
            methodFunc = Ralston
        elif method == "RK4th Method":
            methodFunc = RK4th

        for step in stepSize:
            n = int((X_MAX - X_MIN) / step)

            coorx, coory = myArange(X_MIN, X_MAX + step, step), np.empty(n + 1)
            coorx[0] = x0
            coory[0] = y0

            for i in range(n):
                y = methodFunc(f, coorx[i], coory[i], step)
                coory[i + 1] = y

            pp.plot(coorx, coory, label="Stepsize " + str(step))

        pp.xlabel("Value of x")
        pp.ylabel("Value of y")
        pp.title(method)
        pp.legend()
        pp.grid()
        pp.show()


def PlotStep(x0, y0):
    stepSize = [0.5, 0.1, 0.05, 0.01]
    methodName = ["Euler's Method", "Heun's Method", "Midpoint Method", "Ralston Method", "RK4th Method"]

    for step in stepSize:

        for method in methodName:

            if method == "Euler's Method":
                methodFunc = Euler
            elif method == "Heun's Method":
                methodFunc = Heun
            elif method == "Midpoint Method":
                methodFunc = Midpoint
            elif method == "Ralston Method":
                methodFunc = Ralston
            elif method == "RK4th Method":
                methodFunc = RK4th

            n = int((X_MAX - X_MIN) / step)

            coorx, coory = myArange(X_MIN, X_MAX + step, step), np.empty(n + 1)
            coorx[0] = x0
            coory[0] = y0

            for i in range(n):
                y = methodFunc(f, coorx[i], coory[i], step)
                coory[i + 1] = y

            pp.plot(coorx, coory, label=method)

        pp.xlabel("Value of x")
        pp.ylabel("Value of y")
        pp.title("For step size " + str(step))
        pp.legend()
        pp.grid()
        pp.show()



if __name__ == '__main__':
    print("Graphs for each method \n")
    PlotMethod(X_INIT, Y_INIT)
    print("\n Graph for each step \n")
    PlotStep(X_INIT, Y_INIT)
