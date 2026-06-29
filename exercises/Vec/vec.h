#pragma once
#include<string>
#include<iostream>

namespace pp{
    template<typename T>
    struct vec
    {
        T x,y,z;
        vec(T a, T b, T c)
        {
            std::cout<<"vec constructor called with "<<a<<" "<<b<<" "<<c<<std::endl;
            x=a;
            y=b;
            z=c;
        }

        vec() : vec(0,0,0) {
            std::cout<<"vec default constructor called"<<std::endl;
        }

        vec(const vec&) = default;
        vec(vec&&) = default;

        ~vec() {
            std::cout<<"vec destructor called"<<std::endl;
        }

        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;

        vec& operator+=(const vec&);
        vec& operator-=(const vec&);
        vec& operator*=(double);
        vec& operator/=(double);

        void print(const std::string& s="") const;
        
        //friend std::ostream& operator<<(std::ostream&, const vec&);
    };

    template<typename T>
    vec<T> operator+(vec<T>, const vec<T>&);
    template<typename T>
    vec<T> operator-(vec<T>, const vec<T>&);
    template<typename T>
    vec<T> operator*(const vec<T>&, double);
    template<typename T>
    vec<T> operator*(double, const vec<T>&);
    template<typename T>
    vec<T> operator/(const vec<T>&, double);
    template<typename T>
    vec<T> operator-(const vec<T>&);
    
    template<typename T>
    void vec<T>::print(const std::string& s) const {
        std::cout<<s<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
        os<<"("<<v.x<<","<<v.y<<","<<v.z<<")";
        return os;
    }

    template<typename T>
    vec<T>& vec<T>::operator+=(const vec<T>& v) {
        x+=v.x;
        y+=v.y;
        z+=v.z;
        return *this;
    }

    template<typename T>
    vec<T> operator+(vec<T> a, const vec<T>& b) {
        a += b;
        return a;
    }

    template<typename T>
    vec<T>& vec<T>::operator-=(const vec<T>& v) {
        x-=v.x;
        y-=v.y;
        z-=v.z;
        return *this;
    }

    template<typename T>
    vec<T> operator-(vec<T> a, const vec<T>& b) {
        a -= b;
        return a;
    }

    template<typename T>
    vec<T>& vec<T>::operator*=(double s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template<typename T>
    vec<T> operator*(const vec<T>& v, double s) {
        vec<T> r = v;
        r *= s;
        return r;
    }

    template<typename T>
    vec<T> operator*(double s, const vec<T>& v) {
        return v * s;
    }   

    template<typename T>
    vec<T>& vec<T>::operator/=(double s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;

    }   

    template<typename T>
    vec<T> operator/(const vec<T>& v, double s) {
        vec<T> r = v;
        r /= s;
        return r;
    }

}