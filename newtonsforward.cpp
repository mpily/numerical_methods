#include "newtonsforward.hpp"
#include "polynomial.cpp"
#include<iostream>
#include<iomanip>
template<class S>
std :: vector<std :: vector<S>> gen_differences(std :: vector<S> yvals){
    std::vector<std::vector<S>> differences;
    differences.push_back(yvals);
    while((int)differences.back().size() != 1){
        std::vector<S>next_diff;
        int last_len = differences.back().size();
        for(int i = 1; i < last_len; ++i){
            next_diff.push_back(differences.back()[i] - differences.back()[i-1]);
        }
        differences.push_back(next_diff);
    }
    return differences;
}

/*
    the formula we are trying to use is 
    Sum_i = 0 ^ i = n (differences_i[0] * product_{j < i}(p-j) * 1/i!)
    p = x - x_0/h
*/
template<class S,S(*e)()>
polynomial<S> newtonsforward<S,e> :: genpoly(){
    std::vector<std::vector<S>> differences = gen_differences(this->yvals);
    double invfact = 1.0;
    int mul = 1;
    if(is_backward){
        mul = -1;
    }
    polynomial<S>unity = make_poly<S>(S(1));
    std::vector<S> pv = {-this->x_o,S(1)};
    polynomial<S>finpoly = make_poly<S>(this->yvals[0]);
    if(this -> is_backward){
        finpoly = make_poly<S>(this->yvals.back());
    }
    polynomial<S>ppoly(pv);
    ppoly = ppoly * ((S)(1)/ this-> h);
    //std::cerr << finpoly;
    for(int i = 1; i < (int)differences.size(); ++i){
        //std::cerr << " + ";
        polynomial<S> uglynum = unity;
        for(int j = 0; j < i; ++j){
            polynomial<S> new_poly = ppoly + make_poly(S(-j * mul));
            uglynum = uglynum * new_poly;
            //std::cerr <<'(' << new_poly << ')' < "\n";
        }
        //if(i == 2) std:: cerr << uglynum << "\n";
        invfact/=(double)i;
        //std::cerr << '*' << invfact <<"*" << make_poly(S(differences[i][0]));
        if(!(this -> is_backward)){
            uglynum = uglynum * make_poly(S(invfact)) * make_poly(S(differences[i][0]));
            //std::cerr << differences[i][0] << "\n";
        }
        else{
             uglynum = uglynum * make_poly(S(invfact)) * make_poly(S(differences[i].back()));
             //std::cerr << differences[i].back() << "\n";
        }
        finpoly = finpoly + uglynum;
    }
    //std::cerr << "\n";
    
    return finpoly;
}
template<class S,S(*e)()>
polynomial<S> newtonsforward<S,e> :: genpoly_central(int idx){
    std::vector<std::vector<S>> differences = gen_differences(this->yvals);
    std :: cerr << " differences table \n";
    for(int i = 0; i < (int)differences[0].size(); ++i){
        for(int j = 0; j < (int)differences.size(); ++j){
            if(i >= differences[j].size()){
                break;
            }
            else{
                std :: cerr << differences[j][i] << "\t";
            }
        }
        std :: cerr << "\n";
    }
    double invfact = 1.0;
    int mul = 1;
    if(is_backward){
        mul = -1;
    }
    polynomial<S>unity = make_poly<S>(S(1));
    std::vector<S> pv = {-this->xvals[idx],S(1)};
    polynomial<S>ppoly(pv);
    ppoly = ppoly * ((S)(1)/ this-> h);
    polynomial<S>ppolysq = ppoly * ppoly;
    polynomial<S>finpoly = make_poly<S>(differences[0][idx]);
    //std::cerr << "the first term is " << differences[0][idx] << "\n";
    for(int i = 1; i < (int)differences.size() && idx >= 0; i+=2){
        auto common = unity;
        for(int j = 1; j <= i/2 ; ++j){
            polynomial<S>tosub = make_poly(S(-j*j));
            auto tomul = ppolysq + tosub;
            common = common * tomul;
        }
        S mulone = S(0);
        S multwo = S(0);
        if(idx){
            mulone = differences[i][idx] + differences[i][idx-1];
            mulone /= 2.0;
            if(i + 1 < (int)differences.size()){
                multwo = differences[i+1][idx - 1];
            }
        }
        //std :: cerr << common << "\n";
        //std::cerr << "multiplier for next term is " << mulone << "\n";
        //std::cerr << "multiplier for next term is " << multwo << "\n";
        invfact /= (i);
        //std :: cerr << invfact << "\n";
        std :: cerr << ppoly << " * "<< common << " * "<< mulone << " * "<< invfact << " = \n\n";
        auto nxtterm = ppoly * common * mulone * invfact;
        std :: cerr << nxtterm << "\n\n";
        finpoly = finpoly + nxtterm;
        invfact /= (i+1);
        //std :: cerr << invfact << "\n";
        nxtterm = ppolysq * common * multwo * invfact;
        finpoly = finpoly + nxtterm;
        idx--;
    }
    //std:: cerr << finpoly << "\n";
    return finpoly;
}
double e(){
    return 1e-13;
}
int main(){
    float x;
    std::vector<double>x_vals = {0.f,0.1,0.2,0.3,0.4,0.5,0.6};
    std::vector<double>y_vals = {30.13,31.62,32.87,33.64,33.95,33.81,33.24};
    newtonsforward<double,e>test1(x_vals,y_vals,false);
    auto tmp = test1.genpoly();
    auto tmp2 = test1.genpoly_central(3);
    tmp2.sanitize();
    tmp.sanitize();
    std :: cerr << tmp << "\n\n";
    std :: cerr << tmp2 << "\n";
    std :: cerr << tmp.evaluate(0.1) << "\n";
    std :: cout << "\n"<< tmp2.differentiate().evaluate(0.3) << "\n";
    std :: cout << "\n"<< tmp2.differentiate().differentiate().evaluate(0.3) << "\n";
    /*for(auto a : x_vals){
        std::cout << tmp2.evaluate(a) << " : " << tmp.evaluate(a) << "\n";
    }*/
}

//    works for both forward and backward differences and now central differences...
/*
    for central differences you give the position of the point of interest for example in the above example you if you are interested in 0.3 you pass 3 as a parameter to central differences as shown above...  the polynomials are the same for central and forward and backward differences... Based on the examples done... For printing you might have to edit the code yourself
*/
    

