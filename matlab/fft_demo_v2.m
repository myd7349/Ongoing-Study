Fs = 200;            % Sampling frequency                    
T = 1/Fs;             % Sampling period       
L = 1500;             % Length of signal
t = (0:L-1)*T;        % Time vector

S = sin(2*pi*1*t) + sin(2*pi*2*t);
noise = sin(2*pi*25*t) + sin(2*pi*50*t);
S_noise = S + noise;

FFT_size = L;
Fre = (0:FFT_size-1)*Fs/FFT_size;
Fre = Fre(1:FFT_size/2);

subplot(2,2,1);
plot(t, S);
title('Original signal');

Y = fft(S);
Amp = abs(Y);
Amp(1) = Amp(1)/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)/(L/2);
Amp(FFT_size/2) = Amp(FFT_size/2)/L;
Amp = Amp(1:FFT_size/2);

subplot(2,2,2);
plot(Fre,Amp);
title('Amplitude');

subplot(2,2,3);
plot(t, S_noise);
title('Signal with noise(25Hz+50Hz)');

Y = fft(S_noise);
Amp = abs(Y);
Amp = Amp/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)*2;
Amp = Amp(1:FFT_size/2);

subplot(2,2,4);
plot(Fre,Amp);
title('Amplitude');

% References:
% doc fft
% [频谱分析-FFT之后的那些事情](https://blog.csdn.net/czyt1988/article/details/84995295)
