%% Set Desired Setpoint Temperature
T_set = 96;  % Modify this value as needed

%% Generate FIS Using Function
fis = FIS_Test_1(T_set);

%% Define Test Inputs
% Define a range of temperature readings and slopes to test
TempReadings = linspace(-40, 120, 50); % From -40°C to 120°C
TempSlopes = linspace(-1, 1, 10); % From -1°C/s to 1°C/s

%% Evaluate the FIS
PowerAdjustResults = zeros(length(TempReadings), length(TempSlopes));

for i = 1:length(TempReadings)
    for j = 1:length(TempSlopes)
        inputValues = [TempReadings(i), TempSlopes(j)];
        PowerAdjustResults(i, j) = evalfis(fis, inputValues);
    end
end

%% Plot Results
figure;
surf(TempSlopes, TempReadings, PowerAdjustResults);
xlabel("Temperature Slope (°C/s)");
ylabel("Temperature Reading (°C)");
zlabel("Power Adjustment (V)");
title(sprintf("Fuzzy Inference System Output for OCXO Control (T_{set} = %.2f°C)", T_set));
colorbar;
grid on;

%% Single Test Cases (for debugging)
disp("Testing specific input cases:");
testCases = [
    -40, -1;   % Extreme cold, rapidly decreasing
    -40, 0;    % Extreme cold, stable
    -40, 1;    % Extreme cold, increasing
    
    -20, -0.5; % Very cold, cooling
    -20, 0.5;  % Very cold, warming
    
    10, -0.5;  % Cold, cooling
    10, 0.5;   % Cold, warming
    
    40, -0.2;  % Cold, slight cooling
    40, 0.2;   % Cold, slight warming
    
    60, -0.1;  % Approaching optimal, cooling
    60, 0.1;   % Approaching optimal, warming
    
    85, -0.05; % Near-optimal, slight cooling
    85, 0.05;  % Near-optimal, slight warming
    
    97, -0.1;  % Ideal temp, slight cooling
    97, 0;     % Ideal temp, stable
    97, 0.1;   % Ideal temp, slight warming
    
    105, -0.5; % Slightly hot, cooling
    105, 0.5;  % Slightly hot, warming
    
    115, -0.2; % Very hot, cooling
    115, 0.2;  % Very hot, warming
    
    120, -1;   % Extreme hot, rapidly cooling
    120, 0;    % Extreme hot, stable
    120, 1;    % Extreme hot, rapidly increasing
];

for i = 1:size(testCases, 1)
    result = evalfis(fis, testCases(i, :));
    fprintf("Temp: %.2f°C, Slope: %.2f°C/s -> Power Adjust: %.2fV\n", ...
            testCases(i, 1), testCases(i, 2), result);
end
