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
        time = 0;
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
        if(time < 4.0){
            time += 12 * e.asSeconds();
        }else{
            time = 0.0;
        }
        if(time < 1){
            setTextureRect(bits_of_texture[1]);
        }else if(time < 2){
            setTextureRect(bits_of_texture[2]);
        }else if(time < 3){
            setTextureRect(bits_of_texture[3]);
        }else
            setTextureRect(bits_of_texture[4]);
    }
}


void Postac::walk(const sf::Time &e){
    v_y += a_y * e.asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        v_x=-200;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        v_x=200;
    }else{
        v_x=0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        v_y=-350;
    }
    move(v_x*e.asSeconds(), v_y*e.asSeconds());
}


Food::Food(const sf::Texture &texture, const sf::Vector2f position) : sf::Sprite(texture){
    setPosition(position);
}

Good_Food::Good_Food(const sf::Texture &texture, const sf::Vector2f position):Food(texture,position){}
Bad_Food::Bad_Food(const sf::Texture &texture, const sf::Vector2f position):Food(texture,position){}

void Food::drop(const sf::Time &e){
    if(zlapane<25)
        v_y=50;
    if(zlapane>=20 && zlapane <50)
        v_y=100;
    if(zlapane>=50 && zlapane <75)
        v_y=150;
    if(zlapane>=75 && zlapane <=100)
        v_y=200;
    move(0,v_y*e.asSeconds());
}


void Postac::disappear(std::vector<Good_Food> &jo){
    //auto GUY = getGlobalBounds();
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

/*void Bad_Food::disappear(Postac &guy){
    auto FOOD_b = getGlobalBounds();
    auto GUY = guy.getGlobalBounds();
    if(FOOD_b().intersects(GUY)){
        std::cout<<"nie zlapal"<<std::endl;
    }
}*/

