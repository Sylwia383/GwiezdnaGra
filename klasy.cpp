#include "klasy.h"



// METODY JEDZENIA

void Food::drop(const sf::Time &e, int zlapane){//drop się wykonuje przez klasę postaci  //zmiana prędkości spadającego jedzenia
        if(zlapane<10){
            v_y_=100;
        }if(zlapane>=10 && zlapane <25){
            v_y_=150;
        }if(zlapane>=25 && zlapane <40){
            v_y_=150;
        }if(zlapane>=40){
            v_y_=200;
        }
    move(0,2*v_y_*e.asSeconds());
    rotate(rotat_*e.asSeconds());
}
