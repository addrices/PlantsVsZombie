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
public:
    Plant(int TYPE,int PRICE,int ATTACK,int HP,const char* NAME){
        type = TYPE;
        price = PRICE;
        attack = ATTACK;
        hp = HP;
        strcpy(name,NAME);
        col = -1;
        row = -1;
    }
    Plant(const Plant &plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        strcpy(name,plant.name);
        col = plant.col;
        row = plant.row;
    }

    Plant& operator = (const Plant& plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        col = plant.col;
        row = plant.row;
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
    virtual int get_sunny(){
        return 0;
    };
    virtual bullet shot(){
        bullet b;
        b.valid = false;
        return b;
    };
    virtual Plant* copy_me() = 0;
    virtual bool IfBoom(){
        return false;
    };
    virtual int get_BoomScope(){
        return 0;
    };

};

class SunFlower: public Plant{
    int product_count;
    int product_speed;
public:
    SunFlower():Plant(SUNNY_PLANT,25,0,100,"sunflower"){
        product_count = 0;
        product_speed = 10;
    };
    SunFlower(const SunFlower &plant):Plant(SUNNY_PLANT,25,0,100,"sunflower"){
        product_count = plant.product_count;
        product_speed = plant.product_speed;
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
    Plant* copy_me(){
        SunFlower* np = new SunFlower();
        return np;
    }
    SunFlower& operator = (const SunFlower& plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        col = plant.col;
        row = plant.row;
        strcpy(name,plant.name);
        product_count = plant.product_count;
        product_speed = plant.product_speed;
    }
};

class PeaShooter: public Plant{
protected:
    int shot_speed;
    int shot_count;
public:
    PeaShooter():Plant(ATTACK_PLANT,25,20,100,"peashooter"){
        shot_speed = 10;
        shot_count = 0;
    };
    PeaShooter(const PeaShooter &plant):Plant(ATTACK_PLANT,25,20,100,"peashooter"){
        shot_count = plant.shot_count;
        shot_speed = plant.shot_speed;
    }

    virtual bullet shot(){
        if(type == ATTACK_PLANT && shot_speed!= 0){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = row;
            b.local = 12;
            b.cold = false;
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
    Plant* copy_me(){
        PeaShooter* np = new PeaShooter();
        return np;
    }
    PeaShooter& operator = (const PeaShooter& plant){
        type = plant.type;
        price = plant.price;
        attack = plant.attack;
        hp = plant.hp;
        col = plant.col;
        row = plant.row;
        strcpy(name,plant.name);
        shot_count = plant.shot_count;
        shot_speed = plant.shot_speed;
    }
};


class Potato : public Plant{
public:
    Potato():Plant(HANHAN_PLANT,15,0,800,"patato"){};
    Plant* copy_me(){
        Potato* np = new Potato();
        return np;
    }
};

class BigPotato : public Plant{
public:
    BigPotato():Plant(HANHAN_PLANT,25,0,1500,"bigpatato"){};
    Plant* copy_me(){
        BigPotato* np = new BigPotato();
        return np;
    }
};

class Garlic :public Plant{
public:
    Garlic():Plant(GARLIC_PLANT,50,0,100,"garlic"){};
    Plant* copy_me(){
        Garlic* np = new Garlic();
        return np;
    }
};

class ColdPeaShooter : public PeaShooter{
public:
    ColdPeaShooter():PeaShooter(){
        strcpy(name,"Cpeashooter");
        price = 30;
    };
    virtual bullet shot(){
        if(type == ATTACK_PLANT && shot_speed!= 0){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = row;
            b.local = 12;
            b.cold = true;
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
    Plant* copy_me(){
        ColdPeaShooter* np = new ColdPeaShooter();
        return np;
    }    
};

class FastPeaShooter : public PeaShooter{
public:
    FastPeaShooter():PeaShooter(){
        strcpy(name,"Fpeashooter");
        shot_speed = 4;
        price = 50;
    };
    virtual bullet shot(){
        if(type == ATTACK_PLANT && shot_speed!= 0){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = row;
            b.local = 12;
            b.cold = false;
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
    Plant* copy_me(){
        FastPeaShooter* np = new FastPeaShooter();
        return np;
    }    
};

class DoublePeaShooter : public PeaShooter{
int flag;
public:
    DoublePeaShooter():PeaShooter(){
        strcpy(name,"Dpeashooter");
        price = 50;
        flag = false;
    };
    virtual bullet shot(){
        if(flag == true){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = (row+1)%ROW;
            b.local = 12;
            b.cold = false;
            b.valid = true;
            flag = false;
            return b; 
        }
        if(type == ATTACK_PLANT && shot_speed!= 0){
            shot_count++;
            bullet b;
            b.attack = attack;
            b.col = col;
            b.row = row;
            b.local = 12;
            b.cold = false;
            if(shot_count >= shot_speed){
                b.valid = true;
                shot_count -= shot_speed;
                flag = true;

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
    Plant* copy_me(){
        DoublePeaShooter* np = new DoublePeaShooter();
        return np;
    }    
};

class PumpkinBoom : public Plant{
int count;
int BoomScope;
public:
    PumpkinBoom():Plant(BOOM_PLANT,25,300,300,"PumpkinBoom"){
        BoomScope = BLOCK_BOOM;
        count = 3;
    }
    bool IfBoom(){
        if(count == 0)
            return true;
        count--;
        return false;
    }
    int get_BoomScope(){
        return BoomScope;
    }
    Plant* copy_me(){
        PumpkinBoom* np = new PumpkinBoom();
        return np;
    }    
};

class ChiliBoom : public Plant{
int count;
int BoomScope;
public:
    ChiliBoom():Plant(BOOM_PLANT,55,300,300,"ChiliBoom"){
        BoomScope = LINE_BOOM;
    }
    int get_BoomScope(){
        return BoomScope;
    }
    bool IfBoom(){
        if(count == 0)
            return true;
        count--;
        return false;
    }
    Plant* copy_me(){
        ChiliBoom* np = new ChiliBoom();
        return np;
    }    
};
