#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double PI = 3.14159265358979323846;

// -----------------------------
// Error function approximation
// -----------------------------
double erf(double x) {
    if (x < 0) return -erf(-x);

    std::vector<double> a {
        0.254829592, -0.284496736, 1.421413741,
       -1.453152027, 1.061405429
    };

    double t = 1.0 / (1.0 + 0.3275911 * x);
    double sum = t * (a[0] + t*(a[1] + t*(a[2] + t*(a[3] + t*a[4]))));
    return 1.0 - sum * std::exp(-x*x);
}

// -----------------------------
// Stirling gamma approximation
// -----------------------------
double sgamma(double x) {
    if (x < 0)
        return PI / (std::sin(PI * x) * sgamma(1 - x));

    if (x < 9)
        return sgamma(x + 1) / x;

    double lnsgamma =
        std::log(2 * PI) / 2 + (x - 0.5) * std::log(x) - x + (1.0 / 12) / x - (1.0 / 360) / (x * x * x) + (1.0 / 1260) / (x * x * x * x * x);

    return std::exp(lnsgamma);
}

// -----------------------------
// log gamma approximation
// -----------------------------
double lngamma(double x) {
    if (x <= 0) return NAN;

    if (x < 9)
        return lngamma(x + 1) - std::log(x);

    return x * std::log(x + 1 / (12 * x - 1.0 / (10 * x))) - x +
           std::log(2 * PI / x) / 2;
}

// -----------------------------
int main() {

    std::ofstream erf_file("erf.dat");
    std::ofstream gamma_file("gamma.dat");
    std::ofstream lgamma_file("lgamma.dat");

    std::ofstream erf_tab("erf_tab.dat");
    std::ofstream gamma_tab("gamma_tab.dat");
    std::ofstream lgamma_tab("lgamma_tab.dat");

    // ---------------------------------------------------------
    // error function data
    // ----------------------------------------------------------
    for (double x = -3; x <= 3; x += 0.02) {
        erf_file << x << " "
                 << erf(x) << " "
                 << std::erf(x) << "\n";
    }

    for (double x = -3; x <= 3; x += 0.5) {
        erf_tab << x << " " << std::erf(x) << "\n";
    }

    // ---------------------------------------------------------
    // gamma function data
    // ----------------------------------------------------------
    for (double x = 0.1; x <= 6; x += 0.02) {
        gamma_file << x << " "
                   << sgamma(x) << " "
                   << std::tgamma(x) << "\n";
    }

    for (int n = 1; n <= 6; n++) {
        gamma_tab << n << " " << std::tgamma(n) << "\n";
    }

    // ---------------------------------------------------------
    // log gamma function data
    // ---------------------------------------------------------
    for (double x = 0.1; x <= 6; x += 0.02) {
        lgamma_file << x << " "
                    << lngamma(x) << " "
                    << std::lgamma(x) << "\n";
    }
    for (int n = 1; n <= 6; n++) {
        lgamma_tab << n << " " << std::log(std::tgamma(n)) << "\n";
    }
    

    return 0;
}