%% Create Type-2 Sugeno Fuzzy Inference System for OCXO Control
fis = sugfis("Type", "sugeno", "Name", "OCXO_Controller_1");

%% Add Input: Temperature Deviation (OCXO Operating Range: -40°C to 120°C)
fis = addInput(fis, [-40 120], "Name", "TempReadings");  % Possible range of temp values

T_set = 97.00; % example ideal setpt temp
coldLower = -40; % always the lower bound of the range of temps
coldUpper = T_set - 8; % 97 - 8 = 89
optimalLower = T_set - 0.02;
optimalUpper = T_set + 0.02;
hotLower = T_set + 8;
hotUpper = 120; %always the upper bound of possible temps?

% Type-2 Gaussian MFs for Temperature Deviation
fis = addMF(fis, "TempReadings", "gauss2mf", [2.5, coldLower, 2.5, coldUpper], "Name", "Cold");
fis = addMF(fis, "TempReadings", "gauss2mf", [1, optimalLower, 1, optimalUpper], "Name", "Optimal");
fis = addMF(fis, "TempReadings", "gauss2mf", [2.5, hotLower, 2.5, hotUpper], "Name", "Hot");

%% Add Input: Temperature Slope (Rate of Temperature Change)
fis = addInput(fis, [-1 1], "Name", "TempSlope"); % °C per second

% Type-2 Gaussian MFs for Temperature Slope
fis = addMF(fis, "TempSlope", "gauss2mf", [0.2, -1, 0.2, -0.35], "Name", "Decreasing");
fis = addMF(fis, "TempSlope", "gauss2mf", [0.2, -0.03, 0.2, 0.03], "Name", "Stable");
fis = addMF(fis, "TempSlope", "gauss2mf", [0.2, 0.35, 0.2, 1], "Name", "Increasing");

%% Add Output: Power Adjustment (Heater Control)

fis = addOutput(fis, [0 2], "Name", "PowerAdjust"); % Scaled heater power (0 to 2)
% heater power is based on the difference from the last heater level
% so if the previous state of the heater was 2.0V, and we want to turn off
% the heater, we would say that the power adjustment is 2.0 V (since 2 -2 =
% 0 and 0V turns the heater off)

% LargeDecrease: take 1.5V off previous level
% SmallDecrease: take 0.75V off previous level
% NoChange: take 0V off previous level
% SmallIncrease: take -0.5V off previous level (add 0.5V)
% LargeIncrease: take -1V off previous level (add 1V)
% VeryLargeIncrease: take -1.5V off previous level (add 1.5V)

% Sugeno-style singleton outputs

fis = addMF(fis, "PowerAdjust", "constant", 1.5, "Name", "LargeDecrease"); 
fis = addMF(fis, "PowerAdjust", "constant", 0.75, "Name", "SmallDecrease");
fis = addMF(fis, "PowerAdjust", "constant", 0, "Name", "NoChange");
fis = addMF(fis, "PowerAdjust", "constant", -0.5, "Name", "SmallIncrease");
fis = addMF(fis, "PowerAdjust", "constant", -0.75, "Name", "LargeIncrease");
fis = addMF(fis, "PowerAdjust", "constant", -1.5, "Name", "VeryLargeIncrease");

%% Define Fuzzy Rules

ruleList = [
    "If TempReadings is Cold and TempSlope is Decreasing then PowerAdjust is VeryLargeIncrease"
    "If TempReadings is Cold and TempSlope is Stable then PowerAdjust is LargeIncrease"
    "If TempReadings is Cold and TempSlope is Increasing then PowerAdjust is SmallIncrease"

    "If TempReadings is Optimal then PowerAdjust is NoChange"
    
    "If TempReadings is Hot and TempSlope is Decreasing then PowerAdjust is NoChange"
    "If TempReadings is Hot and TempSlope is Stable then PowerAdjust is SmallDecrease"
    "If TempReadings is Hot and TempSlope is Increasing then PowerAdjust is LargeDecrease"
];

fis = addRule(fis, ruleList);

%% Plot FIS Structure

figure;
plotfis(fis);
title("Type-2 Sugeno FIS for OCXO Temperature Control");

%% Save FIS
writeFIS(fis, "OCXO_Type2_Sugeno_1.fis"); 
% /home/dan/Documents/MATLAB/ add this when using Ubuntu