#pragma once

#define READY 1
#define GAMING 2
#define ENDING 3

#define ROW 4
#define COLUMN 8
#define HEIGHT 45
#define WIDTH 200

#define NORMAL_ZOMBIE 1
#define RB_ZOMBIE 2
#define BUCKET_ZOMBIE 3
#define PAPER_ZOMBIE 4
#define FAST_ZOMBIE 5
#define DANCE_ZOMBIE 6

#define SUNNY_PLANT 1
#define ATTACK_PLANT 2
#define HANHAN_PLANT 3
#define EARTH_PLANT 4
#define GARLIC_PLANT 5
#define BOOM_PLANT 6

#define BLOCK_BOOM 1
#define LINE_BOOM 2
#define NINE_BOOM 3

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

int TotalZombie = 14;
Zombie_time Zombie_timing[14] = {
    {10,NORMAL_ZOMBIE,1},
    {50,RB_ZOMBIE,2},
    {100,BUCKET_ZOMBIE,3},
    {120,FAST_ZOMBIE,0},
    {125,FAST_ZOMBIE,0},
    {150,PAPER_ZOMBIE,2},
    {180,DANCE_ZOMBIE,2},
    {200,NORMAL_ZOMBIE,1},
    {300,BUCKET_ZOMBIE,0},
    {390,NORMAL_ZOMBIE,1},
    {450,BUCKET_ZOMBIE,2},
    {451,BUCKET_ZOMBIE,3},
    {452,BUCKET_ZOMBIE,0},
    {458,PAPER_ZOMBIE,3},
};