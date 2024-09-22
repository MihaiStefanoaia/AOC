#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>

struct ingredient{
    long capacity;
    long durability;
    long flavor;
    long texture;
    long calories;
    bool operator==(const ingredient& other) const{
        return capacity == other.capacity 
        && durability == other.durability 
        && flavor == other.flavor
        && texture == other.texture
        && calories == other.calories;
    }
    bool operator<(const ingredient& other) const{
        return calories < other.calories;
    }
};

std::string rm_last_char(std::string s){
    s.pop_back();
    return s;
}

long score(std::map<ingredient,long>& quantities){
    long capacity = 0;
    long durability = 0;
    long flavor = 0;
    long texture = 0;
    long calories = 0;

    for(auto kvp : quantities){
        capacity   += (kvp.first.capacity   * kvp.second);
        durability += (kvp.first.durability * kvp.second);
        flavor     += (kvp.first.flavor     * kvp.second);
        texture    += (kvp.first.texture    * kvp.second);
        calories   += (kvp.first.calories   * kvp.second);
    }

    capacity   = std::max(0l,capacity);
    durability = std::max(0l,durability);
    flavor     = std::max(0l,flavor);
    texture    = std::max(0l,texture);
    calories   = std::max(0l,calories);

    return capacity * durability * flavor * texture;
}

long calories(std::map<ingredient,long>& quantities){
    long ret = 0;
    for(auto& kvp : quantities)
        ret += kvp.second * kvp.first.calories;
    return ret;
}

std::pair<long,long> max_score(std::vector<ingredient>& ingredients){
    long s = 0;
    long light = 0;

    std::map<ingredient,long> qts;

    for(long i = 0; i < 100; i++){
        for(long j = 0; j < 100; j++){
            for(long k = 0; k < 100; k++){
                if(i+j+k > 100)
                    break;
                qts[ingredients[0]] = i;
                qts[ingredients[1]] = j;
                qts[ingredients[2]] = k;
                qts[ingredients[3]] = 100 - i - j - k;
                auto sc = score(qts);
                if(s < sc){
                    s = sc;
                }
                if(light < sc && calories(qts) == 500){
                    light = sc;
                }
            }
        }
    }

    return {s,light};
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    char buf[256];
    std::vector<ingredient> ingredients;
    while(f.getline(buf,255)){
        std::stringstream ss(buf);
        std::vector<std::string> parse;
        char p_buf[128];
        while(ss.getline(p_buf,127,' ')){
            parse.push_back(p_buf);
        }
        ingredients.push_back({std::stoi(rm_last_char(parse[2])),std::stoi(rm_last_char(parse[4])),std::stoi(rm_last_char(parse[6])), std::stoi(rm_last_char(parse[8])), std::stoi(parse[10])});
    }
    // for(auto& ing : ingredients){
    //     std::cout << "capacity " << ing.capacity << ", durability " << ing.durability << ", flavor " << ing.flavor << ", texture " << ing.texture << ", calories " << ing.calories <<"\n";
    // }
    auto scores = max_score(ingredients);
    std::cout << scores.first << ' ' << scores.second <<'\n';

    return 0;
}
