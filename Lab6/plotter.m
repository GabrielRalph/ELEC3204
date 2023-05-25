clear; clc;
pr = 0.565;
mg = 0.08;
msp = 0.15;
ph = (1-2*mg - msp);
sp1p = [mg, (msp + mg +  ph * (1-pr)), (1 - 2*mg), ph * pr];
sp2p = [mg, mg, (1 - 2*mg), ph * (1-pr)];
FS1 = 14;
FS2 = 12;
files = {"halfwave rectifier.txt", "hw";
         "three phase full wave.txt", "fw";
         "last section capacitor add.txt", "dpc",
         "full wave.txt", "dp";
         "Oscilloscope.txt", "test";
};
set(gca,'FontName', "def")
set(gca, 'FontAngle', 'normal')
%%
for fid = 1:2


    partid = files{fid, 2};
    data = sdata.open(files{fid, 1});


    pvi = [1, 3, 5];
    voi = 7;
    f = figure;
    f.Position(3:4) = f.Position(3:4) .* [1.3, 1.4];
    
    subplot('Position', sp1p);
    data.plot(pvi);
    legend boxoff
    pv = data.y(:, pvi);
    [minv, maxv] = srange(pv, 2);
    snapylim([minv*1.2, maxv*1.2])
    plotrange(minv, maxv, "unit","V");
    title("Phase Voltages E_1, E_2, and E_3", 'FontSize',FS1);
    grid on;
    
    subplot('Position', sp2p);
    vo = data.y(:, voi);
    data.plot(voi);
    legend boxoff
    [mivo, mvo] = srange(vo, 3);
    snapylim([0, mvo*1.05]);
    plotrange(mivo, mvo, "unit","V");
    title("Rectifier Output Voltage E_4", 'FontSize',FS1);
    subtitle(sprintf("AVG(E_4) = %.1fV,   RMS(E_4) = %.1fV", mean(vo), rms(vo)), "FontSize",FS2);
    grid on;
    
    saveas(f, sprintf("fig-%s-v", partid), "svg");
    
    clf;
    ioi = 8;
    ids = [2, 4, 6];
    
    f = figure;
    f.Position(3:4) = f.Position(3:4) .* [1.3, 1.4];
    
    
    subplot('Position', sp1p);
    data.plot(ids);
    legend boxoff
    title("Diode Currents I_1, I_2 and I_3", 'FontSize',FS1);
    grid on;
    [mini, maxi] = srange(data.y(:, ids), 3);
    dy = (maxi-mini)/5;
    snapylim([min(0, mini-dy), maxi+dy]);
    
    subplot('Position', sp2p);
    data.plot(ioi);
    legend boxoff
    io = data.y(:, ioi);
    [mini, maxi] = srange(io, 5);
    plotrange(mini, maxi,'unit','A');
    title(sprintf("Rectifier Output Current I_4"), 'FontSize',FS1);
    subtitle(sprintf("AVG(I_4) = %s,   RMS(I_4) = %s", funit(mean(io), "A", 'precision',1), funit(rms(io), "A", 'precision',1)), "FontSize",FS2);
    grid on;
    dy = (maxi-mini)/5;
    snapylim([min(0, mini-dy), maxi+dy]);
    
    saveas(f, sprintf("fig-%s-i", partid), "svg");
end
%%
f = figure;
subplot('Position', [0.1 0.1 0.8, 0.7]);
fid = 4;
partid = files{fid, 2};
data = sdata.open(files{fid, 1});
data.plot([1,3,4]);
legend boxoff
e2 = data.y(:, 3);
e3 = data.y(:, 4);
[min2, max2] = srange(e2, 3);
[min3, max3] = srange(e3, 3);
plotrange(min2, max2, 'unit', "V");
plotrange(min3, max3, 'unit', "V");
title("Dual-Polarity DC Power Supply", 'FontSize',FS1);
subtitle(sprintf("AVG(E_2) = %s,    RMS(E_2) = %s\nAVG(E_3) = %s,    RMS(E_3) = %s", ...
    funit(mean(e2), "V", 'precision',1), funit(rms(e2), "V", 'precision',1),...
    funit(mean(e3), "V", 'precision',1), funit(rms(e3), "V", 'precision',1)), 'FontSize',FS2);
grid on;
saveas(f, sprintf("fig-%s-i", partid), "svg");
%%
f = figure;
subplot('Position', [0.1 0.1 0.8, 0.7]);
fid = 3;
partid = files{fid, 2};
data = sdata.open(files{fid, 1});
data.plot([1,3,4]);
legend boxoff
e2 = data.y(:, 3);
e3 = data.y(:, 4);
[min2, max2] = srange(e2, 3);
[min3, max3] = srange(e3, 3);
plotrange(min2, max2, 'unit', "V");
plotrange(min3, max3, 'unit', "V");
title("Dual-Polarity DC Power Supply with Capacitor", 'FontSize',FS1);
subtitle(sprintf("AVG(E_2) = %s,    RMS(E_2) = %s\nAVG(E_3) = %s,    RMS(E_3) = %s", ...
    funit(mean(e2), "V", 'precision',1), funit(rms(e2), "V", 'precision',1),...
    funit(mean(e3), "V", 'precision',1), funit(rms(e3), "V", 'precision',1)), 'FontSize',FS2);
grid on;
saveas(f, sprintf("fig-%s-i", partid), "svg");
%%
% fid = 4;
% data = sdata.open(files{fid, 1});
% size(data.y)
% data.plot(1:4);

n = 0:14;
di = (1./(14 - 2*n)) .* (factorial(14) ./ (factorial(n) .* factorial(14 - n)))
di2 = ( 1 + sqrt(2) ).^(14 - 2*n) - 1

di3 = di .* di2

% sum(di)