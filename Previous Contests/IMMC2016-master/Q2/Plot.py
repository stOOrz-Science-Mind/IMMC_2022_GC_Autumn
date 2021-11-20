import numpy as np
import matplotlib.pyplot as plt
import pylab

def f(x):
    z = 500
    w = 800
    return -(26661.1+10.5322*(z+w))*np.e**(0.049*x)+(51661.1134+20.4082*(z+w))

x = np.linspace(0, 14, num = 14)
y = f(x)
print(f(x))
pylab.show(plt.plot(x,y))