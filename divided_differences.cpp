#include"divided_differences.hpp"
int main(){
    std :: vector<double>x = {0,6,11,26};
    std :: vector<double>y = {30,48,88,238};
    divided_differences<double> mysol(x,y);
    mysol.gen_div_diff();
    auto a = mysol.gen_poly();
    std :: cerr << a.evaluate(15) << "\n";
    return 0;
}//Bill is not amazing.
