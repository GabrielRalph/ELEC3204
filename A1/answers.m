Vin = 12;
Don = 0.42;
fsw = 10^5;
L = 1e-4;
R = 10;

vo = Vin * Don;
Tdown = (1/fsw) * (1 - Don);
Ton = (1/fsw) * Don;
DI_L = Tdown * vo / L;
AVG_I_L = vo / R;

a1 = DI_L - 0.5 * AVG_I_L;
a2 = DI_L + 0.5 * AVG_I_L;
b1 = DI_L/Ton;
b2 = DI_L/Tdown;

 
rmss1 = Ton * a1^2 + (1/3) * b1^2 * Ton^3 + a1 * b1 * Ton^2;
rmss2 = Tdown * a2^2 + (1/3) * b2^2 * Tdown^3 + a2 * b2 * Tdown^2;
rms = sqrt(fsw * (rmss1 + rmss2));

fprintf("RMS = %f\n", rms)