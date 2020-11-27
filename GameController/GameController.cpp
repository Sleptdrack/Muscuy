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

void GameController::Action::Move(Player^ player, int dir[2])
{
    dir[1] = 0;
    dir[0] = 0;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (player->Y > 120) {
            player->Y -= player->Speed;
        }
        dir[1] -= 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        if (player->Y < Heigth) {
            player->Y += player->Speed;
        }
        dir[1] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        if (player->X < 140 + Width) {
            player->X += player->Speed;
        }
        dir[0] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        if (player->X > 140) {
            player->X -= player->Speed;
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
void GameController::Action::MinionMove(Minion^ minion)
{
    if (minion->Wall == 0) {
        if (minion->X >= 140) {
            minion->X-=minion->Speed;
        }
        else {
            minion->Wall = 1;
        }
    }
    else{
        if (minion->X < 140+Width) {
            minion->X += minion->Speed;
        }
        else {
            minion->Wall = 0;
        }
    }
    if (minion->Wally == 0) {
        if (minion->Y >= 140) {
            minion->Y -= minion->Speed;
        }
        else {
            minion->Wally = 1;
        }
    }
    else {
        if (minion->Y < Heigth) {
            minion->Y += minion->Speed;
        }
        else {
            minion->Wally = 0;
        }
    }

}
void GameController::Action::LevelUp(Player^ player)
{
    if (player->Exp == 100) {
        player->Level += 1;
        player->Health += 20;
        player->Exp = 0;
    }
}

void GameController::Action::PickUP(Player^ player, Room^ room)
{
    for (int i = 0; i < room->LItem->Count; i++) {
        if ((player->X < (room->LItem[i]->X + room->LItem[i]->Size) && player->X >(room->LItem[i]->X - room->LItem[i]->Size)) && (player->Y < (room->LItem[i]->Y + room->LItem[i]->Size) && player->Y >(room->LItem[i]->Y - room->LItem[i]->Size))) {
            if (room->LItem[i]->Used==0) {
                int p = room->LItem[i]->Type;
                if (p == 0) {
                    Health^ health = gcnew Health(room->LItem[i]->X, room->LItem[i]->Y, p);
                    player->LItem->Add(health);
                }
                else if (p == 1) {
                    Velocity^ velocity = gcnew Velocity(room->LItem[i]->X, room->LItem[i]->Y, p);
                    player->LItem->Add(velocity);
                }
                else if (p == 2) {
                    Attack^ attack = gcnew Attack(room->LItem[i]->X, room->LItem[i]->Y, p);
                    player->LItem->Add(attack);
                }
                room->LItem[i]->Used = 1;
            }
        }
    }
}

int GameController::Action::CompleteTutorial(int t[8])
{
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        t[0] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        t[1] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        t[2] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        t[3] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        t[4] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        t[5] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        t[6] = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        t[7] = 0;
    }
    for (int i = 0; i < 8; i++) {
        if (t[i] == 1) {
            return 0;
        }
    }
    return 1;
}

void GameController::Interaction::InizialiceRoom(Room^ Room)
{
    Room->LItem->Clear();
    Room->LTrap->Clear();
    Room->LMinion->Clear();
    for (int i = 0; i < 10; i++) {
        Trap^ trp = gcnew Trap((float)(rand() % Width + 140), (float)((rand() % (Heigth-120))+120), 40, 20);
        Room->LTrap->Add(trp);
    }
    for (int i = 0; i < 5; i++) {
        Minion^ minion = gcnew Minion(10, (float)(rand() % Width + 140), (float)((rand() % (Heigth - 120)) + 120), 40, 20, 0, 1);
        Room->LMinion->Add(minion);
    }
    for (int i = 0; i < 5; i++) {
        int p = rand() % 3;
        if (p == 0) {
            Health^ health = gcnew Health((float)(rand() % Width + 140), (float)((rand() % (Heigth - 120)) + 120), p);
            Room->LItem->Add(health);
        }
        else if (p == 1) {
            Velocity^ velocity = gcnew Velocity((float)(rand() % Width + 140), (float)((rand() % (Heigth - 120)) + 120), p);
            Room->LItem->Add(velocity);
        }
        else if (p == 2) {
            Attack^ attack = gcnew Attack((float)(rand() % Width + 140), (float)((rand() % (Heigth - 120)) + 120), p);
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
void GameController::Interaction::InizialiceFloor(Floor^ Level)
{

    Level->LRoom->Clear();
    for (int i = 0; i < 9; i++) {
        Room^ room = gcnew Room(i);
        GameController::Interaction::InizialiceRoom(room);
        Level->LRoom->Add(room);
    }
}

void GameController::Interaction::ChangeRoom(Floor^ Level, Player^ player,int *state)
{
    RectangleShape Door(Vector2f(20, 100));
    Door.setFillColor(Color::Black);
    Door.setPosition(1100, 335);
    if (RoomCleared(Level->LRoom[player->CurrentRoom])) {
        if (player->CurrentRoom < 9) {
            Door.setFillColor(Color::Red);
            if (Door.getGlobalBounds().contains(player->X, player->Y)) {
                player->X = 140;
                player->CurrentRoom += 1;
                *state = 5;
                DB::SaveGame(player->Id, player, Level);
                DB::LoadGame(player->Id, player, Level);
            }
        }
    }
}

void GameController::Interaction::UseItem(Player^ player)
{
    for (int i = 0; i < player->LItem->Count; i++) {
        if (player->LItem[i]->Used == 0) {
            if (player->LItem[i]->Type == 0) {
                player->Health += 20;
                player->LItem[i]->Used = 1;
            }
            else if (player->LItem[i]->Type == 1) {
                player->Speed += 1;
                player->LItem[i]->Used = 1;
            }
            else if (player->LItem[i]->Type == 2) {
                player->Attack += 5;
                player->LItem[i]->Used = 1;
            }
        }
    }
}
void GameController::Interaction::GetHit(Player^ player, Trap^ trp,int *hit)
{
    if ((player->X < (trp->X + trp->Size) && player->X >(trp->X - trp->Size)) && (player->Y < (trp->Y + trp->Size) && player->Y >(trp->Y - trp->Size))){
        if (*hit == 0) {
            player->Health -= trp->Damage;
            *hit = 1;
        }

    }
    if (*hit == 1) {
        if (!((player->X < (trp->X + trp->Size) && player->X > (trp->X - trp->Size)) && (player->Y < (trp->Y + trp->Size) && player->Y > (trp->Y - trp->Size)))) {
            *hit = 0;
        }
    }
}
void GameController::Interaction::FightMinion(Player^ player, sf::Sprite& chain, Minion^ minion,int *hit)
{
    if ((player->X < (minion->X + minion->Size) && player->X >(minion->X - minion->Size)) && (player->Y < (minion->Y + minion->Size) && player->Y >(minion->Y - minion->Size))) {
        if (*hit == 0) {
            player->Health -= minion->Attack;
            *hit = 1;
        }

    }
    if (*hit == 1) {
        if (!((player->X < (minion->X + minion->Size) && player->X >(minion->X - minion->Size)) && (player->Y < (minion->Y + minion->Size) && player->Y >(minion->Y - minion->Size)))) {
            *hit = 0;
        }
    }
    if (chain.getGlobalBounds().contains(minion->X, minion->Y)) {
        minion->Health -= player->Attack;
    }
}

void GameController::DB::SavePlayer()
{
    Stream^ stream = File::Open("players.bin", FileMode::Create);
    BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
    bFormatter->Serialize(stream, playerDB->ListDB);
    stream->Close();
}
void GameController::DB::SaveFloor()
{
    Stream^ stream = File::Open("floor.bin", FileMode::Create);
    BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
    bFormatter->Serialize(stream, floorDB->ListDB);
    stream->Close();
}
void GameController::DB::SaveGame(int id,Player^ player, Floor^ floor)
{
    //SaveGameDB(player);
    //al igual que el loadplayerdb se usara para cuando se requiera base de datos
    player->Id = id;
    floor->Id = id;
    if (floorDB->ListDB->Count <= id) {
        playerDB->ListDB->Add(player);
        floorDB->ListDB->Add(floor);
    }
    else {
        playerDB->ListDB[id] = player;
        floorDB->ListDB[id] = floor;
    }
    SavePlayer();
    SaveFloor();
}
int GameController::DB::Length()
{
    return playerDB->ListDB->Count;
}
void GameController::DB::Remove(int id)
{
    playerDB->ListDB->RemoveAt(id);
    floorDB->ListDB->RemoveAt(id);
}
void GameController::DB::LoadPlayer()
{
    if (File::Exists("players.bin")) {
        Stream^ stream = File::Open("players.bin", FileMode::Open);
        BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
        playerDB->ListDB = (List <Player^>^) bFormatter->Deserialize(stream);
        stream->Close();
    }
}
void GameController::DB::LoadFloor()
{
    if (File::Exists("floor.bin")) {
        Stream^ stream = File::Open("floor.bin", FileMode::Open);
        BinaryFormatter^ bFormatter = gcnew BinaryFormatter();
        floorDB->ListDB = (List <Floor^>^) bFormatter->Deserialize(stream);
        stream->Close();
    }
}

void GameController::DB::LoadGame(int id,Player^ player,Floor^ room)
{
    //player=LoadPlayerDB(id);
    //para la utilizacion de la base de datos
    LoadFloor();
    LoadPlayer();
    for (int i = 0; i < playerDB->ListDB->Count; i++) {
        if (playerDB->ListDB[i]->Id == id) {
            player = playerDB->ListDB[i];
        }
        if (floorDB->ListDB[i]->Id == id) {
            room = floorDB->ListDB[i];
        }
    }
    
}

/*SqlConnection^ GameController::DB::GetConnection()
{
	SqlConnection^ conn = gcnew SqlConnection();
	String^ strConn = "Server=muscuy.cjvxsxw5p3iw.us-east-1.rds.amazonaws.com;" +
		"Database=muscuy;User ID=admin;Password=lpooadmin";
	conn->ConnectionString = strConn;
	conn->Open();
	return conn;
}

void GameController::DB::SavePlayerDB(Player^ player)
{
	SqlConnection^ conn = GetConnection();
	SqlCommand^ comm = gcnew SqlCommand();
	comm->Connection = conn;
	comm->CommandText = "Update Player set id ='"+player ->Id+"',health= '"+player ->Health+"',x='"+player ->X+"',y='"+player ->Y+"',attack='"+player ->Attack+"',attackspeed='"+player ->AttackSpeed+"',speed='"+player ->Speed+"',expe='"+player ->Exp+"',llevel='"+player ->Level+"',furypoints='"+player ->Furypoints+"',currentroom='"+player ->CurrentRoom+"'");
	comm->ExecuteNonQuery();
}

Player^ GameController::DB::LoadPlayerDB(int id) {
	Player^ player = nullptr;
	SqlConnection^ conn = GetConnection();
	SqlCommand^ comm = gcnew SqlCommand();
	comm->Connection = conn;
	comm->CommandText = "SELECT * FROM Player WHERE id='" + id + "'";

	SqlDataReader^ dr = comm->ExecuteReader();

	if (dr->Read()) {
		player = gcnew Player();
		player ->Id = (int)dr["id"];
		player ->Health = (int) (dr["health"]);		
		player ->X = safe_cast<float>(dr["x"]);
		player ->Y = safe_cast<float>(dr["y"]);
		player ->Attack = safe_cast<double>(dr["attack"]);
		player ->AttackSpeed = safe_cast<double>(dr["attackspeed"]);
		player ->Speed = safe_cast<float>(dr["speed"]);		
		player ->Exp = (int)(dr["expe"]);
		player ->Level = (int)(dr["llevel"]);
		player ->Furypoints = (int)(dr["furypoints"]);
		player ->CurrentRoom = (int)(dr["currentroom"]);
	}

	return player;
}
*/

GameController::PlayerDB::PlayerDB()
{
}

GameController::FloorDB::FloorDB()
{
}
