#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <cstring>
#include <map>
#include <limits.h>

std::string to_string(std::vector<std::string> v){
    std::string ret;
    for(auto s : v){
        ret += s;
    }
    return ret;
}

std::vector<std::string> split_by_spaces(char* s){
    std::stringstream ss(s);
    std::vector<std::string> parse;
    char p_buf[128];
    while(ss.getline(p_buf,127,' ')){
        parse.push_back(p_buf);
    }
    return parse;
}

std::vector<std::string> split_by_tokens(const char* s, std::set<std::string> tok){
    auto len = strlen(s);
    char buf[3] = {0};
    std::vector<std::string> ret;
    for(int i = 0; i < len; i++){
        buf[1] = 0;
        buf[0] = s[i];
        if(tok.count(buf)){
            ret.push_back(buf);
        } else {
            if(s[i+1] >= 'A' && s[i+1] <= 'Z'){
                ret.push_back(buf);
                continue;
            }
            buf[1] = s[i+1];
            ret.push_back(buf);
            i++;
        }
    }
    return ret;
}

unsigned int steps_to_generate(std::string to_make,const std::set<std::string> tokens, const std::map<std::string,std::vector<std::string>>& transforms){
    auto tknz = split_by_tokens(to_make.c_str(),tokens);
    int Rn = 0;
    int Ar = 0;
    int Y = 0;
    for(auto t : tknz){
        if(t == "Rn")
            Rn++;
        if(t == "Ar")
            Ar++;
        if(t == "Y")
            Y++;
    }
    return tknz.size() - Rn - Ar - 2*Y - 1;
}

int main(int argc, char const *argv[])
{
    std::set<std::string> molecules;
    std::ifstream f("input.txt");
    std::map<std::string,std::vector<std::string>> transformations;
    std::set<std::string> tokens;
    char buf[512];
    while(f.getline(buf,511) && buf[0]) {
        auto parse = split_by_spaces(buf);

        transformations[parse[0]].emplace_back(parse[2]);
        tokens.insert(parse[0]);
    }
    f.getline(buf,511);

    for(auto tr : transformations){
        std::cout << tr.first << " -> { ";
        for(auto t : tr.second){
            std::cout << t << ' ';
        }
        std::cout << "}" << '\n';
    }
    std::cout << buf << '\n';

    auto split = split_by_tokens(buf,tokens);
    for(auto c : split){
        std::cout << c << ' ';
    }
    std::cout << '\n';

    for(int i = 0; i < split.size(); i++){
        if(!tokens.count(split[i]))
            continue;
        auto tmp = split[i];
        for(auto tr : transformations[split[i]]){
            split[i] = tr;
            molecules.insert(to_string(split));
        }
        split[i] = tmp;
    }

    std::cout << molecules.size() << '\n';
    std::cout << steps_to_generate(buf,tokens,transformations) << '\n';
    return 0;
}
