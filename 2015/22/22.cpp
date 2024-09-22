#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

struct entity{
    int health;
    int mana;
    int damage;
    int armor;
};

struct effect{
    std::string name;
    int instant_damage;
    int damage;
    int healing;
    int armor_increase;
    int recharge_amount;
    int duration;
    int cost;
};

std::vector<effect> spells= {  
                                {"Magic Missile",4,0,0,0,  0,0, 53},
                                {"Drain",        2,0,2,0,  0,0, 73},
                                {"Shield",       0,0,0,7,  0,6,113},
                                {"Poison",       0,3,0,0,  0,6,173},
                                {"Recharge",     0,0,0,0,101,5,229},
                            };
#define FAILURE 10000000
int min_cost = FAILURE;
int cheapest_win(entity player, entity boss, bool hard = false, std::map<effect*,int> active_effects = {}, int mana_spent = 0){
    if(boss.health <= 0){
        min_cost = std::min(min_cost,mana_spent);
        // std::cout << "WON: " << mana_spent << "\t min cost: " << min_cost << '\n';
        return mana_spent;
    }
    if(player.health <= 0){
        // std::cout << "We messed up: " << mana_spent << "\t min cost: " << min_cost << '\n';
        return FAILURE;
    }

    int best = min_cost;

    //try each spell
    for(auto& s : spells){
        if(mana_spent + s.cost >= min_cost || player.mana < s.cost)
            continue;
        // build the copies
        entity player_c = player;
        entity boss_c = boss;
        auto active_effects_c(active_effects);

        // ** your turn **
        if(hard){
            player_c.health -= 1;
            if(player.health <= 0){
                // std::cout << "We messed up: " << mana_spent << "\t min cost: " << min_cost << '\n';
                return FAILURE;
            }
        }

        // apply effects
        player_c.armor = 0;
        for(auto& e : active_effects_c){
            if(e.second == 0)
                continue;
            player_c.mana += e.first->recharge_amount;
            player_c.armor += e.first->armor_increase;
            boss_c.health -= e.first->damage;
            e.second = std::max(0,e.second-1);
        }


        // cast the actual spell
        boss_c.health -= s.instant_damage;
        player_c.health += s.healing;
        player_c.mana -= s.cost;
        active_effects_c[&s] = s.duration;

        // ** boss turn **

        // apply effects
        player_c.armor = 0;
        for(auto& e : active_effects_c){
            if(e.second == 0)
                continue;
            player_c.mana += e.first->recharge_amount;
            player_c.armor += e.first->armor_increase;
            boss_c.health -= e.first->damage;
            e.second = std::max(0,e.second-1);
        }

        // let the boss do it's attack
        player_c.health -= std::max(1, boss_c.damage - player_c.armor);

        // continue the fight after this
        int r = cheapest_win(player_c,boss_c,hard,active_effects_c,mana_spent+s.cost);
        best = std::min(r,best);
    }

    return best;
}


int main(){
    min_cost = FAILURE;
    std::cout << "Easy mode: " << cheapest_win({50,500,0,0},{55,0,8,0},false) << '\n';
    min_cost = FAILURE;
    std::cout << "Hard mode: " << cheapest_win({50,500,0,0},{55,0,8,0},true) << '\n';
    return 0;
}