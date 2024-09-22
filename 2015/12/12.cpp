#include <iostream>
#include <cstring>
#include <fstream>
#include "json.hpp"

int add_from_json(nlohmann::json& j){
    int sum = 0;
    if(j.is_number())
        return j;
    if(j.is_object()){
        //ignore
        for(auto v : j){
            if(v == "red")
                return 0;
        }
        
        for(auto o : j){
            sum += add_from_json(o);
        }        
    } else if(j.is_array()){
        for(auto o : j){
            sum += add_from_json(o);
        }
        //do not ignore
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    char ch;
    int nr = 0;
    bool is_neg = false;
    std::ifstream f("12_input.txt");

    int sum = 0;
    while(f.read(&ch,1)){
        if(ch == '-'){
            is_neg = true;
        } else if(ch >= '0' && ch <= '9'){
            nr = nr * 10;
            nr += ch - '0';
        } else {
            if(is_neg)
                nr = -nr;
            is_neg = false;
            sum += nr;
            nr = 0;
        }
    }
    std::cout << sum << '\n';

    std::ifstream fj("12_input.txt");
    nlohmann::json j = nlohmann::json::parse(fj);
    std::cout << add_from_json(j) << "\n";
    return 0;
}