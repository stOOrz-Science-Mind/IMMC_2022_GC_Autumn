from scipy.misc import comb
from math import e

def C(r,z,w,n):
    C = float((25000*e**(n*r))/(r*(e**(n*r)-1))+(25000*e**(26*r))/(r*(e**(26*r)-1))+z+w)
    return C

def A(Pm,Pw,n):
    sumM = 0.0
    sumW = 0.0
    for i in range(0,n+1,1):
        M = float(comb(n, i)*(1-Pm)**(14-i)*(Pm**i)*25000*i)
        sumM += M
    for j in range(0,n+1,1):
        W = float(comb(n, i)*(1-Pw)**(26-i)*(Pw**i)*25000*i)
        sumW += W
    A = sumM + sumW
    return A