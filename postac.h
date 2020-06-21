#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "klasy.h"
#include "icytower.h"
#include "wrogowie_poziom_3.h"


class Postac : public sf::Sprite{
    float czas_poczatku=0;
    bool pocz1_=0,pocz2_=0,pocz3_=0;//która tekstura początkowa
    bool g1_=0, g2_=0, g3_=0, g4_=0;
    std::vector<sf::IntRect> bits_of_texture;
    float time_animacji_guya_;
    float czas_tla_=0;
    float v_x_;
    float v_y_;
    int a_y_ = 0;//800;//przyspieszenie grawitacyjne
    int zlapane_=0;//do jedzenia
    int ile_kolizji_=0;//do icy tower
    bool skakac_=0;
    int zycia_=10;
    bool start_drop_food_=0;//jak if sie wykona to zacznyna spadać jedzenie
    bool start_icy_tower_=0;
    bool start_wrogowie_=0;
    bool w_statku_=0;
    float czas_pocisku_=0;
    bool kolizja_ze_statkiem_=0;
    bool kolizja_z_czeresnia_=0;
    int zestrzelony_=0;
    int przesuwanie_tla_tloo_=2575;
    int przesuwanie_tla_tlo_=550;
public:
    Postac(const sf::Texture &texture, const sf::Vector2f &position) : sf::Sprite(texture){
        setPosition(position);
    }
    void poczatek_tla(const sf::Time &e,sf::RenderWindow &window,sf::Sprite &poczatek,sf::Texture &pocz1,sf::Texture &pocz2,sf::Texture &pocz3,sf::Texture &G1,sf::Texture &G2,sf::Texture &G3,sf::Texture &G4);
    void add_bits_of_texture(sf::IntRect);
    void texture_walk(const sf::Time &e);
    void walk(const sf::Time &e,sf::RenderWindow &window);
    void disappear_food(std::vector<std::unique_ptr<Food>> &v_jedzonko,sf::RenderWindow &window);//tutaj odejmowanie żyć i złapane++
    void start_drop_food(const sf::Time &e, std::vector<std::unique_ptr<Food>> &v_jedzonko);//tuyaj większa prędkość wzależności od wysokości
    void start_icy_tower(const sf::Time &e, std::vector<std::unique_ptr<platformy>> & platformy);//,std::vector<std::unique_ptr<Food>> &jo);
    void start_wrogowie(const sf::Time &e, std::vector<std::unique_ptr<Wrogowie>> &wrogowie,sf::RenderWindow &window, std::vector<std::unique_ptr<sf::Sprite>> &statek,sf::Texture &stat,sf::Texture &sG1,sf::Texture &sG2,sf::Texture &sG3,sf::Texture &sG4);
    void pocisk_start(const sf::Time &e,std::vector<std::unique_ptr<Wrogowie>> &wektor,sf::Texture &uff);
    void znikanie_wrogow_i_pociskow(std::vector<std::unique_ptr<Wrogowie> > &wektor, sf::RenderWindow &window,sf::Texture &tak,sf::Texture &nie,std::vector<std::unique_ptr<Wrogowie>> &wektor2);
    void przesuwajace_tlo(const sf::Time &e,sf::Sprite &tloo,sf::Sprite &tlo);
    void wyswieltanie_danych(sf::Sprite &zlap,sf::Sprite &l1,sf::Sprite &l2,sf::Sprite &l3,sf::Sprite &l4,sf::Texture &zl,sf::Texture &ze);
    void koniec_gry(sf::RenderWindow &window,std::vector<std::unique_ptr<sf::Sprite>> &czeresnia,sf::Texture &tak);
};
