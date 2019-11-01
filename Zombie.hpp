#pragma once
#include "item.hpp"
#include <string>

class Zombie{
private:
    string name;
    int row_local;
    int col_local;
    int block_local;
    int attack;
    item* Item;
    int speed;
    int health;
public:
    Zombie(int Nrow,int Ncol){
        name = "Zombie";
        row_local = Nrow;
        col_local = Ncol;
        Item = NULL;
        speed = 10;
        block_local = 0;
        attack = 2;
    };
    bool hurted(int damage){
        if(Item != NULL){
            if(Item->ruined(damage) == true)
                Item = NULL;
            else
                return true;
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
        block_local += speed;        
        col_local = col_local - 1;
        if(block_local >= 100){
            block_local -= 100;
            return true;
        }
        return false;
    };
    int get_attack(){
        return attack;
    };
    int get_row(){
        return row_local;
    };
    int get_col(){
        return col_local;
    };
};