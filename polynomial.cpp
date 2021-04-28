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
int main(){
    /*std :: vector<int>p1 = {1,1,1,1,7};
    std :: vector<int>p2 = {0,1,3,1,2,4};
    polynomial<int> mp1(p1);
    polynomial<int>mp2(p2);
    std :: cout << '(' << mp1 << " ) * (" << mp2 << " = ("<< mp1 * mp2 << ") \n";
    */
    std :: vector<double>num = {1.2,3.6,4.5, 8.9,9.1};
    polynomial<double>nums(num);
    auto nums2 = nums * nums;
    auto twonums2 = nums2 + nums2;
    std::cout << twonums2;
}

