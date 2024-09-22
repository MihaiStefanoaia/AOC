#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using aunt = std::map<std::string,int>;

std::string rm_last_char(std::string s){
    s.pop_back();
    return s;
}

int correct_aunt(std::vector<aunt>& aunts){
    aunt eq = {
    {"children",3},
    {"samoyeds",2},
    {"akitas",0},
    {"vizslas",0},
    {"cars",2},
    {"perfumes",1}};
    
    aunt lt = {    
    {"pomeranians",3},
    {"goldfish",5}
    };
    
    aunt gt = {
    {"cats",7},
    {"trees",3}
    };

    int index = 1;
    for(auto au : aunts){
        bool fail = false;
        for(auto p : eq){
            if(au.count(p.first) && au[p.first] != p.second){
                fail = true;
            }
        }
        for(auto p : lt){
            if(au.count(p.first) && au[p.first] >= p.second){
                fail = true;
            }
        }
        for(auto p : gt){
            if(au.count(p.first) && au[p.first] <= p.second){
                fail = true;
            }
        }
        if(!fail)
            return index;
        index++;
    }
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    char buf[256];
    std::vector<aunt> aunts;
    std::set<std::string> all_properties = {"children", "cats","samoyeds","pomeranians","akitas","vizslas","goldfish","trees","cars","perfumes"};
    while(f.getline(buf,255)){
        std::stringstream ss(buf);
        std::vector<std::string> parse;
        char p_buf[128];
        while(ss.getline(p_buf,127,' ')){
            parse.push_back(p_buf);
        }
        aunt a = {{rm_last_char(parse[2]),std::stoi(rm_last_char(parse[3]))},
                         {rm_last_char(parse[4]),std::stoi(rm_last_char(parse[5]))},
                         {rm_last_char(parse[6]),std::stoi(parse[7])}};
        aunts.push_back(a);
    }
    std::cout << correct_aunt(aunts) << '\n';
    return 0;
}
