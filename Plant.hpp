#pragma once
#include <ncurses.h>
#include "Const.h"
#include <string.h>

class Plant{
protected:
    char name[15];
    int price;
    int hp;
    int type;
    int attack;
    int col;
    int row;
    int product_speed;
    int product_count;
    int shot_speed;
    int shot_count;
public:
    Plant(int TYPE,int PRICE,int ATTACK,int HP,const char* NAME,int PRODUCTSPEED,int SHOTSPEED){
        type = TYPE;
        price = PRICE;
        attack = ATTACK;
        hp = HP;
        strcpy(name,NAME);
        col = -1;
        row = -1;
        product_speed = PRODUCTSPEED;
        product_count = 0;
        shot_count = 0;
        shot_speed = SHOTSPEED;
    }
    Plant(const Plant &plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        strcpy(name,plant.name);
        col = plant.col;
        row = plant.row;
        product_speed = plant.product_speed;
        shot_speed = plant.shot_speed;
        shot_count = 0;
    }

    Plant& operator = (const Plant& plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        col = plant.col;
        row = plant.row;
        product_speed = plant.product_speed;
        shot_speed = plant.shot_speed;
        shot_count = 0;
        strcpy(name,plant.name);
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
        mvprintw(starty+3,startx+3,"%s",name);
        mvprintw(starty+4,startx+3,"(%d)",hp);
    }
    void plant(int r,int c){
        col = c;
        row = r;
    }
    int get_sunny(){
        if(product_count < product_speed){
            product_count++;
            return 0;
        }else{
            product_count-= product_speed;
            return 1;
        }
    };
    bullet shot(){
        if(type == ATTACK_PLANT && shot_speed!= 0){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = row;
            b.local = 12;
            if(shot_count >= shot_speed){
                b.valid = true;
                shot_count -= shot_speed;
            }
            else
                b.valid = false;
            return b;
        }
        else{
            bullet b;
            b.valid = false;
            return b;
        }
    }
};

// class SunFlower: public Plant{
// public:
//     SunFlower():Plant(SUNNY_PLANT,25,0,100,"sunflower"){
//         ProductSunny = 2;
//     };
//     int get_sunny(){
//         return ProductSunny;
//     };
//     Plant& operator = (const SunFlower& plant){
//         type = plant.type;
//         price = plant.price;
//         attack = plant.attack;
//         hp = plant.hp;
//         name = plant.name;
//     }
// };

// class PeaShooter: public Plant{
// int shot_speed;
// int shot_count;
// public:
//     PeaShooter():Plant(ATTACK_PLANT,25,20,100,"peashooter"){
//         shot_speed = 10;
//         shot_count = 0;
//     };
//     bullet shot(){
//         bullet b;
//         b.attack = attack;
//         b.col = col;
//         b.row = row;
//         b.local = 50;
//         if(shot_count == shot_speed){
//             b.valid = true;
//         }
//         else
//             b.valid = false;
//         return b;
//     }
// };