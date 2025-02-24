x = -40:0.01:120; % Increased resolution for better accuracy
T_set = 97.00; % Example ideal setpoint temperature

% Define temperature ranges
coldLower = -40;
coldUpper = T_set - 8;
optimalLower = T_set - 0.02;
optimalUpper = T_set + 0.02;
hotLower = T_set + 8;
hotUpper = 120;

% Generate Gaussian membership functions
yCold = gauss2mf(x, [2.5, coldLower, 2.5, coldUpper]);
yOptimal = gauss2mf(x, [1, optimalLower, 1, optimalUpper]);
yHot = gauss2mf(x, [2.5, hotLower, 2.5, hotUpper]);

% Find intersection points
% idx_cold_optimal = find(abs(yCold - yOptimal) < 0.001); % Cold-Optimal intersection
% idx_optimal_hot = find(abs(yOptimal - yHot) < 0.001);   % Optimal-Hot intersection

% Extract x-coordinates of intersection points
x_cold_optimal = x(idx_cold_optimal);
x_optimal_hot = x(idx_optimal_hot);

% Plot the membership functions
figure; 
hold on; 

plot(x, yCold, 'b', 'LineWidth', 2);
plot(x, yOptimal, 'g', 'LineWidth', 2);
plot(x, yHot, 'r', 'LineWidth', 2);

% Mark intersection points
% scatter(x_cold_optimal, yOptimal(idx_cold_optimal), 60, 'm', 'filled', 'DisplayName', 'Cold-Optimal Intersection');
% scatter(x_optimal_hot, yOptimal(idx_optimal_hot), 60, 'k', 'filled', 'DisplayName', 'Optimal-Hot Intersection');

legend("Cold", "Optimal", "Hot", "Cold-Optimal Intersection", "Optimal-Hot Intersection");
xlabel("Temperature (°C)");
ylabel("Membership Degree");
title("Gaussian Membership Functions for Individual Temperature Readings");
grid on;
hold off;
