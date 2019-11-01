#pragma once
#include <string>
using namespace std;

class item{
private:
    string name;
    int durable;
public:
    bool ruined(int damage){
        durable -= damage;
        if(durable <= 0){
            return true;
        }else{
            return false;
        }
    };
};