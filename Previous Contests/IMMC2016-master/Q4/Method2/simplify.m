syms Po h d Vw Vo cosAlpha cosTheta V cosBeta m sinAlpha sinBeta sinTheta g;
Rho=1.293*((Po*(1-(h/44330)^5.255))/Po)*(273.15/(298.15-0.006*h));
A=0.22*d;
ax=(A*Rho*(Vw*cosAlpha-V*cosTheta*cosBeta)^2)/m;
ay=(A*Rho*(Vw*sinAlpha-V*cosTheta*sinBeta)^2)/m;
az=((-A*Rho*(V*cosBeta*sinTheta)^2)/m) - g;
t = (2*m*Vo*sinTheta)/(A*Rho*((V*cosBeta*sinTheta)^2) - m*g);
Vx = Vo*cosTheta + ax*t;
Vy = ay*t;
Vz=Vo*sinTheta + az*t;
V = (Vx^2 + Vy^2 + Vz^2)^0.5;
Sx=Vo*t*cosTheta+(((ax*t)^2)/2);
Sy=((ay*t)^2)/2;
S=(Sx^2+Sy^2)^0.5
i=combine(S)