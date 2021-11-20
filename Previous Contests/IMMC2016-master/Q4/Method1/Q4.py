from scipy.misc import comb
from math import e

n = 10
r = 0.03
z = 1000
w = 2376.07
R = 0.055

RawPm = open("./Raw/Pm.txt")
RawPw = open("./Raw/Pw.txt")
ResultC = open("./Result/ResultCommittee.txt", "w")
ResultI = open("./Result/ResultInsurer.txt", "w")
dataRow = int(input("Input the total amount data you want to calculate: "))

for k in range(0,dataRow,1):
    Pm = float(RawPm.readline())
    Pw = float(RawPw.readline())
    C = float((25000*e**(n*r))/(r*(e**(n*r)-1))+(25000*e**(26*r))/(r*(e**(26*r)-1))+z+w)
    sumM = 0.0
    sumW = 0.0
    for i in range(0,n+1,1):
        M = float(comb(n, i)*(1-Pm)**(14-i)*(Pm**i)*25000*i)
        sumM += M
    for j in range(0,n+1,1):
        W = float(comb(n, i)*(1-Pw)**(26-i)*(Pw**i)*25000*i)
        sumW += W
    A = sumM + sumW

    if C*(R+1.0) > A > C:
        ResultC.write("Deal\n")
        ResultI.write("Deal\n")
    if C > A:
        ResultC.write("Should not\n")
        ResultI.write("Should\n")
    if A > C*(R+1.0):
        ResultC.write("Should\n")
        ResultI.write("Should not\n")
    print("Recorded!")

ResultC.close()
ResultI.close()
RawPm.close()
RawPw.close()
print("Process finished!")