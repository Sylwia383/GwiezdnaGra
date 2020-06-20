#include "postac.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super gra");
    sf::Clock zegar;

    sf::Texture guyy;
    if(!guyy.loadFromFile("tekstury/character_femaleAdventurer_sheet.png")) { return 1; }
    Postac guy(guyy,sf::Vector2f(570,110));
    guy.add_bits_of_texture(sf::IntRect(16,32,64,97));
    guy.add_bits_of_texture(sf::IntRect(300,542,65,97));
    guy.add_bits_of_texture(sf::IntRect(390,542,77,97));
    guy.add_bits_of_texture(sf::IntRect(491,542,67,97));
    guy.add_bits_of_texture(sf::IntRect(590,542,64,97));


    std::vector<sf::Texture> tekstury_jedenia(15); //wektor tekstur jedzenia
    if(!tekstury_jedenia[0].loadFromFile("tekstury/OKjedzenie/cherry.png")) { return 1; }
    if(!tekstury_jedenia[1].loadFromFile("tekstury/OKjedzenie/burger_SE.png")) { return 1; }
    if(!tekstury_jedenia[2].loadFromFile("tekstury/OKjedzenie/cupcake_NE.png")) { return 1; }
    if(!tekstury_jedenia[3].loadFromFile("tekstury/OKjedzenie/donutSprinkles_SW.png")) { return 1; }
    if(!tekstury_jedenia[4].loadFromFile("tekstury/OKjedzenie/fries_SW.png")) { return 1; }
    if(!tekstury_jedenia[5].loadFromFile("tekstury/OKjedzenie/iceCream_SE.png")) { return 1; }
    if(!tekstury_jedenia[6].loadFromFile("tekstury/OKjedzenie/loaf_NW.png")) { return 1; }
    if(!tekstury_jedenia[7].loadFromFile("tekstury/OKjedzenie/pizza_NW.png")) { return 1; }
    if(!tekstury_jedenia[8].loadFromFile("tekstury/OKjedzenie/plateSauerkraut_NW.png")) { return 1; }
    if(!tekstury_jedenia[9].loadFromFile("tekstury/OKjedzenie/sub_SE.png")) { return 1; }
    if(!tekstury_jedenia[10].loadFromFile("tekstury/OKjedzenie/sundae_SE.png")) { return 1; }
    if(!tekstury_jedenia[11].loadFromFile("tekstury/ZLEjedzenie/pet.png")) { return 1; }
    if(!tekstury_jedenia[12].loadFromFile("tekstury/ZLEjedzenie/zubrowka.png")) { return 1; }
    if(!tekstury_jedenia[13].loadFromFile("tekstury/ZLEjedzenie/fryingPan_NE.png")) { return 1; }
    if(!tekstury_jedenia[14].loadFromFile("tekstury/ZLEjedzenie/cookingKnife_NW.png")) { return 1; }


// WEKTOR JEDZENIA
    sf::Vector2f pozycja(300,0);
    std::vector<std::unique_ptr<Food>> v_jedzonko;
    for(int i=0; i<10; i++){
        int ktora_klasa = std::rand()%4;
        if(ktora_klasa==1 || ktora_klasa==2 || ktora_klasa==3)
            v_jedzonko.emplace_back(std::make_unique<Good_Food>(tekstury_jedenia[rand()%11],sf::Vector2f(std::rand() % (window.getSize().x -200),-120)));
        else if(ktora_klasa==0)
            v_jedzonko.emplace_back(std::make_unique<Bad_Food>(tekstury_jedenia[(rand()%4)+11],sf::Vector2f(std::rand() % (window.getSize().x -200),-120)));
    }


// ICY TOWER
    sf::Texture icyy;
    if(!icyy.loadFromFile("tekstury/platformy/chmura.png")) { return 1; }
    std::vector<std::unique_ptr<platformy>> v_platform;
    for(int i=0; i<100; i++){
        int ktora_platforma = std::rand()%4;
        //if(ktora_platforma==1 || ktora_platforma==2 || ktora_platforma==3)
           // v_platform.emplace_back(std::make_unique<w_dol>(icyy,sf::Vector2f(std::rand() % (window.getSize().x -200),-120)));
        //else if(ktora_platforma==0)
            v_platform.emplace_back(std::make_unique<w_dol_i_w_boki>(icyy,sf::Vector2f(std::rand() % (window.getSize().x -200),-120)));
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
        guy.disappear_food(v_jedzonko,window);
        guy.start_drop_food(elapsed,v_jedzonko); // kiedy postać coś osiągnie to zaczynają spadać (najlepiej żeby to było cos nieodwracalnego) może boola jakiegoś zrobić
        guy.start_icy_tower(elapsed,v_platform,v_jedzonko);
        guy.koniec_gry(window);

        window.clear(sf::Color::Black);


        window.draw(guy);
        for(auto &it : v_jedzonko){
            window.draw(*it);
        }
        for(auto &it : v_platform){
            window.draw(*it);
        }

        window.display();
    }

    return 0;
}
