x = -1:0.001:1; % Higher resolution for better accuracy

% Define Gaussian membership functions
yDec = gauss2mf(x, [0.2, -1, 0.2, -0.35]);
yStable = gauss2mf(x, [0.2, -0.03, 0.2, 0.03]);
yInc = gauss2mf(x, [0.2, 0.35, 0.2, 1]);

% Find intersection points
%idx_dec_stable = find(abs(yDec - yStable) < 0.001); % Dec-Stable intersection
%idx_stable_inc = find(abs(yStable - yInc) < 0.001); % Stable-Inc intersection

% Extract x-coordinates of intersection points
%x_dec_stable = x(idx_dec_stable);
%x_stable_inc = x(idx_stable_inc);

% Plot the membership functions
figure; hold on;

plot(x, yDec, 'b', 'LineWidth', 2);
plot(x, yStable, 'g', 'LineWidth', 2);
plot(x, yInc, 'r', 'LineWidth', 2);

% Mark intersection points
%scatter(x_dec_stable, yStable(idx_dec_stable), 60, 'm', 'filled', 'DisplayName', 'Dec-Stable Intersection');
%scatter(x_stable_inc, yStable(idx_stable_inc), 60, 'k', 'filled', 'DisplayName', 'Stable-Inc Intersection');

legend("Decreasing", "Stable", "Increasing", "Dec-Stable Intersection", "Stable-Inc Intersection");
xlabel("Temperature Slope (°C/sec)");
ylabel("Membership Degree");
title("Gaussian Membership Functions for Temperature Slope");
grid on;
hold off;
