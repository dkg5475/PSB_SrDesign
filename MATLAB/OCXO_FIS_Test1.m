%% Load the Type-2 Sugeno FIS
fis = readfis("OCXO_Type2_Sugeno_1.fis");

%% Define Test Input Ranges
numSamples = 50;
TempDeviationRange = linspace(90, 105, numSamples); % Extended temp range
TempSlopeRange = linspace(-0.5, 0.5, numSamples); % °C per second

%% Meshgrid for 3D Evaluation
[TDev, TSlope] = meshgrid(TempDeviationRange, TempSlopeRange);
FIS_Output = zeros(size(TDev));

%% Evaluate FIS for Each Input Combination
for i = 1:numel(TDev)
    inputVals = [TDev(i), TSlope(i)];
    FIS_Output(i) = evalfis(fis, inputVals);
end

%% Plot the FIS Response
figure;
surf(TDev, TSlope, FIS_Output);
xlabel("Temperature Deviation (°C)");
ylabel("Temperature Slope (°C/s)");
zlabel("Power Adjustment");
title("FIS Response for OCXO Temperature Control");
colorbar;

%% Test Specific Scenarios
TestCases = [
    92, -0.3;  % Cold and cooling fast
    92, 0;     % Cold but stable
    96, 0;     % Optimal and stable
    100, 0.3;  % Hot and heating up
    103, 0.5   % Too hot and increasing temp
];

numTests = size(TestCases, 1);
TestResults = zeros(numTests, 1);

for i = 1:numTests
    TestResults(i) = evalfis(fis, TestCases(i, :));
end

%% Display Test Results
fprintf("\nOCXO Controller Simulation Results:\n");
for i = 1:numTests
    fprintf("TempDeviation: %.1f°C, TempSlope: %.2f°C/s -> PowerAdjust: %.2f\n", ...
        TestCases(i, 1), TestCases(i, 2), TestResults(i));
end
