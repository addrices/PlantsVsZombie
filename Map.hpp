#pragma once
#include "Const.h"
#include "ZombieFactory.hpp"
#include <ncurses.h>
#include <vector>
using namespace std;

class Map{
private:
    int row;
    int column;
    int Zombie_num;
    int order_Zombie;
    Button **blocks;
    vector<Zombie*> **Zombies;
public:
    Map(int r,int c){
        row = r;
        column = c;
        blocks = new Button*[row]; 
        Zombie_num = 0;
        order_Zombie = 0;
        Zombies = new vector<Zombie*>*[row];
        for(int i = 0; i < row;i++){
            blocks[i] = new Button[column]; 
            Zombies[i] = new vector<Zombie*>[column];
        } 
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                blocks[i][j].starty = 8*i;
                blocks[i][j].endy = 8*i + 8;
                blocks[i][j].startx = 25*j;
                blocks[i][j].endy = 25*j + 25;
            }
        }
    };
    void show_init(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                WINDOW *win;
                int height = 8;
                int width = 25;
                win = newwin(8,26,blocks[i][j].starty,blocks[i][j].startx);             
                box(win, 0 , 0);
                wrefresh(win);
            }
        }

    };
    void show(){
          
    };
    void update(int sec){
        if(Zombie_timing[order_Zombie].second == sec){
            Zombie* new_zombie = ZombieFactory::GetZombieFactory()->newZombie(Zombie_timing[order_Zombie].type,Zombie_timing[order_Zombie].line,7);
            Zombies[Zombie_timing[order_Zombie].line][7].push_back(new_zombie);
        }

        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                for(int k = 0; k < Zombies[i][j].size; k++){
                    if(Zombies[i][j][k]->walk() == true){
                        if(j == 0){
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                            //DEAD
                        }
                    }
                }
            }
        }
    };
};
