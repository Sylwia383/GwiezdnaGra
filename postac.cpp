#include "postac.h"

void Postac::poczatek_tla(const sf::Time &e,sf::RenderWindow &window,sf::Sprite &poczatek,sf::Texture &pocz1,sf::Texture &pocz2,sf::Texture &pocz3,sf::Texture &G1,sf::Texture &G2,sf::Texture &G3,sf::Texture &G4){
    //e.asSeconds();
    pocz1_=true;
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if(pocz1_==1){
        poczatek.setTexture(pocz1);
    }


    if(pocz1_==1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)){//myszkaaaaaaa zagraj
        if(mouse_pos.x>50 && mouse_pos.x<410 && mouse_pos.y>420  && mouse_pos.y<520){
            pocz1_=0;
            pocz2_=1;
        }
    }
    if(pocz2_==1){
        poczatek.setTexture(pocz2);
    }

    if(pocz2_==1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(mouse_pos.x>120 && mouse_pos.x<310 && mouse_pos.y>600  && mouse_pos.y<680){
            pocz2_=0;
            pocz3_=1;
        }
    }
    if(pocz3_==1){
        poczatek.setTexture(pocz3);
    }
    if(pocz3_==1&& sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        std::cout<<mouse_pos.x<<"  "<<mouse_pos.y<<std::endl;
        if(mouse_pos.x>85 && mouse_pos.x<145 && mouse_pos.y>275  && mouse_pos.y<405){
            setTexture(G1);
            g1_=1;
        }else if(mouse_pos.x>280 && mouse_pos.x<345 && mouse_pos.y>280  && mouse_pos.y<405){
            setTexture(G2);
            g2_=1;
        }else if(mouse_pos.x>83 && mouse_pos.x<150 && mouse_pos.y>470  && mouse_pos.y<600){
            setTexture(G3);
            g3_=1;
        }else if(mouse_pos.x>280 && mouse_pos.x<345 && mouse_pos.y>470  && mouse_pos.y<600){
            setTexture(G4);
            g4_=1;
        }
    }
    if(g1_==1||g2_==1||g3_==1||g4_==1){
        poczatek.setPosition(-500,0);
    }
}


void Postac::add_bits_of_texture(sf::IntRect xxx){// dodawanie elementów tekstury do wekrota
    bits_of_texture.emplace_back(xxx);
}



void Postac::texture_walk(const sf::Time &e)//animacja tekstury
{
    if(w_statku_==false){//anikacja tekstury przed rozpoczęciem trzeciego poziomu
        auto b = getGlobalBounds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            time_animacji_guya_ = 0;
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
            if(time_animacji_guya_ < 4.0){
                time_animacji_guya_ += 12 * e.asSeconds();
            }else{
                time_animacji_guya_ = 0.0;
            }
            if(time_animacji_guya_ < 1){
                setTextureRect(bits_of_texture[1]);
            }else if(time_animacji_guya_ < 2){
                setTextureRect(bits_of_texture[2]);
            }else if(time_animacji_guya_ < 3){
                setTextureRect(bits_of_texture[3]);
            }else
                setTextureRect(bits_of_texture[4]);
        }
    }
}

void Postac::walk(const sf::Time &e,sf::RenderWindow &window){
    auto guy_bounds = getGlobalBounds();

    if(w_statku_==0 && guy_bounds.left > 0 && guy_bounds.left+guy_bounds.width < window.getSize().x){
        a_y_=800;
        v_y_ += a_y_ * e.asSeconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                v_x_=-200;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                v_x_=200;
        }else{
            v_x_=0;
        }
        if(ile_kolizji_<=0||ile_kolizji_>30){
            if(guy_bounds.top+guy_bounds.height>550){
                v_y_=0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    v_y_=-500;
                }

            }
        }
        move(v_x_*e.asSeconds(), v_y_*e.asSeconds());
    }else if(w_statku_==1){//jeżeli zostanie odpalony trzeci poziom
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
                zlapane_++;
                std::cout<<"ZLAPANE: "<<zlapane_<<std::endl;
            }else{//jeżeli złapie złe jedzenie
                zycia_--;
                std::cout<<"ZYCIA: "<<zycia_<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }else if(FOOD_b.top>window.getSize().y){//jeżeli nie złapie
            if(jo[i]->typ()=="good_food"){//jeżeli nie złapie dobrego jedzenia
                zycia_--;
                std::cout<<"ZYCIA: "<<zycia_<<std::endl;
            }
        jo.erase(jo.begin()+i);//znika
        }
    }
}

void Postac::start_drop_food(const sf::Time &e, std::vector<std::unique_ptr<Food>> &jo){
    auto guy_bounds = getGlobalBounds();
    if(g1_==1||g2_==1||g3_==1||g4_==1){//jakiśiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
        start_drop_food_=1;
        }// jeśli typek spełni jakiś warunek to zaczynają spadać
    if(start_drop_food_==1){
        if(jo.size()>0 && zlapane_<2){
            jo[0]->drop(e,zlapane_);
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
    if(zlapane_>=2){//warunek
        start_icy_tower_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać
    }//else{
    if(ile_kolizji_>30){
        //start_icy_tower_=0;
        for(auto &it : platformy){
            it->setPosition(-200,0);
        }
    }
    if(start_icy_tower_==1){
        platformy[0]->ruch(e,ile_kolizji_);
        for(int j=1;j<=platformy.size();j++){
            if(platformy[j-1]->getGlobalBounds().top>200){//&&ile_kolizji<10){   // jeśli wcześniejsze jedzenie będzie dalej niż 200 to następne zaczyna spadać
                platformy[j]->ruch(e,ile_kolizji_);
                //start_icy_tower_=0;
            }
            if(platformy[j-1]->getGlobalBounds().top>720){//jak za nisko to znika
                platformy.erase(platformy.begin()+j-1);
            }
        }
    }
    for (auto& platform : platformy) {// dla każdej chmurki
        auto boundsPlatform = platform->getGlobalBounds();
        if(getGlobalBounds().intersects(boundsPlatform)){
            if(guy_bounds.top+guy_bounds.height<boundsPlatform.top+20){
                v_y_=platform->v_y();
                v_x_=platform->v_x();
                move(v_x_*e.asSeconds(),0);
                if(guy_bounds.top>200){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                        v_y_=-500;
                        ile_kolizji_++;
                    }
                }
            }else if(guy_bounds.top+guy_bounds.height>boundsPlatform.top){
                v_y_=-300;//łapanie chmurek od dołu
            }
        }
    }
}

void Postac::start_wrogowie(const sf::Time &e, std::vector<std::unique_ptr<Wrogowie>> &wrogowie,sf::RenderWindow &window, std::vector<std::unique_ptr<sf::Sprite>> &statek,sf::Texture &stat,sf::Texture &sG1,sf::Texture &sG2,sf::Texture &sG3,sf::Texture &sG4){
    auto guy_bounds = getGlobalBounds();
    if(ile_kolizji_>30 && zestrzelony_==0){
        statek.emplace_back(std::make_unique<sf::Sprite>());
        statek[0]->setTexture(stat);
        statek[0]->setPosition(sf::Vector2f(180,400));
        if(guy_bounds.left<226&&guy_bounds.left+guy_bounds.width>180&&
           guy_bounds.top+guy_bounds.height>400&&guy_bounds.top<550){
            kolizja_ze_statkiem_=1;
            if(g1_==1){
                setTexture(sG1);
            }else if(g2_==1){
                setTexture(sG2);
            }else if(g3_==1){
                setTexture(sG3);
            }else if(g4_==1){
                setTexture(sG4);
            }
            setTextureRect(sf::IntRect(0,0,82,144));
            setPosition(sf::Vector2f(190,500));
            w_statku_=1;
            start_wrogowie_=1;  // jeśli typek spełni jakiś warunek to zaczynają spadać


        }
    }
    if(kolizja_ze_statkiem_==1){//&&zestrzelony_<=0){
        statek[0]->setPosition(-200,0);
        //w_statku_=1;
    }
    if(start_wrogowie_==1&&zestrzelony_<25){
        for(auto &it : wrogowie){
            it->ruch(e);
        }
    }
    if(zestrzelony_>=25){
        for(auto &it : wrogowie){
            it->setPosition(1,-200);
        }
    }
}

void Postac::pocisk_start(const sf::Time &e,std::vector<std::unique_ptr<Wrogowie>> &wektor,sf::Texture &uff){
    auto bounds=getGlobalBounds();
    //if(w_statku_==1){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(czas_pocisku_==0){
                wektor.emplace_back(std::make_unique<Pocisk>(uff,sf::Vector2f(bounds.left+(bounds.width/2),bounds.top+(bounds.height/2))));;
            }else if(czas_pocisku_>=0.5){
                czas_pocisku_=0;
            }
            czas_pocisku_=czas_pocisku_+e.asSeconds();
        }else{
            czas_pocisku_=0;
        }
    //}
}

//zestrzeliwanie mobów
void Postac::znikanie_wrogow_i_pociskow(std::vector<std::unique_ptr<Wrogowie> > &wektor, sf::RenderWindow &window,sf::Texture &tak,sf::Texture &nie,std::vector<std::unique_ptr<Wrogowie>> &wektor2){
    for(int i=0; i<wektor.size(); i++){
        auto wektor_bounds =wektor[i]->getGlobalBounds();
        //jeżeli kolizja z postacią
        if(getGlobalBounds().intersects(wektor_bounds)){
            if(wektor[i]->typ()=="TAK"){
                wektor.emplace_back(std::make_unique<Wrogowie_na_boki>(tak,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
            }else if(wektor[i]->typ()=="NIE"){
                wektor.emplace_back(std::make_unique<Wrogowie_prosto>(nie,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
            }
            wektor.erase(wektor.begin()+i);
            zycia_--;
            std::cout<<"ZYCIA: "<<zycia_<<std::endl;
        }
        //jeżeli wyleci za ekran
        if(wektor_bounds.top>700 || wektor_bounds.left<-50 || wektor_bounds.left>460){
            if(wektor[i]->typ()=="TAK"){
                wektor.emplace_back(std::make_unique<Wrogowie_na_boki>(tak,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
            }else if(wektor[i]->typ()=="NIE"){
                wektor.emplace_back(std::make_unique<Wrogowie_prosto>(nie,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
            }
            wektor.erase(wektor.begin()+i);
            zycia_--;
            std::cout<<"ZYCIA: "<<zycia_<<std::endl;
        }
        //jeżeli trafią pociski
        for(int j=0; j<wektor2.size(); j++){
            auto wektor_bounds2 =wektor2[j]->getGlobalBounds();
            if(wektor_bounds.intersects(wektor_bounds2)){
                if(wektor[i]->typ()=="TAK"){
                    wektor.emplace_back(std::make_unique<Wrogowie_na_boki>(tak,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
                }else if(wektor[i]->typ()=="NIE"){
                    wektor.emplace_back(std::make_unique<Wrogowie_prosto>(nie,sf::Vector2f((std::rand() % (window.getSize().x -200)),-110)));
                }
                zestrzelony_++;
                std::cout<<"ZESTRZELONY: "<<zestrzelony_<<std::endl;
                wektor.erase(wektor.begin()+i);
                wektor2.erase(wektor2.begin()+j);
            }
        }
    }
}

void Postac::przesuwajace_tlo(const sf::Time &e,sf::Sprite &tloo,sf::Sprite &tlo){
    //ruszające się tło
    if(ile_kolizji_>0){
        czas_tla_ += 12 * e.asSeconds();
        if(czas_tla_>0.5){
            tloo.setTextureRect(sf::IntRect(0,przesuwanie_tla_tloo_,460,700));
            czas_tla_=0;
            przesuwanie_tla_tloo_-=1;
            if(przesuwanie_tla_tlo_<700){
                tlo.setPosition(0,przesuwanie_tla_tlo_);
                przesuwanie_tla_tlo_+=2;
            }
        }
    }
}


void Postac::wyswieltanie_danych(sf::Sprite &zlap_zest,sf::Sprite &l1,sf::Sprite &l2,sf::Sprite &l3,sf::Sprite &l4,sf::Texture &zl,sf::Texture &ze){
    std::vector<sf::IntRect> cyfry(10);
    cyfry[0]=sf::IntRect(404,0,45,59);
    cyfry[1]=sf::IntRect(0,0,45,59);
    cyfry[2]=sf::IntRect(45,0,45,59);
    cyfry[3]=sf::IntRect(89,0,45,59);
    cyfry[4]=sf::IntRect(135,0,45,59);
    cyfry[5]=sf::IntRect(180,0,45,59);
    cyfry[6]=sf::IntRect(225,0,45,59);
    cyfry[7]=sf::IntRect(271,0,45,59);
    cyfry[8]=sf::IntRect(314,0,45,59);
    cyfry[9]=sf::IntRect(360,0,45,59);

    if(zycia_==10){
        l1.setTextureRect(cyfry[1]);
        l2.setTextureRect(cyfry[0]);
    }
    for(int i=9; i>0; i--){
        if(zycia_==i){
            l1.setTextureRect(cyfry[0]);
            l2.setTextureRect(cyfry[i]);
        }
    }

    if(zlapane_>0&&zlapane_<=50){
        zlap_zest.setTexture(zl);
        for(int i=5; i>=0; i--){
            if(zlapane_>50){}// ///////////////////////////////////////////////// tuuu
            l3.setTextureRect(cyfry[i]);
            for(int j=9; j>=0; j--){
                l4.setTextureRect(cyfry[j]);
            }
        }
    }

    if(zestrzelony_>0&&zestrzelony_<=50){
        zlap_zest.setTexture(ze);
        for(int i=5; i>=0; i--){
            l3.setTextureRect(cyfry[i]);
            for(int j=9; j>=0; j--){
                l4.setTextureRect(cyfry[j]);
            }
        }
    }


}

void Postac::koniec_gry(sf::RenderWindow &window,std::vector<std::unique_ptr<sf::Sprite>> &czeresnia,sf::Texture &czer){
    auto guy_bounds = getGlobalBounds();
    if(zycia_<=0){// jeśli życia się skończą to koniec gry
        std::cout<<"PRZEGRALES"<<std::endl;
        window.close();
    }
    if(guy_bounds.top>720){
        window.close();
    }
    if(zestrzelony_>=25){
        czeresnia.emplace_back(std::make_unique<sf::Sprite>());
        czeresnia[0]->setTexture(czer);
        czeresnia[0]->setPosition(sf::Vector2f(140,50));
        czeresnia[0]->setTextureRect(sf::IntRect(0,0,185,185));
        if(guy_bounds.left<225&&guy_bounds.left+guy_bounds.width>140&&
           guy_bounds.top+guy_bounds.height>50&&guy_bounds.top<235){
            kolizja_z_czeresnia_=1;
        }
    }
    if(kolizja_z_czeresnia_==1){
        std::cout<<"WYGRALES!!!"<<std::endl;
        window.close();
    }
}
