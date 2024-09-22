#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class command {
public:
    enum cmd_t {TURN_ON,TURN_OFF,TOGGLE};
    cmd_t cmd;
    std::pair<int,int> start;
    std::pair<int,int> end;
    static command parse(std::string str){
        command ret;
        std::stringstream ss(str);
        std::vector<std::string> v = {};
        char buf[128];
        while(ss.getline(buf,127,' ')){
            v.push_back(buf);
        }
        int offset = 0;
        if(v[0] == "turn"){
            if(v[1] == "on"){
                ret.cmd = TURN_ON;
            } else {
                ret.cmd = TURN_OFF;
            }
            offset = 1;
        } else {
            ret.cmd = TOGGLE;
        }

        std::stringstream ss_start(v[1 + offset]);
        ss_start.getline(buf,127,',');
        ret.start.first = std::stoi(buf);
        ss_start.getline(buf,127,',');
        ret.start.second = std::stoi(buf);

        std::stringstream ss_finish(v[3 + offset]);
        ss_finish.getline(buf,127,',');
        ret.end.first = std::stoi(buf);
        ss_finish.getline(buf,127,',');
        ret.end.second = std::stoi(buf);

        return ret;
    }
    void execute(int **leds){
        for(int i = start.first; i <= end.first; i++)
            for(int j = start.second; j <= end.second; j++){
                switch(cmd){
                case TURN_ON:
                    leds[i][j] += 1;
                    break;
                case TURN_OFF:
                    leds[i][j] = std::max(0,leds[i][j]-1);
                    break;
                case TOGGLE:
                    leds[i][j] += 2;
                    break;
                }
            }
    }
        void execute_1(int **leds){
        for(int i = start.first; i <= end.first; i++)
            for(int j = start.second; j <= end.second; j++){
                switch(cmd){
                case TURN_ON:
                    leds[i][j] = 1;
                    break;
                case TURN_OFF:
                    leds[i][j] = 0;
                    break;
                case TOGGLE:
                    leds[i][j] = leds[i][j] ? 0 : 1;
                    break;
                }
            }
    }
    friend std::ostream& operator <<(std::ostream& o, const command& cmd){
        std::string s;
        switch(cmd.cmd){
        case command::TURN_ON:
            s = "turn on ";
            break;
        case command::TURN_OFF:
            s = "turn off";
            break;
        case command::TOGGLE:
            s = "toggle  ";
            break;
        }
        o << s << " [" << cmd.start.first << " " << cmd.start.second << "]" << " -> " << "[" << cmd.end.first << " " << cmd.end.second << "]";
        return o;
    } 
};



int main(int argc, char const *argv[])
{
    std::ifstream f("input.txt");
    int** leds;
    leds = new int*[1000];
    for(int i = 0; i < 1000; i++)
        leds[i] = new int[1000] {false};
    char buf[128];
    while(f.getline(buf,127)){
        auto cmd = command::parse(buf);
        // std::cout << cmd << "\n";
        cmd.execute(leds);
        // cmd.execute_1(leds);
    }

    int count = 0;
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 1000; j++)
                count += leds[i][j];
    std::cout << count << "\n";
    return 0;
}
