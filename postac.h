#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "klasy.h"
#include "icytower.h"
#include "wrogowie_poziom_3.h"


class Postac : public sf::Sprite{
    std::vector<sf::IntRect> bits_of_texture;
    float time_animacji_guya;
    float v_x;
    float v_y;
    int a_y = 0;//800;//przyspieszenie grawitacyjne
    int zlapane=0;//do jedzenia
    int ile_kolizji=0;//do icy tower
    bool skakac_=0;
    int zycia=10;
    bool start_drop_food_=0;//jak if sie wykona to zacznyna spadać jedzenie
    bool start_icy_tower_=0;
    bool start_wrogowie_=0;
    //bool gora_dol=0;
    bool w_statku=0;
    float czas_pocisku=0;
public:
    Postac(const sf::Texture &texture, const sf::Vector2f &position) : sf::Sprite(texture){
        setPosition(position);
    }
    void add_bits_of_texture(sf::IntRect);
    void texture_walk(const sf::Time &e);
    void walk(const sf::Time &e,sf::RenderWindow &window);
    void disappear_food(std::vector<std::unique_ptr<Food>> &v_jedzonko,sf::RenderWindow &window);//tutaj odejmowanie żyć i złapane++
    void start_drop_food(const sf::Time &e, std::vector<std::unique_ptr<Food>> &v_jedzonko);//tuyaj większa prędkość wzależności od wysokości
    void start_icy_tower(const sf::Time &e, std::vector<std::unique_ptr<platformy>> & platformy);//,std::vector<std::unique_ptr<Food>> &jo);
    void start_wrogowie(const sf::Time &e, std::vector<std::unique_ptr<Wrogowie>> &wrogowie,sf::RenderWindow &window);
    void pocisk_start(const sf::Time &e,std::vector<std::unique_ptr<Wrogowie>> &wektor,sf::Texture &uff);
    void znikanie_wrogow_i_pociskow(std::vector<std::unique_ptr<Wrogowie> > &wektor, sf::RenderWindow &window,sf::Texture &tak,sf::Texture &nie,std::vector<std::unique_ptr<Wrogowie>> &wektor2);
    void koniec_gry(sf::RenderWindow &window);
};
