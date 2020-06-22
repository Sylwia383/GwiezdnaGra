#include "postac.h"
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(460, 700), "Super gra");
    sf::Clock zegar;

//POCZĄTEK
    sf::Texture pocz1;
    if(!pocz1.loadFromFile("tekstury/poczatek/C1.jpg")) { return 1; }
    sf::Texture pocz2;
    if(!pocz2.loadFromFile("tekstury/poczatek/C2.jpg")) { return 1; }
    sf::Texture pocz3;
    if(!pocz3.loadFromFile("tekstury/poczatek/C3.jpg")) { return 1; }

    sf::Sprite poczatek_tlo;
    poczatek_tlo.setPosition(0,0);


//POSTAĆ
    sf::Texture G1;
    if(!G1.loadFromFile("tekstury/Postac/character_femaleAdventurer_sheet.png")) { return 1; }
    sf::Texture G2;
    if(!G2.loadFromFile("tekstury/Postac/character_femalePerson_sheet.png")) { return 1; }
    sf::Texture G3;
    if(!G3.loadFromFile("tekstury/Postac/character_malePerson_sheet.png")) { return 1; }
    sf::Texture G4;
    if(!G4.loadFromFile("tekstury/Postac/character_maleAdventurer_sheet.png")) { return 1; }


    Postac guy(G1,sf::Vector2f(200,300));
    guy.add_bits_of_texture(sf::IntRect(16,32,64,97));
    guy.add_bits_of_texture(sf::IntRect(300,542,65,97));
    guy.add_bits_of_texture(sf::IntRect(390,542,77,97));
    guy.add_bits_of_texture(sf::IntRect(491,542,67,97));
    guy.add_bits_of_texture(sf::IntRect(590,542,64,97));


//POSTAĆ W RAKIECIE
    sf::Texture statek_z_G1;
    if(!statek_z_G1.loadFromFile("tekstury/Postac/Statek/statekG1.png")) { return 1; }
    sf::Texture statek_z_G2;
    if(!statek_z_G2.loadFromFile("tekstury/Postac/Statek/statekG2.png")) { return 1; }
    sf::Texture statek_z_G3;
    if(!statek_z_G3.loadFromFile("tekstury/Postac/Statek/statekG3.png")) { return 1; }
    sf::Texture statek_z_G4;
    if(!statek_z_G4.loadFromFile("tekstury/Postac/Statek/statekG4.png")) { return 1; }


//TEKSTURY JEDZENIA
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
    for(int i=0; i<90; i++){
        int ktora_klasa = std::rand()%4;
        if(ktora_klasa==1 || ktora_klasa==2 || ktora_klasa==3)
            v_jedzonko.emplace_back(std::make_unique<Good_Food>(tekstury_jedenia[rand()%11],sf::Vector2f((std::rand() % (window.getSize().x -200))+70,-120)));
        else if(ktora_klasa==0)
            v_jedzonko.emplace_back(std::make_unique<Bad_Food>(tekstury_jedenia[(rand()%4)+11],sf::Vector2f((std::rand() % (window.getSize().x -200))+70,-120)));
    }


// ICY TOWER
    sf::Texture icyy;
    if(!icyy.loadFromFile("tekstury/platformy/chmura.png")) { return 1; }
    std::vector<std::unique_ptr<platformy>> v_platform;
    for(int i=0; i<100; i++){
        int ktora_platforma = std::rand()%3;
        if(ktora_platforma==1 || ktora_platforma==2)
            v_platform.emplace_back(std::make_unique<w_dol>(icyy,sf::Vector2f((std::rand() % (window.getSize().x -200))+50,-120)));
        else if(ktora_platforma==0)
            v_platform.emplace_back(std::make_unique<w_dol_i_w_boki>(icyy,sf::Vector2f((std::rand() % (window.getSize().x -200))+50,-120)));
    }


// WROGOWIE
    sf::Texture strzelajacy;
    if(!strzelajacy.loadFromFile("tekstury/wrogowie/strzelajacy.png")) { return 1; }
    sf::Texture nie_strzelajacy;
    if(!nie_strzelajacy.loadFromFile("tekstury/wrogowie/nie_strzelajacy.png")) { return 1; }
    std::vector<std::unique_ptr<Wrogowie>> v_wrogowie;
    for(int i=0;i<10;i++){
        if(i<5){
            auto cos = std::make_unique<Wrogowie_na_boki>(strzelajacy,sf::Vector2f((std::rand() % (window.getSize().x -200))+50,(std::rand() % 200)-300));
            v_wrogowie.emplace_back(move(cos));
        }else{
            auto cos = std::make_unique<Wrogowie_prosto>(nie_strzelajacy,sf::Vector2f(std::rand() % (window.getSize().x -200),(std::rand() % 300)-400));
            v_wrogowie.emplace_back(move(cos));
        }
    }

//POCISKI
    sf::Texture poci;
    if(!poci.loadFromFile("tekstury/pocisk.png")) { return 1; }
    std::vector<std::unique_ptr<Wrogowie>> pociski;


//POJAZD KOSMICZNY
    sf::Texture stat;
    if(!stat.loadFromFile("tekstury/statek.png")) { return 1; }
    sf::Texture czer;
    if(!czer.loadFromFile("tekstury/czeresnia.png")) { return 1; }
    std::vector<std::unique_ptr<sf::Sprite>> statek_i_czeresnia;


//TLO
    sf::Texture tlo1;
    if(!tlo1.loadFromFile("tekstury/sheett.png")) { return 1; }
    sf::Sprite tlo;
    tlo.setTexture(tlo1);
    tlo.setScale(2,2);
    tlo.setPosition(0,550);

    sf::Texture tlo2;
    if(!tlo2.loadFromFile("tekstury/tlo.jpg")) { return 1; }
    sf::Sprite tloo;
    tloo.setTexture(tlo2);
    tloo.setTextureRect(sf::IntRect(0,2580,460,700));
    tloo.setPosition(0,0);


//ODLICZANIE
    sf::Texture zyciaa;
    if(!zyciaa.loadFromFile("tekstury/odliczanie/zycia.png")) { return 1; }
    sf::Sprite zycia;
    zycia.setPosition(20,20);
    zycia.setScale(0.5,0.5);
    zycia.setTexture(zyciaa);

    sf::Texture zlapane;
    if(!zlapane.loadFromFile("tekstury/odliczanie/zlapane.png")) { return 1; }
    sf::Texture zestrzelone;
    if(!zestrzelone.loadFromFile("tekstury/odliczanie/zestrzelone.png")) { return 1; }
    sf::Sprite zlapane_zestrzelone;
    zlapane_zestrzelone.setPosition(300,20);
    zlapane_zestrzelone.setScale(0.5,0.5);

    sf::Texture liczb;
    if(!liczb.loadFromFile("tekstury/odliczanie/1234.png")) { return 1; }
    sf::Sprite l1;
    l1.setPosition(20,40);
    l1.setTexture(liczb);
    l1.setTextureRect(sf::IntRect(0,0,1,1));
    sf::Sprite l2;
    l2.setPosition(45,40);
    l2.setTexture(liczb);
    l2.setTextureRect(sf::IntRect(0,0,1,1));
    sf::Sprite l3;
    l3.setPosition(370,40);
    l3.setTexture(liczb);
    l3.setTextureRect(sf::IntRect(0,0,1,1));
    sf::Sprite l4;
    l4.setPosition(395,40);
    l4.setTexture(liczb);
    l4.setTextureRect(sf::IntRect(0,0,1,1));


//MUZYKA
    sf::Music music;
        if (!music.openFromFile("muzyka/calaa1.ogg")){return 1;}
        music.play();
        music.setLoop(true);

// /// // /// // /// //

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = zegar.restart();

        guy.poczatek_tla(elapsed,window,poczatek_tlo,pocz1,pocz2,pocz3,G1,G2,G3,G4);
        guy.texture_walk(elapsed);
        guy.walk(elapsed,window);
        guy.disappear_food(v_jedzonko,window);
        guy.start_drop_food(elapsed,v_jedzonko); // kiedy postać coś osiągnie to zaczynają spadać (najlepiej żeby to było cos nieodwracalnego) może boola jakiegoś zrobić
        guy.start_icy_tower(elapsed,v_platform);
        guy.start_wrogowie(elapsed,v_wrogowie,window,statek_i_czeresnia,stat,statek_z_G1,statek_z_G2,statek_z_G3,statek_z_G4);
        guy.pocisk_start(elapsed,pociski,poci);
        guy.znikanie_wrogow_i_pociskow(v_wrogowie,window,strzelajacy,nie_strzelajacy,pociski);
        guy.przesuwajace_tlo(elapsed,tloo,tlo);
        guy.wyswieltanie_danych(zlapane_zestrzelone,l1,l2,l3,l4,zlapane,zestrzelone);
        guy.koniec_gry(window,statek_i_czeresnia,czer);

        for(auto &it : pociski){
            it->ruch(elapsed);
        }

        window.clear(sf::Color::Black);

        window.draw(tloo);
        window.draw(tlo);

        window.draw(zycia);
        window.draw(zlapane_zestrzelone);
        window.draw(l1);
        window.draw(l2);
        window.draw(l3);
        window.draw(l4);

        window.draw(guy);
        for(auto &it : v_jedzonko){
            window.draw(*it);
        }
        for(auto &it : v_platform){
            window.draw(*it);
        }
        for(auto &it : v_wrogowie){
            window.draw(*it);
        }
        for(auto &it : pociski){
            window.draw(*it);
        }
        for(auto &it : statek_i_czeresnia){
            window.draw(*it);
        }

        window.draw(poczatek_tlo);

        window.display();
    }

    return 0;
}
