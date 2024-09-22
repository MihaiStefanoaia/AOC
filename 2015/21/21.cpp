#include <string>
#include <iostream>
#include <vector>


struct item{
    std::string name;
    int cost;
    int damage;
    int armor;
};

struct entity{
    int health;
    int damage;
    int armor;
};

bool run_battle(entity player, entity boss){
    while(player.health > 0 && boss.health > 0){
        boss.health -= std::max(1, player.damage - boss.armor);
        if(boss.health <= 0)
            return true;
        player.health -= std::max(1, boss.damage - player.armor);
    }
    return false;
}

int best_winning(std::vector<item>& weapons, std::vector<item>& armors, std::vector<item>& rings, entity boss){
    int best_cost = 2000000000;
    for(auto const& w : weapons){
        for(auto const& a : armors){
            for(auto const& r1 : rings){
                for(auto const& r2 : rings){
                    if(r1.name == r2.name && r1.name != "None")
                        continue;
                    int cost = w.cost + a.cost + r1.cost + r2.cost;
                    int damage = w.damage + a.damage + r1.damage + r2.damage;
                    int armor = w.armor + a.armor + r1.armor + r2.armor;
                    if(best_cost >= cost && run_battle({100,damage,armor},boss)){
                        best_cost = cost;
                    }
                }
            }
        }
    }
    return best_cost;
}

int worst_losing(std::vector<item>& weapons, std::vector<item>& armors, std::vector<item>& rings, entity boss){
    int best_cost = -1;
    for(auto const& w : weapons){
        for(auto const& a : armors){
            for(auto const& r1 : rings){
                for(auto const& r2 : rings){
                    if(r1.name == r2.name && r1.name != "None")
                        continue;
                    int cost = w.cost + a.cost + r1.cost + r2.cost;
                    int damage = w.damage + a.damage + r1.damage + r2.damage;
                    int armor = w.armor + a.armor + r1.armor + r2.armor;
                    if(best_cost < cost && !run_battle({100,damage,armor},boss)){
                        best_cost = cost;
                    }
                }
            }
        }
    }
    return best_cost;
}

int main(){
    std::vector<item> weapons ={{"Dagger",      8,4,0},
                                {"Shortsword", 10,5,0},
                                {"Warhammer",  25,6,0},
                                {"Longsword",  40,7,0},
                                {"Greataxe",   74,8,0}};
    std::vector<item> armors = {{"None",        0,0,0},
                                {"Leather",    13,0,1},
                                {"Chainmail",  31,0,2},
                                {"Splintmail", 53,0,3},
                                {"Bandedmail", 75,0,4},
                                {"Platemail", 102,0,5}};
    std::vector<item> rings =  {{"None",        0,0,0},
                                {"Damage1",    25,1,0},
                                {"Damage2",    50,2,0},
                                {"Damage3",   100,3,0},
                                {"Defense1",   20,0,1},
                                {"Defense2",   40,0,2},
                                {"Defense3",   80,0,3}};
    std::cout << best_winning(weapons,armors,rings,{103,9,2}) << '\n'
              << worst_losing(weapons,armors,rings,{103,9,2});
    return 0;
}