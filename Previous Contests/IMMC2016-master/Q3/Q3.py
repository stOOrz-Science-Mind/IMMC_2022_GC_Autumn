from scipy.misc import comb
from math import e

r = 0.03
z = 5618.00
w = 107061.00
Pm = 1/14
Pw = 1/26
R = 0.055 + 1
sumM = 0
sumW = 0

C = (25000*e**(13.5*r))/(r*(e**(13.5*r)-1))+(25000*e**(26*r))/(r*(e**(26*r)-1))+z+w

for i in range(0,15,1):
    M=comb(14, i)*Pm**(14-i)*((1-Pm)**i)*25000*i
    sumM += M
for j in range(0,27,1):
    W=comb(26, i)*Pw**(26-i)*((1-Pw)**i)*25000*i
    sumW += W
A = sumM + sumW

if C*R > A > C:
    print("Deal!")
if C > A:
    print("Committee should not!\nInsurer should!")
if A > C*R:
    print("Committee should!\nInsurer should not!")