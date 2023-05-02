fname = "Slowing Down due to Button";

data = csvread(sprintf("%s.csv", fname));
data(:, 1) = data(:, 1) / 1000;
clf;
% fig = figure;
% set(fig,'defaultAxesColorOrder',[[0 0 0]; [0 0 0]]);
yyaxis left
plot(data(:, 1), data(:, 2));
hold on;
plot(data(:, 1), data(:, 5), 'Color', [0.2, 0.7, 0]);


xlabel("time (s)");
ylabel("RPM");

hold on;
yyaxis right
plot(data(:, 1), 50 + data(:, 4), 'Color', [1, 0.32, 0]);
ylabel("Duty Cycle")

legend(["RPM", "Goal RPM", "Duty Cycle"]);

title(fname);
%subtitle("p = 0.02211 load at t \approx [7, 15]");