% script for testing the membership functions and what parts of temp range
% they cover
x = -40:0.5:120; %temp range
T_set = 97.00; % example ideal setpt temp
vColdLower = -40; % always the very lower bound of possible temps?
vColdUpper = T_set - 50; % 47 
coldLower = vColdUpper + 3; % 47
coldUpper = T_set - 8; % 87
optimalLower = T_set - 0.02;
optimalUpper = T_set + 0.02;
hotLower = T_set + 8;
hotUpper = 120; %always the upper bound of possible temps?


y_vCold = gauss2mf(x, [3, vColdLower, 3, vColdUpper]);
y_Cold = gauss2mf(x, [2.5, coldLower, 2.5, coldUpper]);
y_Optimal = gauss2mf(x, [1, optimalLower, 1, optimalUpper]);
y_Hot = gauss2mf(x, [2.5, hotLower, 2.5, hotUpper]);


figure;
hold on;
plot(x, y_vCold, 'c', 'LineWidth', 2);
plot(x, y_Cold, 'b', 'LineWidth', 2);
plot(x, y_Optimal, 'g', 'LineWidth', 2);
plot(x, y_Hot, 'r', 'LineWidth', 2);

legend("Very cold", "cold", "good", "high");
xlabel("Temperature Deviation (°C)");
ylabel("Membership Degree");
title("Gaussian Membership Functions for Temperature");
grid on;
