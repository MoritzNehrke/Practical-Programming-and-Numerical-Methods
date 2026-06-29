#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
#include"linearalgebra.h"
#define SELF (*this)
#define FOR(i,V) for(int i=0;i<V.size();i++)
#define FOR1(i,A) for(int i=0;i<A.size1();i++)
#define FOR2(j,A) for(int j=0;j<A.size2();j++)

namespace pp{

vector& vector::operator+=(const vector& other){
	FOR(i,SELF) SELF[i]+=other[i];
	return SELF;
}

vector& vector::operator-=(const vector& other){
   FOR(i,SELF) SELF[i]-=other[i];
	return SELF;
}

vector& vector::operator*=(double c){
	FOR(i,SELF) SELF[i]*=c;
	return SELF;
}

vector& vector::operator/=(double c){
	FOR(i,SELF) SELF[i]/=c;
	return SELF;	
}

double vector::norm() const {
	double sum2=0;
	FOR(i,SELF) sum2+=SELF[i]*SELF[i];
	return std::sqrt(sum2);
}

void vector::print(std::string s) const {
	std::cout<<s;
	for(auto &x : data) printf("%10.3g ",x);
	std::cout<<"\n";	
}

vector vector::map(std::function<double(double)> f) const{
	vector r(size());
	FOR(i,SELF) r.data[i]=f(data[i]);
	return r;
}

vector operator+(vector a, const vector& b){ a+=b ; return a; }
vector operator-(vector a)                 { a*=-1; return a; }
vector operator-(vector a, const vector& b){ a-=b ; return a; }
vector operator*(vector a, const double c) { a*=c ; return a; }
vector operator*(const double c, vector a) { a*=c ; return a; }
double operator*(const vector& a, const vector& b) {
	if(a.size()!=b.size()) throw std::invalid_argument("size mismatch");
	double sum=0;
	for(int i=0;i<a.size();i++) sum+=a[i]*b[i];
	return sum;
}
vector operator/(vector a, const double c) { a/=c ; return a; }

bool approx
(double x, double y, double acc, double eps){
	if(std::abs(x-y) < acc) return true;
	if(std::abs(x-y) < eps*std::max(std::abs(x),std::abs(y))) return true;
	return false;	}

bool approx
(const vector& a, const vector& b, double acc, double eps){
	if(a.size() != b.size()) return false;
	for(int i=0;i<a.size();i++)
		if(!approx(a[i],b[i],acc,eps)) return false;
	return true;
}

void matrix::setid(){		assert(size1()==size2());
		for(int i=0;i<size1();i++){
		SELF[i][i]=1;
		for(int j=i+1;j<size1();j++) SELF[j][i] = SELF[i][j] = 0;
	}
}

matrix matrix::transpose() const{
	matrix R(size2(),size1());
	FOR1(i,SELF)
	FOR2(j,SELF)
		R[i][j]=SELF[j][i];
	return R;
}

matrix& matrix::operator+=(const matrix& B){
	for(int i=0;i<size2();i++)SELF[i]+=B[i];
	return *this;
}
matrix& matrix::operator-=(const matrix& B){
	for(int i=0;i<size2();i++)SELF[i]-=B[i];
	return *this;
}
matrix& matrix::operator*=(const double c){
	for(int i=0;i<size2();i++)SELF[i]*=c;
	return *this;
}
matrix& matrix::operator/=(const double c){
	for(int i=0;i<size2();i++)SELF[i]/=c;
	return *this;
}
        
void matrix::print(std::string s) const {
	printf("%s\n",s.c_str());
	for(int i=0;i<size1();i++){
		for(int j=0;j<size2();j++)printf("%10.3g ",SELF[j][i]);
    		printf("\n");
	}
}

matrix operator+(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]+=B[i];
	return A;
	}

matrix operator-(matrix A, const matrix& B){
	for(int i=0;i<A.size2();i++)A[i]-=B[i];
	return A;
	}

matrix operator*(const matrix& A, const matrix& B){
	if(A.size2()!=B.size1()) throw std::invalid_argument("size mismatch");
	matrix R(A.size1(),B.size2());
	for(int k=0;k<A.size2();k++)
	for(int j=0;j<B.size2();j++) {
		double Bkj = B[j][k];
		for(int i=0;i<A.size1();i++) R[j][i] += A[k][i]*Bkj;
		}
	return R;
}

matrix operator*(matrix A, const double c){
	for(auto &col : A.cols) col*=c;
	return A;
}

matrix operator*(const double c, matrix A){
	for(auto &col : A.cols) col*=c;
	return A;
}

matrix operator/(matrix A, const double c){
	for(auto &col : A.cols) col/=c;
	return A;
}

vector operator*(const matrix& A, const vector& v){
	vector r(A.size1());
	FOR2(j,A){
		double vj=v[j];
		FOR1(i,A) r[i]+=A[j][i]*vj;
		}
	return r;
}

void qr::setcolumn(matrix& A, const pp::vector& v, int j){
    if (A.size1() != v.size()) throw std::invalid_argument("size mismatch");
    for(int i=0;i<A.size1();i++) A[j][i]=v[i];

}


qr::qr(const pp::matrix& A){
    int n = A.size1();
    int m = A.size2();
    if (n < m) throw std::invalid_argument("qr: n < m");
    Q = A;
    R = pp::matrix(m, m);
    for(int j=0;j<m;j++){
        R(j,j) = Q[j].norm();
        Q[j] /= R(j,j);
        for(int k=j+1;k<m;k++){
            R(j,k) = Q[j]*Q[k];
            Q[k] -= R(j,k) * Q[j];
        }
    }
}

vector qr::solve(const pp::vector& b) const {
    if (b.size() != Q.size1()) throw std::invalid_argument("size mismatch");
    pp::vector y = Q.transpose() * b;
    pp::vector x(R.size2());
    for(int i=x.size()-1;i>=0;i--){
        double sum = 0;
        for(int k=i+1;k<x.size();k++){ 
            sum += R(i,k)*x[k];
        }
        x[i] = (y[i]-sum)/R(i,i);
    }
    return x;
}

double qr::det() const {
    if (Q.size1() != Q.size2()) throw std::invalid_argument("det: matrix is not square");
    double det = 1.0;
    for(int i=0;i<R.size1();i++){
        det *= R(i,i);
    }
	return det;

}

matrix qr::inverse() const {
    if (Q.size1() != Q.size2()) throw std::invalid_argument("inverse: matrix is not square");
    int n = Q.size1();
    pp::matrix inv(n, n);
    for(int j=0;j<n;j++){
        pp::vector e(n);
        e[j] = 1.0;
        inv[j] = solve(e);
    }
    return inv;

}

//-------------------------------------------------------------------------------------
// This is mostly copied from the exercise
//-------------------------------------------------------------------------------------

void evd::timesJ(pp::matrix& A, int p, int q, double theta){
	double c = std::cos(theta);
	double s = std::sin(theta);
	for(int i=0;i<A.size1();i++){
		double aip = A(i,p);
		double aiq = A(i,q);
		A(i,p) = c*aip - s*aiq;
		A(i,q) = s*aip + c*aiq;
	}
}

void evd::Jtimes(pp::matrix& A, int p, int q, double theta){
	double c = std::cos(theta);
	double s = std::sin(theta);
	for(int j=0;j<A.size2();j++){
		double apj = A(p,j);
		double aqj = A(q,j);
		A(p,j) = c*apj + s*aqj;
		A(q,j) = -s*apj + c*aqj;
	}

}

evd::evd(const pp::matrix& A_in){
	if(A_in.size1() != A_in.size2())
		throw std::invalid_argument("evd: matrix is not square");
	int n = A_in.size1();
	pp::matrix A = A_in;
	V = pp::matrix(n,n);
	V.setid();
 
	bool changed;
	do{
		changed = false;
		for(int p=0;p<n-1;p++)
		for(int q=p+1;q<n;q++){
			double apq = A(p,q), app = A(p,p), aqq = A(q,q);
			double theta = 0.5*std::atan2(2*apq, aqq-app);
			double c = std::cos(theta), s = std::sin(theta);
			double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
			double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
			//if(!pp::approx(new_app,app,1e-12,1e-12) || !pp::approx(new_aqq,aqq,1e-12,1e-12)){
			if(new_app!=app || new_aqq!=aqq){	
			changed = true;
				timesJ(A,p,q, theta); // A <- A*J
				Jtimes(A,p,q,-theta); // A <- J^T*A
				timesJ(V,p,q, theta); // V <- V*J
			}
		}
	}while(changed);
 
	w = pp::vector(n);
	for(int i=0;i<n;i++) w[i] = A(i,i);

	D = pp::matrix(n,n);
	for(int i=0; i<n; i++) D(i,i) = w[i];
}

pp::vector lsfit(const std::vector<std::function<double(double)>>& fs,const pp::vector& x, const pp::vector& y, const pp::vector& dy){
    int n = x.size();
    int m = fs.size();
    if (y.size() != n || dy.size() != n)
        throw std::invalid_argument("lsfit: x, y, dy size mismatch");
    if (n < m)
        throw std::invalid_argument("lsfit: fewer data points than fit parameters");
 
    pp::matrix A(n, m);
    pp::vector b(n);
    for(int i=0;i<n;i++){
        b[i] = y[i]/dy[i];
        for(int k=0;k<m;k++){
            A(i,k) = fs[k](x[i])/dy[i];
        }
    }
 
    pp::qr ls(A);
    return ls.solve(b);
}

std::tuple<pp::vector,pp::matrix> lsfit_cov(const std::vector<std::function<double(double)>>& fs,const pp::vector& x, const pp::vector& y, const pp::vector& dy){
    int n = x.size();
    int m = fs.size();
    if (y.size() != n || dy.size() != n)
        throw std::invalid_argument("lsfit: x, y, dy size mismatch");
    if (n < m)
        throw std::invalid_argument("lsfit: fewer data points than fit parameters");
 
    pp::matrix A(n, m);
    pp::vector b(n);
    for(int i=0;i<n;i++){
        b[i] = y[i]/dy[i];
        for(int k=0;k<m;k++){
            A(i,k) = fs[k](x[i])/dy[i];
        }
    }
 
    pp::qr ls(A);
    pp::vector c = ls.solve(b);
	pp::matrix B = A.transpose()*A;
	pp::qr ls2(B);
	pp::matrix sigma = ls2.inverse();
	return std::make_tuple(c,sigma);
}

int binsearch(const pp::vector& x, double z){
	assert(z>=x[0] && z<=x[x.size()-1]);
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
	}
	return i;
}
 
double linterp(const pp::vector& x, const pp::vector& y, double z){
	int i=binsearch(x,z);
	double dx=x[i+1]-x[i];
	assert(dx>0);
	double dy=y[i+1]-y[i];
	return y[i]+dy/dx*(z-x[i]);
}
 
double linterpInteg(const pp::vector& x, const pp::vector& y, double z){
	int pos=binsearch(x,z);
	double sum=0;
	for(int i=0;i<pos;i++){
		double dx=x[i+1]-x[i];
		sum += 0.5*(y[i]+y[i+1])*dx;
	}
	double dx=x[pos+1]-x[pos];
	double dy=y[pos+1]-y[pos];
	sum += (y[pos]*(z-x[pos])+(dy/dx)*0.5*(z-x[pos])*(z-x[pos]));
	return sum;
}

//AI generated adaptation of the C code for qspline() provided in the lecture

qspline::qspline(const pp::vector& xin, const pp::vector& yin)
	: n(xin.size()), x(xin), y(yin), b(n-1), c(n-1)
{
	assert(n>=3); 
 
	pp::vector h(n-1), p(n-1);
	for(int i=0;i<n-1;i++){
		h[i] = x[i+1]-x[i];
		assert(h[i]>0);
		p[i] = (y[i+1]-y[i])/h[i];
	}
	c[0] = 0;
	for(int i=0;i<n-2;i++)
		c[i+1] = (p[i+1]-p[i]-c[i]*h[i])/h[i+1];
	c[n-2] /= 2;
	for(int i=n-3;i>=0;i--)
		c[i] = (p[i+1]-p[i]-c[i+1]*h[i+1])/h[i];
 
	for(int i=0;i<n-1;i++)
		b[i] = p[i]-c[i]*h[i];
}
 
double qspline::eval(double z) const {
	int i = binsearch(x,z);
	double dz = z-x[i];
	return y[i]+b[i]*dz+c[i]*dz*dz;
}
 
double qspline::deriv(double z) const {
	int i = binsearch(x,z);
	double dz = z-x[i];
	return b[i]+2*c[i]*dz;
}
 
double qspline::integ(double z) const {
	int i = binsearch(x,z);
	double sum=0;
	for(int k=0; k<i; k++){
		double dx=x[k+1]-x[k];
		sum += y[k]*dx+b[k]*dx*dx/2+c[k]*dx*dx*dx/3;
	}
	double dz=z-x[i];
	sum += y[i]*dz+b[i]*dz*dz/2+c[i]*dz*dz*dz/3;
	return sum;
}

std::function<double(double)> make_qspline(pp::vector x, pp::vector y){
	
	//calculation same as before

	int n = x.size();
	assert(n>=3); 
 
	pp::vector h(n-1), p(n-1);
	for(int i=0;i<n-1;i++){
		h[i] = x[i+1]-x[i];
		assert(h[i]>0);
		p[i] = (y[i+1]-y[i])/h[i];
	}

	pp::vector b(n-1), c(n-1);
	c[0] = 0;
	for(int i=0;i<n-2;i++)
		c[i+1] = (p[i+1]-p[i]-c[i]*h[i])/h[i+1];
	c[n-2] /= 2;
	for(int i=n-3;i>=0;i--)
		c[i] = (p[i+1]-p[i]-c[i+1]*h[i+1])/h[i];
 
	for(int i=0;i<n-1;i++)
		b[i] = p[i]-c[i]*h[i];

	return [x=std::move(x), y=std::move(y), b=std::move(b), c=std::move(c)]
		(double z){
			int i = binsearch(x,z);
			double dz = z-x[i];
			return y[i]+b[i]*dz+c[i]*dz*dz;
		};
}

}

