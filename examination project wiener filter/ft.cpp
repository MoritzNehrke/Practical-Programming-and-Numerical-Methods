#include"ft.h"
#define _USE_MATH_DEFINES
#include<cmath>

namespace ft{

cvec dft(const cvec& y, int sign){
	int N = y.size();
	cvec Y(N);
	for(int k=0; k<N; k++){
		cplx sum = 0;
		for(int n=0; n<N; n++){
			double angle = sign * 2*M_PI * n*k / N;
			sum += y[n] * std::polar(1.0, angle);
		}
		Y[k] = sum;
	}
	return Y;
}

cvec idft(const cvec& Y){
	int N = Y.size();
	cvec y = dft(Y, +1);
	for(int n=0; n<N; n++){
        y[n] /= N;
    }
	return y;
}

cvec to_complex(const pp::vector& y){
	cvec z(y.size());
	for(int n=0; n<y.size(); n++) z[n] = cplx(y[n], 0.0);
	return z;
}

pp::vector to_real(const cvec& Y){
	pp::vector y(Y.size());
	for(int n=0; n<y.size(); n++) y[n] = Y[n].real();
	return y;
}

cvec amplitude_filter(const cvec& Y, double threshold){
	int N = Y.size();
	cvec Yf = Y;
	for(int k=0; k<N; k++)
		if(std::abs(Yf[k]) < threshold) Yf[k] = 0;
	return Yf;
}
 
cvec lowpass_filter(const cvec& Y, double cutoff_freq, double dt){
	int N = Y.size();
	cvec Yf = Y;
	for(int k=0; k<N; k++){
		int kk = k;
        if(k>=N/2){
            kk = N - k;
        }
		double freq = kk/(N*dt);
		if(freq > cutoff_freq) Yf[k] = 0;
	}
	return Yf;
}

cvec fft(const cvec& y, int sign){
	int N = y.size();
	if(N == 1) return y;
 
	if(N % 2 != 0) return dft(y, sign);
 
	int M = N/2;
	cvec even(M), odd(M);
	for(int m=0; m<M; m++){
		even[m] = y[2*m];
		odd[m]  = y[2*m+1];
	}

	cvec ce = fft(even, sign);
	cvec co = fft(odd, sign);

	cvec c(N);
	for(int k=0; k<M; k++){
		cplx w = std::polar(1.0, sign*2*M_PI*k/N) * co[k];
		c[k]   = ce[k] + w;
		c[k+M] = ce[k] - w;
	}
	return c;
}

cvec ifft(const cvec& Y){
	int N = Y.size();
	cvec y = fft(Y, +1);
	for(int n=0; n<N; n++) y[n] /= N;
	return y;
}

cvec convolve(const cvec& signal, const cvec& detector){
	ft::cvec Y = fft(signal);
	ft::cvec H = fft(detector);
	int N = signal.size();
	ft::cvec S(N);
	for(int k=0; k<N; k++) S[k] = Y[k] * H[k];
	return ifft(S);
}

cvec deconvolve(const cvec& signal, const cvec& detector){
	ft::cvec S = fft(signal);
	ft::cvec H = fft(detector);
	int N = signal.size();
	ft::cvec Y(N);
	for(int k=0; k<N; k++) Y[k] = S[k] / H[k];
	return ifft(Y);
}

cvec wiener(const cvec& signal, const cvec& detector, double lambda){
	ft::cvec S = fft(signal);
	ft::cvec H = fft(detector);
	int N = signal.size();
	ft::cvec Y(N);
	for(int k=0; k<N; k++){
		double Habs2 = std::norm(H[k]);
		Y[k] = std::conj(H[k])*S[k]/(Habs2 + lambda);
	}
	return ifft(Y);
}

}