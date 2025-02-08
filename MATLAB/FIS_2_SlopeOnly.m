%% Create Type-2 Sugeno Fuzzy Inference System for OCXO Control
fis = sugfis("Type", "sugeno", "Name", "OCXO_Controller_2");

%% Add Input: Temperature Deviation (OCXO Operating Range: 92°C to 102°C)
fis = addInput(fis, [90 105], "Name", "TempDeviation");  % Slightly extended range

% Type-2 Gaussian MFs for Temperature Deviation
fis = addMF(fis, "TempDeviation", "gauss2mf", [1.5, 90, 2, 93], "Name", "Low");
fis = addMF(fis, "TempDeviation", "gauss2mf", [2, 96, 2, 98], "Name", "Optimal");
fis = addMF(fis, "TempDeviation", "gauss2mf", [1.5, 100, 2, 103], "Name", "High");

%% Add Input: Temperature Slope (Rate of Temperature Change)
fis = addInput(fis, [-0.5 0.5], "Name", "TempSlope"); % °C per second

% Type-2 Gaussian MFs for Temperature Slope
fis = addMF(fis, "TempSlope", "gauss2mf", [0.1, -0.3, 0.2, -0.1], "Name", "Decreasing");
fis = addMF(fis, "TempSlope", "gauss2mf", [0.1, -0.05, 0.2, 0.05], "Name", "Stable");
fis = addMF(fis, "TempSlope", "gauss2mf", [0.1, 0.1, 0.2, 0.3], "Name", "Increasing");

%% Add Output: Power Adjustment (Heater Control)
fis = addOutput(fis, [-1 1], "Name", "PowerAdjust"); % Scaled heater power (-1 to 1)

% Sugeno-style singleton outputs
fis = addMF(fis, "PowerAdjust", "constant", -1, "Name", "LargeDecrease");
fis = addMF(fis, "PowerAdjust", "constant", -0.5, "Name", "SmallDecrease");
fis = addMF(fis, "PowerAdjust", "constant", 0, "Name", "NoChange");
fis = addMF(fis, "PowerAdjust", "constant", 0.5, "Name", "SmallIncrease");
fis = addMF(fis, "PowerAdjust", "constant", 1, "Name", "LargeIncrease");

%% Define Fuzzy Rules
ruleList = [
    "If TempDeviation is Low and TempSlope is Decreasing then PowerAdjust is LargeIncrease"
    "If TempDeviation is Low and TempSlope is Stable then PowerAdjust is SmallIncrease"
    "If TempDeviation is Low and TempSlope is Increasing then PowerAdjust is NoChange"
    "If TempDeviation is Optimal then PowerAdjust is NoChange"
    "If TempDeviation is High and TempSlope is Decreasing then PowerAdjust is NoChange"
    "If TempDeviation is High and TempSlope is Stable then PowerAdjust is SmallDecrease"
    "If TempDeviation is High and TempSlope is Increasing then PowerAdjust is LargeDecrease"
];

fis = addRule(fis, ruleList);

%% Plot FIS Structure
figure;
plotfis(fis);
title("Type-2 Sugeno FIS for OCXO Temperature Control");

%% Save FIS
writeFIS(fis, "OCXO_Type2_Sugeno_2.fis");
