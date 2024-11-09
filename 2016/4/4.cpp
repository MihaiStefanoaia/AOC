#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>
#include <tuple>

bool compare(std::tuple<char,int>& a, std::tuple<char,int>& b){
    auto& [c_a, n_a] = a;
    auto& [c_b, n_b] = b;
    if(n_a != n_b){
        return n_a > n_b;
    }
    return c_a < c_b;
}

template <typename T>
int get_index(std::vector<T> v, T K) {
    auto it = std::find(v.begin(), v.end(), K); 
    if (it != v.end()){ 
        return it - v.begin(); 
    } else { 
        return -1;
    } 
} 

int main(int argc, char const *argv[]){
    std::ifstream f("input.txt");
    char buf[4096];
    int real_rooms = 0;
    while(f.getline(buf,4095) && buf[0]) {
        std::map<char,int> aparitions;
        std::vector<std::tuple<char,int>> ordered;
        auto checksum = strchr(buf,'[');
        buf[strlen(buf) - 1] = 0;
        *checksum = 0;
        checksum += 1;

        auto len = strlen(buf);
        int id; 
        for(auto i = 0; i < len; i++){
            if(buf[i] == '-'){
                continue;
            }
            if(isalpha(buf[i])){
                aparitions[buf[i]] += 1;
            } else if(isalnum(buf[i])){
                id = std::atoi(buf+i);
                break;
            }
        }
        for(auto [c, n] : aparitions){
            ordered.push_back({c,n});
        }
        std::sort(ordered.begin(),ordered.end(),compare);
        // for(auto [c,n] : ordered){
        //     std:: cout << c << ' ' << n << "; ";
        // }
        // std::cout << "\n";

        int valid = 1;
        std::stringstream ss;
        for(auto i = 0; i < 4; i++){
            if(get_index(ordered,{checksum[i],aparitions[checksum[i]]}) >= get_index(ordered,{checksum[i+1],aparitions[checksum[i+1]]})){
                valid = 0;
            }
            auto [c,n] = ordered[i];
            ss << c;
        }
        auto [c,n] = ordered[4];
        ss << c;
        if(valid){
            // std::cout << buf << " " << id << " " << checksum << " " << ss.str() << "\n";
            auto mod_id = id % 26;
            len = strlen(buf);
            for(auto i = 0; i < len; i++){
                if(buf[i] == '-'){
                    buf[i] = ' ';
                    continue;
                }
                if(buf[i] >= '0' && buf[i] <='9'){
                    continue;
                }
                buf[i] -= 'a';
                buf[i] += mod_id;
                buf[i] %= 26;
                buf[i] += 'a';
            }
            std::cout << buf << '\n';
        }
        real_rooms += valid * id;
    }   
    std::cout << real_rooms << '\n';
    return 0;
}
