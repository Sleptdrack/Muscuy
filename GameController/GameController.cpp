#include "pch.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace GameModel;
using namespace sf;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Xml::Serialization;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;

void GameController::Action::Move(Player &player, int dir[2])
{
    dir[1] = 0;
    dir[0] = 0;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (player.Y > 120) {
            player.Y -= player.Speed;
        }
        dir[1] -= 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        if (player.Y < Alto) {
            player.Y += player.Speed;
        }
        dir[1] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        if (player.X < 140 + Ancho) {
            player.X += player.Speed;
        }
        dir[0] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        if (player.X > 140) {
            player.X -= player.Speed;
        }
        dir[0] -= 1;
    }
}
void GameController::Action::Hit(sf::Sprite &chain, sf::Clock &time, int *chainT)
{
    Time mili500 = milliseconds(500), mili1000 = milliseconds(1000);

    if (*chainT == 0) {

        if (time.getElapsedTime() >= (mili500)) {
            chain.scale(4, 1);
            time.restart();
            *chainT = 1;
        }
    }
    else if (*chainT == 1) {
        if (time.getElapsedTime() >= mili500) {
            chain.scale(0.25, 1);
            time.restart();
            *chainT = 2;

        }
    }
    //Direccion de la cadena
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.05, (float)0.05);
        chain.setRotation(0);
        chain.rotate(-90);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.05, (float)0.05);
        chain.setRotation(0);
        chain.rotate(90);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        *chainT = 0;
        chain.setScale((float)0.05, (float)0.05);
        chain.setRotation(0);
        time.restart();
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.05, (float)0.05);
        chain.setRotation(0);
        chain.rotate(180);
    }
}
void GameController::Action::MinionMove(Minion^ minion,int *wall,int *wally)
{
    if (*wall == 0) {
        if (minion->X >= 140) {
            minion->X-=minion->Speed;
        }
        else {
            *wall = 1;
        }
    }
    else{
        if (minion->X < 140+Ancho) {
            minion->X += minion->Speed;
        }
        else {
            *wall = 0;
        }
    }
    if (*wally == 0) {
        if (minion->Y >= 140) {
            minion->Y -= minion->Speed;
        }
        else {
            *wally = 1;
        }
    }
    else {
        if (minion->Y < Alto) {
            minion->Y += minion->Speed;
        }
        else {
            *wally = 0;
        }
    }

}
void GameController::Action::LevelUp(Player& player)
{
    if (player.Exp == 100) {
        player.Level += 1;
        player.Health += 20;
        player.Exp = 0;
    }
}

void GameController::Action::PickUP(Player& player, Room^ room)
{
    for (int i = 0; i < room->LItem->Count; i++) {
        if ((player.X < (room->LItem[i]->X + room->LItem[i]->Size) && player.X >(room->LItem[i]->X - room->LItem[i]->Size)) && (player.Y < (room->LItem[i]->Y + room->LItem[i]->Size) && player.Y >(room->LItem[i]->Y - room->LItem[i]->Size))) {
            if (!player.LItem->Contains(room->LItem[i])) {
                player.LItem->Add(room->LItem[i]);
            }
        }
    }
}

void GameController::Interaction::InizialiceRoom(Room^ Room)
{
    Room->LTrap->Clear();
    Room->LMinion->Clear();
    for (int i = 0; i < 10; i++) {
        Trap trp((float)(rand() % Ancho + 140), (float)(rand() % (Alto)+80), 40, 20);
        Room->LTrap->Add(trp);
    }
    for (int i = 0; i < 5; i++) {
        Minion^ minion = gcnew Minion(10, (float)(rand() % Ancho + 140), (float)(rand() % (Alto)+80), 40, 20, 0, 1);
        Room->LMinion->Add(minion);
    }
    for (int i = 0; i < 5; i++) {
        int p = rand() % 3;
        if (p == 0) {
            Health^ health = gcnew Health((float)(rand() % Ancho + 140), (float)(rand() % (Alto)+80), p);
            Room->LItem->Add(health);
        }
        else if (p == 1) {
            Velocity^ velocity = gcnew Velocity((float)(rand() % Ancho + 140), (float)(rand() % (Alto)+80), p);
            Room->LItem->Add(velocity);
        }
        else if (p == 2) {
            Attack^ attack = gcnew Attack((float)(rand() % Ancho + 140), (float)(rand() % (Alto)+80), p);
            Room->LItem->Add(attack);
        }
    }
}
int GameController::Interaction::RoomCleared(Room^ room)
{
    int x=0;
    for (int i = 0; i < room->LMinion->Count; i++) {
        if (room->LMinion[i]->Health > 0) {
            return 0;
        }
    }
    return 1;

}
void GameController::Interaction::UseItem(Player& player)
{
    for (int i = 0; i < player.LItem->Count; i++) {
        if (player.LItem[i]->Used == 0) {
            if (player.LItem[i]->Type == 0) {
                player.Health += 20;
                player.LItem[i]->Used = 1;
            }
            else if (player.LItem[i]->Type == 1) {
                player.Speed += 1;
                player.LItem[i]->Used = 1;
            }
            else if (player.LItem[i]->Type == 2) {
                player.Attack += 5;
                player.LItem[i]->Used = 1;
            }
        }
    }
}
void GameController::Interaction::GetHit(Player& player, Trap& trp,int *hit)
{
    if ((player.X < (trp.X + trp.Size) && player.X >(trp.X - trp.Size)) && (player.Y < (trp.Y + trp.Size) && player.Y >(trp.Y - trp.Size))){
        if (*hit == 0) {
            player.Health -= trp.Damage;
            *hit = 1;
        }

    }
    if (*hit == 1) {
        if (!((player.X < (trp.X + trp.Size) && player.X > (trp.X - trp.Size)) && (player.Y < (trp.Y + trp.Size) && player.Y > (trp.Y - trp.Size)))) {
            *hit = 0;
        }
    }
}
void GameController::Interaction::FightMinion(Player& player, sf::Sprite& chain, Minion^ minion,int *hit)
{
    if ((player.X < (minion->X + minion->Size) && player.X >(minion->X - minion->Size)) && (player.Y < (minion->Y + minion->Size) && player.Y >(minion->Y - minion->Size))) {
        if (*hit == 0) {
            player.Health -= minion->Attack;
            *hit = 1;
        }

    }
    if (*hit == 1) {
        if (!((player.X < (minion->X + minion->Size) && player.X >(minion->X - minion->Size)) && (player.Y < (minion->Y + minion->Size) && player.Y >(minion->Y - minion->Size)))) {
            *hit = 0;
        }
    }
    if (chain.getGlobalBounds().contains(minion->X, minion->Y)) {
        minion->Health -= player.Attack;
    }
}

void GameController::DB::SavePlayer()
{
    Stream^ stream = File::Open("players.bin", FileMode::Create);
    BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
    bFormatter->Serialize(stream, playerDB->ListDB);
    stream->Close();
}
void GameController::DB::SaveRoom()
{
    Stream^ stream = File::Open("rooms.bin", FileMode::Create);
    BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
    bFormatter->Serialize(stream, roomDB->ListDB);
    stream->Close();
}
void GameController::DB::SaveGame(int id,Player& player, Room^ room)
{
    if (roomDB->ListDB->Count <= id) {
        playerDB->ListDB->Add(player);
        roomDB->ListDB->Add(room);
    }
    else {
        playerDB->ListDB[id] = player;
        roomDB->ListDB[id] = room;
    }
    SavePlayer();
    SaveRoom();
}
int GameController::DB::Length()
{
    return playerDB->ListDB->Count;
}
void GameController::DB::Remove(int id)
{
    playerDB->ListDB->RemoveAt(id - 1);
    roomDB->ListDB->RemoveAt(id - 1);
}
void GameController::DB::LoadPlayer()
{
    if (File::Exists("players.bin")) {
        Stream^ stream = File::Open("players.bin", FileMode::Open);
        BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
        playerDB->ListDB = (List <Player>^) bFormatter->Deserialize(stream);
        stream->Close();
    }
}
void GameController::DB::LoadRoom()
{
    if (File::Exists("rooms.bin")) {
        Stream^ stream = File::Open("rooms.bin", FileMode::Open);
        BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
        roomDB->ListDB = (List <Room^>^) bFormatter->Deserialize(stream);
        stream->Close();
    }
}

void GameController::DB::LoadGame(int id,Player& player,Room^ room)
{
    LoadRoom();
    LoadPlayer();
    player = playerDB->ListDB[id];
    room = roomDB->ListDB[id];
}

GameController::PlayerDB::PlayerDB()
{
}

GameController::RoomDB::RoomDB()
{
}
