#pragma once
#include "Zombie.hpp"
#include "Const.h"

class ZombieFactory{
private:
    ZombieFactory(){
    };
    static ZombieFactory* ZF;
public:
    static ZombieFactory* GetZombieFactory(){
        if(ZF == nullptr){
            ZF = new ZombieFactory();
        }
        return ZF;
    };
    Zombie* newZombie(int identifier,int row,int col){
        Zombie* newZom;
        switch (identifier){
            case NORMAL_ZOMBIE: newZom = new Zombie(row,col);break;
            case RB_ZOMBIE: newZom = new RoadBlockZombie(row,col);break;
            case BUCKET_ZOMBIE: newZom = new BucketZombie(row,col);break;
            case PAPER_ZOMBIE: newZom = new PaperZombie(row,col);break;
            case FAST_ZOMBIE: newZom = new FastZombie(row,col);break;
            case DANCE_ZOMBIE: newZom = new DanceZombie(row,col);break;
            default: newZom = NULL;
        }
        return newZom;
    }
};
ZombieFactory * ZombieFactory::ZF = nullptr;
