#include "klasy.h"



// METODY JEDZENIA

void Food::drop(const sf::Time &e, int zlapane){//drop się wykonuje przez klasę postaci  //zmiana prędkości spadającego jedzenia
    if(zlapane<7)
            v_y=100;
        if(zlapane>=7 && zlapane <15)
            v_y=150;
        if(zlapane>=15 && zlapane <75)
            v_y=150;
        if(zlapane>=75 && zlapane <=100)
            v_y=200;
        //move(0,v_y*e.asSeconds());
    move(0,2*v_y*e.asSeconds());
    rotate(rotat*e.asSeconds());
}
