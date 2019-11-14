#pragma once

#define READY 1
#define GAMING 2
#define ENDING 3

#define ROW 4
#define COLUMN 8
#define HEIGHT 45
#define WIDTH 200

#define NORMAL_ZOMBIE 1

#define SUNNY_PLANT 1
#define ATTACK_PLANT 2
#define HANHAN_PLANT 3
#define EARTH_PLANT 4
#define GARLIC_PLANT 5

struct bullet{
    bool valid;
    int row;
    int col;
    int local;
    int attack;
    bool cold;
};

struct Button{
    int startx;
    int endx;
    int starty;
    int endy;
};

struct Zombie_time{
    int second;
    int type;
    int line;
};

int TotalZombie = 10;
Zombie_time Zombie_timing[10] = {
    {10,NORMAL_ZOMBIE,1},
    {50,NORMAL_ZOMBIE,2},
    {100,NORMAL_ZOMBIE,3},
    {120,NORMAL_ZOMBIE,0},
    {150,NORMAL_ZOMBIE,2},
    {180,NORMAL_ZOMBIE,3},
    {200,NORMAL_ZOMBIE,1},
    {300,NORMAL_ZOMBIE,0},
    {390,NORMAL_ZOMBIE,1},
    {400,NORMAL_ZOMBIE,2}
};