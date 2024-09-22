#include <string.h>
#include <iostream>

void process(char* in, char* out, int len){
    memset(out,0,len);
    int out_index = 0;
    char commit_char = in[0];
    char commit_qt = 0;
    auto len = strlen(in);
    for(int i = 0; i < len; i++){
        if(in[i] == commit_char){
            commit_qt++;
        } else {
            out[out_index] = commit_qt + '0';
            out_index++;
            out[out_index] = commit_char;
            out_index++;

            commit_char = in[i];
            commit_qt = 1;
        }
    }
    out[out_index] = commit_qt + '0';
    out_index++;
    out[out_index] = commit_char;
    out_index++;
}

#define BUF_SIZE 4096*4096*2

int main(int argc, char const *argv[])
{
    char *input = new char[BUF_SIZE];
    char *buf = new char[BUF_SIZE];
    strcpy(input,"1113122113");

    for(int i = 0; i < 50; i++){
        process(input,buf,BUF_SIZE);
        char* aux = input;
        input = buf;
        buf = aux;
        std::cout << i << ": " << strlen(input) << '\n';
    }
    std::cout << input << " " << strlen(input);
    return 0;
}
