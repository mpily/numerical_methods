#ifndef POLYNOMIALC
#define POLYNOMIALC
#include"polynomials.hpp"
#include<algorithm>
template<class S>
polynomial<S> polynomial<S>:: operator*(polynomial<S>rhs){
    int her_len = rhs.coeffecients.size();
    int my_len = this -> coeffecients.size();
    std::vector<S>sol(my_len + her_len);
    for(int i = 0; i < my_len; ++i){
        for(int j = 0; j < her_len; ++j){
            sol[i + j] = sol[i + j] + this -> coeffecients[i] * rhs.coeffecients[j];
        }
    }
    for(auto & a : sol){
        if(fabs(a) < 1e-20)a = 0.f;
    }
    polynomial<S>result(sol);
    //result.sanitize();
    return result;
}
template<class S>
polynomial<S> polynomial<S>:: operator + (polynomial<S>rhs){
    int her_len = rhs.coeffecients.size();
    int my_len = this -> coeffecients.size();
    std:: vector<S> sol(std::max(my_len, her_len));
    for(int i = 0; i < std::max(my_len,her_len); ++i){
        S fromme = (i < my_len ? this-> coeffecients[i] : S(0));
        S fromher = (i < her_len ? rhs.coeffecients[i] : S(0));
        sol[i] = fromme + fromher;
    }
     for(auto & a : sol){
        if(fabs(a) < 1e-20)a = 0.f;
    }
    polynomial<S>result(sol);
    //result.sanitize();
    return result;
}
template<class S>
polynomial<S> polynomial<S>:: operator * (S num){
    std :: vector<S> sol(this-> coeffecients.size());
    for(int i = 0; i < (int)this -> coeffecients.size(); ++i){
        sol[i] = this -> coeffecients[i] * num;
    }
     for(auto & a : sol){
        if(fabs(a) < 1e-20)a = 0.f;
    }
    polynomial<S> result(sol);
    //result.sanitize();
    return result;
}
template<class S>
S polynomial<S>:: evaluate(S x){
    S ans = 0;
    S v = 1;
    for(int i = 0; i < (int)this -> coeffecients.size(); ++i){
        ans += v * coeffecients[i];
        v *= x;
    }
    return ans;
}
template<class S>
polynomial<S> polynomial<S> :: differentiate(){
    std :: vector<S> newpoly;
    for(int i = 1; i < (int) this-> coeffecients.size(); ++i){
        newpoly.push_back(this->coeffecients[i] * S(i));
    }
    polynomial<S>derivative(newpoly);
    return derivative;
}
template<class S> 
polynomial<S>make_poly(S i){
    std::vector<S>val = {i};
    return polynomial<S>(val);
}
#endif
