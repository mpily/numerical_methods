#include "polynomials.hpp"
#include<assert.h>
#ifndef NEWTONFORWARD
#define NEWTONFORWARD
template<class S,S (*e)()>
struct newtonsforward{
    std::vector<S>xvals,yvals;
    S h;
    newtonsforward(std::vector<S> x_vals, std::vector<S>y_vals){
        assert(x_vals.size() == y_vals.size() && "data isn't consistent");
        assert((int)x_vals.size() > 1 && "too few points");
        this -> h = x_vals[1] - x_vals[0];
        for(int i = 2; i < (int)x_vals.size(); ++i){
            assert(x_vals[i] - x_vals[i-1] - h <= e() && " the data is not uniquely spaced can't use Newton's method"); 
        }
        this -> xvals = x_vals;
        this -> yvals = y_vals;
    }
    polynomial<S>genpoly();
    
};
#endif
