#include"polynomials.hpp"
#include<algorithm>
template<class S>
polynomial<S> polynomial<S>:: operator*(polynomial<S>rhs){
    int her_len = rhs.coeffecients.size();
    int my_len = this -> coeffecients.size();
    std::vector<S>sol(my_len + her_len);
    for(int i = 0; i < my_len; ++i){
        for(int j = 0; j < her_len; ++j){
            sol[i + j] += this -> coeffecients[i] * rhs.coeffecients[j];
        }
    }
    polynomial<S>result(sol);
    return result;
}
template<class S>
polynomial<S> polynomial<S>:: operator + (polynomial<S>rhs){
    int her_len = rhs.coeffecients.size();
    int my_len = this -> coeffecients.size();
    std:: vector<S> sol(std::max(my_len, her_len));
    for(int i = 0; i < std::max(my_len,her_len); ++i){
        sol[i] = this->coeffecients[i] + rhs.coeffecients[i];
    }
    polynomial<S>result(sol);
    return result;
}
template<class S>
polynomial<S> polynomial<S>:: operator * (S num){
    std :: vector<S> sol(this-> coeffecients.size());
    for(int i = 0; i < (int)this -> coeffecients.size(); ++i){
        sol[i] = this -> coeffecients[i] * num;
    }
    polynomial<S> result(sol);
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

