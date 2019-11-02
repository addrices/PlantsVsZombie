#pragma once
#include "Const.h"
#include "ZombieFactory.hpp"
#include "PlantStore.hpp"
#include <ncurses.h>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(const Zombie* a,const Zombie* b)
{
    return a->block_local < b->block_local;
}

class Map{
private:
    int sunny_energy;
    int row;
    int column;
    int Zombie_num;
    int order_Zombie;
    Button **blocks;
    vector<Zombie*> **Zombies;
    void draw_box(int starty,int startx)
    {
        mvprintw(starty  ,startx,"**************************");
        mvprintw(starty+1,startx,"*                        *");
        mvprintw(starty+2,startx,"*                        *");
        mvprintw(starty+3,startx,"*                        *");
        mvprintw(starty+4,startx,"*                        *");
        mvprintw(starty+5,startx,"*                        *");
        mvprintw(starty+6,startx,"*                        *");
        mvprintw(starty+7,startx,"*                        *");
        mvprintw(starty+8,startx,"**************************");
    }
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
        sunny_energy = 100;
    };
    void show_init(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                draw_box(blocks[i][j].starty,blocks[i][j].startx);             
            }
        }
        refresh();
    };
    void show(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                sort(Zombies[i][j].begin(),Zombies[i][j].end(),comp);
                if(Zombies[i][j].size() != 0){
                    draw_box(blocks[i][j].starty,blocks[i][j].startx);             
                    mvprintw(blocks[i][j].starty+2,blocks[i][j].startx+12,"%s",Zombies[i][j][0]->get_name().c_str());
                    mvprintw(blocks[i][j].starty+3,blocks[i][j].startx+12,"(%d)",Zombies[i][j].size());
                }
                else{
                    draw_box(blocks[i][j].starty,blocks[i][j].startx);
                }
            }
        }
        PlantStore::GetPlantStore()->draw_store();
        refresh();
    };
    bool update(int sec){
        if(Zombie_timing[order_Zombie].second == sec && order_Zombie < TotalZombie){
            Zombie* new_zombie = ZombieFactory::GetZombieFactory()->newZombie(Zombie_timing[order_Zombie].type,Zombie_timing[order_Zombie].line,7);
            Zombies[Zombie_timing[order_Zombie].line][7].push_back(new_zombie);
            order_Zombie++;
        }

        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                for(int k = 0; k < Zombies[i][j].size(); k++){
                    if(Zombies[i][j][k]->walk() == true){
                        if(j == 0){
                            delete Zombies[i][j][k];
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                            //DEAD
                            return true;
                        }
                        else{
                            Zombies[i][j-1].push_back(Zombies[i][j][k]);
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                        }
                    }
                }
            }
        }
        return false;
    };
    void MapInit(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                for(int k = 0; k < Zombies[i][j].size();k++){
                    delete Zombies[i][j][k];
                }
                Zombies[i][j].clear();
            }
        }
        order_Zombie = 0;
        sunny_energy = 100;
    }
};
