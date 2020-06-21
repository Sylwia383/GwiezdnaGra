#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Wrogowie : public sf::Sprite{
protected:
    float v_x_=0;
    float v_y_=0;
    float czas=0;
public:
    Wrogowie(const sf::Texture &texture, const sf::Vector2f &position) : sf::Sprite(texture){
        setPosition(position);
    }
    virtual void ruch(const sf::Time &e,sf::RenderWindow &window)=0;
    virtual std::string typ()=0;
};

class Wrogowie_nie_strzelajacy : public Wrogowie{
    std::string typ_="NIE";
    //float czas=0;
public:
    Wrogowie_nie_strzelajacy(const sf::Texture &texture, const sf::Vector2f &position):Wrogowie(texture,position){}
    void ruch(const sf::Time &e,sf::RenderWindow &window);
    std::string typ(){return typ_;}
};

class Wrogowie_strzelajacy : public Wrogowie{
    std::string typ_="TAK";
    //float czas=0;
    int strona = rand()%2;
public:
    Wrogowie_strzelajacy(const sf::Texture &texture, const sf::Vector2f &position):Wrogowie(texture,position){}
    void ruch(const sf::Time &e,sf::RenderWindow &window);
    void strzelanie(const sf::Time &e);
    std::string typ(){return typ_;}
};

class Pocisk : public Wrogowie {
    std::string typ_="POCISK";
    float v_y_ = -300;
public:
    Pocisk(const sf::Texture &texture, const sf::Vector2f &position) : Wrogowie(texture,position){}
    std::string typ(){return typ_;}
    void ruch(const sf::Time &e,sf::RenderWindow &window);
};
