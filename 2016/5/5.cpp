#include <iostream>
#include <fstream>
#include <string>
#include "./md5.h"
#include <sys/types.h>

char nibbleToHex(char nibble)
{
    auto value = nibble & 0xF;
    if (value < 10)
        return value + '0';
    else
        return value - 10 + 'a';
}

int main(int argc, char const *argv[])
{
    long int index = 0;
    char result_a[9] = {0};
    std::string input;
    std::cin >> input;
    u_int32_t md5_buffer[4] = {~0x0u};
    auto hasher = MD5();
    for(int i = 0; i < 8; i++){
        
        while(true){
            hasher.reset();
            auto tmpstr = input + std::to_string(index);
            hasher.add(tmpstr.c_str(),tmpstr.length());
            hasher.getHash((uint8_t*)md5_buffer);
            if((md5_buffer[0] & 0xF0FFFF) == 0){
                index += 1;
                // std::cout << tmpstr << '\n';
                // std::cout << hasher.getHash() << '\n';
                // std::cout << std::hex << md5_buffer[0] << std::dec << '\n'; 
                // std::cout << index << '\n';
                break;
            }
            index += 1;
        }
        result_a[i] = nibbleToHex((md5_buffer[0] >> 16) & 0xF);
    }
    std::cout << result_a << '\n';
    hasher.reset();
    index = 0;
    char result_b[9] = "________";
    char mask_b[9] = {0};
    result_b[8] = 0;

    while(!mask_b[0] || !mask_b[1] || !mask_b[2] || !mask_b[3] || !mask_b[4] || !mask_b[5] || !mask_b[6] || !mask_b[7]){
        hasher.reset();
        auto tmpstr = input + std::to_string(index);
        hasher.add(tmpstr.c_str(),tmpstr.length());
        hasher.getHash((uint8_t*)md5_buffer);
        index += 1;
        if((md5_buffer[0] & 0xF0FFFF) == 0){
            // std::cout << tmpstr << '\n';
            // std::cout << hasher.getHash() << '\n';
            // std::cout << std::hex << md5_buffer[0] << std::dec << '\n'; 
            // std::cout << index << '\n';
            auto index = (md5_buffer[0] >> 16) & 0xF;
            if(index >= 8 || mask_b[index] == 1){
                continue;
            }
            result_b[index] = nibbleToHex((md5_buffer[0] >> 28) & 0xF);
            mask_b[index] = 1;
            std::cout << "tmp_b: " << result_b << '\n';
        }
    }
    std::cout << result_b << '\n';
    return 0;
}
