
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
unsigned int ancho = 1280, alto = 720;
unsigned int Ancho = 1000, Alto = 600;
//DESTINO DEL SONIDO

RenderWindow window(VideoMode(ancho, alto), "Muscuy");
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
        void ApplyToSprite(sf::Sprite& s)const
        {
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
        void Update(float dt)
        {
            animations[int(curAnimation)].Update(dt);
            animations[int(curAnimation)].ApplyToSprite(sprite);
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
    };

}
int main()
{
    SoundBuffer Buffer;
    //Sonido a cargar
    Sound Sonido;
    Buffer.loadFromFile("general.wav");
    // SE GUARDARA EL SONIDO EN EL BUFFER LISTO PARA SER USADO
    Sonido.setBuffer(Buffer);
    GameView::Item ListItem[5];
    GameView::ItemArmor A;
    GameView::ItemDamage D;
    GameView::ItemHealth H;
    GameView::ItemVelocity V;
    int state = 0,InPause=0,id=0;
    auto tp = std::chrono::steady_clock::now();
    float dt;
    Clock time2;
    Texture T_Map;
    Sprite Map;
    T_Map.loadFromFile("Imagenes/Mapa.jpeg");
    Map.setTexture(T_Map);
    int flag = 0;
    Vector2i M;
    //texto;
    std::string health = "Health: ",expp="Exp: ",level="Level: ",fp="FuryPoint: ";
    GameView::Word Loss("LOSSER!!!", (float)ancho / 2 - 50, (float)alto / 2);
    Loss.Size(40);
    GameView::Word Btn("Restart", (float)ancho / 2 - 50, (float)alto / 2 + 50);
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
    Title.Size(100);
    ///
    int wall[10],wally[10],pared=0,pared1=0;
    int minion_dead[10];
    int m_hit[10];
    Minion minion(100, 200, 200,50, 10, 0, 1);
    Sprite V_minion[10];
    Texture T_minion;
    T_minion.loadFromFile("Imagenes/Personaje2.png");
    //Variables para el ataque
    int dir[2];
    Clock time;
    int chainT=2;
    //Creacion y ubicacion de una trampa
    int hit[10];
    Room^ room = gcnew Room(5);
    Sprite V_trp[10];
    Texture Texture_trp;
    Texture_trp.loadFromFile("Imagenes/spike.png");
    //Actualizacion de variables y visualizacion de trampas
    //
    Player personaje(100, 140, 140, 20, 1, 1, 0, 1, 1);
    GameView::Character VP({ 140.f,140.f });
    Sprite chain;
    Texture tchain;
    FloatRect Rect_chain;
    tchain.loadFromFile("Imagenes/chain.png");
    chain.setTexture(tchain);
    chain.setScale((float)0.05, (float)0.05);
    //
    while (window.isOpen())
    {
        Sonido.play();
        if (Save.Clk_btn(window)) {
            DB::SaveGame(id, personaje, room);
        }
        if (Menu.Clk_btn(window)) {
            state = 0;
        }
        if (state == 0) {
            if (StartNew.Clk_btn(window)) {
                state = 3;
                Interaction::InizialiceRoom(room);
                //Actualizacion de variables y visualizacion de Minions
                for (int u = 0; u < 5; u++) {
                    minion_dead[u] = 0;
                    wall[u] = 0;
                    wally[u] = 0;
                    m_hit[u] = 0;
                    V_minion[u].setTexture(T_minion);
                    V_minion[u].setScale(0.5, 0.5);
                }
                for (int u = 0; u < 5; u++) {
                    if (room->LItem[u]->Type == 0) {
                        ListItem[u] = H;
                        ListItem[u].SetPosition(room->LItem[u]->X, room->LItem[u]->Y);
                    }
                    else if (room->LItem[u]->Type == 2) {
                        ListItem[u] = D;
                        ListItem[u].SetPosition(room->LItem[u]->X, room->LItem[u]->Y);
                    }
                    else if (room->LItem[u]->Type == 1) {
                        ListItem[u] = V;
                        ListItem[u].SetPosition(room->LItem[u]->X, room->LItem[u]->Y);
                    }
                }
                personaje.Reset();
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
            for (int u = 0; u < 10; u++) {
                hit[u] = 0;
                V_trp[u].setTexture(Texture_trp);
                V_trp[u].setScale((float)0.1, (float)0.072);
                V_trp[u].setPosition(room->LTrap[u].X, room->LTrap[u].Y);
            }
            if (InPause==1) {
                window.clear();
                window.draw(Map);
                for (int o = 0; o < 10; o++) {
                    window.draw(V_trp[o]);

                }
                for (int i = 0; i < 5; i++) {
                    if (room->LMinion[i]->Health > 0) {
                        window.draw(V_minion[i]);
                    }
                }
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
                if (personaje.Health > 0) {
                    while (operator<=(time2.getElapsedTime(), milliseconds(5)));
                    time2.restart();
                    //Visualizacion de vida
                    Live.UpdateString(health.replace(8, 3, (std::to_string(personaje.Health))));
                    Exp.UpdateString(expp.replace(5, 3, std::to_string(personaje.Exp)));
                    Level.UpdateString(level.replace(7, 3, std::to_string(personaje.Level)));
                    FP.UpdateString(fp.replace(11, 3, std::to_string(DB::Length())));
                    //Coleccion de Objetos
                    Action::PickUP(personaje, room);
                    Interaction::UseItem(personaje);
                    //Colision con trampas:
                    Action::LevelUp(personaje);
                    for (int i = 0; i < 5; i++) {
                        Action::MinionMove(room->LMinion[i], &wall[i], &wally[i]);
                        V_minion[i].setPosition(room->LMinion[i]->X, room->LMinion[i]->Y);
                        if (room->LMinion[i]->Health > 0) {
                            Interaction::FightMinion(personaje, chain, room->LMinion[i], &m_hit[i]);
                        }
                        else if (minion_dead[i] == 0) {
                            minion_dead[i] = 1;
                            personaje.Exp += 20;
                        }
                    }
                    for (int i = 0; i < 10; i++) {
                        Interaction::GetHit(personaje, room->LTrap[i], &hit[i]);
                    }
                    const auto new_tp = std::chrono::steady_clock::now();
                    dt = std::chrono::duration<float>(new_tp - tp).count();
                    tp = new_tp;
                    //
                    //Movimiento del personaje y correspondiente Sprite
                    Action::Move(personaje, dir);
                    VP.SetDirection(dir);
                    VP.Update(dt);
                    VP.sprite.setPosition(personaje.X, personaje.Y);
                    //
                    //Accion de la cadena
                    chain.setPosition(personaje.X, personaje.Y);
                    Rect_chain = chain.getGlobalBounds();
                    Action::Hit(chain, time, &chainT);
                    //
                    window.clear();
                    window.draw(Map);
                    for (int o = 0; o < 10; o++) {
                        window.draw(V_trp[o]);

                    }
                    for (int i = 0; i < 5; i++) {
                        if (room->LMinion[i]->Health > 0) {
                            window.draw(V_minion[i]);
                        }
                    }
                    for (int i = 0; i < 5; i++) {
                        if (room->LItem[i]->Used == 0) {
                            ListItem[i].Draw(window);
                        }
                    }
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
                        Interaction::InizialiceRoom(room);
                        for (int u = 0; u < 10; u++) {
                            hit[u] = 0;
                            V_trp[u].setTexture(Texture_trp);
                            V_trp[u].setScale((float)0.1, (float)0.072);
                            V_trp[u].setPosition(room->LTrap[u].X, room->LTrap[u].Y);
                        }
                        //Actualizacion de variables y visualizacion de Minions
                        for (int u = 0; u < 5; u++) {
                            minion_dead[u] = 0;
                            wall[u] = 0;
                            wally[u] = 0;
                            m_hit[u] = 0;
                            V_minion[u].setTexture(T_minion);
                            V_minion[u].setScale(0.5, 0.5);
                        }
                        //clase con ref y agregar clase spritey texture
                        personaje.Reset();
                    }
                    window.clear();
                    window.draw(Loss.text);
                    window.draw(Btn.text);
                    window.draw(Menu.text);
                    window.display();
                }
            }

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
                if (state == 2)DB::LoadGame(0, personaje, room);
                else if (state == 3)DB::SaveGame(0, personaje, room);
                state = 1;
                id = 0;
            }
            if (Game1.Clk_btn(window)) {
                
                if (state == 2)DB::LoadGame(1, personaje, room);
                else if (state == 3)DB::SaveGame(1, personaje, room);
                state = 1;
                id = 1;
            }
            if (Game2.Clk_btn(window)) {
                
                if (state == 2)DB::LoadGame(2, personaje, room);
                else if (state == 3)DB::SaveGame(2, personaje, room);
                state = 1;
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

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}
