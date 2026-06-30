#define _USE_MATH_DEFINES
#include<cmath>
#include<fstream>
#include<random>
#include"linearalgebra.h"
#include"ft.h"

double wiener_phi(const pp::vector& p, const ft::cvec& signal, const ft::cvec& detector, const pp::vector& reference){
    double lambda = std::pow(10.0, p[0]);
    ft::cvec yw   = ft::wiener(signal, detector, lambda);
    double diff2   = 0;
    for(int n=0; n<reference.size(); n++){
        double diff = yw[n].real() - reference[n];
        diff2 += diff*diff;
    }
    return diff2 / reference.size();
}

int main(){

    //--------------------------------------------------------------------------------------
    // Step 1: generate a noisy test signal
    //--------------------------------------------------------------------------------------

	int N = std::pow(2,8);
	double T = 1.0;
    double nT = 3.0;
    double duration = nT*T;
	double noise_strength = 0.3;

	pp::vector x(N), y(N);

	std::mt19937 gen(1234);
	std::normal_distribution<double> noise(0.0, noise_strength);

	for(int n=0; n<N; n++){
		double xn = n*duration/N;
		x[n] = xn;
		y[n] = std::cos(2*M_PI*xn/T) + noise(gen);
	}

	std::ofstream out1("noisysignal.dat");
	for(int n=0; n<N; n++)
		out1 << x[n] << " " << y[n] << "\n";
	out1.close();

    //--------------------------------------------------------------------------------------
    // Step 1.1: implement a DFT and inverse DFT routine and apply it to the test signal
    //--------------------------------------------------------------------------------------

    {
    double dt = duration/N;
    
    ft::cvec yc = ft::to_complex(y);
    ft::cvec Y = ft::dft(yc);
	pp::vector y_back = ft::to_real(ft::idft(Y));

    std::ofstream out2("dftnoisysignal.dat");
    for(int k=0; k<N; k++){
        double freq = k/(N*dt);
        out2 << x[k] << " " << freq << " " << std::abs(Y[k]) << " " << y_back[k] << "\n";
    }
    out2.close();
    
    //--------------------------------------------------------------------------------------
    // Step 1.2: try an apmlitude and frequency filter to remove the noise 
    //--------------------------------------------------------------------------------------

    double amp_cutoff = 30.0;
    ft::cvec Y_amp = ft::amplitude_filter(Y, amp_cutoff);
    pp::vector y_amp_filtered = ft::to_real(ft::idft(Y_amp));
 
    double freq_cutoff = 1.5;
    ft::cvec Y_freq = ft::lowpass_filter(Y, freq_cutoff, dt);
    pp::vector y_freq_filtered = ft::to_real(ft::idft(Y_freq));
 
    std::ofstream out3("filteredsignal.dat");
    for(int n=0; n<N; n++)
        out3 << x[n] << " " << y[n] << " " << y_amp_filtered[n] << " " << y_freq_filtered[n] << "\n";
    out3.close();
    }

    //--------------------------------------------------------------------------------------
    // Step 1.3: implement a FFT and inverse FFT routine and apply it to the test signal
    //--------------------------------------------------------------------------------------

    {
    double dt = duration/N;

    ft::cvec yc = ft::to_complex(y);
    ft::cvec Y = ft::fft(yc);
	pp::vector y_back = ft::to_real(ft::ifft(Y));

    std::ofstream out2("fftnoisysignal.dat");
    for(int k=0; k<N; k++){
        double freq = k/(N*dt);
        out2 << x[k] << " " << freq << " " << std::abs(Y[k]) << " " << y_back[k] << "\n";
    }
    out2.close();
    }

    //--------------------------------------------------------------------------------------
    // Step 1.4: compare the runtime of the DFT and FFT routine
    //--------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------
    // Step 2: generate a more difficult test signal (Breit-Wigner peak)
    //--------------------------------------------------------------------------------------

    int Nbw = std::pow(2,9);
    double x0 = 5.0;
    double Gamma = 1.0;
    double A = 1.0;
    double xmin = 0.0;
    double xmax = 10.0;
    double dx = (xmax - xmin) / Nbw;
    double bw_noise = 0.05;

    pp::vector xbw(Nbw), ybw_clean(Nbw), ybw_noisy(Nbw);
    std::normal_distribution<double> bwnoise(0.0, bw_noise);
 
    for(int n=0; n<Nbw; n++){
        double xn = xmin + n*dx;
        xbw[n] = xn;
        double denom = (xn-x0)*(xn-x0) + (Gamma/2)*(Gamma/2);
        ybw_clean[n] = A*(Gamma/2)*(Gamma/2)/denom;
        ybw_noisy[n] = ybw_clean[n] + bwnoise(gen);
    }

    {
    ft::cvec yc = ft::to_complex(ybw_noisy);
    ft::cvec Y = ft::fft(yc);

    double amp_cutoff = 5.0;
    ft::cvec Y_amp = ft::amplitude_filter(Y, amp_cutoff);
    pp::vector y_amp_filtered = ft::to_real(ft::ifft(Y_amp));
 
    double freq_cutoff = 1.5;
    ft::cvec Y_freq = ft::lowpass_filter(Y, freq_cutoff, dx);
    pp::vector y_freq_filtered = ft::to_real(ft::ifft(Y_freq));

 
    std::ofstream outbw("breitwigner.dat");
    for(int n=0; n<Nbw; n++)
        outbw << xbw[n] << " " << ybw_clean[n] << " " << ybw_noisy[n] << " " << y_amp_filtered[n] << " " << y_freq_filtered[n] << "\n";
    outbw.close();
    }

    //--------------------------------------------------------------------------------------
    // Step 2.1: convolve signal with a detector efficiency function
    //--------------------------------------------------------------------------------------

    {
    double gausswidth = 1.0;

    ft::cvec detector(Nbw);
    double norm = 0;
    for(int n=0; n<Nbw; n++){
        //circular convolution proposed by AI
        int m = (n <= Nbw/2) ? n : n - Nbw;
        double dist = m * dx;
        detector[n] = std::exp(-dist*dist/(2*gausswidth*gausswidth));
        norm += detector[n].real();
    }
    for(int n=0; n<Nbw; n++) detector[n] /= norm;

    ft::cvec yc_clean  = ft::to_complex(ybw_clean);
    ft::cvec s_blurred = ft::convolve(yc_clean,detector);
 
    double meas_noise = 0.02;
    std::normal_distribution<double> measnoise(0.0, meas_noise);
    pp::vector s_measured(Nbw);
    for(int n=0; n<Nbw; n++){
        s_measured[n] = s_blurred[n].real() + measnoise(gen);
    }

    
    std::ofstream out2("convolved.dat");
    for(int n=0; n<Nbw; n++)
        out2 << xbw[n] << " " << ybw_clean[n] << " " << s_blurred[n].real() << " " << s_measured[n] << "\n";
    out2.close();
    

    //--------------------------------------------------------------------------------------
    // Step 2.2: naive deconvolution of the signal
    //--------------------------------------------------------------------------------------

    
    ft::cvec sc_measured   = ft::to_complex(s_measured);
    ft::cvec y_deconv_naive = ft::deconvolve(sc_measured, detector);
    pp::vector y_naive = ft::to_real(y_deconv_naive);
 
    std::ofstream out3("deconvolved.dat");
    for(int n=0; n<Nbw; n++)
        out3 << xbw[n] << " " << ybw_clean[n] << " " << s_measured[n] << " " << y_naive[n] << "\n";
    out3.close();
    }

    //more realistic efficiency function for the following calculations

    double gausswidth = 0.3;

    ft::cvec detector(Nbw);
    double norm = 0;
    for(int n=0; n<Nbw; n++){
        //circular convolution proposed by AI
        int m = (n <= Nbw/2) ? n : n - Nbw;
        double dist = m * dx;
        detector[n] = std::exp(-dist*dist/(2*gausswidth*gausswidth));
        norm += detector[n].real();
    }
    for(int n=0; n<Nbw; n++) detector[n] /= norm;

    ft::cvec yc_clean  = ft::to_complex(ybw_clean);
    ft::cvec s_blurred = ft::convolve(yc_clean,detector);
 
    double meas_noise = 0.02;
    std::normal_distribution<double> measnoise(0.0, meas_noise);
    pp::vector s_measured(Nbw);
    for(int n=0; n<Nbw; n++){
        s_measured[n] = s_blurred[n].real() + measnoise(gen);
    }

    //--------------------------------------------------------------------------------------
    // Step 3: use the wiener filter instead
    //--------------------------------------------------------------------------------------

    {
    ft::cvec sc_measured = ft::to_complex(s_measured);
 
    std::ofstream out2("wiener.dat");
    for(int n=0; n<Nbw; n++){
        out2 << xbw[n] << " " << ybw_clean[n] << " " << s_measured[n] << " ";
        for(double lambda : {1e-4, 1e-3, 1e-2, 1e-1}){
            ft::cvec y_wiener = ft::wiener(sc_measured, detector, lambda);
            out2 << " " << y_wiener[n].real();
        }
        out2 << "\n";
    }
    out2.close();
    }

    //--------------------------------------------------------------------------------------
    // Step 3.1: use a minimization routine to find the optimal lambda
    //--------------------------------------------------------------------------------------

    {
    ft::cvec sc_measured = ft::to_complex(s_measured);
    pp::vector p0(1);
    p0[0] = -2.0;

    auto phi = [&](const pp::vector& p) -> double {
        return wiener_phi(p, sc_measured, detector, ybw_clean);
    };
 
    auto [p_opt, n_iter] = pp::newton_minimize(phi, p0, 1e-4);
 
    double lambda_opt = std::pow(10.0, p_opt[0]);
    std::cout << "Optimal lambda computed by newton_minimize: lambda = " << lambda_opt << " in iterations = " << n_iter << std::endl;
 
    ft::cvec y_wiener_opt = ft::wiener(sc_measured, detector, lambda_opt);
 
    std::ofstream out2("wieneroptimal.dat");
    for(int n=0; n<Nbw; n++)
        out2 << xbw[n] << " " << y_wiener_opt[n].real() << "\n";
    out2.close();
    }

    //--------------------------------------------------------------------------------------
    // Step 3.2: compare the lambdas for different noise strengths
    //--------------------------------------------------------------------------------------

    {
    std::ofstream out2("lambda.dat");
 
    for(double noise_strength : {0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5}){
        std::normal_distribution<double> noise(0.0, noise_strength);
        pp::vector s_ns(Nbw);
        for(int n=0; n<Nbw; n++)
            s_ns[n] = s_blurred[n].real() + noise(gen);
 
        ft::cvec sc_ns = ft::to_complex(s_ns);
 
        auto phi_ns = [&](const pp::vector& p) -> double {
            return wiener_phi(p, sc_ns, detector, ybw_clean);
        };
 
        pp::vector p0(1);
        p0[0] = -2.0;
        auto [p_opt, n_iter] = pp::newton_minimize(phi_ns, p0, 1e-4);
        double lambda_opt = std::pow(10.0, p_opt[0]);
 
        out2 << noise_strength << " " << lambda_opt << "\n";
    }
    out2.close();
    }

	return 0;
}