#include "wrogowie_poziom_3.h"



void Wrogowie_prosto::ruch(const sf::Time &e){
    //v_y_=100;
    czas_=czas_+e.asSeconds();
    if(czas_>=0.5){
        v_y_+=25;
        czas_=0;
    }
    move(0,v_y_*e.asSeconds());
}

void Wrogowie_na_boki::ruch(const sf::Time &e){
    if(strona==0){
        v_x_=35;
    }else{
        v_x_=-35;
    }
    czas_=czas_+e.asSeconds();
    if(czas_>=3){
        v_y_+=40;
        if(strona==0){
            strona=1;
        }else{
            strona=0;
        }
        czas_=0;
    }
    move(v_x_*e.asSeconds(),v_y_*e.asSeconds());
}


void Pocisk::ruch(const sf::Time &e){
    move(0,e.asSeconds() * v_y_);
}
