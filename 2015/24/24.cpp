#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>

bool is_2way_splittable(std::vector<std::tuple<int,int>>& filtered, int target){
    int sum = 0;
    for(const auto& [n, used] : filtered){
        sum += n*(used != 0);
    }
    for(auto& [n, used] : filtered){
        if(used || sum + n > target){
            continue;
        }
        if(sum + n == target){
            return true;
        }
        used = 2;
        auto res = is_2way_splittable(filtered,target);
        used = false;
        if(res){
            return true;
        }
    }
    return false;
}

bool can_be_evenly_split(std::vector<std::tuple<int,int>>& presents,int target){
    std::vector<std::tuple<int,int>> filtered;
    for(const auto& [n, used] : presents){
        if(!used){
            filtered.push_back({n,false});
        }
    }
    return is_2way_splittable(filtered,target);
}

int shortest = -1;
std::vector<std::vector<int>> generate_center(std::vector<std::tuple<int,int>>& presents, int target, int starting = 0){
    std::vector<std::vector<int>> ret;
    int sum = 0;
    int len = 0;
    for(const auto& [n, used] : presents){
        sum += n*used;
        len += 1*used;
    }
    if(len + 1 > shortest){
        return {};
    }

    int idx = 0;
    for(auto& [n, used] : presents){
        idx++;
        if(used || idx < starting || sum + n > target){
            continue;
        }
        used = true;
        if(sum + n == target && can_be_evenly_split(presents,target)){
            std::vector<int> v;
            for(const auto& [x, u] : presents){
                if(u){
                    v.push_back(x);
                }
            }
            ret.push_back(v);
            shortest = v.size();
            for(auto i : v){
                std::cout << i << ' ';
            }
            std::cout << ';' << shortest << ' ' << sum + n << '\n';
            used = false;
            continue;
        }
        auto results = generate_center(presents,target,idx);
        for(auto& r : results){
            ret.push_back(r);
        }
        used = false;
    }
    return ret;
}

int main(int argc, char const *argv[]){
    std::vector<std::tuple<int,int>> presents;
    int i_buf;
    char c_buf[512];
    std::ifstream f("input.txt");
    auto sum = 0;
    while(f.getline(c_buf,511)){
        auto x = std::atoi(c_buf);
        sum += x;
        presents.push_back({x,false});
    }
    std::sort(presents.begin(),presents.end(),[](auto a, auto b){ return a > b;});
    auto tgt = sum / 3;
    shortest = presents.size();
    std::cout << shortest << '\n';
    std::vector<std::vector<int>> solutions = generate_center(presents,tgt);
    
    std::cout << sum << " " << tgt << "\n";
    std::vector<unsigned long long int> entanglements;
    for(auto& sol : solutions){
        if(sol.size() != shortest){
            continue;
        }
        unsigned long long int qe = 1;
        for(auto i : sol){
            qe *= i;
            std::cout << i << ' ';
        }
        std::cout << "; " << qe << '\n';
        entanglements.push_back(qe);
    }
    std::sort(entanglements.begin(),entanglements.end());
    std::cout << entanglements[0] << '\n';
    return 0;
}
