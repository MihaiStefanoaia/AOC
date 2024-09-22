#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    int buf = 0;
    std::vector<int> cbuf;

    while(f >> buf){
        cbuf.push_back(buf);
    }

    int answers = 0;
    unsigned amount = 150;
    int siz = cbuf.size();

    int* containers = new int[cbuf.size()];
    int minpop = 32;
    int ans_minpop = 0;

    for(int i = 0; i < siz; i++){
        containers[i] = cbuf[i];
    }

    for(unsigned int mask = 0; mask < (1<<siz); mask++){
        unsigned int acc = 0;
        auto pop = 0;
        for(int i = 0; i < siz; i++){
            acc += containers[i] & (0 - ((mask >> i) & 1));
            pop += ((mask >> i) & 1);
        }
        if(amount == acc){
            answers++;            
            if(pop < minpop){
                minpop = pop;
                ans_minpop = 0;
            }
            if(pop == minpop){
                ans_minpop++;
            }
        }
    }

    std::cout << std::dec << answers << ' ' << ans_minpop << '\n';
    return 0;
}
