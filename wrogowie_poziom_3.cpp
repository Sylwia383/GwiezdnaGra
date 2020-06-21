#include "wrogowie_poziom_3.h"



void Wrogowie_nie_strzelajacy::ruch(const sf::Time &e,sf::RenderWindow &window){
    //v_y_=100;
    czas=czas+e.asSeconds();
    if(czas>=0.5){
        v_y_+=9;
        czas=0;
    }
    move(0,v_y_*e.asSeconds());
}

void Wrogowie_strzelajacy::ruch(const sf::Time &e,sf::RenderWindow &window){
    //v_y_=100;
    if(strona==0){
        v_x_=35;
    }else{
        v_x_=-35;
    }
    czas=czas+e.asSeconds();
    if(czas>=3){
        v_y_+=20;
        if(strona==0){
            strona=1;
        }else{
            strona=0;
        }
        czas=0;
    }
    move(v_x_*e.asSeconds(),v_y_*e.asSeconds());
}

void Wrogowie_strzelajacy::strzelanie(const sf::Time &e){

}

void Pocisk::ruch(const sf::Time &e, sf::RenderWindow &window){
    //v_y_=50;
    move(0,e.asSeconds() * v_y_);
}
