#pragma once
#include<vector>
#include<complex>
#include"linearalgebra.h"

namespace ft{

using cplx = std::complex<double>;
using cvec = std::vector<cplx>;

cvec dft(const cvec& y, int sign = -1);

cvec idft(const cvec& Y);

cvec to_complex(const pp::vector& y);

pp::vector to_real(const cvec& Y);

cvec amplitude_filter(const cvec& Y, double threshold);

cvec lowpass_filter(const cvec& Y, double cutoff_freq, double dt);

cvec fft(const cvec& y, int sign = -1);
 
cvec ifft(const cvec& Y);

cvec convolve(const cvec& signal, const cvec& detector);

cvec deconvolve(const cvec& signal, const cvec& detector);

cvec wiener(const cvec& signal, const cvec& detector, double lambda);

}