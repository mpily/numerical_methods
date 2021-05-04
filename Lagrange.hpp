#ifndef LAGRANGE
#define LAGRANGE
#include"polynomials.hpp"
#include"polynomial.cpp"
#include<assert.h>
#include<vector>
template<class S>
struct Lagrange{
    std:: vector<S> x_vals;
    std :: vector<S> y_vals;
    polynomial<S> lagrange_interpol;
    Lagrange(std::vector<S>x, std::vector<S> y): x_vals(x),y_vals(y){};
    void generate_Ls();
};
template<class S>
void Lagrange<S> :: generate_Ls(){
    lagrange_interpol = make_poly<S>(S(0));
    int n = x_vals.size();
    assert((int)y_vals.size() == n && "the data is inconsistent");
    for(int i = 0; i < n; ++i){
        S denominator = 1;
        auto numerator = make_poly<S>(S(1));
        for(int j = 0; j < n; ++j){
            if(i == j)continue;
            std::vector<S> nxt = {-x_vals[j],S(1)};
            polynomial<S>tomul(nxt);
            numerator = numerator * tomul;
            denominator = denominator * (x_vals[i] - x_vals[j]);
        }
        std:: cerr << numerator << "/" << denominator << "\n";
        numerator = numerator * (y_vals[i] * 1.f/denominator);
        lagrange_interpol = lagrange_interpol + numerator;
    }
    std :: cout << lagrange_interpol << "\n";
}
#endif
/*
    Given a set of points generates a polynomial via Lagrange interpolation
    the formula for Lagrange interpolation is 
    sum(l_i * y_i)
    where l_i = (Product(x-xj))/(Product(xi - xj)) for all j != i;
*/
