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
}