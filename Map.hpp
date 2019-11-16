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
        sunny_energy = 500;
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
                    mvprintw(blocks[i][j].starty+2,blocks[i][j].startx+12,"%s",Zombies[i][j][0]->get_name());
                    if(Zombies[i][j][0]->get_description() != NULL)
                        mvprintw(blocks[i][j].starty+3,blocks[i][j].startx+12,"%s",Zombies[i][j][0]->get_description());
                    else
                        mvprintw(blocks[i][j].starty+3,blocks[i][j].startx+12,"NO ITEM",Zombies[i][j][0]->get_description());
                    mvprintw(blocks[i][j].starty+4,blocks[i][j].startx+12,"(%d)",Zombies[i][j].size());
                }
                else{
                    draw_box(blocks[i][j].starty,blocks[i][j].startx);
                }
                if(Plants[i][j] != NULL){
                    mvprintw(blocks[i][j].starty+2,blocks[i][j].startx+1,"%s",Plants[i][j]->get_name());
                    mvprintw(blocks[i][j].starty+3,blocks[i][j].startx+1,"hp:%d",Plants[i][j]->get_hp());
                }
            }
        }

        for(int i = 0; i < bullets.size();i++){
            mvprintw(bullets[i].row*8+4,bullets[i].col*25+(bullets[i].local),"O");
        }
        PlantStore::GetPlantStore()->draw_store();
        mvprintw(33,10,"sunny:%d      ",sunny_energy);
        mvprintw(34,10,"score:%d      ",score);
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
                    if(Plants[i][j] != NULL){
                        if(Plants[i][j]->get_type() == GARLIC_PLANT){
                            Zombies[(i+1)%4][j].push_back(Zombies[i][j][k]);
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                        }
                        if(Plants[i][j]->attacked(Zombies[i][j][k]->get_attack()) == true){
                            delete(Plants[i][j]);
                            Plants[i][j] = NULL;
                        }
                    }
                    else if(Zombies[i][j][k]->walk() == true){
                        if(j == 0){
                            delete Zombies[i][j][k];
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                            return true;
                        }
                        else{
                            Zombies[i][j-1].push_back(Zombies[i][j][k]);
                            Zombies[i][j].erase(Zombies[i][j].begin()+k);
                        }
                    }

                    if(Zombies[i][j][k]->get_type() == DANCE_ZOMBIE){
                        if(Zombies[i][j][k]->CallZom() == true){
                            if(j < COLUMN-1){
                                Zombie* Z = new Zombie(i,j+1);
                                Zombies[i][j+1].push_back(Z);
                            }
                            if(j > 0){
                                Zombie* Z = new Zombie(i,j-1);
                                Zombies[i][j-1].push_back(Z);
                            }
                            if(i > 0){
                                Zombie* Z = new Zombie(i-1,j);
                                Zombies[i-1][j+1].push_back(Z);
                            }
                            if(i < ROW-1){
                                Zombie* Z = new Zombie(i,j+1);
                                Zombies[i+1][j].push_back(Z);
                            }
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
                else if(Plants[i][j] != NULL && Plants[i][j]->get_type() == BOOM_PLANT){
                    if(Plants[i][j]->IfBoom() == true){
                        switch(Plants[i][j]->get_BoomScope()){
                            case BLOCK_BOOM: boom(Plants[i][j]->get_attack(),i,j); 
                                            delete(Plants[i][j]);
                                            Plants[i][j] = NULL;                                
                                            break;
                            case LINE_BOOM: for(int k = 0;k < COLUMN;k++){
                                                boom(Plants[i][j]->get_attack(),i,k);
                                            }
                                            delete(Plants[i][j]);
                                            Plants[i][j] = NULL;
                                            break;
                        }
                    }
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
                        score += Zombies[bullets[i].row][bullets[i].col][0]->get_score();
                        delete(Zombies[bullets[i].row][bullets[i].col][0]);
                        Zombies[bullets[i].row][bullets[i].col].erase(Zombies[bullets[i].row][bullets[i].col].begin());
                    }
                    if(bullets[i].cold == true){
                        Zombies[bullets[i].row][bullets[i].col][0]->freezed();
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
        sunny_energy = 500;
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
                            Plant* NewPlant = buy_plant->copy_me();
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

    void boom(int attack,int row,int col){
        for(int i = 0; i < Zombies[row][col].size();i++){
            if(Zombies[row][col][i]->hurted(attack) == true){
                score += Zombies[row][col][i]->get_score();
                delete Zombies[row][col][i];
                Zombies[row][col].erase(Zombies[row][col].begin()+i);
            }
        }
    }
};

