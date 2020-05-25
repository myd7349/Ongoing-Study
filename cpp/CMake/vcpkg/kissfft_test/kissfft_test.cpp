/*
Fs = 1000;                    % Sampling frequency
T = 1/Fs;                     % Sample time
L = 1000;                     % Length of signal
t = (0:L-1)*T;                % Time vector
% Sum of a 50 Hz sinusoid and a 120 Hz sinusoid
x = 0.7*sin(2*pi*50*t) + sin(2*pi*120*t);
y = x + 2*randn(size(t));     % Sinusoids plus noise
plot(Fs*t(1:50),y(1:50))
title('Signal Corrupted with Zero-Mean Random Noise')
xlabel('time (milliseconds)')


NFFT = 2^nextpow2(L); % Next power of 2 from length of y
Y = fft(y,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2+1);

% Plot single-sided amplitude spectrum.
plot(f,2*abs(Y(1:NFFT/2+1)))
title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
*/
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <numeric>
#include <valarray>
#include <vector>

#include <kiss_fft.h>

constexpr int Fs = 1000;
constexpr float T = 1.0f / Fs;
constexpr int L = 1000;

// github::concurrentqueue
template <typename T>
static inline T ceil_to_pow_2(T x) {
  static_assert(
      std::is_integral<T>::value && !std::numeric_limits<T>::is_signed,
      "ceil_to_pow_2 is intended to be used only with unsigned integer types");

  // Adapted from
  // http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
  --x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  for (std::size_t i = 1; i < sizeof(T); i <<= 1) {
    x |= x >> (i << 3);
  }
  ++x;
  return x;
}

int main() {
  std::valarray<float> t(L);
  std::iota(std::begin(t), std::end(t), 0);
  t *= T;

  // Sum of a 50 Hz sinusoid and a 120 Hz sinusoid
  auto x = 0.7f * std::sin(2 * static_cast<float>(M_PI) * 50 * t) +
           std::sin(2 * static_cast<float>(M_PI) * 120 * t);
  auto y = x;

  auto nfft = static_cast<int>(ceil_to_pow_2(static_cast<unsigned int>(L)));

  auto fft_config = kiss_fft_alloc(nfft, 0, nullptr, 0);
  std::vector<kiss_fft_cpx> fft_in(nfft);
  std::transform(std::cbegin(y), std::cend(y), fft_in.begin(), [](float v) {
    kiss_fft_cpx cpx{};
    cpx.r = v;
    return cpx;
  });
  std::vector<kiss_fft_cpx> fft_out(nfft);
  kiss_fft(fft_config, fft_in.data(), fft_out.data());
  for (const auto &v : fft_out)
    std::cout << v.r / L << " + " << v.i / L << "i\n";
  kiss_fft_free(fft_config);

  return 0;
}

// References:
// https://stackoverflow.com/questions/1602451/c-valarray-vs-vector
// https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
// https://stackoverflow.com/questions/364985/algorithm-for-finding-the-smallest-power-of-two-thats-greater-or-equal-to-a-giv
