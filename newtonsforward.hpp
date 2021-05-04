#include "polynomials.hpp"
#include<assert.h>
#include<math.h>
#ifndef NEWTONFORWARD
#define NEWTONFORWARD
template<class S,S (*e)()>
struct newtonsforward{
    std::vector<S>xvals,yvals;
    S h;
    S x_o;
    bool is_backward = false;
    newtonsforward(std::vector<S> x_vals, std::vector<S>y_vals,bool back){
        assert(x_vals.size() == y_vals.size() && "data isn't consistent");
        assert((int)x_vals.size() > 1 && "too few points");
        this -> h = x_vals[1] - x_vals[0];
        is_backward = back;
        for(int i = 2; i < (int)x_vals.size(); ++i){
            assert(fabs(x_vals[i] - x_vals[i-1] - h) <= e() && " the data is not uniquely spaced can't use Newton's method"); 
        }
        this -> xvals = x_vals;
        this -> yvals = y_vals;
        this -> is_backward = back;
        if(back){
            this -> x_o = x_vals.back();
        }
        else{
            this -> x_o = x_vals[0];
        }
    }
    polynomial<S>genpoly();
    polynomial<S>genpoly_central(int idx);
    
};
#endif
