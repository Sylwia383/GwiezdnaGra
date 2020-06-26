#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class platformy : public sf::Sprite{
protected:
    float v_x_;
    float v_y_;
    float czas_=0;
public:
    platformy(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &scale) : sf::Sprite(texture){
        setPosition(position);
        setScale(scale);
    }
    virtual void ruch(const sf::Time &e, int ile_kolizji)=0;
    float v_y();
    float v_x();
};

class w_dol : public platformy{
public:
    w_dol(const sf::Texture &texture, const sf::Vector2f &position):platformy(texture,position,sf::Vector2f(0.3,0.3)){}
    void ruch(const sf::Time &e, int ile_kolizji);
};

class w_dol_i_w_boki: public platformy{
    int strona = rand()%2;
public:
    w_dol_i_w_boki(const sf::Texture &texture, const sf::Vector2f &position):platformy(texture,position,sf::Vector2f(0.3,0.3)){}
    void ruch(const sf::Time &e, int ile_kolizji);

};
