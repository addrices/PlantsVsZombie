#include "Map.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "Const.h"

class GameControl{
private:
    int Zombie_num;
    Map map;
    int State;
    int second;
    Button Ready_start;
    Button Ready_exit;
    bool start_Gaming_flag;
    void show(){
        if(State == READY){
            WINDOW *ready_win;
            int startx, starty;
            int win_width,win_height;
            win_width = 20;
            win_height = 4;
            starty = (HEIGHT - win_height)/2 + 5;
            startx = (WIDTH - win_width)/2;
	        ready_win = newwin(win_height, win_width, starty, startx);
            box(ready_win, 0 , 0);
            wrefresh(ready_win);
            mvprintw(starty+1,startx+3,"1.start");
            Ready_start.startx = startx+3;
            Ready_start.endx = startx+9;
            Ready_start.starty = starty+1;
            Ready_start.endy = starty+1;
            mvprintw(starty+2,startx+3,"2.exit");
            Ready_exit.startx = startx+3;
            Ready_exit.endx = startx+9;
            Ready_exit.starty = starty+2;
            Ready_exit.endy = starty+2;
            mvprintw(starty-6,startx," PLANTS VS ZOMBIES");
            int pic_startx = 75;
            int pic_starty = 5;
            mvprintw(pic_starty  ,pic_startx," ********                                   *******     ");
            mvprintw(pic_starty+1,pic_startx,"*    @   *                                 *       *    ");
            mvprintw(pic_starty+2,pic_startx,"*                                          *       *    ");
            mvprintw(pic_starty+3,pic_startx,"*        *                                  *******     ");
            mvprintw(pic_starty+4,pic_startx," ********                                   *     *     ");
            mvprintw(pic_starty+5,pic_startx,"     *                                      *     *     ");
            mvprintw(pic_starty+6,pic_startx,"     ***                                    *     *     ");
            mvprintw(pic_starty+7,pic_startx,"     ***                                    *******     ");
            mvprintw(pic_starty+8,pic_startx,"     *                                       *   *      ");
            mvprintw(pic_starty+9,pic_startx," *********                                   *   *      ");
            int sec = second / 15;
            if(sec % 2 == 1){
                mvprintw(pic_starty+1,pic_startx,"*    @   *                                 * @  @  *    ");            
            }
            else{
                mvprintw(pic_starty+1,pic_startx,"*    @   *                                 *  @  @ *    ");            
            }
            int bull_local = pic_startx + 10 +((int)second/10) % 33;
            mvprintw(pic_starty+2,bull_local," O");
        }else if(State == GAMING){
            if(start_Gaming_flag == true){
                start_Gaming_flag = false;
                map.show_init();
            }
            map.show();
        }else if(State == ENDING){
            int startx, starty;
            int win_width,win_height;
            win_width = 20;
            win_height = 5;
            starty = (HEIGHT - win_height)/2 + 10;
            startx = (WIDTH - win_width)/2;
            WINDOW *ending_win = newwin(win_height, win_width, starty, startx);
            box(ending_win, 0 , 0);
            wrefresh(ending_win);
            mvprintw(starty+1,startx+3,"Game Over");
            mvprintw(starty+2,startx+3,"Click to return");

        }
        refresh();
    };
    void input(MEVENT &event){
        int y = event.y;
        int x = event.x;
        mvprintw(1,1,"Y:%d X:%d\n", event.y, event.x);
        refresh();
        if(State == READY){
            if (y >= Ready_start.starty && y <= Ready_start.endy && x >= Ready_start.startx && x <= Ready_start.endx){
                State = GAMING;
                second = 0;
                start_Gaming_flag = true;
            }
            else if (y >= Ready_exit.starty && y <= Ready_exit.endy && x >= Ready_exit.startx && x <= Ready_exit.endx){
                endwin();
                _exit(0);
            }
        }
        else if(State == GAMING){
            map.input(y,x);
        }else if(State == ENDING){
            clear();
            State = READY;
        }
    };
public:
    GameControl():map(ROW,COLUMN){
        Zombie_num = 0;
        State = READY;
        second = 0;
        start_Gaming_flag = false;
    };
    void start(){
        MEVENT event;
        int key;
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);
        while(1){
            show();
            timeout(0);
            key = getch();
            if(key == KEY_MOUSE){
                getmouse(&event);
                input(event);
            }
            usleep(15000);
            second += 1;
            if(second % 10 == 0 && State == GAMING){
                bool flag = map.update(second/10);
                if(flag == true){
                    map.MapInit();
                    State = ENDING;
                }
            }
        }
    };
};