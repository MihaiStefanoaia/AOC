#include <iostream>
#include <fstream>
#include <unordered_set>

class vector2i{
public:
    int x;
    int y;
    vector2i(int x, int y) : x(x),y(y){};
    uint64_t to_uint64(){
        return *(uint64_t*)this;
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    std::unordered_set<uint64_t> houses;
    vector2i santa = {0,0};
    vector2i robot = {0,0};
    vector2i* active = &santa;
    char c;
    houses.insert(santa.to_uint64());
    while(f.get(c)){
        switch(c){
            case '<':
                active->x--;
                break;
            case '>':
                active->x++;
                break;
            case 'v':
                active->y--;
                break;
            case '^':
                active->y++;
                break;
        }
        houses.insert(active->to_uint64());
        if(active == &santa)
            active = &robot;
        else
            active = &santa;
    }
    std::cout << houses.size() << '\n';

    return 0;
}
