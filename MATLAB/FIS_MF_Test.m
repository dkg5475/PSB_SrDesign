% Testing std deviation values for membership functions

% Define temperature range
x = -40:0.5:120; % Temperature range
T_set = 97; % Example ideal setpoint temperature

% Define temperature ranges for membership functions
vColdLower = -40;
vColdUpper = T_set - 50; % 77°C
coldLower = vColdUpper;
coldUpper = T_set - 0.02;
optimalLower = coldUpper;
optimalUpper = T_set + 0.02;
hotLower = optimalUpper;
hotUpper = 120;

% Different sigma values for comparison
sigma_values = [1, 2, 3];

figure;
hold on;
colors = {'c', 'b', 'g', 'r'}; % Colors for different MFs
labels = {'Very Cold', 'Cold', 'Optimal', 'Hot'};

% Loop through different sigma values
for i = 1:length(sigma_values)
    sigma = sigma_values(i);

    % Define membership functions with varying sigma
    y_vCold = gauss2mf(x, [sigma, vColdLower, sigma + 1, vColdUpper]);
    y_Cold = gauss2mf(x, [sigma + 0.5, coldLower, sigma + 1.5, coldUpper]);
    y_Optimal = gauss2mf(x, [sigma, optimalLower, sigma, optimalUpper]);
    y_Hot = gauss2mf(x, [sigma + 0.5, hotLower, sigma + 1.5, hotUpper]);

    % Plot each MF with its corresponding sigma
    plot(x, y_vCold, strcat(colors{1}, '--'), 'LineWidth', 1.5);
    plot(x, y_Cold, strcat(colors{2}, '--'), 'LineWidth', 1.5);
    plot(x, y_Optimal, strcat(colors{3}, '--'), 'LineWidth', 1.5);
    plot(x, y_Hot, strcat(colors{4}, '--'), 'LineWidth', 1.5);
end

% Plot labels and legend
legend(["VC σ=1", "C σ=1", "O σ=1", "H σ=1", ...
        "VC σ=2", "C σ=2", "O σ=2", "H σ=2", ...
        "VC σ=3", "C σ=3", "O σ=3", "H σ=3"]);

xlabel("Temperature Deviation (°C)");
ylabel("Membership Degree");
title("Effect of Different Sigma Values on Membership Functions");
grid on;
hold off;
