#include <iostream>
#include <fstream>

void iterate(bool** current, bool** next_st, int size){
    for(int i = 1; i < size-1; i++){
        for(int j = 1; j < size-1; j++){
            int n = 
            current[i-1][j-1] +
            current[i-1][j  ] + 
            current[i-1][j+1] + 
            current[i  ][j-1] + 
            current[i  ][j+1] + 
            current[i+1][j-1] + 
            current[i+1][j  ] + 
            current[i+1][j+1];
            next_st[i][j] = n == 3 || (current[i][j] && n == 2);
        }
    }
}

void iterate_stuck(bool** current, bool** next_st, int size){
    current[1     ][1     ] = true;
    current[1     ][size-2] = true;
    current[size-2][1     ] = true;
    current[size-2][size-2] = true;
    for(int i = 1; i < size-1; i++){
        for(int j = 1; j < size-1; j++){
            int n = 
            current[i-1][j-1] +
            current[i-1][j  ] + 
            current[i-1][j+1] + 
            current[i  ][j-1] + 
            current[i  ][j+1] + 
            current[i+1][j-1] + 
            current[i+1][j  ] + 
            current[i+1][j+1];
            next_st[i][j] = n == 3 || (current[i][j] && n == 2);
        }
    }
    next_st[1     ][1     ] = true;
    next_st[1     ][size-2] = true;
    next_st[size-2][1     ] = true;
    next_st[size-2][size-2] = true;
}

int main(int argc, char const *argv[])
{
    bool** initial;
    bool** lights;
    bool** n_lights;
    char buf;
    
    initial = new bool*[102];
    lights = new bool*[102];
    n_lights = new bool*[102];
    for(int i = 0; i < 102; i++){
        initial[i] = new bool[102]{false};
        lights[i] = new bool[102]{false};
        n_lights[i] = new bool[102]{false};
    }

    std::ifstream f("input.txt");
    for(int i = 1; i < 101; i++){
        for(int j = 1; j < 101; j++){
            f>>buf;
            initial[i][j] = buf == '#';
            lights[i][j] = initial[i][j];
        }
    }

    for(int i = 0; i < 100; i++){
        iterate(lights,n_lights,102);
        std::swap(lights,n_lights);
    }

    int sum = 0;

    for(int i = 1; i < 101; i++){
        for(int j = 1; j < 101; j++){
            sum += lights[i][j];
        }
    }

    std::cout << sum << '\n';

    for(int i = 0; i < 100; i++){
        iterate_stuck(initial,n_lights,102);
        std::swap(initial,n_lights);
    }

    sum = 0;

    for(int i = 1; i < 101; i++){
        for(int j = 1; j < 101; j++){
            sum += initial[i][j];
        }
    }

    std::cout << sum << '\n';

    return 0;
}
