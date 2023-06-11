Vin = 48;
eVo = 12;
fsw = 100e3;
DI_L = 0.5;
DV_o = 0.1;

Don = eVo/Vin;
Ton = Don/fsw;


L = Ton * (Vin - eVo) / DI_L;
uprint(L, "H");
C = DI_L / (8 * fsw * DV_o);
uprint(C, "F");
R_crit = 2 * eVo / DI_L;
uprint(R_crit, "Ohm");

R = 1:100;
a = 2 * L * 1/fsw;
b = Vin * R * Ton^2;
c = -R * Vin^2 * Ton^2;
Vo = (-b + sqrt(b.^2 - 4 .* a .* c))./(2 * a);

%% Ton^2 a + b = 0
Don = sqrt((eVo^2 * 2 * L * 1/fsw) ./ (R * Vin * (Vin - eVo))) * fsw;
Don(1:48) = eVo/Vin;
plot(R, Don);
% yline(eVo);
axis([0, 100, 0, 1])
xline(R_crit);

% uprint(Vo, "V");
%% L C R filter
clc;
R = 100;

Vg = 5;
a = L * C;
b = L / R;
n = 4;
K = [-n*a, -n*b, 0.9985];
k = [a, b, 1] - K;
l1 = (-k(2) - sqrt(k(2)^2 - 4 * k(1) * k(3))) / (2 * k(1));
l2 = (-k(2) + sqrt(k(2)^2 - 4 * k(1) * k(3))) / (2 * k(1));

t = linspace(0, 0.03, 10000);
c1 = 1;
c2 = 3;
vo = Vg * (1 + (l2/(l1 - l2)) * exp(l1 * t) + (l1/(l2 - l1)) * exp(l2 * t));
vop = l1 * (l2/(l1 - l2)) * exp(l1 * t) + l2 * (l1/(l2 - l1)) * exp(l2 * t);
vopp = l1^2 * (l2/(l1 - l2)) * exp(l1 * t) + l2^2 * (l1/(l2 - l1)) * exp(l2 * t);

vu = sum((K') .* [vopp; vop; vo]);

plot(t, vo, t, vu);
%%
Don = 0.1
k = (1:100)';
x = linspace(-20, 20, 100000);
a_k = 2 ./ (pi*k) .* sin(Don * pi * k);
f_x = Don + sum(cos(k .* x) .* a_k);
plot(a_k);

%%
clear;
w = 60 * pi *2;
vrms = 120/sqrt(2);
sc = 1000 + 1000 * tan(acos(0.8)) * 1i;
sc2 = 1000 + 1000 * tan(acos(0.95)) * 1i;
b = imag(sc);
d = imag(sc2);

C = (d - b) / (b * d * w);
z = vrms^2 / sc;

vrms = sqrt(10^2 + 20^2/2 + 30^2/2)
P = vrms^2 / 5


vc = 8*exp(1i * pi/18) + 5*exp(1i * 5 * pi/18);
sqrt(4^2 + (abs(vc)/sqrt(2))^2)

%%
deg = pi/180;

R = 5;
L = 15e-3;

z = @(w) R + 1i * w * L;
ph = [0, -25*deg, 20*deg];
w = [0, 2*pi*60, 4*pi*60];
v = [10, 20 * exp(-25*deg*1i), 30 * exp(20*deg*1i)];

i = v ./ z(w);
p = sqrt(sum(abs(v .* i).^2 ./ [1, 2, 2]))


% fprintf("i(t) = %.2f + %.2fcos(%.2f t + %.2f) + %.1fcos(%.1f t + %.2f)\n", i_w0, abs(i_w1), w1, angle(i_w1)/deg, abs(i_w2), w2, angle(i_w2)/deg);
