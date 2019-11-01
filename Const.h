#define READY 1
#define GAMING 2

#define ROW 4
#define COLUMN 8
#define HEIGHT 45
#define WIDTH 200

#define NORMAL_ZOMBIE 1

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

Zombie_time Zombie_timing[10] = {
    {1,NORMAL_ZOMBIE,1},
    {5,NORMAL_ZOMBIE,2},
    {10,NORMAL_ZOMBIE,3},
    {12,NORMAL_ZOMBIE,0},
    {15,NORMAL_ZOMBIE,2},
    {18,NORMAL_ZOMBIE,3},
    {20,NORMAL_ZOMBIE,1},
    {30,NORMAL_ZOMBIE,0},
    {39,NORMAL_ZOMBIE,1},
    {40,NORMAL_ZOMBIE,2}
};