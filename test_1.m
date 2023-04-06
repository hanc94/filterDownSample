clear all;
close all;
clc;
%% prueba Tarea 1. 
fs=44.1e3;
fc=5512.5;
f=3e3;
t=0:1/fs:1;
s=sin(2*pi*f*t);
M=1000;
n=-M:M;
Omc=2*pi*fc/fs;
h_LP=Omc/pi*sinc(Omc*n/pi);
[H_LP,Om]=freqz(h_LP,1,65536);
y=conv(s,h_LP);
y_user=convUser(s,h_LP);
y1_user=Diezm(y_user);
y1=downsample(y,4);