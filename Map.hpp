#pragma once
#include "Const.h"
#include "ZombieFactory.hpp"
#include "PlantStore.hpp"
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool comp(const Zombie* a,const Zombie* b)
{
    return a->block_local < b->block_local;
}

class Map{
private:
    int score;
    int sunny_energy;
    int row;
    int column;
    int Zombie_num;
    int order_Zombie;
    Button **blocks;
    Plant ***Plants;
    vector<Zombie*> **Zombies;
    bool if_buy;
    Plant *buy_plant;
    vector<bullet> bullets;
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
        Plants = new Plant**[row];
        if_buy = false;
        for(int i = 0; i < row;i++){
            blocks[i] = new Button[column]; 
            Zombies[i] = new vector<Zombie*>[column];
            Plants[i] = new Plant*[column];
        }
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                blocks[i][j].starty = 8*i;
                blocks[i][j].endy = 8*i + 8;
                blocks[i][j].startx = 25*j;
                blocks[i][j].endx = 25*j + 25;
                Plants[i][j] = NULL;
            }
        }
        sunny_energy = 100;
        score = 0;
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
                if(Plants[i][j] != NULL){
                    mvprintw(blocks[i][j].starty+2,blocks[i][j].startx+1,"%s",Plants[i][j]->get_name().c_str());
                    mvprintw(blocks[i][j].starty+3,blocks[i][j].startx+1,"hp:%d",Plants[i][j]->get_hp());
                }
            }
        }

        for(int i = 0; i < bullets.size();i++){
            mvprintw(bullets[i].row*8+4,bullets[i].col*25+(bullets[i].local),"O");
        }
        PlantStore::GetPlantStore()->draw_store();
        mvprintw(35,50,"sunny:%d      ",sunny_energy);
        mvprintw(36,50,"score:%d      ",score);
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
                if(Plants[i][j] != NULL && Plants[i][j]->get_type() == SUNNY_PLANT){
                    sunny_energy += Plants[i][j]->get_sunny();
                }
                else if(Plants[i][j] != NULL && Plants[i][j]->get_type() == ATTACK_PLANT){
                    bullet b = Plants[i][j]->shot();
                    if(b.valid == true)
                        bullets.push_back(b);
                }
            }
        }

        for(int i = 0; i < bullets.size();i++){
            bullets[i].local += 8;
            if(bullets[i].local >= 25){
                bullets[i].local -= 25;
                bullets[i].col++;
                if(bullets[i].col > 7){
                    bullets.erase(bullets.begin()+i);
                }
                if(Zombies[bullets[i].row][bullets[i].col].size() != 0){
                    if(Zombies[bullets[i].row][bullets[i].col][0]->hurted(bullets[i].attack) == true){
                        delete(Zombies[bullets[i].row][bullets[i].col][0]);
                        Zombies[bullets[i].row][bullets[i].col].erase(Zombies[bullets[i].row][bullets[i].col].begin());
                    }
                    bullets.erase(bullets.begin()+i);
                    i--;
                }
            }
        }
        return false;
    };
    void MapInit(){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                if(Plants[i][j] != NULL){
                    delete(Plants[i][j]);
                    Plants[i][j] = NULL;
                }
                for(int k = 0; k < Zombies[i][j].size();k++){
                    delete Zombies[i][j][k];
                }
                Zombies[i][j].clear();
            }
        }
        order_Zombie = 0;
        sunny_energy = 100;
    };
    void input(int y,int x){
        PlantStore *PS = PlantStore::GetPlantStore();
        if(if_buy == false){
            buy_plant = PS->BuyPlant(y,x);
            if(buy_plant != NULL)
            if_buy = true;
            return;
        }
        else{
            for(int i = 0; i < row;i++){
                for(int j = 0; j < column;j++){
                    if( y >= blocks[i][j].starty && y <= blocks[i][j].endy && x >= blocks[i][j].startx && x <= blocks[i][j].endx){
                        if(Plants[i][j] == NULL && sunny_energy >= buy_plant->get_price()){
                            Plant* NewPlant = (Plant*)malloc(sizeof(Plant));
                            *NewPlant = *buy_plant;
                            Plants[i][j] = NewPlant;
                            Plants[i][j]->plant(i,j);
                            sunny_energy -= NewPlant->get_price();
                            mvprintw(40,5,"                          ");
                        }
                        else if(Plants[i][j] != NULL){
                            mvprintw(40,5,"there is a plant already!!");
                        }
                        else if(sunny_energy < buy_plant->get_price()){
                            mvprintw(40,5,"lack sunny!!              ");
                        }
                        PS->ResetChosen();
                        buy_plant = NULL;
                        if_buy = false;
                        return;
                    }
                }
            }
        }
        PS->ResetChosen();
        buy_plant = NULL;
        if_buy = false;
    };
};

