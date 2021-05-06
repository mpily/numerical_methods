#ifndef NUMERICALINT
#define NUMERICALINT
#include"polynomials.hpp"
#include"polynomial.cpp"
#include<iostream>
template<typename S, S (*f)(S)>
struct integrals{
    std :: vector<S> y_vals;
    S h;
    integrals(){
        y_vals = {0};
        h = S(1);
    }
    integrals(S start, S stop, S step){
        for(S a = start; a <= stop; a += step){
            y_vals.push_back(f(a));
            std :: cerr << a << " : " << f(a) << "\n";
        }
        this->h = step;
    }
    S trapezoidal(){
        S term1 = y_vals[0] + y_vals.back();
        S term2 = S(0);
        int len = y_vals.size();
        for(int i = 1; i + 1 < len; ++i){
            term2 += y_vals[i];
        }
        std :: cerr << term1 << " "<< term2 << "\n";
        return (this->h/2.f * ((term1) + 2.0 *(term2)));
    }
    S three_eight(){
        S term1 = y_vals[0] + y_vals.back();
        S term2 = 0, term3 = 0;
        int len = y_vals.size();
        for(int i = 1; i + 1 < len; ++i){;
            if(i % 3){
                term2 += y_vals[i];
            }
            else{
                term3 += y_vals[i];
            }
        }
        return ((this->h * 3)/8.f * (term1 + term2 * 3 + term3 * 2));
    }
    S one_third(){
        S term1 = y_vals[0] + y_vals.back();
        S term2 = 0, term3 = 0;
        int len = y_vals.size();
        for(int i = 1; i + 1 < len; ++i){
            if(i % 2){
                term2 += y_vals[i];
            }
            else{
                term3 += y_vals[i];
            }
        }
        std :: cerr << term1 << " "<< term2 << " "<< term3 << "\n";
        return ((this -> h)/3. * (term1 + term2 * 4 + term3 * 2));
    }
    S Booles(){
        S term1 = y_vals[0] + y_vals.back();
        S term2 = 0, term3 = 0, term4 = 0;
        int len = y_vals.size();
        for(int i = 1; i + 1 < len;++i){
            if(i % 4 == 0){
                term4 += y_vals[i];
            }
            else if(i % 2 == 0){
                term3 += y_vals[i];
            }
            else{
                term2 += y_vals[i];
            }
        }
        return ((h * 2)/ 45.  * (term1 * 7 + term2 * 32 + term3 * 12 + term4 * 14));
    }
};
#endif
