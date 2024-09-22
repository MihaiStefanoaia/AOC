#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

class wire{
public:
    unsigned short int value = 0;
    bool determined = false;
    int operation = 0;
    wire* op1 = nullptr;
    wire* op2 = nullptr;
    bool determine(){ // returns the change in the determination state
        if(determined)
            return false;
        
        if(operation == 0){ // NOT
            if(op1 == nullptr || !op1->determined)
                return false;

            determined = true;
            value = ~op1->value;
            return true;
        } else if(operation == 1){ //AND
            if(op1 == nullptr || op2 == nullptr || !op1->determined || !op2->determined)
                return false;
            value = op1->value & op2->value;
            determined = true;
            return true;
        } else if(operation == 2){ //OR
            if(op1 == nullptr || op2 == nullptr || !op1->determined || !op2->determined)
                return false;
            value = op1->value | op2->value;
            determined = true;
            return true;
        } else if(operation == 3){ //RSHIFT
            if(op1 == nullptr || op2 == nullptr || !op1->determined || !op2->determined)
                return false;
            value = op1->value >> op2->value;
            determined = true;
            return true;
        } else if(operation == 4){ //LSHIFT
            if(op1 == nullptr || op2 == nullptr || !op1->determined || !op2->determined)
                return false;
            value = op1->value << op2->value;
            determined = true;
            return true;
        } else { //assignment
            if(op1 == nullptr || !op1->determined)
                return false;

            determined = true;
            value = op1->value;
            return true;
        }
    }
};


class machine {
public:
    std::map<std::string, wire*> wires;

    ~machine(){
        for(auto kvp : wires){
            delete kvp.second;
        }
    }
    

    void add_connection(std::string cmd){
        std::cout << cmd << "\n";
        std::vector<std::string> tokens;
        std::stringstream ss(cmd);
        char buf[128];
        while(ss.getline(buf,127,' ')){
            tokens.emplace_back(buf);
        }

        if(tokens[0] == "NOT"){
            if(!wires.count(tokens[1]))
                wires[tokens[1]] = new wire;
            if(!wires.count(tokens[3]))
                wires[tokens[3]] = new wire;
            wires[tokens[3]]->operation = 0;
            wires[tokens[3]]->op1 = wires[tokens[1]];
            return;
        }
        
        wire* op1;
        wire* op2;
        wire* res;
        int operation;

        if(!wires.count(tokens[0]))
            wires[tokens[0]] = new wire;
        op1 = wires[tokens[0]];
        try{
            auto tmp = std::stoi(tokens[0]);
            op1->value = tmp;
            op1->determined = true;
        } catch(std::exception& e){
            std::cout << e.what() << '\n';
        }

        if(!wires.count(tokens[2]))
            wires[tokens[2]] = new wire;
        op2 = wires[tokens[2]];

        try{
            auto tmp = std::stoi(tokens[2]);
            op2->value = tmp;
            op2->determined = true;
        } catch(std::exception& e){
            std::cout << e.what() << '\n';
        }

        if(tokens[1] == "->"){
            res = op2;
            res->operation = 5;
            res->op1 = op1;
            return;
        } else if(tokens[1] == "AND"){
            operation = 1;
        } else if(tokens[1] == "OR"){
            operation = 2;
        } else if(tokens[1] == "RSHIFT"){
            operation = 3;
        } else if(tokens[1] == "LSHIFT"){
            operation = 4;
        }

        if(!wires.count(tokens[4]))
            wires[tokens[4]] = new wire;
        res = wires[tokens[4]];
        res->op1 = op1;
        res->op2 = op2;
        res->operation = operation;
    }
    void execute(){
        for(auto kvp : wires){
            std::cout << kvp.first << ": " << kvp.second->value << "\n";
        }

        bool changed = true;
        while(changed){
            // std::cout << "running pass...\n";
            changed = false;
            for(auto kvp : wires){
                changed = changed || kvp.second->determine();
            }
        }
    }
};


int main(int argc, char const *argv[])
{
    machine m;
    std::ifstream f("input.txt");
    char buf[128];
    while(f.getline(buf,127)){
        m.add_connection(buf);
    }
    m.execute();
    std::cout << m.wires["a"]->value << ' ' << m.wires["b"]->value << "\n";
    return 0;
}
