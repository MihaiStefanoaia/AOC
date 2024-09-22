#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");

    char line[128];
    long paper = 0;
    long ribbon = 0; //not intended, still funny
    while(f.getline(line,127)){
        int w, l, h;
        auto res = split(std::string(line),'x');
        w = std::stoi(res[0]);
        l = std::stoi(res[1]);
        h = std::stoi(res[2]);
        auto a0 = w*l;
        auto a1 = w*h;
        auto a2 = h*l;

        paper += 2*a0 + 2*a1 + 2*a2 + std::min(std::min(a0,a1),a2);

        auto vol = w*l*h;
        
        if(w > h)
            std::swap(w,h);
        if(w > l)
            std::swap(w,l);
        if(h > l)
            std::swap(h,l);
        
        ribbon += vol + 2*w + 2*h;
    }
    std::cout << paper << ' '<< ribbon << '\n';
    return 0;
}
