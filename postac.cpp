#include "postac.h"


void Postac::add_bits_of_texture(sf::IntRect xxx){
    bits_of_texture.emplace_back(xxx);
}



void Postac::texture_walk(const sf::Time &e)
{
    if(w_statku==0){
        auto b = getGlobalBounds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            time_animacji_guya = 0;
            setScale(1.0, 1.0);
            setTextureRect(bits_of_texture[0]);
            setPosition(b.left, b.top);
        }
        else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                setScale(1.0, 1.0);
                setPosition(b.left, b.top);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                setScale(-1.0, 1.0);
                setPosition(b.left+b.width, b.top);
            }
            if(time_animacji_guya < 4.0){
                time_animacji_guya += 12 * e.asSeconds();
            }else{
                time_animacji_guya = 0.0;
            }
            if(time_animacji_guya < 1){
                setTextureRect(bits_of_texture[1]);
            }else if(time_animacji_guya < 2){
                setTextureRect(bits_of_texture[2]);
            }else if(time_animacji_guya < 3){
                setTextureRect(bits_of_texture[3]);
            }else
                setTextureRect(bits_of_texture[4]);
        }
    }
}

void Postac::walk(const sf::Time &e,sf::RenderWindow &window){
    auto guy_bounds = getGlobalBounds();

    if(w_statku==0){
        a_y=800;
        v_y += a_y * e.asSeconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            v_x=-200;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            v_x=200;
        }else{
            v_x=0;
        }
        if(ile_kolizji<=0||ile_kolizji>30){
            if(guy_bounds.top+guy_bounds.height>450){
                v_y=0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    v_y=-500;
                }
            }
        }
        move(v_x*e.asSeconds(), v_y*e.asSeconds());
    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(guy_bounds.top >0)
                move(0,e.asSeconds() * -200);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(guy_bounds.top+guy_bounds.height < window.getSize().y)
                move(0,e.asSeconds() * 200);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(guy_bounds.left > 0)
                move(e.asSeconds() * -200,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(guy_bounds.left+guy_bounds.width < window.getSize().x)
                move(e.asSeconds() * 200,0);
        }
    }
}


void Postac::disappear_food(std::vector<std::unique_ptr<Food>> &jo, sf::RenderWindow &window){
    for(int i=0; i<jo.size(); i++){
        auto FOOD_b =jo[i]->getGlobalBounds();
        if(getGlobalBounds().intersects(FOOD_b)){//jeżeni kolizja z postacią
            if(jo[i]->typ()=="good_food"){//jeżeli złapie dobre jedzenie
                zlapane++;
                std::cout<<"ZLAPANE: "<<zlapane<<std::endl;
            }else{//jeżeli złapie złe jedzenie
                zycia--;
                std::cout<<"ZYCIA: "<<zycia<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }else if(FOOD_b.top>window.getSize().y){//jeżeli nie złapie
            if(jo[i]->typ()=="good_food"){//jeżeli nie złapie dobrego jedzenia
                zycia--;
                std::cout<<"ZYCIA: "<<zycia<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }
    }
}

void Postac::start_drop_food(const sf::Time &e, std::vector<std::unique_ptr<Food>> &jo){
    auto guy_bounds = getGlobalBounds();
    if(guy_bounds.left<500)
        start_drop_food_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
    if(start_drop_food_==1){
        if(jo.size()>0 && zlapane<2){
            jo[0]->drop(e,zlapane);
        }
        for(int j=1;j<jo.size();j++){//że dla ilu? i tak spadają wszystkie
            if(jo[j-1]->getGlobalBounds().top>200){   // jeśli wcześniejsze jedzenie będzie dalej niż 200 to następne zaczyna spadać
                //jo[j]->drop(e,zlapane);
            }
        }
    }

}



void Postac::start_icy_tower(const sf::Time &e, std::vector<std::unique_ptr<platformy>> & platformy){//}, std::vector<std::unique_ptr<Food>> &jo){
    auto guy_bounds = getGlobalBounds();
    if(zlapane>=2){//warunek
        start_icy_tower_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
    }//else{
    if(ile_kolizji>30){
        //start_icy_tower_=0;
        for(auto &it : platformy){
            it->setPosition(-200,0);
        }
    }
    if(start_icy_tower_==1){
        platformy[0]->ruch(e,ile_kolizji);
        for(int j=1;j<=platformy.size();j++){
            if(platformy[j-1]->getGlobalBounds().top>200){//&&ile_kolizji<10){   // jeśli wcześniejsze jedzenie będzie dalej niż 200 to następne zaczyna spadać
                platformy[j]->ruch(e,ile_kolizji);
                //start_icy_tower_=0;
            }
            if(platformy[j-1]->getGlobalBounds().top>620){
                platformy.erase(platformy.begin()+j-1);
            }
        }
    }
    for (auto& platform : platformy) {
        auto boundsPlatform = platform->getGlobalBounds();
        if(getGlobalBounds().intersects(boundsPlatform)){
            if(guy_bounds.top+guy_bounds.height<boundsPlatform.top+20){
                v_y=platform->v_yfunkcja();
                v_x=platform->v_xfunkcja();
                move(v_x*e.asSeconds(),0);
                if(guy_bounds.top>200){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                        v_y=-500;
                        ile_kolizji++;
                    }
                }
            }else if(guy_bounds.top+guy_bounds.height>boundsPlatform.top){
                v_y=-300;//łapanie chmurek od dołu
            }
        }
    }
}

void Postac::start_wrogowie(const sf::Time &e, std::vector<std::unique_ptr<Wrogowie>> &wrogowie,sf::RenderWindow &window, std::vector<std::unique_ptr<sf::Sprite>> &statek,sf::Texture &stat,sf::Texture &statek_nowy){
    auto guy_bounds = getGlobalBounds();
    if(ile_kolizji>30&&zestrzelony<=0){
        statek.emplace_back(std::make_unique<sf::Sprite>());
        statek[0]->setTexture(stat);
        statek[0]->setPosition(sf::Vector2f(300,300));
        if(guy_bounds.left<450&&guy_bounds.left+guy_bounds.width>300&&
           guy_bounds.top>300&&guy_bounds.top+guy_bounds.height<500){
            kolizja_ze_statkiem_=1;
            setTexture(statek_nowy);
            setTextureRect(sf::IntRect(0,0,82,144));
            setPosition(sf::Vector2f(200,450));
            w_statku=1;
            start_wrogowie_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
        }
    }
    if(kolizja_ze_statkiem_==1){
        statek[0]->setPosition(-200,0);
    }
    if(start_wrogowie_==1&&zestrzelony<25){
        for(auto &it : wrogowie){
            it->ruch(e,window);
        }
    }
    if(zestrzelony>=25){
        for(auto &it : wrogowie){
            it->setPosition(1,-200);
        }
    }
}

void Postac::pocisk_start(const sf::Time &e,std::vector<std::unique_ptr<Wrogowie>> &wektor,sf::Texture &uff){
    auto bounds=getGlobalBounds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if(czas_pocisku==0){
            wektor.emplace_back(std::make_unique<Pocisk>(uff,sf::Vector2f(bounds.left+(bounds.width/2),bounds.top+(bounds.height/2))));;
        }else if(czas_pocisku>=0.5){
            czas_pocisku=0;
        }
        czas_pocisku=czas_pocisku+e.asSeconds();
    }else{
        czas_pocisku=0;
    }
}

//zestrzeliwanie mobów
void Postac::znikanie_wrogow_i_pociskow(std::vector<std::unique_ptr<Wrogowie> > &wektor, sf::RenderWindow &window,sf::Texture &tak,sf::Texture &nie,std::vector<std::unique_ptr<Wrogowie>> &wektor2){
    for(int i=0; i<wektor.size(); i++){
        auto wektor_bounds =wektor[i]->getGlobalBounds();
        //jeżeli kolizja z postacią
        if(getGlobalBounds().intersects(wektor_bounds)){
            if(wektor[i]->typ()=="TAK"){
                wektor.emplace_back(std::make_unique<Wrogowie_strzelajacy>(tak,sf::Vector2f((std::rand() % 800),-80)));
            }else if(wektor[i]->typ()=="NIE"){
                wektor.emplace_back(std::make_unique<Wrogowie_nie_strzelajacy>(nie,sf::Vector2f((std::rand() % 800),-80)));
            }
            wektor.erase(wektor.begin()+i);
            zycia--;
            std::cout<<"ZYCIA: "<<zycia<<std::endl;
        }
        //jeżeli wyleci za ekran
        if(wektor_bounds.top+wektor_bounds.height>650 || wektor_bounds.left<-50 || wektor_bounds.left>850){
            if(wektor[i]->typ()=="TAK"){
                wektor.emplace_back(std::make_unique<Wrogowie_strzelajacy>(tak,sf::Vector2f((std::rand() % 800),-80)));
            }else if(wektor[i]->typ()=="NIE"){
                wektor.emplace_back(std::make_unique<Wrogowie_nie_strzelajacy>(nie,sf::Vector2f((std::rand() % 800),-80)));
            }
            wektor.erase(wektor.begin()+i);
            zycia--;
            std::cout<<"ZYCIA: "<<zycia<<std::endl;
        }
        //jeżeli trafią pociski
        for(int j=0; j<wektor2.size(); j++){
            auto wektor_bounds2 =wektor2[j]->getGlobalBounds();
            if(wektor_bounds.intersects(wektor_bounds2)){
                if(wektor[i]->typ()=="TAK"){
                    wektor.emplace_back(std::make_unique<Wrogowie_strzelajacy>(tak,sf::Vector2f((std::rand() % 800),-80)));
                }else if(wektor[i]->typ()=="NIE"){
                    wektor.emplace_back(std::make_unique<Wrogowie_nie_strzelajacy>(nie,sf::Vector2f((std::rand() % 800),-80)));
                }
                zestrzelony++;
                std::cout<<"ZESTRZELONY: "<<zestrzelony<<std::endl;
                wektor.erase(wektor.begin()+i);
                wektor2.erase(wektor2.begin()+j);
            }
        }
    }
}

void Postac::koniec_gry(sf::RenderWindow &window,std::vector<std::unique_ptr<sf::Sprite>> &czeresnia,sf::Texture &czer){
    auto guy_bounds = getGlobalBounds();
    if(zycia<=0){// jeśli życia się skończą to koniec gry
        std::cout<<"PRZEGRALES"<<std::endl;
        window.close();
    }
    if(guy_bounds.top>620){
        window.close();
    }
    if(zestrzelony>=25){
        czeresnia.emplace_back(std::make_unique<sf::Sprite>());
        czeresnia[0]->setTexture(czer);
        czeresnia[0]->setPosition(sf::Vector2f(300,300));
        czeresnia[0]->setTextureRect(sf::IntRect(0,0,185,185));
        if(guy_bounds.left<450&&guy_bounds.left+guy_bounds.width>300&&
           guy_bounds.top>300&&guy_bounds.top+guy_bounds.height<500){
            kolizja_z_czeresnia_=1;
        }
    }
    if(kolizja_z_czeresnia_==1){
        std::cout<<"WYGRALES!!!"<<std::endl;
        window.close();
    }
}
