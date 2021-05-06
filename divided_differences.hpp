#ifndef DIVIDED_DIFFERENCES
#define DIVIDED_DIFFERENCES
#include"polynomials.hpp"
#include"polynomial.cpp"
#include<vector>
#include<map>
#include<utility>
#include<math.h>
#include<iostream>
#include<cassert>
template<class S>
struct divided_differences{
    std :: map<S,S>f;
    std :: vector<S> x_vals, y_vals;
    std :: map<std :: pair<S,int>,S>div_diff;
    divided_differences(std :: vector<S> x, std :: vector<S> y){
        assert(x.size() == y.size() && "inconsistent data ");
        int len = x.size();
        for(int i = 0; i < len; ++i){
            assert(f.count(x[i]) == 0 && " multivalued point");
            f[x[i]] = y[i];
        }
        x_vals = x;
        y_vals = y;
    }
    S get_div_difference(std::vector<S> points){
        std :: cerr << points[0] << " "<< points.size()  << "\n";
        std :: pair<S,int> nxt = {points[0],points.size()};
        if(div_diff.count(nxt)){
            return div_diff[nxt];
        }
        if((int) points.size() == 0){
            assert(false && "can't get divided differences");
        }
        else if((int)points.size() == 1){
            return div_diff[nxt] = f[points[0]];
        }
        else if((int)points.size() == 2){
            return div_diff[nxt] = (f[points[1]] - f[points[0]])/(points[1] - points[0]);
        }
        else{
            std :: vector<S> pref,suff;
            int len = points.size();
            for(int i = 0; i < len; ++i){
                if(i == 0){
                    pref.push_back(points[i]);
                }
                else if(i == len - 1){
                    suff.push_back(points[i]);
                }
                else{
                    pref.push_back(points[i]);
                    suff.push_back(points[i]);
                }
            }
            return div_diff[nxt] =  (get_div_difference(suff) - get_div_difference(pref))/ (points.back() - points[0]);
        }
    }
    void gen_div_diff(){
        std :: cerr << "been called " << "\n";
        for(int i = 0; i < (int)this->x_vals.size(); ++i){
            div_diff[{this->x_vals[i],1}] = this->y_vals[i];
        }
        get_div_difference(this -> x_vals);
    }
    void print_div_diff(){
        int n = x_vals.size();
        for(int i = 0; i < n; ++i){
            for(int j = 1; j <= n; ++j){
                if(div_diff.count({x_vals[i],j})){
                    std :: cerr << div_diff[{x_vals[i],j}] << " ";
                }
                else{
                    break;
                }
            }
            std :: cerr << "\n";
        }
    }
    polynomial<S> gen_poly(){
        polynomial<S> sol = make_poly(S(0));
        polynomial<S> mul = make_poly(S(1));
        print_div_diff();
        int n = x_vals.size();
        for(int i = 0; i < n; ++i){
            sol = sol + mul * div_diff[{x_vals[0],i + 1}];
            std::vector<S> tom = {-x_vals[i],1};
            polynomial<S>tomul(tom);
            mul = mul * tomul;
        }
        std :: cout << sol << "\n";
        return sol;
    }
};
#endif
