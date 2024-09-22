#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>

int factor_sum(int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i + n/i;
        }
    }
    return sum;
}

inline int part_1(const int input){
   for(int x = 1; ; x++){
        int a = factor_sum(x);
        if(a >= input / 10){
            return x;
        }
    }
}

int factor_sum_p2(int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if(i <= 50)
                sum += n/i;
            if(n/i <= 50)
                sum += i;
        }
    }
    return sum * 11;
}

inline int part_2(const int input){
    for(int x = 1; x ; x++){
        int a = factor_sum_p2(x);
        if(a >= input){
            return x;
        }
    }
}


int main(int argc, char const *argv[])
{
    const int input = 34000000;
    std::cout << part_1(input) << '\n' << part_2(input);
    return 0;
}
