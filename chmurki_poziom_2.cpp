#include "chmurki_poziom_2.h"


void przyspieszaniee(float &v, int wzgledem){
    if(wzgledem<10)
        v=150;
    if(wzgledem>=10 && wzgledem <20)
        v=200;
    if(wzgledem>=20 && wzgledem <30)
        v=250;
    if(wzgledem>=30 && wzgledem <40)
        v=300;
    if(wzgledem>=40){
        v=350;
    }
}

void w_dol::ruch(const sf::Time &e, int ile_kolizji){
    v_x_=0;
    przyspieszaniee(v_y_, ile_kolizji);
    move(0,v_y_*e.asSeconds());
}

void w_dol_i_w_boki::ruch(const sf::Time &e, int ile_kolizji){
    auto bounds = getGlobalBounds();
    if(strona==0){
        v_x_=100;
    }else{
        v_x_=-100;
    }if(bounds.left <= 0) { //lewo
        strona=0;
    }if(bounds.left + bounds.width >= 460) { //prawo
        strona=1;
    }
    przyspieszaniee(v_y_, ile_kolizji);
    move(v_x_*e.asSeconds(),v_y_*e.asSeconds());
}


float platformy::v_y(){
    return v_y_;
}
float platformy::v_x(){
    return v_x_;
}
