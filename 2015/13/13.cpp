#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <cstring>
#include <set>
#include <limits.h>

int arrange_core(std::set<std::string>& people, std::map<std::pair<std::string,std::string>,int>& connections, std::vector<std::string> arrangement, bool lt_mode){
    
    auto remaining_people(people);

    for(auto& p : arrangement){
        if(remaining_people.count(p))
            remaining_people.erase(p);
    }

    if(remaining_people.empty()){
        return connections[{arrangement.back(),arrangement.front()}] + connections[{arrangement.front(),arrangement.back()}];
    }

    auto& last_person = arrangement.back();

    std::map<std::string,int> choices = {};
    for(auto& person : remaining_people){
        auto next_arrangement(arrangement);
        next_arrangement.push_back(person);
        choices[person] = connections[{last_person,person}] + connections[{person,last_person}] + arrange_core(remaining_people,connections,next_arrangement,lt_mode);
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

int arrange(std::set<std::string>& people, std::map<std::pair<std::string,std::string>,int>& connections, bool lt_mode = false){
    return arrange_core(people,connections,{*people.begin()},lt_mode);
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    char buf[256];
    std::map<std::pair<std::string,std::string>,int> preferences;
    std::set<std::string> people;
    while(f.getline(buf,255)){
        std::stringstream ss(buf);
        std::vector<std::string> parse;
        char p_buf[128];
        while(ss.getline(p_buf,127,' ')){
            auto pp = strchr(p_buf,'.');
            if(pp)
                *pp = '\0';
            parse.push_back(p_buf);
        }
        people.insert(parse[0]);
        preferences[{parse[0],parse[10]}] = std::stoi(parse[3]) * (parse[2] == "lose" ? -1 : 1);
    }
    // for(auto kvp : preferences){
    //     std::cout << "{" << kvp.first.first << ", " << kvp.first.second << "}" << " = " << kvp.second << "\n";
    // }

    std::cout << arrange(people,preferences) << "\n";

    for(auto p : people){
        preferences[{"You",p}] = 0;
        preferences[{p,"You"}] = 0;
    }
    people.insert("You");
    std::cout << arrange(people,preferences) << "\n";
    return 0;
}
