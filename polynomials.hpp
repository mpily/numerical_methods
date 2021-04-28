#include<vector>
#include<math.h>
#include<iostream>
#ifndef POLYNOMIAL
#define POLYNOMIAL
template<class S>struct polynomial{
    std::vector<S>coeffecients;
    polynomial(std::vector<S> arr):coeffecients(arr){};
    void operator = (polynomial<S> rhs){
        coeffecients = rhs;
    }
    polynomial<S> operator * (polynomial<S> rhs);
    polynomial<S> operator * ( S num);
    polynomial<S> operator +(polynomial<S> rhs);
    friend std :: ostream& operator << (std :: ostream & os, polynomial p){
        int my_len = p.coeffecients.size();
        for(int i = 0; i < my_len; ++i){
            os << p.coeffecients[i] << " x ^ "<< i  << (i == my_len - 1 ? " . " : " + ");
        }
        //os << "\n";
        return os;
    }
};
#endif
/*
    Given a list of coeffecients for a polynomial , a_0 X^0 + a_1 x^1 + a_2 x ^ 2 +.., in the order a_1, a_2,a_3 stores the polynomial with the properties * which is polynomial multiplication with another polynomial and + which is polynomial addition
    Example Usage :
    vector<double>num = {1.2,3.6,4.5, 8.9,9.1};
    polynomial<double>nums(num);
    auto nums2 = nums * nums;
    auto 2nums2 = nums2 + nums2;
    cout << twonums2;
    
    outputs 2.88 x ^ 0 + 17.28 x ^ 1 + 47.52 x ^ 2 + 107.52 x ^ 3 + 212.34 x ^ 4 + 291.24 x ^ 5 + 322.22 x ^ 6 + 323.96 x ^ 7 + 165.62 x ^ 8 + 0 x ^ 9 
    which is correct by wolfram alpha

*/
