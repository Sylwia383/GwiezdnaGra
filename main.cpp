#include "klasy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super gra");
    sf::Clock zegar;

    sf::Texture guyy;
    if(!guyy.loadFromFile("character_femaleAdventurer_sheet.png")) { return 1; }
    Postac guy(guyy,sf::Vector2f(180,110));
    guy.add_bits_of_texture(sf::IntRect(16,32,64,97));
    guy.add_bits_of_texture(sf::IntRect(300,542,65,97));
    guy.add_bits_of_texture(sf::IntRect(390,542,77,97));
    guy.add_bits_of_texture(sf::IntRect(491,542,67,97));
    guy.add_bits_of_texture(sf::IntRect(590,542,64,97));


    std::vector<sf::Texture> jedzenie(20); //wektor tekstur dobrego jedzenia
    if(!jedzenie[0].loadFromFile("cherry.png")) { return 1; }


    sf::Vector2f pozycja(300,0);
    Good_Food pll(jedzenie[0],pozycja);
    Good_Food plll(jedzenie[0],pozycja);
    Good_Food pllll(jedzenie[0],pozycja);
    std::vector<Good_Food> v_jedzonko;
    v_jedzonko.emplace_back(pll);
    v_jedzonko.emplace_back(Good_Food(jedzenie[0],sf::Vector2f(400,0)));
    v_jedzonko.emplace_back(Good_Food(jedzenie[0],sf::Vector2f(200,0)));




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = zegar.restart();
        guy.texture_walk(elapsed);
        guy.walk(elapsed);
        for(auto &it : v_jedzonko){
            it.drop(elapsed);
        }
        guy.disappear(v_jedzonko);
        window.clear(sf::Color::Black);


        window.draw(guy);
        //window.draw(v_jedzonko[0]);
        for(auto &it : v_jedzonko){
            window.draw(it);
        }

        window.display();
    }

    return 0;
}
