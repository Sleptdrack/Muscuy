#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>
using namespace GameModel;
//using namespace GameView;
using namespace GameController;
using namespace sf;
unsigned int Width_W = 1280, Heigth_W = 720;
unsigned int Width = 1100, Heigth = 650,Border;
//DESTINO DEL SONIDO

RenderWindow window(VideoMode(Width_W, Heigth_W), "Muscuy");
namespace GameView {
    class Animation
    {
    public:
        Animation() = default;
        Animation(int x, int y, int width, int height)
        {
            texture.loadFromFile("Imagenes/main_character.png");
            for (int i = 0; i < nFrames; i++)
            {

                frames[i] = { x + i * width,y, width, height };
            }



        }
        void ApplyToSprite(sf::Sprite& s, Player^ player)

        {
            if (player->Health > 75)
            {
                texture.loadFromFile("Imagenes/main_character.png");
            }
            if ((player->Health <= 75) && (player->Health > 50))
            {
                texture.loadFromFile("Imagenes/main_character_75.png");
            }
            if ((player->Health <= 50) && (player->Health > 25))
            {
                texture.loadFromFile("Imagenes/main_character_50.png");
            }
            if ((player->Health <= 25) && (player->Health > 0))
            {
                texture.loadFromFile("Imagenes/main_character_25.png");
            }

            s.setTexture(texture);
            s.setTextureRect(frames[iFrame]);


        }
        void Update(float dt)
        {
            time += dt;
            while (time >= holdTime)
            {
                time -= holdTime;
                Advance();
            }
        }


    private:
        void Advance()
        {
            if (++iFrame >= nFrames)
            {
                iFrame = 0;
            }
        }

    private:
        //9 images for the character's movement
        static constexpr int nFrames = 8;
        static constexpr float holdTime = 0.1f;
        sf::Texture texture;
        sf::IntRect frames[nFrames];
        int iFrame = 0;
        float time = 0.0f;
    };
    class Character
    {
    private:
        enum class AnimationIndex
        {
            WalkingRight,
            WalkingLeft,
            WalkingDown,
            WalkingUp,
            Count,
        };

    public:
        Character(const sf::Vector2f& pos)
            :
            pos(pos)
        {
            sprite.setTextureRect({ 0,0,64,64 });
            animations[int(AnimationIndex::WalkingRight)] = Animation(64, 0, 64, 64);
            animations[int(AnimationIndex::WalkingLeft)] = Animation(64, 64, 64, 64);
            animations[int(AnimationIndex::WalkingUp)] = Animation(64, 128, 64, 64);
            animations[int(AnimationIndex::WalkingDown)] = Animation(64, 192, 64, 64);
        }
        void Draw(sf::RenderTarget& rt)const
        {
            rt.draw(sprite);
        }
        void SetDirection(int dir[2])
        {

            if (dir[0] > 0.0f)
            {
                curAnimation = AnimationIndex::WalkingRight;
            }
            else if (dir[0] < 0.0f)
            {
                curAnimation = AnimationIndex::WalkingLeft;
            }
            else if (dir[1] > 0.0f)
            {
                curAnimation = AnimationIndex::WalkingDown;
            }
            else if (dir[1] < 0.0f)
            {
                curAnimation = AnimationIndex::WalkingUp;
            }
        }
        void Update(float dt, Player^ player)
        {
            animations[int(curAnimation)].Update(dt);
            animations[int(curAnimation)].ApplyToSprite(sprite, player);
        }



    private:
        static constexpr float speed = 100.0f;
        sf::Vector2f pos;
        sf::Vector2f vel = { 0.0f,0.0f };
        Animation animations[int(AnimationIndex::Count)];
        AnimationIndex curAnimation = AnimationIndex::WalkingRight;
    public:
        sf::Sprite sprite;
    };

    class Animation_boss
    {
    public:
        Animation_boss() = default;
        Animation_boss(int width, int height)
        {
            texture.loadFromFile("boss_1_vida100.png");

            frames[0] = { 0, 0, width, height };
            frames[1] = { 128, 0, width, height };
            frames[2] = { 256, 0, width, height };
            frames[3] = { 384, 0, width, height };
            frames[4] = { 0, 128, width, height };
            frames[5] = { 128, 128, width, height };
            frames[6] = { 256, 128, width, height };
            frames[7] = { 384, 128, width, height };
        }

        void ApplyToSprite(sf::Sprite& s, Boss^ boss)
        {
            if (boss->Health > 800)
            {
                texture.loadFromFile("Imagenes/boss_1_vida100.png");
            }
            if ((boss->Health <= 800) && (boss->Health > 600))
            {
                texture.loadFromFile("Imagenes/boss_1_vida80.png");
            }
            if ((boss->Health <= 600) && (boss->Health > 400))
            {
                texture.loadFromFile("Imagenes/boss_1_vida60.png");
            }
            if ((boss->Health <= 400) && (boss->Health > 200))
            {
                texture.loadFromFile("Imagenes/boss_1_vida40.png");
            }
            if ((boss->Health <= 200) && (boss->Health > 0))
            {
                texture.loadFromFile("Imagenes/boss_1_vida20.png");
            }

            s.setTexture(texture);
            s.setTextureRect(frames[iFrame]);
        }

        void Update(float dt)
        {
            time += dt;
            while (time >= holdTime)
            {
                time -= holdTime;
                Advance();
            }
        }

    private:
        void Advance()
        {
            if (++iFrame >= nFrames)
            {
                iFrame = 0;
            }
        }

    private:
        //9 images for the character's movement
        static constexpr int nFrames = 8;
        static constexpr float holdTime = 0.1f;
        sf::Texture texture;
        sf::IntRect frames[nFrames];
        int iFrame = 0;
        float time = 0.0f;
    };
    class character_boss
    {

    private:
        enum class AnimationIndex
        {
            Walking,
            Count,
        };

    public:
        character_boss(const sf::Vector2f& pos)
            :
            pos(pos)
        {
            sprite.setTextureRect({ 0,0,128,128 });
            animations = Animation_boss(128, 128);

        }
        void Draw(sf::RenderTarget& rt)const
        {
            rt.draw(sprite);
        }


        void Update(float dt, Boss^ boss)
        {
            pos += vel * dt;

            animations.Update(dt);
            animations.ApplyToSprite(sprite, boss);

            sprite.setPosition(pos);
        }




    private:
        static constexpr float speed = 100.0f;
        sf::Vector2f pos;
        sf::Vector2f vel = { 0.0f,0.0f };
        Animation_boss animations;
    public:
        sf::Sprite sprite;
    };

    //lo invocas asi: character_boss boss({600.0f,300.0f});
    // boss.Update(dt, personaje);; esto es para que se actualize la animacion 
    // boss.Draw(window); esto es para el dibujo
    // boss.sprite.setPosition(personaje->X, personaje->Y);


    class Item {
    public:
        sf::Sprite sprite;
        sf::Texture texture;
    public:
        Item() {

        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(sprite);
        }
        void SetPosition(float x, float y) {
            sprite.setPosition(x, y);
        }
    };
    class ItemArmor :public Item{
    public:
        ItemArmor()
        {
            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 192, 64, 64 });


        }
        void SetTexture() {
            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 192, 64, 64 });
        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(sprite);
        }
    };
    class ItemVelocity :public Item{
    public:
        ItemVelocity()
        {

            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 128, 64, 64 });


        }
        void SetTexture() {
            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 128, 64, 64 });
        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(sprite);
        }
    };
    class ItemDamage :public Item {
    public:
        ItemDamage()
        {

            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 64, 64, 64 });


        }
        void SetTexture() {
            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 64, 64, 64 });
        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(sprite);
        }
    };
    class ItemHealth :public Item{
    public:
        ItemHealth()
        {

            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 0, 64, 64 });


        }
        void SetTexture() {
            texture.loadFromFile("Imagenes/objetos.png");
            sprite = sf::Sprite(texture);
            sprite.setTextureRect({ 0, 0, 64, 64 });
        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(sprite);
        }
    };
    class Word {
    public:
        Font font;
        Text text;
        String string;
        float X;
        float Y;
        FloatRect Box;
    public:
        Word(String string, float x, float y) {
            this->font.loadFromFile("Font/arial.ttf");
            this->text.setFont(this->font);
            this->text.setPosition(x, y);
            this->text.setString(string);
            this->text.setColor(sf::Color::White);
            this->Box = this->text.getGlobalBounds();
        }
        void UpdateString(String string) {
            this->text.setString(string);
        }
        void UpdateColor(Color color) {
            this->text.setColor(color);
        }
        int Clk_btn(sf::RenderWindow& rt_i) {
            Vector2i M = Mouse::getPosition(rt_i);
            if (this->Box.contains(M.x, M.y)) {
                this->UpdateColor(Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    return 1;
                }
            }
            else {
                this->UpdateColor(Color::Yellow);
                return 0;
            }
        }
        void Size(int size) {
            text.setCharacterSize(size);
        }
        void Draw(sf::RenderTarget& rt_i)const
        {
            rt_i.draw(text);
        }
    };

}

int main()
{
    
    SoundBuffer Buffer;
    //Sonido a cargar
    Sound Sonido;
    Buffer.loadFromFile("SoundTrack/music_background.wav");
    // SE GUARDARA EL SONIDO EN EL BUFFER LISTO PARA SER USADO
    Sonido.setBuffer(Buffer);
    GameView::Item ListItem[5];
    GameView::ItemArmor A;
    GameView::ItemDamage D;
    GameView::ItemHealth H;
    GameView::ItemVelocity V;
    int state = 0,InPause=0,id=0;
    int prob = 0;
    int prob10 = 0;
    int prob_vel = 0;
    int typeb = 0;
    auto tp = std::chrono::steady_clock::now();
    float dt;
    Clock time2;
    Texture T_Map,T1,T2;
    T1.loadFromFile("Imagenes/RM.png");
    T2.loadFromFile("Imagenes/TM.png");
    Sprite Map,W[4];
    W[0].setTexture(T1);
    W[1].setTexture(T1);
    W[2].setTexture(T2);
    W[3].setTexture(T2);
    Border = (Width_W - Width) / 2;
    W[0].setScale((float)(Border+5)/95, 1);
    W[0].setPosition(0, 0);
    W[1].setPosition((float)Width+Border, 0);
    W[1].setScale((float)(Border + 5) / 95, 1);
    W[2].setPosition((float)Border, 0);
    W[2].setScale((float)(Width+5)/1280, (float)(Border+5)/102);
    W[3].setPosition((float)(Border), Heigth);
    W[3].setScale((float)(Width + 5) / 1280, (float)(Border+5)/ 102);
    T_Map.loadFromFile("Imagenes/Mapa.png");
    Map.setTexture(T_Map);
    Map.setPosition(Border, Border);
    Map.setScale((float)Width/1007, (float)(Heigth-Border)/552);
    int flag = 0;
    Vector2i M;
    //texto;


    std::string health = "Health: ",expp="Exp: ",level="Level: ",fp="Room Number: ", healthboss = " BOSS=  " , healthworm1 = " WORM1=  ", healthworm2 = " WORM2=  ", healthworm3 = " WORM3=  ";
    GameView::Word Loss("LOSSER!!!", (float)Width_W / 2 - 50, (float)Heigth_W / 2);
    Loss.Size(40);
    GameView::Word Btn("Restart", (float)Width_W / 2 - 50, (float)Heigth_W / 2 + 50);
    GameView::Word Live(health, 0, 0);
    GameView::Word Exp(expp, 200, 0);
    GameView::Word Level(level, 350, 0);
    GameView::Word FP(fp, 500, 0);
    GameView::Word Pause("Pause", 1000, 0);
    GameView::Word Save("Save", 1100, 0);
    GameView::Word Menu("Menu", 1200, 0);
    GameView::Word Title("Muscuy", 450, 200);
    GameView::Word StartNew("Start New Game", 500, 400);
    GameView::Word LoadGame("Load Game", 525, 450);
    //SSS
    GameView::Word LiveBoss(healthboss, 450, 600);

    GameView::Word LiveWorm1(healthboss, 100, 650);
    GameView::Word LiveWorm2(healthboss, 400, 650);
    GameView::Word LiveWorm3(healthboss, 700, 650);

    //
    Title.Size(100);
    //Tutorial
    GameView::Word M1("W", 300, 100);
    GameView::Word M2("A", 250, 150);
    GameView::Word M3("S", 350, 150);
    GameView::Word M4("D", 300, 150);
    GameView::Word M5("MOVEMENT", 225, 200);
    GameView::Word A1("A", 900, 100);
    GameView::Word A2("I", 850, 150);
    GameView::Word A3("B", 950, 150);
    GameView::Word A4("D", 900, 150);
    GameView::Word A5("Attack", 875, 200);
    A1.text.setString(L"▲");
    A2.text.setString(L"◄");
    A3.text.setString(L"►");
    A4.text.setString(L"▼");
    RectangleShape Door(Vector2f(20, 100));
    Door.setFillColor(Color::Black);
    Door.setPosition(Width+Border, 335);
    int Tutorial[8],ver=0,base=1000;
    for (int p = 0; p < 8; p++) {
        Tutorial[p] = 1;
    }
    //NUEVO
    Sprite V_boss[10];
    Texture T_boss;
    T_boss.loadFromFile("Imagenes/gus.png");

    int boss_dead[10];

    Texture T_boss2;
    T_boss2.loadFromFile("Imagenes/boss_100.png");
    int boss_dead2[10];
    //
    //lo invocas asi: character_boss boss({600.0f,300.0f});
    // boss.Update(dt, personaje);; esto es para que se actualize la animacion 
    // boss.Draw(window); esto es para el dibujo
    // boss.sprite.setPosition(personaje->X, personaje->Y);
     //SSS
    int flag100 = 50;
    int flag_hit = 2;

    int pared=0,pared1=0,amount=5;
    int minion_dead[10];
    int m_hit[10];
    int m_hit2[10];
    int m_hit3[10];
    Sprite V_minion[10];
    Texture T_minion;
    T_minion.loadFromFile("Imagenes/Personaje2.png");
    //Variables para el ataque
    int dir[2];
    Clock time;
    int chainT=2;
    //Creacion y ubicacion de una trampa
    int hit[10];
    Sprite V_trp[10];
    Texture Texture_trp;
    Texture_trp.loadFromFile("Imagenes/spike.png");
    //Actualizacion de variables y visualizacion de trampas
    //
    //
     //
    for (int u = 0; u < 3; u++) {
        V_boss[u].setTexture(T_boss);
        V_boss[u].setScale(1.5, 1.5);
    }

    //V_boss[3].setTexture(T_boss2);
    //V_boss[3].setScale(0.5, 0.5);
    //

    Boss^ boss = gcnew Boss(100, 100, 140, 100, 0, 0, 1);
    Floor^ floor = gcnew Floor(boss);



    //
    /*
    int Done = 0;
   Player^ personaje= gcnew Player(0,100, 140, 140, 20, 1, 1, 0, 1);
    GameView::Character VP({ 140.f,140.f });
    Sprite chain;
    Texture tchain;
    FloatRect Rect_chain;
    tchain.loadFromFile("Imagenes/chain.png");
    chain.setTexture(tchain);
    chain.setScale((float)0.05, (float)0.05);
    */
    int Done = 0;
    Player^ personaje = gcnew Player(0, 100, 140, 140, 20, 1, 1, 0, 1);
    GameView::Character VP({ 140.f,140.f });
    GameView::character_boss boss_main({ 100.f,140.f });

    Sprite chain;
    Texture tchain;
    FloatRect Rect_chain;
    tchain.loadFromFile("Imagenes/cadena_normal_7.png");
    chain.setTexture(tchain);
    chain.setTextureRect({ 0,186,576,70 });
    chain.setScale(0.10f, 0.30f);

    //
    Sonido.play();
    while (window.isOpen())
    {
        //Sonido.play();
        if (Save.Clk_btn(window)) {
            DB::SaveGame(id, personaje, floor);
        }
        if (Menu.Clk_btn(window)) {
            state = 0;
        }
        if (state == 0) {
            if (StartNew.Clk_btn(window)) {
                state = 3;
                Interaction::InizialiceFloor(floor);
                //Actualizacion de variables y visualizacion de Minions
                for (int u = 0; u < 8; u++) {
                    Tutorial[u] = 1;
                }
                Door.setFillColor(Color::Black);
                personaje->Reset();
                personaje->X = Width / 2 + 140;
                personaje->Y = Heigth / 2;
            }
            if (LoadGame.Clk_btn(window)) {
                state = 2;
            }
            window.clear();
            window.draw(Title.text);
            window.draw(StartNew.text);
            window.draw(LoadGame.text);
            window.display();
        }
        else if (state == 1) {
            if (InPause==1) {
                window.clear();
                window.draw(Map);
                for (int o = 0; o < 10; o++) {
                    window.draw(V_trp[o]);

                }
                for (int i = 0; i < 5; i++) {
                    ListItem[i].Draw(window);
                }
                for (int i = 0; i < 8; i++) {
                    if (floor->LRoom[personaje->CurrentRoom]->LMinion[i]->Health > 0) {
                        window.draw(V_minion[i]);
                    }
                }

                //NUEVO
                if (personaje->CurrentRoom == 4) {
                    for (int i = 0; i < 3; i++) {
                        if (floor->LRoom[personaje->CurrentRoom]->LBoss[i]->Health > 0) {
                            window.draw(V_boss[i]);
                            window.draw(LiveWorm1.text);
                            window.draw(LiveWorm2.text);
                            window.draw(LiveWorm3.text);
                        }
                    }
                }

                if (personaje->CurrentRoom == 8) {
                    if (floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health > 0) {
                        boss_main.Draw(window);
                        window.draw(LiveBoss.text);
                    }
                }
                //



                window.draw(Exp.text);
                window.draw(Live.text);
                window.draw(Level.text);
                window.draw(FP.text);
                window.draw(Pause.text);
                window.draw(Save.text);
                window.draw(Menu.text);
                window.draw(chain);
                VP.Draw(window);
                window.display();
                if (Pause.Clk_btn(window)) {
                    while (Pause.Clk_btn(window));
                    InPause = 0;
                }
            }
            else {
                if (Pause.Clk_btn(window)) {
                    while (Pause.Clk_btn(window));
                    InPause = 1;
                }
                if (personaje->Health > 0) {
                    while (operator<=(time2.getElapsedTime(), milliseconds(5)));
                    time2.restart();
                    //Visualizacion de vida
                    Live.UpdateString(health.replace(8, 3, (std::to_string(personaje->Health))));
                    Exp.UpdateString(expp.replace(5, 3, std::to_string(personaje->Exp)));
                    Level.UpdateString(level.replace(7, 3, std::to_string(personaje->Level)));
                    FP.UpdateString(fp.replace(13, 3, std::to_string(personaje->CurrentRoom+1)));
                    //SSS
                    LiveBoss.UpdateString(healthboss.replace(8, 3, (std::to_string(floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health))));

                    LiveWorm1.UpdateString(healthworm1.replace(8, 3, (std::to_string(floor->LRoom[personaje->CurrentRoom]->LBoss[0]->Health))));
                    LiveWorm2.UpdateString(healthworm2.replace(8, 3, (std::to_string(floor->LRoom[personaje->CurrentRoom]->LBoss[1]->Health))));
                    LiveWorm3.UpdateString(healthworm3.replace(8, 3, (std::to_string(floor->LRoom[personaje->CurrentRoom]->LBoss[2]->Health))));

                    if (floor->LRoom[0]->LMinion[0]->Y>= ver) {
                        ver = floor->LRoom[0]->LMinion[0]->Y;
                    }
                    if (floor->LRoom[0]->LMinion[0]->Y <= base) {
                        base = floor->LRoom[0]->LMinion[0]->Y;
                    }
                    //Coleccion de Objetos
                    Action::PickUP(personaje, floor->LRoom[personaje->CurrentRoom]);
                    Interaction::UseItem(personaje);
                    //Colision con trampas:
                    Action::LevelUp(personaje);
                    for (int i = 0; i < amount; i++) {
                        Action::MinionMove(floor->LRoom[personaje->CurrentRoom]->LMinion[i]);
                        V_minion[i].setPosition(floor->LRoom[personaje->CurrentRoom]->LMinion[i]->X, floor->LRoom[personaje->CurrentRoom]->LMinion[i]->Y);
                        if (floor->LRoom[personaje->CurrentRoom]->LMinion[i]->Health > 0) {
                            Interaction::FightMinion(personaje, chain, floor->LRoom[personaje->CurrentRoom]->LMinion[i],&m_hit[i]);
                        }
                        else if (minion_dead[i] == 0) {
                            minion_dead[i] = 1;
                            personaje->Exp += 20;
                        }
                    }

                    //NUEVO
                    if (personaje->CurrentRoom == 4) {

                        for (int i = 0; i < 3; i++) {
                            Action::BossMove1(floor->LRoom[personaje->CurrentRoom]->LBoss[i], &prob, &prob_vel, &prob10);
                            V_boss[i].setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[i]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[i]->Y);
                            if (floor->LRoom[personaje->CurrentRoom]->LBoss[i]->Health > 0) {
                                Interaction::FightBoss(personaje, chain, floor->LRoom[personaje->CurrentRoom]->LBoss[i], &m_hit2[i], & flag_hit);
                            }
                            else if (boss_dead[i] == 0) {
                                boss_dead[i] = 1;
                                personaje->Exp += 40;
                            }
                        }
                    }
                    //

                    //NUEVO2
                    if (personaje->CurrentRoom == 8) {

                        Action::BossMove2(floor->LRoom[personaje->CurrentRoom]->LBoss[3],&prob, & prob_vel, &prob10, &typeb);
                        //V_boss[3].setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[3]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Y);
                        if (flag100 == 50) {
                            boss_main.Update(dt, floor->LRoom[personaje->CurrentRoom]->LBoss[3]);
                            boss_main.sprite.setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[3]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Y);
                        }

                        flag100++;
                        if (flag100 == 53) {
                            flag100 = 50;
                        }


                        if (floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health > 0) {
                            Interaction::FightBoss(personaje, chain, floor->LRoom[personaje->CurrentRoom]->LBoss[3], &m_hit3[3], & flag_hit );
                        }
                        else if (boss_dead[3] == 0) {
                            boss_dead[3] = 1;
                            personaje->Exp += 40;
                        }
                    }

                    //



                    for (int i = 0; i < 10; i++) {
                        Interaction::GetHit(personaje, floor->LRoom[personaje->CurrentRoom]->LTrap[i], &hit[i]);
                    }
                    const auto new_tp = std::chrono::steady_clock::now();
                    dt = std::chrono::duration<float>(new_tp - tp).count();
                    tp = new_tp;
                    //
                    //Movimiento del personaje y correspondiente Sprite
                    Action::Move(personaje, dir);
                    VP.SetDirection(dir);
                    VP.Update(dt, personaje);
                    VP.sprite.setPosition(personaje->X, personaje->Y);
                    //
                    //Accion de la cadena
                    chain.setPosition((personaje->X) + 32, (personaje->Y) + 32);
                    Rect_chain = chain.getGlobalBounds();
                    Action::Hit(chain, time, &chainT);
                    //
                    //Cambiar Cuarto
                   // if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom])) {
                    //    Interaction::ChangeRoom(floor, personaje, &state);
                    //}

                    //NUEVO
                    if (personaje->CurrentRoom != 4 && personaje->CurrentRoom != 8) {
                        if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom])) {
                            Interaction::ChangeRoom(floor, personaje, &state);
                        }
                    }
                    else {
                        if (personaje->CurrentRoom == 4) {
                            if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom]) && floor->LRoom[personaje->CurrentRoom]->LBoss[0]->Health < 1 && floor->LRoom[personaje->CurrentRoom]->LBoss[1]->Health < 1 && floor->LRoom[personaje->CurrentRoom]->LBoss[2]->Health < 1) {
                                Interaction::ChangeRoom(floor, personaje, &state);
                            }
                        }
                        else {
                            if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom]) && floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health < 1) {
                                Interaction::ChangeRoom(floor, personaje, &state);
                            }
                        }
                    }


                    //

                    window.clear();
                    
                    for (int i = 0; i < 4; i++) {
                        window.draw(W[i]);
                    }
                    window.draw(Map);
                    for (int o = 0; o < 10; o++) {
                        window.draw(V_trp[o]);

                    }
                    for (int i = 0; i < 5; i++) {
                        if (floor->LRoom[personaje->CurrentRoom]->LItem[i]->Used == 0) {
                            ListItem[i].Draw(window);
                        }
                    }
                    for (int i = 0; i < amount; i++) {
                        if (floor->LRoom[personaje->CurrentRoom]->LMinion[i]->Health > 0) {
                            window.draw(V_minion[i]);
                        }
                    }
                    //NUEVO
                    if (personaje->CurrentRoom == 4) {
                        for (int i = 0; i < 3; i++) {
                            if (floor->LRoom[personaje->CurrentRoom]->LBoss[i]->Health > 0) {
                                window.draw(V_boss[i]);
                            }
                        }
                    }


                    if (personaje->CurrentRoom == 8) {
                        if (floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health > 0) {
                            boss_main.Draw(window);
                        }
                    }

                    //

                    //NUEVO

                    if (personaje->CurrentRoom != 4 && personaje->CurrentRoom != 8) {
                        if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom])) {
                            window.draw(Door);
                        }
                    }
                    else {
                        if (personaje->CurrentRoom == 4) {
                            if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom]) && floor->LRoom[personaje->CurrentRoom]->LBoss[0]->Health < 1 && floor->LRoom[personaje->CurrentRoom]->LBoss[1]->Health < 1 && floor->LRoom[personaje->CurrentRoom]->LBoss[2]->Health < 1) {
                                window.draw(Door);
                            }
                        }
                        else {
                            if (Interaction::RoomCleared(floor->LRoom[personaje->CurrentRoom]) && floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Health < 1) {
                                window.draw(Door);
                            }
                        }
                    }

                    //SSS
                    if (personaje->CurrentRoom == 8) {
                        window.draw(LiveBoss.text);
                    }
                    
                    if (personaje->CurrentRoom == 4) {
                        window.draw(LiveWorm1.text);
                        window.draw(LiveWorm2.text);
                        window.draw(LiveWorm3.text);
                    }

                    //
                    window.draw(Exp.text);
                    window.draw(Live.text);
                    window.draw(Level.text);
                    window.draw(FP.text);
                    window.draw(Pause.text);
                    window.draw(Save.text);
                    window.draw(Menu.text);
                    window.draw(chain);
                    VP.Draw(window);
                    window.display();
                }
                else {
                    if (Btn.Clk_btn(window)) {
                        //clase con ref y agregar clase spritey texture
                        Interaction::InizialiceFloor(floor);
                        personaje->Reset();
                        personaje->X = Width / 2 + 140;
                        personaje->Y = Heigth / 2;
                        state = 5;
                    }
                    window.clear();
                    window.draw(Loss.text);
                    window.draw(Btn.text);
                    window.draw(Menu.text);
                    window.display();
                }
            }

        }
        else if (state == 4) {
            //
            while (operator<=(time2.getElapsedTime(), milliseconds(5)));
            time2.restart();
            //
            const auto new_tp = std::chrono::steady_clock::now();
            dt = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;
            //
            //Movimiento del personaje y correspondiente Sprite
            Action::Move(personaje, dir);
            VP.SetDirection(dir);
            VP.Update(dt, personaje);
            VP.sprite.setPosition(personaje->X, personaje->Y);
            //
            //Accion de la cadena
            chain.setPosition((personaje->X) + 32, (personaje->Y) + 32);
            Rect_chain = chain.getGlobalBounds();
            Action::Hit(chain, time, &chainT);
            //
            if (Action::CompleteTutorial(Tutorial)) {
                Door.setFillColor(Color::Red);
                if (Door.getGlobalBounds().intersects(VP.sprite.getGlobalBounds())) {
                    personaje->X = 140;
                    state = 5;
                }
            }
            
            window.clear();
            M1.Draw(window);
            M2.Draw(window);
            M3.Draw(window);
            M4.Draw(window);
            M5.Draw(window);
            A1.Draw(window);
            A2.Draw(window);
            A3.Draw(window);
            A4.Draw(window);
            A5.Draw(window);
            window.draw(Door);
            window.draw(chain);
            VP.Draw(window);
            window.display();
            
        }
        else if (state == 2 ||state==3) {
            GameView::Word Select("Select Game:", 500, 100);
            GameView::Word Back("Back", 0, 0);
            GameView::Word Game("1 Game", 500, 200);
            GameView::Word Game1("2 Game", 500, 250);
            GameView::Word Game2("3 Game", 500, 300);
            GameView::Word R("Remove", 650, 200);
            GameView::Word R1("Remove", 650, 250);
            GameView::Word R2("Remove", 650, 300);
            if (Back.Clk_btn(window)) {
                state = 0;
            }
            if (Game.Clk_btn(window)) {
                if (state == 2) {
                    DB::LoadGame(0, personaje, floor);
                    state = 5;
                }
                else if (state == 3) {
                    DB::SaveGame(0, personaje, floor);
                    state = 4;
                }
                id = 0;
            }
            if (Game1.Clk_btn(window)) {
                
                if (state == 2) {
                    DB::LoadGame(1, personaje, floor);
                    state = 5;
                }
                else if (state == 3) {
                    DB::SaveGame(1, personaje, floor);
                    state = 4;
                }
                id = 1;
            }
            if (Game2.Clk_btn(window)) {
                
                if (state == 2) {
                    DB::LoadGame(2, personaje, floor);
                    state = 5;
                }

                else if (state == 3) {
                    DB::SaveGame(2, personaje, floor);
                    state = 4;
                }
                id = 2;
            }
            if (R.Clk_btn(window)) {
                DB::Remove(1);
            }
            if (R1.Clk_btn(window)) {
                DB::Remove(2);
            }
            if (R2.Clk_btn(window)) {
                DB::Remove(3);
            }
            if (DB::Length() < 3)Game2.UpdateColor(Color::Blue);
            if (DB::Length() < 2)Game1.UpdateColor(Color::Blue);
            if (DB::Length() < 1)Game.UpdateColor(Color::Blue);
            window.clear();
            window.draw(Select.text);
            window.draw(Back.text);
            window.draw(R.text);
            window.draw(R1.text);
            window.draw(R2.text);
            window.draw(Game.text);
            window.draw(Game1.text);
            window.draw(Game2.text);
            window.display();
        }
        else if (state == 5) {
            if (personaje->CurrentRoom < 3) {
                amount = 5;
            }
            else if (personaje->CurrentRoom <= 5) {
                amount = 7;
            }
            else if (personaje->CurrentRoom < 9) {
                amount = 10;
            }
            for (int u = 0; u < 10; u++) {
                hit[u] = 0;
                V_trp[u].setTexture(Texture_trp);
                V_trp[u].setScale((float)0.1, (float)0.072);
                V_trp[u].setPosition(floor->LRoom[personaje->CurrentRoom]->LTrap[u]->X, floor->LRoom[personaje->CurrentRoom]->LTrap[u]->Y);
            }
            for (int u = 0; u < amount; u++) {
                minion_dead[u] = 0;
                m_hit[u] = 0;
                V_minion[u].setTexture(T_minion);
                V_minion[u].setScale(0.5, 0.5);
                V_minion[u].setPosition(floor->LRoom[personaje->CurrentRoom]->LMinion[u]->X, floor->LRoom[personaje->CurrentRoom]->LMinion[u]->Y);
            }

            //NUEVO

            if (personaje->CurrentRoom == 4) {
                for (int u = 0; u < 3; u++) {
                    boss_dead[u] = 0;
                    m_hit2[u] = 0;
                    V_boss[u].setTexture(T_boss);
                    V_boss[u].setScale(1.5, 1.5);
                    V_boss[u].setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[u]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[u]->Y);
                }
            }

            if (personaje->CurrentRoom == 8) {

                boss_dead[3] = 0;
                m_hit3[3] = 0;
                boss_main.sprite.setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[3]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Y);

                // boss_dead[3] = 0;
                 //m_hit3[3] = 0;
                 //V_boss[3].setTexture(T_boss2);
                 //V_boss[3].setScale(0.5, 0.5);
                 //V_boss[3].setPosition(floor->LRoom[personaje->CurrentRoom]->LBoss[3]->X, floor->LRoom[personaje->CurrentRoom]->LBoss[3]->Y);
            }

            //

            for (int u = 0; u < 5; u++) {
                if (floor->LRoom[personaje->CurrentRoom]->LItem[u]->Type == 0) {
                    ListItem[u] = H;
                    ListItem[u].SetPosition(floor->LRoom[personaje->CurrentRoom]->LItem[u]->X, floor->LRoom[personaje->CurrentRoom]->LItem[u]->Y);
                }
                else if (floor->LRoom[personaje->CurrentRoom]->LItem[u]->Type == 2) {
                    ListItem[u] = D;
                    ListItem[u].SetPosition(floor->LRoom[personaje->CurrentRoom]->LItem[u]->X, floor->LRoom[personaje->CurrentRoom]->LItem[u]->Y);
                }
                else if (floor->LRoom[personaje->CurrentRoom]->LItem[u]->Type == 1) {
                    ListItem[u] = V;
                    ListItem[u].SetPosition(floor->LRoom[personaje->CurrentRoom]->LItem[u]->X, floor->LRoom[personaje->CurrentRoom]->LItem[u]->Y);
                }
            }
            state = 1;
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}
