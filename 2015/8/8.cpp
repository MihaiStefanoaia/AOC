#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

void decode(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '\\'){
            if(str[i+1] == 'x')
                strcpy(str+i,str+i+3);
            else
                strcpy(str+i,str+i+1);
        }
    }
}
void encode(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '\\' || str[i] == '\"'){
            str[strlen(str)+1] = '\0';
            str[strlen(str)  ] = '_';
        }
    }
}

int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    char buf[128];
    char enc[256];
    int code_str_size = 0;
    int proc_str_size = 0;
    int encd_str_size = 0;
    while(f.getline(buf,127)){
        memset(enc,0,256);
        strcpy(enc,buf);
        code_str_size += strlen(buf);
        decode(buf);
        proc_str_size += strlen(buf) - 2;
        // std::cout << enc << '\n';
        encode(enc);
        // std::cout << enc << '\n';
        encd_str_size += strlen(enc)+2;
    }
    std::cout << code_str_size - proc_str_size << " " << encd_str_size - code_str_size;
    return 0;
}
