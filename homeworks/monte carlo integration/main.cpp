#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <numbers>
#include <vector>

//AI adaptation of the python code from the exercise
class LCG {
public:
    explicit LCG(uint64_t seed, uint64_t a = 1664525, uint64_t c = 1013904223,
                 uint64_t m = (uint64_t{1} << 32))
        : seed_(seed), a_(a), c_(c), m_(m) {}

    double operator()() {
        seed_ = (a_ * seed_ + c_) % m_;
        return static_cast<double>(seed_ + 1) / static_cast<double>(m_ + 1);
    }

private:
    uint64_t seed_, a_, c_, m_;
};

struct McResult {
    double mean;
    double error;
};

//pretty much a C++ version of the code from the exercise

McResult plainmc(const std::function<double(const std::vector<double>&)>& f,const std::vector<double>& a, const std::vector<double>& b,double N, LCG& rng){
    const int dim = a.size();

    double V = 1.0;
    for (int i = 0; i < dim; ++i){
        V *= b[i] - a[i];
    }
    double sum1 = 0.0, sum2 = 0.0;
    std::vector<double> x(dim);
    for (double n = 0; n < N; ++n){
        for (int i = 0; i < dim; ++i)
            x[i] = a[i] + rng() * (b[i] - a[i]);
        double fx = f(x);
        sum1 += fx;
        sum2 += fx * fx;
    }

    double mean = sum1 / N;
    double variance = sum2 / N - mean * mean;
    if (variance < 0.0) variance = 0.0;  // guard proposed by AI
    double sigma = std::sqrt(variance);

    return {mean * V, sigma * V / std::sqrt(N)};
}

//These are adapted from the lectures

double corput(int n, int b) {
    double q = 0, bk = 1.0/b;
    while (n > 0) {
        q += n % b * bk;
        n/=b;
        bk/=b;
    }
    return q;
}


 
std::vector<int> prime_numbers(int n) {
    std::vector<int> primes;
    int candidate = 2;
    while ((int)primes.size() < n){
        bool candidate_is_prime = true;
        for (int p : primes){
            if (p * p > candidate) break;
            if (candidate % p == 0){ 
                candidate_is_prime = false;
                break;
            }
        }
        if (candidate_is_prime) primes.push_back(candidate);
        candidate++;
    }
    return primes;
}

//Halton was adapted with the help of AI

struct Halton {
    std::vector<int> bases;
 
    explicit Halton(int dim) : bases(prime_numbers(dim)) {}

    explicit Halton(std::vector<int> b) : bases(std::move(b)) {}
 
    std::vector<double> x(int n) const {
        std::vector<double> point(bases.size());
        for (std::size_t i = 0; i < bases.size(); ++i)
            point[i] = corput(n, bases[i]);
        return point;
    }
};

double quasimc(const std::function<double(const std::vector<double>&)>& f,const std::vector<double>& a, const std::vector<double>& b,long N, const Halton& seq){
    const int dim = a.size();
 
    double V = 1.0;
    for (int i = 0; i < dim; ++i){
        V *= b[i] - a[i];
    }
 
    double sum = 0.0;
    for (long n = 1; n <= N; ++n){
        std::vector<double> u = seq.x(n);
        std::vector<double> x(dim);
        for (int i = 0; i < dim; ++i)
            x[i] = a[i] + u[i] * (b[i] - a[i]);
        sum += f(x);
    }
    return (sum / N) * V;
}

struct QmcResult {
    double mean;
    double error;
};
 
QmcResult quasimc_with_error(const std::function<double(const std::vector<double>&)>& f,const std::vector<double>& a, const std::vector<double>& b,long N, const std::vector<int>& bases1,const std::vector<int>& bases2){
    Halton seq1(bases1);
    Halton seq2(bases2);
    double r1 = quasimc(f, a, b, N, seq1);
    double r2 = quasimc(f, a, b, N, seq2);
    return {0.5 * (r1 + r2), 0.5 * std::fabs(r1 - r2)};
}

//AI adaptaion of the code provided in the lecture notes

double strata(const std::function<double(const std::vector<double>&)>& f,
              std::vector<double> a, std::vector<double> b,
              double acc, double eps,
              int n_reuse, double mean_reuse, LCG& rng, int depth = 0, int max_depth = 40) {
    const int dim = a.size();
    int N = 16 * dim;
 
    double V = 1.0;
    for (int k = 0; k < dim; ++k) V *= b[k] - a[k];
 
    std::vector<int> n_left(dim, 0), n_right(dim, 0);
    std::vector<double> mean_left(dim, 0.0), mean_right(dim, 0.0);
    std::vector<double> x(dim);
    double mean = 0.0;
 
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < dim; ++k) x[k] = a[k] + rng() * (b[k] - a[k]);
        double fx = f(x);
        mean += fx;
        for (int k = 0; k < dim; ++k) {
            if (x[k] > 0.5 * (a[k] + b[k])) {
                ++n_right[k];
                mean_right[k] += fx;
            } else {
                ++n_left[k];
                mean_left[k] += fx;
            }
        }
    }
    mean /= N;
    for (int k = 0; k < dim; ++k) {
        if (n_left[k] > 0) mean_left[k] /= n_left[k];
        if (n_right[k] > 0) mean_right[k] /= n_right[k];
    }
 
    // dimension whose lower/upper means differ the most
    int kdiv = 0;
    double maxvar = 0.0;
    for (int k = 0; k < dim; ++k) {
        double var = std::fabs(mean_right[k] - mean_left[k]);
        if (var > maxvar) { maxvar = var; kdiv = k; }
    }
 
    double integ = (mean * N + mean_reuse * n_reuse) / (N + n_reuse) * V;
    double error = std::fabs(mean_reuse - mean) * V;
    double toler = acc + std::fabs(integ) * eps;
    if (error < toler || depth >= max_depth) return integ;
 
    std::vector<double> a2 = a, b2 = b;
    double mid = 0.5 * (a[kdiv] + b[kdiv]);
    b2[kdiv] = mid;   // a2..b2 is the left half along kdiv
    a2[kdiv] = mid;   // (reused below as the right half's lower bound)
 
    double integ_left = strata(f, a, b2, acc / std::sqrt(2.0), eps,
                                n_left[kdiv], mean_left[kdiv], rng, depth + 1, max_depth);
    double integ_right = strata(f, a2, b, acc / std::sqrt(2.0), eps,
                                 n_right[kdiv], mean_right[kdiv], rng, depth + 1, max_depth);
    return integ_left + integ_right;
}

bool circle_indicator(const std::vector<double>& x){
    return x[0] * x[0] + x[1] * x[1] <= 1.0;
}

bool ellipsoid_indicator123(const std::vector<double>& x){
    return ((x[0] * x[0]) + (x[1] * x[1]) / 4 + (x[2] * x[2]) / 9) <= 1;
}


double testfunction(const std::vector<double>& x){
    return 1.0/(M_PI*M_PI*M_PI*(1-std::cos(x[0])*std::cos(x[1])*std::cos(x[2])));
}
    

int main() {
    std::vector<double> ca{-1.0, -1.0};
    std::vector<double> cb{1.0, 1.0};

    LCG rng(12345);

    std::ofstream circ_out("circle.dat");
    circ_out << "# N estimate estimated_error actual_error 1/sqrt(N)\n";

    std::cout << "We calculatea the area of a unit circle(known to be " << M_PI << ") with plain MC and quasi-random MC:" << std::endl;

    std::vector<int> cbases1{2, 5};
    std::vector<int> cbases2{3, 7};

    for (int N=10; N<=1e5; N*=10){
        //AI proposed a few repeats to reduce noise
        const int repeats = 3;
        double perr_acc = 0.0, pest_acc = 0.0, pmean_acc = 0.0;
        double qerr_acc = 0.0, qest_acc = 0.0, qmean_acc = 0.0;
        for (int r=0; r<repeats; r++) {
            McResult resp = plainmc(circle_indicator, ca, cb, N, rng);
            pmean_acc += resp.mean;
            pest_acc += resp.error;
            perr_acc += std::fabs(resp.mean - M_PI);
            QmcResult resq = quasimc_with_error(circle_indicator, ca, cb, N, cbases1, cbases2);
            qmean_acc += resq.mean;
            qest_acc += resq.error;
            qerr_acc += std::fabs(resq.mean - M_PI);
        }
        double pmean = pmean_acc / repeats;
        double pest_err = pest_acc / repeats;
        double pact_err = perr_acc / repeats;
        double qmean = qmean_acc / repeats;
        double qest_err = qest_acc / repeats;
        double qact_err = qerr_acc / repeats;



        circ_out << N << " " << pmean << " " << pest_err << " " << pact_err << " " << qmean << " " << qest_err << " " << qact_err << " " << 1.0 / std::sqrt(static_cast<double>(N)) << '\n';
        if(N==1e7){
            std::cout << pmean << std::endl;
            std::cout << qmean << std::endl;
        }
    }
    circ_out.close();

    std::cout << "The error comparison can be seen in circle.pdf." << std::endl;

    std::vector<double> pa{-1, -2, -3};
    std::vector<double> pb{1, 2, 3};

    double N_e = 1e8;
    McResult ell = plainmc(ellipsoid_indicator123, pa, pb, N_e, rng);

    std::cout << "We calculate the area of a ellpisoid (123) known to be " << 8.0*M_PI << ": "<< std::endl << ell.mean << std::endl;

    std::cout << "We calculate ∫0π  dx/π ∫0π  dy/π ∫0π  dz/π [1-cos(x)cos(y)cos(z)]-1 = Γ(1/4)4/(4π3) ≈" << std::pow(std::tgamma(0.25), 4) / (4.0 * std::pow(M_PI, 3)) << "given in the exercise four different ways:" << std::endl;
    
    std::vector<double> ta{0, 0, 0};
    std::vector<double> tb{M_PI, M_PI, M_PI};

    McResult ptest = plainmc(testfunction, ta, tb, 1e7, rng);

    std::cout << "i) using plain MC: " << ptest.mean << std::endl;

    std::vector<int> tbases1{2, 5, 11};
    std::vector<int> tbases2{3, 7, 13};

    QmcResult test = quasimc_with_error(testfunction, ta, tb, 1e7, tbases1, tbases2);
    std::cout << "ii) using quasi-random MC: " << test.mean << std::endl;

    std::cout << "iii) using the generator from the standard C++ library: " << std::pow(std::tgamma(0.25), 4) / (4.0 * std::pow(M_PI, 3)) << std::endl;

    double test_strata = strata(testfunction, ta, tb, 1e-3, 1e-3, 0, 0.0, rng);

    std::cout << "iv) using stratified sampling: " << test_strata << std::endl;

    return 0;
}