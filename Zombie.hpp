#pragma once
#include <string>
#include <string.h>

class item_{
    char name[20];
    int hp;
public:
    item_(char* NAME,int HP){
        strcpy(name,NAME);
        hp = HP;
    }
    bool ruined(int damage){
        hp -= damage;
        if(hp <= 0)
            return true;
        return false;
    }
    char* get_name(){
        return name;
    }
};

class Zombie{
protected:
    char name[20];
    int row_local;
    int col_local;
    int attack;
    item_* Item;
    int speed;
    int health;
    bool cold;
    int type;
    int score;
public:
    int block_local;
    Zombie(int Nrow,int Ncol){
        strcpy( name,"Zombie");
        row_local = Nrow;
        col_local = Ncol;
        Item = NULL;
        speed = 10;
        block_local = 0;
        attack = 2;
        health = 100;
        cold = false;
        type = NORMAL_ZOMBIE;
        score = 100;
    };
    virtual bool hurted(int damage){
        if(Item != NULL){
            if(Item->ruined(damage) == true){
                delete Item;
                Item = NULL;
            }
            return false;
        }
        else{
            health -= damage;
            if(health <= 0)
                return true;
            else
                return false;
        }
    };
    bool walk(){
        if(cold == true){
            cold = false;
            return false;
        }
        block_local += speed;        
        col_local = col_local - 1;
        if(block_local >= 500){
            block_local -= 500;
            return true;
        }
        return false;
    };
    const int get_attack(){
        return attack;
    };
    const int get_row(){
        return row_local;
    };
    const int get_col(){
        return col_local;
    };
    const int get_score(){
        return score;
    }
    char* get_name(){
        return name;
    };
    void freezed(){
        cold = true;
    };
    const int get_type(){
        return type;
    };
    ~Zombie(){
        delete Item;
    };
    char* get_description(){
        if(Item != NULL){
            return Item->get_name();
        }
        else {
            return NULL;
        }
    };
    virtual bool CallZom(){
        return false;
    };
};

class RoadBlockZombie : public Zombie{
public:
    RoadBlockZombie(int Nrow,int Ncol):Zombie(Nrow,Ncol){
        strcpy(name,"RBZombie");
        char na[20] = "RoadBlock";
        Item =  new item_(na,100);
        type = RB_ZOMBIE;
         score = 200;
    }
};

class BucketZombie : public Zombie{
public:
    BucketZombie(int Nrow,int Ncol):Zombie(Nrow,Ncol){
        strcpy(name,"BucketZombie");
        char na[20] = "Bucket";
        Item =  new item_(na,200);
        type = BUCKET_ZOMBIE;
         score = 300;
    }
};

class PaperZombie : public Zombie{
public:
    PaperZombie(int Nrow,int Ncol):Zombie(Nrow,Ncol){
        strcpy(name,"PaperZombie");
        char na[20] = "Paper";
        Item = new item_(na,100);
        speed = 5;
        health = 150;
        score = 250;
        type = PAPER_ZOMBIE;
    }

    virtual bool hurted(int damage){
        if(Item != NULL){
            if(Item->ruined(damage) == true){
                speed = 20;
                delete Item;
                Item = NULL;
            }
            return false;
        }
        else{
            
            health -= damage;
            if(health <= 0)
                return true;
            else
                return false;
        }
    };
};

class FastZombie : public Zombie{
public:
    FastZombie(int Nrow,int Ncol): Zombie(Nrow,Ncol){
        strcpy(name, "FastZombie");
        speed = 25;
        health = 70;
        type = FAST_ZOMBIE;
        score = 75;
    }
};

class DanceZombie : public Zombie{
private:
    int count;
public:
    DanceZombie(int Nrow,int Ncol): Zombie(Nrow,Ncol){
        strcpy(name, "FastZombie");
        speed = 8;
        health = 150;
        type = DANCE_ZOMBIE;
        count = 50;
        score = 400;
    }
    bool CallZom(){
        count--;
        if(count == 0)
            return true;
        return false;
    }
};