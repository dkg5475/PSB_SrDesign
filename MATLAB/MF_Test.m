x = -40:0.5:120;
T_set = 97.00; % example ideal setpt temp
coldLower = -40; % always the lower bound of the range of temps
coldUpper = T_set - 8; % 97 - 8 = 89
optimalLower = T_set - 0.02;
optimalUpper = T_set + 0.02;
hotLower = T_set + 8;
hotUpper = 120; %always the upper bound of possible temps?

yCold = gauss2mf(x, [2.5, coldLower, 2.5, coldUpper]);
yOptimal = gauss2mf(x, [1, optimalLower, 1, optimalUpper]);
yHot = gauss2mf(x, [2.5, hotLower, 2.5, hotUpper]);

figure; 
hold on; 

plot(x, yCold, 'b', 'LineWidth', 2);
plot(x, yOptimal, 'g', 'LineWidth', 2);
plot(x, yHot, 'r', 'LineWidth', 2);

legend("Cold", "Optimal", "Hot");
xlabel("Temperature Deviation (°C)");
ylabel("Membership Degree");
title("Gaussian Membership Functions for OCXO Control");
grid on;

