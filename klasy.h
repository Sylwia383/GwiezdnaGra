#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>


class Good_Food;
class Food;

class Postac : public sf::Sprite{
    std::vector<sf::IntRect> bits_of_texture;
    float time_animacji_guya;
    double time_food_drop;
    float v_x;
    float v_y;
    int a_y = 500;//przyspieszenie grawitacyjne
    int zlapane=0;
    int zycia=5;
    bool start_drop_=0;//jak if sie wykona to zacznyna spadać jedzenie
public:
    Postac(const sf::Texture &texture, const sf::Vector2f &position) : sf::Sprite(texture){
        setPosition(position);
    }
    void add_bits_of_texture(sf::IntRect);
    void texture_walk(const sf::Time &e);
    void walk(const sf::Time &e);
    void disappear(std::vector<std::unique_ptr<Food>> &v_jedzonko,sf::RenderWindow &window);//tutaj odejmowanie żyć i złapane++
    void start_drop(const sf::Time &e, std::vector<std::unique_ptr<Food>> &v_jedzonko);//tuyaj większa prędkość wzależności od wysokości
};



class Food : public sf::Sprite{
    std::string typ_="food";
    float v_y;
    float rotat = (rand()%100)-50;
public:
    Food(const sf::Texture &texture, const sf::Vector2f position): sf::Sprite(texture){
        setPosition(position);
    }
    virtual std::string typ(){return typ_;}
    void drop(const sf::Time &e, int);
};

class Good_Food : public Food{
    std::string typ_="good_food";
public:
    Good_Food(const sf::Texture &texture, const sf::Vector2f position) : Food(texture,position){}
    std::string typ(){return typ_;}
};

class Bad_Food : public Food{
    std::string typ_="bad_food";
public:
    Bad_Food(const sf::Texture &texture, const sf::Vector2f position) : Food(texture,position){}
    std::string typ(){return typ_;}
};
