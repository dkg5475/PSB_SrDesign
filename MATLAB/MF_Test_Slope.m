x = -1:0.01:1; % Slope range

yDec = gauss2mf(x, [0.1, -1, 0.1, -0.35]);
yStable = gauss2mf(x, [0.1, -0.03, 0.1, 0.03]);
yInc = gauss2mf(x, [0.1, 0.35, 0.1, 1]);

% Plot Membership Functions
figure; hold on;
plot(x, yDec, 'b', 'LineWidth', 2);
plot(x, yStable, 'g', 'LineWidth', 2);
plot(x, yInc, 'r', 'LineWidth', 2);

legend("Decreasing", "Stable", "Increasing");
xlabel("Temperature Slope (°C/sec)");
ylabel("Membership Degree");
title("Smooth Gaussian Membership Functions for Temperature Slope");
grid on;
