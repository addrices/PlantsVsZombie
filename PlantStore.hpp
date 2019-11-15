#pragma once
#include "Plant.hpp"
#include <ncurses.h>
#include "Const.h"

class PlantStore{
private:
    Plant** Plants;
    int PlantNum;
    static PlantStore *PS;
    int chosen;
    Button *Solds;
    PlantStore(){
        PlantNum = 10;
        Plants = new Plant*[PlantNum];
        Plants[0] = new SunFlower();
        Plants[1] = new PeaShooter();
        Plants[2] = new ColdPeaShooter();
        Plants[3] = new Potato();
        Plants[4] = new BigPotato();
        Plants[5] = new Garlic();
        Plants[6] = new FastPeaShooter();
        Plants[7] = new DoublePeaShooter();
        Plants[8] = new PumpkinBoom();
        Plants[9] = new ChiliBoom();
        Solds = new Button[PlantNum];
        for(int i = 0;i < PlantNum;i++){
            Solds[i].startx = 5+13*i;
            Solds[i].endx = 5+13*(i+1);
            Solds[i].starty = 35;
            Solds[i].endy = 39;
        }
        chosen = -1;
    }
    void draw_box(int starty,int startx,bool special_flag){
        if(special_flag == false){
            mvprintw(starty  ,startx,"**************");
            mvprintw(starty+1,startx,"*            *");
            mvprintw(starty+2,startx,"*            *");
            mvprintw(starty+3,startx,"*            *");
            mvprintw(starty+4,startx,"**************");
        }
        else{
            mvprintw(starty  ,startx,"++++++++++++++");
            mvprintw(starty+1,startx,"+            +");
            mvprintw(starty+2,startx,"+            +");
            mvprintw(starty+3,startx,"+            +");
            mvprintw(starty+4,startx,"++++++++++++++");            
        }
    }
public:
    static PlantStore* GetPlantStore(){
        if(PS == nullptr){
            PS = new PlantStore;
        }
        return PS;
    }

    const Plant& GetPlant(int num){
        return *(Plants[num]);
    }

    ~PlantStore(){
        for(int i = 0; i < PlantNum;i++){
            delete Plants[i];
        }
        delete Plants;
    }

    void draw_store(){
        for(int i = 0;i < PlantNum;i++){
            int startx = Solds[i].startx;
            int starty = Solds[i].starty;
            if(chosen == i)
                draw_box(starty,startx,true);
            else
                draw_box(starty,startx,false);
            mvprintw(starty+1,startx+3,"%s",Plants[i]->get_name().c_str());
            mvprintw(starty+2,startx+2,"price:%d",Plants[i]->get_price());
        }
    }

    Plant* BuyPlant(int y,int x){
        for(int i = 0; i < PlantNum;i++){
            if(y >= Solds[i].starty && y <= Solds[i].endy && x >= Solds[i].startx && x <= Solds[i].endx){
                chosen = i;
                return Plants[i];
            }
        }
        return NULL;
    }

    Plant* NewPlant(Plant* p){
        Plant* q = p->copy_me();
    }

    void ResetChosen(){
        chosen = -1;
    }
};
PlantStore * PlantStore::PS = nullptr;