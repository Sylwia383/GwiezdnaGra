#include "klasy.h"

// METODY POSTACI

void Postac::add_bits_of_texture(sf::IntRect xxx){
    bits_of_texture.emplace_back(xxx);
}

void Postac::texture_walk(const sf::Time &e)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        time_animacji_guya = 0;
        setScale(1.0, 1.0);
        setTextureRect(bits_of_texture[0]);
    }
    else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            setScale(1.0, 1.0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            setScale(-1.0, 1.0);
        }
        if(time_animacji_guya < 4.0){
            time_animacji_guya += 12 * e.asSeconds();
        }else{
            time_animacji_guya = 0.0;
        }
        if(time_animacji_guya < 1){
            setTextureRect(bits_of_texture[1]);
        }else if(time_animacji_guya < 2){
            setTextureRect(bits_of_texture[2]);
        }else if(time_animacji_guya < 3){
            setTextureRect(bits_of_texture[3]);
        }else
            setTextureRect(bits_of_texture[4]);
    }
}

void Postac::walk(const sf::Time &e){
    auto guy_bounds = getGlobalBounds();
    if(guy_bounds.top+guy_bounds.height>600) v_y=0;
    v_y += a_y * e.asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        v_x=-200;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        v_x=200;
    }else{
        v_x=0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        v_y=-300;
    }
    move(v_x*e.asSeconds(), v_y*e.asSeconds());
}

void Postac::disappear(std::vector<std::unique_ptr<Food>> &jo, sf::RenderWindow &window){
    for(int i=0; i<jo.size(); i++){
        auto FOOD_b =jo[i]->getGlobalBounds();
        if(getGlobalBounds().intersects(FOOD_b)){//jeżeni kolizja z postacią
            if(jo[i]->typ()=="good_food"){//jeżeli złapie dobre jedzenie
                zlapane++;
                std::cout<<"ZLAPANE: "<<zlapane<<std::endl;
            }else{//jeżeli złapie złe jedzenie
                zycia--;
                std::cout<<"ZYCIA: "<<zycia<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }else if(FOOD_b.top>window.getSize().y){//jeżeli nie złapie
            if(jo[i]->typ()=="good_food"){//jeżeli nie złapie dobrego jedzenia
                zycia--;
                std::cout<<"ZYCIA: "<<zycia<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }
    }
    if(zycia<=0){// jeśli życia się skończą to koniec gry
        std::cout<<"PRZEGRALES"<<std::endl;
        window.close();
    }
}

void Postac::start_drop(const sf::Time &e, std::vector<std::unique_ptr<Food>> &jo){
    auto guy_bounds = getGlobalBounds();
    if(guy_bounds.left<500) start_drop_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
    if(start_drop_==1){
        time_food_drop += 10 * e.asSeconds();
        jo[0]->drop(e,zlapane);
        for(int j=1;j<15;j++){
            if(jo[j-1]->getGlobalBounds().top>200){   // jeśli wcześniejsze jedzenie będzie dalej niż 200 to następne zaczyna spadać
                jo[j]->drop(e,zlapane);
            }
        }

    }
}


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
    move(0,v_y*e.asSeconds());
}
