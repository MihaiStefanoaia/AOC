#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

bool is_nice_p1(const char* str){
    bool has_duplicate = false;
    int vowels = 0;
    std::vector<const char*> forbidden = {"ab","cd","pq","xy"}; 
    for(auto f : forbidden){
        if(strstr(str,f))
            return false;
    }    
    if(strchr("aeiou",str[0]))
        vowels++;
    for(int i = 1; str[i]; i++){
        if(strchr("aeiou",str[i]))
            vowels++;
        if(str[i] == str[i-1])
            has_duplicate = true;
    }
    return has_duplicate && (vowels >= 3);
}

bool is_nice_p2(const char* str){
    bool repeats = false;
    for(int i = 2; str[i]; i++){
        if(str[i] == str[i-2] && str[i] != str[i-1])
            repeats = true;
    }
    if(!repeats)
        return false;
    
    char pair[3] = {0};
    for(int i = 0; str[i+2]; i++){
        pair[0] = str[i];
        pair[1] = str[i+1];
        if(strstr(str + i + 2,pair)){
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    int count_p1 = 0;
    int count_p2 = 0;
    char cs[128];
    while(f.getline(cs,127)){
        if(is_nice_p1(cs)){
            count_p1++;
        }
        if(is_nice_p2(cs)){
            count_p2++;
        }
    }
    std::cout << count_p1 << ' ' << count_p2;
    return 0;
}
