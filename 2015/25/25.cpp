#include <iostream>

unsigned long long order_of(int row, int col){
    int col_start = (col+1) * col / 2;
    unsigned long long val = col_start;
    for(int k = col; k < row + col - 1; k++){
        val += k;
    }

    return val;
}

int main(int argc, char const *argv[])
{
    unsigned long long int seed = 20151125;
    auto result = seed;
    int row = 3083;
    int column = 2978;

    auto order = order_of(2978,3083);

    // for(int i = 1; i <= 8; i ++){
    //     for(int j = 1; j <= 8; j++){
    //         int col_start = (j+1) * j / 2;
    //         int val = col_start;
    //         for(int k = j; k < i + j - 1; k++){
    //             val += k;
    //         }
    //         std::cout << order_of(i,j) << ' ';

    //     }
    //     std::cout << '\n';
    
    //     result *= 252533;
    //     result %= 33554393;
    // }
    for(auto i = 0; i < order-1; i++){
        result *= 252533;
        result %= 33554393;
    }
    std::cout << order << ' ' << result << '\n';
    return 0;
}
