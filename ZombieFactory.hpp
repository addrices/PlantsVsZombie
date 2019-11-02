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
            default: newZom = NULL;
        }
        return newZom;
    }
};
ZombieFactory * ZombieFactory::ZF = nullptr;
