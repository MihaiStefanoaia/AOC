#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[]){
    std::ifstream f("input.txt");
    char buf[4096];
    int hor_possible = 0;
    int ver_possible = 0;
    std::vector<std::vector<int>> v = {{0,0,0},{0,0,0},{0,0,0}};
    int iter = 0;
    while(f.getline(buf,4095) && buf[0]) {
        std::vector<int> vec;
        std::stringstream s(buf);
        // std::cout << buf << "\n";
        char vbuf[256];
        while(s.getline(vbuf,255,' ')){
            if(!vbuf[0]){
                continue;
            }
            vec.push_back(std::atoi(vbuf));
        }        
        // for(auto& n : v){
        //     std::cout << n << " ";
        // }
        // std::cout << "\n";
        v[0][iter] = vec[0];
        v[1][iter] = vec[1];
        v[2][iter] = vec[2];

        std::sort(vec.begin(),vec.end());
        if(vec[0] + vec[1] > vec[2]){
            hor_possible++;
        }

        iter += 1;
        if(iter % 3 == 0) {
            for(auto& iv : v){
                std::sort(iv.begin(),iv.end());
                if(iv[0] + iv[1] > iv[2]){
                    ver_possible++;
                }
            }
            v= {
                {0,0,0},
                {0,0,0},
                {0,0,0},
            };
            iter = 0;
        }
    }
    std::cout << hor_possible << "\n";
    std::cout << ver_possible << "\n";
    return 0;
}
