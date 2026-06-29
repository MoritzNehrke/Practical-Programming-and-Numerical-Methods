#pragma once
#include<iostream>
#include<vector>
#include<initializer_list>
#include<cstdio>
#include<cassert>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>
#include<ranges>
#include<random>

//--------------------------------------------------------------------------------------
// Here you can find the implementation for the vector and matrix classes. This is strongly oriented towards the one we discussed in the lecture.
//--------------------------------------------------------------------------------------

namespace pp{

struct vector{
    std::vector<double> data;
    vector() = default;
    vector(int n): data(n) {}
    vector(std::initializer_list<double> list): data(list) {}
    vector(const vector&) = default;
    vector(vector&&) noexcept = default;
    vector& operator=(const vector&) = default;
    vector& operator=(vector&&) noexcept = default;
    inline int size() const { return data.size(); }
    inline double& operator[](int i) { return data[i]; }
    inline const double& operator[](int i) const { return data[i]; }
    vector& operator+=(const vector& other);
    vector& operator-=(const vector& other);
    vector& operator*=(double c);
    vector& operator/=(double c);
    double norm() const;
    void print(std::string s = "") const;
    vector map(std::function<double(double)> f) const;
};

vector operator+(vector a, const vector& b);
vector operator-(vector a);
vector operator-(vector a, const vector& b);
vector operator*(vector a, const double c);
vector operator*(const double c, vector a);
double operator*(const vector& a, const vector& b);
vector operator/(vector a, const double c);
bool approx(double x, double y, double acc = 1e-6, double eps = 1e-6);
bool approx(const vector& a, const vector& b, double acc = 1e-6, double eps = 1e-6);

struct matrix{
    std::vector<pp::vector> cols;
    matrix() = default;
    matrix(int m, int n): cols(n, pp::vector(m)) {}
    matrix(const matrix& other) = default;
    matrix(matrix&& other) = default;
    matrix& operator=(const matrix& other) = default;
    matrix& operator=(matrix&& other) = default;
    inline double& operator()(int i, int j) { return cols[j][i]; }
    //inline double& operator[](int i, int j) { return cols[j][i]; }
    inline const double& operator()(int i, int j) const { return cols[j][i]; }
    //inline const double& operator[](int i, int j) const { return cols[j][i]; }
    inline vector& operator[](int i) { return cols[i]; }
    inline const vector& operator[](int i) const { return cols[i]; }
    void resize(int m, int n);
    inline int size1() const {return cols[0].size();}
    inline int size2() const {return cols.size();}
    void setid();
    matrix transpose() const;
    matrix T() const { return transpose(); }
    matrix& operator+=(const matrix& B);
    matrix& operator-=(const matrix& B);
    matrix& operator*=(const double c);
    matrix& operator/=(const double c);
    matrix& operator*=(const matrix& B);
    matrix operator^(int);
    void print (std::string s = "") const;
};

matrix operator+(matrix A, const matrix& B);
matrix operator-(matrix A, const matrix& B);
matrix operator*(const matrix& A, const matrix& B);
matrix operator*(matrix A, const double c);
matrix operator*(const double c, matrix A);
matrix operator/(matrix A, const double c);
vector operator*(const matrix& A, const vector& v);

struct qr
{
    pp::matrix Q;
    pp::matrix R;

    qr(const pp::matrix& A);
    void setcolumn(matrix& A, const pp::vector& v, int j);

    pp::vector solve(const pp::vector& b) const;

    double det() const;

    matrix inverse() const;

};


}