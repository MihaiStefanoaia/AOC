#include <fstream>
#include <string>
#include <iostream>

#include "md5.h"

bool check_hash_5(unsigned* hash){
    if((hash[0] & 0xF0FFFF) == 0){
        return true;
    } else {
        return false;
    }
}

bool check_hash_6(unsigned* hash){
    if((hash[0] & 0xFFFFFF) == 0){
        return true;
    } else {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    int index = 0;
    std::string key = "yzbqklnj";
    while(true){
        auto hash = md5::MD5Hash(key + std::to_string(index));
        if((index & 0xFFFF) == 0)
            std::cout << index << '\n';
        if(check_hash_5(hash)){
            std::cout << md5::GetMD5String(key + std::to_string(index));
            std::cout << " ";
            std::cout << (key + std::to_string(index));
            std::cout << "\n";
            if(check_hash_6(hash))
                break;
        }
        index++;
    }
    return 0;
}
