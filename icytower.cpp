#include "icytower.h"


void przyspieszaniee(float &v, int wzgledem){
    if(wzgledem<100)
        v=100;
    if(wzgledem>=100 && wzgledem <200)
        v=150;
    if(wzgledem>=200 && wzgledem <300)
        v=150;
    if(wzgledem>=300 && wzgledem <400)
        v=200;
    if(wzgledem>=400){
        v=250;
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
        v_x_=50;
    }else{
        v_x_=-50;
    }if(bounds.left <= 0) { //lewo
        strona=0;
    }if(bounds.left + bounds.width >= 460) { //prawo
        strona=1;
    }
    przyspieszaniee(v_y_, ile_kolizji);
    move(v_x_*e.asSeconds(),v_y_*e.asSeconds());
    std::cout<<"v_x: "<<v_x()<<std::endl;
}


float platformy::v_y(){
    return v_y_;
}
float platformy::v_x(){
    return v_x_;
}
