#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include"linearalgebra.h"
#include<random>

int main(){
	
    //A

    // Rutherford & Soddy (1902) measurements of the radioactivity of 224-Ra.

	pp::vector t = {1,2,3,4,6,9,10,13,15};
	pp::vector y = {117,100,88,72,53,29.5,25.2,15.2,11.1};
	pp::vector dy = {6,5,4,4,4,3,3,2,2};
 
	int n = t.size();
 
	// Write measurements to a .dat file for plotting.

	std::ofstream data_out("224Ra.dat");
	for(int i=0;i<n;i++){
		data_out << t[i] << " " << y[i] << " " << dy[i] << "\n";
	}
	data_out.close();

    pp::vector lny(n);
    pp::vector dlny(n);

    for(int i=0; i<n; i++){
        lny[i] = std::log(y[i]);
        dlny[i] = dy[i]/y[i]; //dlnx = 1/x*dx, simple derivative(used like this a few more times here)
    }

    std::vector<std::function<double(double)>> fs {
		[](double  ) { return 1.0; },
		[](double z) { return z;   }
    };

    auto [c,cov] = lsfit_cov(fs, t, lny, dlny);
    double a = std::exp(c[0]);
    double lambda = -c[1];
    double half_life = std::log(2.0)/lambda;
    pp::vector dc(c.size());
    for(int i = 0; i<c.size(); i++){
        dc[i]=std::sqrt(cov(i,i));
    }
    double dhalf_life = std::log(2.0)/lambda/lambda*dc[1];
    double da = a*dc[0];

    std::cout << "The fitted half time is " << half_life << " +- " << dhalf_life << " days and is close to the 3.66 days I found on Wikipedia." << std::endl;

    std::ofstream fit_out("224Rafit.dat");
	int nfit = 200;
	double tmin = 0.0, tmax = 20.0;
	for(int i=0;i<=nfit;i++){
		double tt = tmin + (tmax-tmin)*i/nfit;
		double yy1 = a*std::exp(-lambda*tt);
        double yy2 = (a-da)*std::exp(-(lambda+dc[1])*tt); 
        double yy3 = (a+da)*std::exp(-(lambda-dc[1])*tt);
		fit_out << tt << " " << yy1 << " " << yy2 << " " << yy3 << "\n";
	}
	fit_out.close();

    std::cout << "A plot of the fit can be found as decay.pdf where also the uncertainties of a and lambda where checked: maximum (a+da,lambda-dlambda) and minimum (a-da,lambda+dlambda)" << std::endl;

    return 0;

}