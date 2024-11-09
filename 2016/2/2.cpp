#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <map>
#include <sstream>
struct v2i
{
    int x = 0;
    int y = 0;

    v2i& operator+=(const v2i& other){
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    friend v2i operator*(const v2i& a,const int scalar){
        return {
            .x=a.x*scalar,
            .y=a.y*scalar
        };
    }
    friend v2i operator+(const v2i& a, const v2i& b){
        return {
            .x=a.x+b.x,
            .y=a.y+b.y
        };
    }

    int magnitude(){
        return std::abs(x) + std::abs(y);
    }

    void clamp(){
        x = std::max(0,x);
        y = std::max(0,y);
        x = std::min(2,x);
        y = std::min(2,y);
    }

    friend bool operator<(const v2i& a, const v2i& b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
    friend bool operator==(const v2i& a, const v2i& b){
        return a.x == b.x && a.y == b.y;
    }
};


int main(int argc, char const *argv[]){
    std::map<char,v2i> directions = {
        {'D',{ 1, 0}},
        {'R',{ 0, 1}},
        {'U',{-1, 0}},
        {'L',{ 0,-1}},
    };
    std::map<v2i,char> keys_v1 = {
        {{0,0},'1'},{{0,1},'2'},{{0,2},'3'},
        {{1,0},'4'},{{1,1},'5'},{{1,2},'6'},
        {{2,0},'7'},{{2,1},'8'},{{2,2},'9'},
    };

    std::map<v2i,char> keys_v2 = {
                                {{0,2},'1'},
                    {{1,1},'2'},{{1,2},'3'},{{1,3},'4'},
        {{2,0},'5'},{{2,1},'6'},{{2,2},'7'},{{2,3},'8'},{{2,4},'9'},
                    {{3,1},'A'},{{3,2},'B'},{{3,3},'C'},
                                {{4,2},'D'},
    };



    std::ifstream f("input.txt");
    char buf[4096];
    std::stringstream v1;
    std::stringstream v2;
    while(f.getline(buf,4095) && buf[0]) {
        v2i position_v1 = {1,1};
        v2i position_v2 = {0,2};
        char res_v1 = -1;
        char res_v2 = -1;
        auto len = strlen(buf);
        for(auto i = 0; i < len; i++){
            position_v1 += directions[buf[i]];
            position_v1.clamp();
            res_v1 = keys_v1[position_v1];


            auto tmp = position_v2 + directions[buf[i]];
            if(keys_v2.count(tmp)){
                position_v2 = tmp;
            }
            res_v2 = keys_v2[position_v2];
        }
        v1 << res_v1;
        v2 << res_v2;
    }
    std::cout << v1.str() << '\n';
    std::cout << v2.str() << '\n';
    return 0;
}
