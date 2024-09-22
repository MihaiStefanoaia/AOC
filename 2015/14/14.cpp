#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <cstring>
#include <set>
#include <limits.h>

struct reindeer_stats{
    int speed;
    int active_seconds;
    int cycle_len;
    int distance;
    int score;
};

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    char buf[256];
    std::map<std::string,reindeer_stats> reindeers;
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
        reindeers[parse[0]] = {std::stoi(parse[3]),std::stoi(parse[6]),std::stoi(parse[6]) + std::stoi(parse[13]),0,0};
    }
    for(int i = 0; i < 2503; i++){
        for(auto& kvp : reindeers){
            if(i % kvp.second.cycle_len < kvp.second.active_seconds)
                kvp.second.distance += kvp.second.speed;
        }
        int m = 0;
        for(auto& kvp : reindeers){
            m = kvp.second.distance > m ? kvp.second.distance : m;
        }
        for(auto& kvp : reindeers){
            if(kvp.second.distance == m)
                kvp.second.score++;
        }
    }
    int m = 0;
    int s = 0;
    for(auto& kvp : reindeers){
        m = kvp.second.distance > m ? kvp.second.distance : m;
        s = kvp.second.score > s ? kvp.second.score : s;
        std::cout << kvp.first << ": " << kvp.second.score << " (" << kvp.second.distance << " km)\n";
    }
    std::cout << m << ' ' << s << '\n';

    return 0;
}
