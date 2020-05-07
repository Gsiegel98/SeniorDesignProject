%{
// Helpful Links:
// https://www.mathworks.com/help/supportpkg/arduinoio/ref/arduino.html
// https://www.mathworks.com/help/supportpkg/arduinoio/ref/readvoltage.html

// ECE 258 Senior Design Project
// Gabriel Siegel
// This MATLAB program should establish an arduino and read in it's analog voltage at a port
%}

clc;
clear all;
close all;

DEAVoltage = zeros(100,1); % Create an array to hold a column of 100 data points
Time = zeros(100,1); % Create an array to hold a column of 100 data points
a = arduino;    % a — Arduino hardware connection
                % A4 pin — Analog pin number

for i = 0:100
   DEAVoltage[i,1] = readVoltage(a,'A4'); %//outputs the voltage read from pin A4
   Time[i,1] = i; % outputs the voltage read from pin A4
   pause(1.0); % wait one second before reading next value
end

T = table(Time, DEAVoltage); % create a table T so we can export it to a text file

writetable(T,'tabledata.txt','Delimiter','\t'); % write T to a textfile

x = Time(:, 1);
y = DEAVoltage(:, 1);
plot(x,y); % Also plot time vs voltage
xlabel('Time (~seconds)');
ylabel('DEA Voltage');
title('Plot of Voltage over Time');