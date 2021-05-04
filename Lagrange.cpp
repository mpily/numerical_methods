#include"Lagrange.hpp"
int main(){
    std::vector<double> x = {0,1,5};
    std::vector<double> y = {15,48,85};
    Lagrange<double>inter(x,y);
    inter.generate_Ls();
    std::cout << inter.lagrange_interpol.evaluate(2) << "\n";
}
/*
    this file is mostly for testing purposes;
*/
