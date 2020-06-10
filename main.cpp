#include "klasy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super gra");
    sf::Clock zegar;

    sf::Texture guyy;
    if(!guyy.loadFromFile("character_femaleAdventurer_sheet.png")) { return 1; }
    Postac guy(guyy,sf::Vector2f(570,110));
    guy.add_bits_of_texture(sf::IntRect(16,32,64,97));
    guy.add_bits_of_texture(sf::IntRect(300,542,65,97));
    guy.add_bits_of_texture(sf::IntRect(390,542,77,97));
    guy.add_bits_of_texture(sf::IntRect(491,542,67,97));
    guy.add_bits_of_texture(sf::IntRect(590,542,64,97));


    std::vector<sf::Texture> tekstury_jedenia(15); //wektor tekstur jedzenia
    if(!tekstury_jedenia[0].loadFromFile("cherry.png")) { return 1; }
    if(!tekstury_jedenia[1].loadFromFile("burger_SE.png")) { return 1; }
    if(!tekstury_jedenia[2].loadFromFile("cupcake_NE.png")) { return 1; }
    if(!tekstury_jedenia[3].loadFromFile("donutSprinkles_SW.png")) { return 1; }
    if(!tekstury_jedenia[4].loadFromFile("fries_SW.png")) { return 1; }
    if(!tekstury_jedenia[5].loadFromFile("iceCream_SE.png")) { return 1; }
    if(!tekstury_jedenia[6].loadFromFile("loaf_NW.png")) { return 1; }
    if(!tekstury_jedenia[7].loadFromFile("pizza_NW.png")) { return 1; }
    if(!tekstury_jedenia[8].loadFromFile("plateSauerkraut_NW.png")) { return 1; }
    if(!tekstury_jedenia[9].loadFromFile("sub_SE.png")) { return 1; }
    if(!tekstury_jedenia[10].loadFromFile("sundae_SE.png")) { return 1; }
    if(!tekstury_jedenia[11].loadFromFile("cherry.png")) { return 1; }
    if(!tekstury_jedenia[12].loadFromFile("cherry.png")) { return 1; }
    if(!tekstury_jedenia[13].loadFromFile("cherry.png")) { return 1; }
    if(!tekstury_jedenia[14].loadFromFile("cherry.png")) { return 1; }



    sf::Vector2f pozycja(300,0);
    std::vector<std::unique_ptr<Food>> v_jedzonko;
    for(int i=0; i<100; i++){
        v_jedzonko.emplace_back(std::make_unique<Good_Food>(tekstury_jedenia[rand()%15],sf::Vector2f(std::rand() % (window.getSize().x -200),-120)));
    }





    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = zegar.restart();

        guy.texture_walk(elapsed);
        guy.walk(elapsed);
        guy.disappear(v_jedzonko,window);
        guy.start_drop(elapsed,v_jedzonko); // kiedy postać coś osiągnie to zaczynają spadać (najlepiej żeby to było cos nieodwracalnego) może boola jakiegoś zrobić

        /*for(auto &it : v_jedzonko){
            it->drop(elapsed,guy);
        }*/

        window.clear(sf::Color::Black);


        window.draw(guy);
        for(auto &it : v_jedzonko){
            window.draw(*it);
        }

        window.display();
    }

    return 0;
}
