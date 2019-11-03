#pragma once
#include <ncurses.h>

#define SUNNY_PLANT 1
#define ATTACK_PLANT 2
#define HANHAN_PLANT 3
#define EARTH_PLANT 4

struct bullet{
    int row;
    int col;
    int local;
};

class Plant{
private:
    string name;
    int price;
    int hp;
    int type;
    int attack;
public:
    Plant(int TYPE,int PRICE,int ATTACK,int HP,string NAME){
        type = TYPE;
        price = PRICE;
        attack = ATTACK;
        hp = HP;
        name = NAME;
    }
    Plant(const Plant &plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        name = plant.name;
    }

    Plant& operator = (const Plant& plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        name = plant.name;
    }

    string get_name(){
        return name;
    }
    int get_attack(){
        return attack;
    }
    int get_type(){
        return type;
    }
    int get_hp(){
        return hp;
    }
    int get_price(){
        return price;
    }
    bool attacked(int a){
        hp -= a;
        if(hp <= 0){
            return true;
        }
        return false;
    }
    void draw_me(int starty,int startx){
        mvprintw(starty+3,startx+3,"%s",name.c_str());
        mvprintw(starty+4,startx+3,"(%d)",hp);
    }
};