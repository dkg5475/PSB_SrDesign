function output = evaluate_fis_fixed(TempDeviation, TempSlope)
    persistent fisCG;
    
    if isempty(fisCG)
        % Load preprocessed FIS data for code generation
        fisCG = coder.load('fisData.mat', 'fisCG');
    end

    % Convert inputs to fixed-point (Q15 format) inside the function
    TempDeviation = fi(TempDeviation, 1, 16, 15); 
    TempSlope = fi(TempSlope, 1, 16, 15);

    % Evaluate the FIS
    input = [TempDeviation, TempSlope]; 
    output = evalfis(fisCG.fisCG, double(input)); % Convert back to double for evalfis
end
