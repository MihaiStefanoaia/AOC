#include <fstream>
#include <string>
#include <iostream>
#include <tuple>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <limits.h>

std::pair<std::pair<std::string,std::string>,int> parse(const char* str){
    std::stringstream ss(str);
    char buf[128];
    ss.getline(buf,127,' ');
    std::string src = buf;
    ss.getline(buf,127,' ');
    ss.getline(buf,127,' ');
    std::string dst = buf;
    ss.getline(buf,127,' ');
    ss.getline(buf,127,' ');
    int len = std::stoi(buf);    
    return {{src,dst},len};
}

std::map<std::vector<std::string>,int> travelling_salesman_cache;
int travelling_salesman_core(std::set<std::string>& cities, std::map<std::pair<std::string,std::string>,int>& roads, std::vector<std::string> path, bool lt_mode = true){
    
    auto remaining_cities(cities);

    for(auto& p : path){
        if(remaining_cities.count(p))
            remaining_cities.erase(p);
    }

    if(remaining_cities.empty()){
        return 0;
    }

    auto& last_city = path.back();

    std::map<std::string,int> choices = {};
    for(auto& city : remaining_cities){
        auto next_path(path);
        next_path.push_back(city);
        choices[city] = roads[{last_city,city}] + travelling_salesman_core(remaining_cities,roads,next_path,lt_mode);
    }

    int ch = lt_mode ? INT_MAX : INT_MIN;

    for(auto& choice : choices){
        if(lt_mode){
            if(choice.second < ch)
                ch = choice.second;
        } else {
            if(choice.second >= ch)
                ch = choice.second;
        }
    }
    // std::cout << "checking: ";
    // for(auto& p : path){
    //     std::cout << p;
    //     if(p != path.back()){
    //         std::cout << " -> ";
    //     } else {
    //         std::cout << ": " << ch << "\n";
    //     }
    // }
    return ch;
}

int travelling_salesman(std::set<std::string>& cities, std::map<std::pair<std::string,std::string>,int>& roads, bool lt_mode = true){
    std::map<std::string,int> choices = {};
    for(auto& city : cities){
        choices[city] = travelling_salesman_core(cities,roads,{city},lt_mode);
    }
    int ch = lt_mode ? INT_MAX : INT_MIN;

    for(auto& choice : choices){
        if(lt_mode){
            if(choice.second < ch)
                ch = choice.second;
        } else {
            if(choice.second >= ch)
                ch = choice.second;
        }
    }

    return ch;
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");

    char buf[128];

    std::set<std::string> locations;
    std::map<std::pair<std::string,std::string>,int> edges;

    while(f.getline(buf,127)){
        auto tp = parse(buf);
        edges.insert(tp);
        edges.insert({{tp.first.second,tp.first.first},tp.second});
        locations.insert(tp.first.first);
        locations.insert(tp.first.second);
    }
    for(auto kvp : edges){
        std::cout << kvp.first.first << " -> " << kvp.first.second << " = " << kvp.second << "\n";
    }
    std::cout << travelling_salesman(locations,edges,true) << " " << travelling_salesman(locations,edges,false) << "\n";
    return 0;
}
