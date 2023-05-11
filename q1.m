%% q1

%% q2

%% q3

%% q4

i1 = 30;
i2 = 12;
Tup = 7e-6;
Tsw = 18e-6;
Tdown = Tsw - Tup;
V = 0.9;

avgI = Tdown * (i1 + i2) / (2 * Tsw);
PL = avgI * V;

%% q5

i1 = 30;
i2 = 17;
Tup = 7e-6;
Tsw = 18e-6;
R = 8e-3;

avgI = Tup * (i1 + i2) / (2 * Tsw);
PL = R * avgI^2;

%% q6 

Vin = 10;
Co = 220e-6;
L = 56e-6;
Fsw = 104e3;
Don = 0.49;
R = 466;

%CCM
Vo = 1/ (1 - Don) * Vin;
Ton = Don / Fsw;
dI = Ton * (Vin/L);
Rcrit = 2 * Vo^2 / (dI * Vin);

%% q7

%% q8

%% q9


%% q10


