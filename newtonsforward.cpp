#include "newtonsforward.hpp"
#include "polynomial.cpp"
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
template<class S> 
polynomial<S>make_poly(S i){
    std::vector<S>val = {i};
    return polynomial<S>(val);
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
    polynomial<S>unity = make_poly<S>(S(1));
    std::vector<S> pv = {-this->xvals[0],S(1)};
    polynomial<S>finpoly = make_poly<S>(this->yvals[0]);
    polynomial<S>ppoly(pv);
    ppoly = ppoly * ((S)(1)/ this-> h);
    //std::cerr << finpoly;
    for(int i = 1; i < (int)differences.size(); ++i){
        //std::cerr << " + ";
        polynomial<S> uglynum = unity;
        for(int j = 0; j < i; ++j){
            polynomial<S> new_poly = ppoly + make_poly(S(-j));
            uglynum = uglynum * new_poly;
            //std::cerr <<'(' << new_poly << ')';
        }
        invfact/=(double)i;
        //std::cerr << '*' << invfact <<"*" << make_poly(S(differences[i][0]));
        uglynum = uglynum * make_poly(S(invfact)) * make_poly(S(differences[i][0]));
        finpoly = finpoly + uglynum;
    }
    //std::cerr << "\n";
    return finpoly;
}
double e(){
    return 1e-13;
}
int main(){
    std::vector<double>x_vals = {1.0,1.5,2.0,2.5};
    std::vector<double>y_vals = {2.718,4.481,7.387,12.179};
    newtonsforward<double,e>test1(x_vals,y_vals);
    std :: cout << "\n"<< test1.genpoly().evaluate(1.362537) << "\n";
    
}
