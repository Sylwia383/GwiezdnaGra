#include "klasy.h"

Postac::Postac(sf::Texture &texture, sf::Vector2f position) : sf::Sprite(texture){
    setPosition(position);
}

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


Food::Food(const sf::Texture &texture, const sf::Vector2f position) : sf::Sprite(texture){
    setPosition(position);
}

Good_Food::Good_Food(const sf::Texture &texture, const sf::Vector2f position):Food(texture,position){}
Bad_Food::Bad_Food(const sf::Texture &texture, const sf::Vector2f position):Food(texture,position){}

void Food::drop(const sf::Time &e, int zlapane){
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


void Postac::disappear(std::vector<Good_Food> &jo){
    for(int i=0; i<jo.size(); i++){
        auto FOOD_b =jo[i].getGlobalBounds();
        if(getGlobalBounds().intersects(FOOD_b)==1){
            std::cout<<"zlapal"<<std::endl;
            jo.erase(jo.begin()+i);
            zlapane++;
            std::cout<<zlapane<<std::endl;
        }
    }
}

void Postac::start_drop(const sf::Time &e, std::vector<Good_Food> &jo){
    auto guy_bounds = getGlobalBounds();
    if(guy_bounds.left<500) start_drop_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
    if(start_drop_==1){
        time_food_drop += 10 * e.asSeconds();
        jo[0].drop(e,zlapane);
        for(int j=1;j<15;j++){
            if(jo[j-1].getGlobalBounds().top>200){   // jeśli wcześniejsze jedzenie będzie dalej niż 200 to następne zaczyna spadać
                jo[j].drop(e,zlapane);
            }
        }

    }
}
/*void Bad_Food::disappear(Postac &guy){
    auto FOOD_b = getGlobalBounds();
    auto GUY = guy.getGlobalBounds();
    if(FOOD_b().intersects(GUY)){
        std::cout<<"nie zlapal"<<std::endl;
    }
}*/

