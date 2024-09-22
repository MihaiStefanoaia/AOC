#include <iostream>
#include <fstream>


int main(){
    std::ifstream f("input.txt");
    int floor = 0;
    int position = 0;
    bool found = false;
    char c;

    while(f.get(c)){
        if(c == '(')
            floor++;
        else if(c == ')')
            floor--;
        position++;
        if(!found && floor < 0){
            found = true;
            std::cout << position << ' ';
        }
    }
    std::cout << floor << '\n';
    return 0;
}