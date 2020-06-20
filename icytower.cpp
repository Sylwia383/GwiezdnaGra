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
    przyspieszaniee(v_y, ile_kolizji);
    move(0,v_y*e.asSeconds());
}



void w_dol_i_w_boki::ruch(const sf::Time &e, int ile_kolizji){
    auto bounds = getGlobalBounds();
    if(strona==0){
        v_x=50;
    }else{
        v_x=-50;
    }

    if(bounds.left <= 0) { //lewo
        //v_x = std::abs(v_x);
        strona=0;
        std::cout<<"dupaaalewo"<<std::endl;
    }
    if(bounds.left + bounds.width >= 800) { //prawo
        //v_x = -std::abs(v_x);
        strona=1;
        std::cout<<"dupaaaprawo"<<std::endl;
    }
    przyspieszaniee(v_y, ile_kolizji);
    move(v_x*e.asSeconds(),v_y*e.asSeconds());
}


float platformy::v_yfunkcja(){
    return v_y;
}
float platformy::v_xfunkcja(){
    return v_x;
}
