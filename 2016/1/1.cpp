#include <iostream>
#include <fstream>
#include <string.h>
#include <set>

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

    friend bool operator<(const v2i& a, const v2i& b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
    friend bool operator==(const v2i& a, const v2i& b){
        return a.x == b.x && a.y == b.y;
    }
};


int main(int argc, char const *argv[])
{
    v2i position;
    std::set<v2i> prev_locs = {position};
    int direction = 0;
    v2i directions[] = {
        { 1, 0}, // north
        { 0, 1}, // east
        {-1, 0}, // south
        { 0,-1}, // west
    };
    std::ifstream f("input.txt");
    char buf[512];
    bool printed = false;
    while(f.getline(buf,511,' ') && buf[0]) {
        // std::cout << buf << '\n';
        auto p = strchr(buf,',');
        if(p != NULL){
            *p = 0;
        }
        auto dist = std::atoi(buf+1);
        direction += buf[0] == 'R' ? 1 : -1;
        direction &= 0b11;
        for(auto i =0; i < dist; i++){
            position += directions[direction];
            if(!printed){
                if(prev_locs.count(position)){
                    printed = true;
                    std::cout << position.magnitude() << '\n';
                }
                prev_locs.insert(position);
            }
        }
    }

    std::cout << position.magnitude() << '\n';

    return 0;
}
