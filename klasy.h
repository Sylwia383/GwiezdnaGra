#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>


class Good_Food;

class Postac : public sf::Sprite{
public:
    std::vector<sf::IntRect> bits_of_texture;
    float time_animacji_guya;
    double time_food_drop;
    float v_x;
    float v_y;
    int a_y = 500;
    int zlapane=0;
    bool start_drop_=0;
public:
    Postac(sf::Texture &texture, sf::Vector2f);
    void add_bits_of_texture(sf::IntRect);
    void texture_walk(const sf::Time &e);
    void walk(const sf::Time &e);
    void disappear(std::vector<Good_Food> &jo);
    void start_drop(const sf::Time &e, std::vector<Good_Food> &jo);
};



class Food : public sf::Sprite{
    float v_y;
public:
    Food(const sf::Texture &texture, const sf::Vector2f position);
    void drop(const sf::Time &e, int);
    //int zlapane=0;
    int upuszczone=0;
};

class Good_Food : public Food{
public:
    Good_Food(const sf::Texture &texture, const sf::Vector2f position);
    void disappear(Postac &guy, std::vector<Good_Food> &jo);
};

class Bad_Food : public Food{
public:
    Bad_Food(const sf::Texture &texture, const sf::Vector2f position);
    void disappear(Postac &guy);
};
