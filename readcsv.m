%{
// Helpful Links:
// https://www.mathworks.com/matlabcentral/answers/108616-plotting-data-from-a-csv-file
// https://www.mathworks.com/matlabcentral/answers/291608-how-to-plot-a-large-data-set-in-matlab#answer_226317

// ECE 258 Senior Design Project
// Gabriel Siegel
// This MATLAB program should read in a CSV file and then plot it
%}

clc;
clear all;
close all;

data=csvread('tek0059ALL.csv', 21, 0); % read a file named tek0059ALL.csv from row 22 column 1 onward

x=data(:,1); % put the first data column in x, likely time
y1=10*data(:,2); % put the second data column in y1, likely voltage
y2=1000*data(:,3); % put the second data column in y2, likely current

plot(x,y1); % plot x and y1
%xlabel('Time (~seconds)');
%ylabel('DEA Voltage');
%title('Plot of Voltage over Time');

% If you would like to place both voltage and current on the same plot un comment the next line
hold on

plot(x,y2); % plot x and y2
xlabel('Time (~seconds)');
ylabel('DEA Response (Volts and Milliamps)');
title('Plots of Current over Time and Voltage over Time');
lgd = legend({'DEA Voltage','Current Response'}, "FontSize",12);

% If you would like to place both voltage and current on the same plot un comment the next line
hold off