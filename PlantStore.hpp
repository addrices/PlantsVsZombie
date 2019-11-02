#include "Plant.hpp"
#include <ncurses.h>

class PlantStore{
private:
    Plant** Plants;
    int PlantNum;
    static PlantStore *PS;
    int chosen;
    PlantStore(){
        PlantNum = 2;
        Plants = new Plant*[2];
        Plants[0] = new Plant(SUNNY_PLANT,25,0,100,"sunflower");
        Plants[1] = new Plant(ATTACK_PLANT,25,20,100,"peashooter");
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
        int starty = 34;
        int startx = 5;
        for(int i = 0;i < PlantNum;i++){
            if(chosen == i)
                draw_box(starty,startx+13*i,true);
            else
                draw_box(starty,startx+13*i,false);
            mvprintw(starty+1,startx+13*i+3,"%s",Plants[i]->get_name().c_str());
            mvprintw(starty+2,startx+13*i+2,"price:%d",Plants[i]->get_price());
        }
    }
};
PlantStore * PlantStore::PS = nullptr;