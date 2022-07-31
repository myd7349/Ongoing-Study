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

subplot(4,2,1);
plot(t, S);
title('Original signal');

Y = fft(S);
Amp = abs(Y);
Amp(1) = Amp(1)/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)/(L/2);
Amp(FFT_size/2) = Amp(FFT_size/2)/L;
Amp = Amp(1:FFT_size/2);

subplot(4,2,2);
plot(Fre,Amp);
title('Amplitude');

subplot(4,2,3);
plot(t, S_noise);
title('Signal with noise(25Hz+50Hz)');

Y = fft(S_noise);
Amp = abs(Y);
Amp = Amp/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)*2;
Amp = Amp(1:FFT_size/2);

subplot(4,2,4);
plot(Fre,Amp);
title('Amplitude');

% Lowpass
% Butterworth
% Order: 2
% Fs: 200
% Fc: 20
% Structure: Direct-Form II, Single Section

NUM = [0.06745527388907, 0.1349105477781, 0.06745527388907];
DEN = [1,-1.14298050254,0.4128015980962];
S_filtered = filter(NUM,DEN,S_noise);
subplot(4,2,5);
plot(t, S_filtered);
title('Filtered signal');

Y = fft(S_filtered);
Amp = abs(Y);
Amp = Amp/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)*2;
Amp = Amp(1:FFT_size/2);

subplot(4,2,6);
plot(Fre,Amp);
title('Amplitude');

% Lowpass
% Butterworth
% Order: 2
% Fs: 200
% Fc: 20
% Structure: Direct-Form II, Second-Order Sections

NUM = [1,2,1];
DEN = [1,-1.14298050254,0.4128015980962];
Gain = 0.06745527388907;

S_filtered2 = zeros(size(S));

last_1 = 0;
last_2 = 0;

for i=1:L
    last = Gain * S_noise(i) - DEN(2)*last_1 - DEN(3)*last_2;
    S_filtered2(i) =  NUM(1)*last + NUM(2)*last_1 + NUM(3)*last_2;
    
    last_2 = last_1;
    last_1 = last;
end

subplot(4,2,7);
plot(t, S_filtered2);
title('Filtered signal');

Y = fft(S_filtered2);
Amp = abs(Y);
Amp = Amp/L;
Amp(2:FFT_size/2-1) = Amp(2:FFT_size/2-1)*2;
Amp = Amp(1:FFT_size/2);

subplot(4,2,8);
plot(Fre,Amp);
title('Amplitude');

d = S_filtered2 - S_filtered

% References:
% doc fft
% [Matlab滤波器的设计](https://blog.csdn.net/qq_41389378/article/details/126927254)
% [频谱分析-FFT之后的那些事情](https://blog.csdn.net/czyt1988/article/details/84995295)
% [42 MATLAB Beginners Tutorial- Low Pass Filter Design Using FDA Tool aka Filter Designer in MATLAB](https://www.youtube.com/watch?v=MT0Q7RqhUBA)
