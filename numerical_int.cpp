#include"numerical_int.hpp"
#include<iostream>
double f(double x){
    return 1./(1. + x * x);
}
int main(){
    integrals<double,f>example1(0.,1.,0.25);
    std :: cout << example1.three_eight();
}
