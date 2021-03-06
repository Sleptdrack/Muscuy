#include "pch.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

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
        if (player->Y > Border) {
            player->Y -= player->Speed;
        }
        dir[1] -= 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        if (player->Y < Heigth-50) {
            player->Y += player->Speed;
        }
        dir[1] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        if (player->X < Border + Width-40) {
            player->X += player->Speed;
        }
        dir[0] += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        if (player->X > Border) {
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
            chain.scale(3.0f, 1.0f);
            time.restart();


            *chainT = 1;

        }
    }
    else if (*chainT == 1) {
        if (time.getElapsedTime() >= mili500) {
            chain.scale(0.3f, 1.0f);
            time.restart();
            *chainT = 2;


        }
    }

    

    //Direccion de la cadena
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.1, (float)0.3);
        chain.setRotation(0);

        chain.rotate(-90);

    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.1, (float)0.3);
        chain.setRotation(0);

        chain.rotate(90);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        *chainT = 0;
        chain.setScale((float)0.1, (float)0.3);
        chain.setRotation(0);

        time.restart();
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        *chainT = 0;
        time.restart();
        chain.setScale((float)0.1, (float)0.3);
        chain.setRotation(0);

        chain.rotate(180);
    }

}

void GameController::Action::MinionMove(Minion^ minion)
{
    if (minion->Type == 0) {
        if (minion->Wall == 0) {
            if (minion->X >= Border) {
                minion->X -= minion->Speed;
            }
            else {
                minion->Wall = 1;
            }
        }
        else {
            if (minion->X < Border + Width - 40) {
                minion->X += minion->Speed;
            }
            else {
                minion->Wall = 0;
            }
        }
        if (minion->Wally == 0) {
            if (minion->Y >= Border) {
                    minion->Y -= minion->Speed;

            }
            else {
                minion->Wally = 1;
            }
        }
        else {
            if (minion->Y < Heigth - 50) {
                    minion->Y += minion->Speed;
            }
            else {
                minion->Wally = 0;
            }
        }
    }
    else if (minion->Type == 1) {
        minion->Y -= 1.5 * sin((minion->Wally) * 3.1416 / 180);
        if (minion->Wally <= 360) {
            minion->Wally += 1;
        }
        else {
            minion->Wally = 0;
        }
        if (minion->Wall == 0) {
            if (minion->X >= Border) {
                minion->X -= minion->Speed;
            }
            else {
                minion->Wall = 1;
            }
        }
        else {
            if (minion->X < Border + Width - 40) {
                minion->X += minion->Speed;
            }
            else {
                minion->Wall = 0;
            }
        }
    }
        
    

}
void GameController::Action::LevelUp(Player^ player)
{
    if (player->Exp >= 100) {
        player->Level += 1;
        player->Health += 20;
        player->Exp -= 100;
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

void GameController::Action::BossMove(Boss^ boss)
{
    if (boss->Wall == 0) {
        if (boss->X >= Border) {
            boss->X = boss->X - boss->Speed * 2;
        }
        else {
            boss->Wall = 1;
        }
    }
    else {
        if (boss->X < Border + Width - 40) {
            boss->X = boss->X + boss->Speed * 2;
        }
        else {
            boss->Wall = 0;
        }
    }
    if (boss->Wally == 0) {
        if (boss->Y >= Border) {
            boss->Y = boss->Y - boss->Speed * 2;
        }
        else {
            boss->Wally = 1;
        }
    }
    else {
        if (boss->Y < Heigth - 50) {
            boss->Y = boss->Y + boss->Speed * 2;
        }
        else {
            boss->Wally = 0;
        }
    }
}

void GameController::Action::BossMove1(Boss^ boss, int* prob, int *prob_vel, int *prob10)
{


    if (*prob == 0 || *prob == 1) {
        if (boss->Wall == 0) {
            if (boss->X >= Border) {
                boss->X = boss->X - boss->Speed   - boss->Speed * *prob_vel;
            }
            else {
                boss->Wall = 1;
            }
        }
        else {
            if (boss->X < Border + Width - 40) {
                boss->X = boss->X + boss->Speed   + boss->Speed * *prob_vel;
            }
            else {
                boss->Wall = 0;
            }
            int prob2 = rand() % 40;
            if (prob2 == 35) {
                *prob = 45;
            }
        }
        int prob3 = rand() % 1000;
        if (prob3 == 50) {
            if (boss->Wall == 1) {
                boss->Wall = 0;
            }
            else {
                boss->Wall = 1;
            }
        }

        if (*prob10 == 0) {
            *prob_vel = 0;
            int prob3 = rand() % 1000;
            if (prob3 == 150  ) {
                *prob10 = 1;
            }
            if (prob3 == 160) {
                *prob10=2;
            }
            if (prob3== 121) {
                *prob10 = 3;
            }
        }
       
        if (*prob10 == 1) {
            *prob_vel = 0.7;
            

            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 2) {
            *prob_vel = 2;

            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 3) {
            *prob_vel = 3;

            int prob4 = rand() % 800;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }

    }

    if (*prob == 45) {
        if (boss->Wally == 0) {
            if (boss->Y >= Border) {
                boss->Y = boss->Y - boss->Speed   - boss->Speed * *prob_vel;
            }
            else {
                boss->Wally = 1;
            }
        }
        else {
            if (boss->Y < Heigth - 50) {
                boss->Y = boss->Y + boss->Speed  + boss->Speed * *prob_vel;
            }
            else {
                boss->Wally = 0;
            }
            int prob2 = rand() % 40;
            if (prob2 == 35) {
                *prob = 0;
            }
        }
        int prob4 = rand() % 900;
        if (prob4 == 50) {
            if (boss->Wally == 1) {
                boss->Wally = 0;
            }
            else {
                boss->Wally = 1;
            }
        }
        
        if (*prob10 == 0) {
            *prob_vel = 0;
            int prob3 = rand() % 1000;
            if (prob3 == 150  ) {
                *prob10 = 1;
            }
            if (prob3 == 160 ) {
                *prob10 = 2;

            }
            if (prob3 == 121) {
                *prob10 = 3;
            }
        }

        if (*prob10 == 1) {
            *prob_vel = 0.7;


            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 2) {
            *prob_vel = 2;

            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 3) {
            *prob_vel = 3;

            int prob4 = rand() % 800;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }

    }
}

void GameController::Action::BossMove2(Boss^ boss, int* prob, int* prob_vel, int* prob10, int *typeb)
{

  if (*typeb == 0) {

    if (*prob == 0 || *prob == 1) {
        if (boss->Wall == 0) {
            if (boss->X >= Border) {
                boss->X = boss->X - boss->Speed - boss->Speed * *prob_vel;
            }
            else {
                boss->Wall = 1;
            }
        }
        else {
            if (boss->X < Border + Width - 40) {
                boss->X = boss->X + boss->Speed + boss->Speed * *prob_vel;
            }
            else {
                boss->Wall = 0;
            }
            int prob2 = rand() % 40;
            if (prob2 == 35) {
                *prob = 45;
            }
        }
        int prob3 = rand() % 1000;
        if (prob3 == 50) {
            if (boss->Wall == 1) {
                boss->Wall = 0;
            }
            else {
                boss->Wall = 1;
            }
        }

        if (*prob10 == 0) {
            *prob_vel = 0;
            int prob3 = rand() % 1000;
            if (prob3 == 150) {
                *prob10 = 1;
            }
            if (prob3 == 160) {
                *prob10 = 2;
            }
            if (prob3 == 121) {
                *prob10 = 3;
            }
        }

        if (*prob10 == 1) {
            *prob_vel = 0.7;


            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 2) {
            *prob_vel = 2;

            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 3) {
            *prob_vel = 3;

            int prob4 = rand() % 800;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }

    }

    if (*prob == 45) {
        if (boss->Wally == 0) {
            if (boss->Y >= Border) {
                boss->Y = boss->Y - boss->Speed - boss->Speed * *prob_vel;
            }
            else {
                boss->Wally = 1;
            }
        }
        else {
            if (boss->Y < Heigth - 50) {
                boss->Y = boss->Y + boss->Speed + boss->Speed * *prob_vel;
            }
            else {
                boss->Wally = 0;
            }
            int prob2 = rand() % 40;
            if (prob2 == 35) {
                *prob = 0;
            }
        }
        int prob4 = rand() % 900;
        if (prob4 == 50) {
            if (boss->Wally == 1) {
                boss->Wally = 0;
            }
            else {
                boss->Wally = 1;
            }
        }

        if (*prob10 == 0) {
            *prob_vel = 0;
            int prob3 = rand() % 1000;
            if (prob3 == 150) {
                *prob10 = 1;
            }
            if (prob3 == 160) {
                *prob10 = 2;

            }
            if (prob3 == 121) {
                *prob10 = 3;
            }
        }

        if (*prob10 == 1) {
            *prob_vel = 0.7;


            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 2) {
            *prob_vel = 2;

            int prob4 = rand() % 4000;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }
        if (*prob10 == 3) {
            *prob_vel = 3;

            int prob4 = rand() % 800;
            if (prob4 == 120) {
                *prob10 = 0;
            }
        }

    }
    int prob6 = rand() % 500;
    if (prob6 == 120) {
        *typeb = 1;
    }
    if (prob6 == 124) {
        *typeb = 2;
    }
  }
  else {
  
   if (*typeb == 1) {
      if (boss->Wall == 0) {
          if (boss->X >= Border) {
              boss->X -= boss->Speed;
          }
          else {
              boss->Wall = 1;
          }
      }
      else {
          if (boss->X < Border + Width - 40) {
              boss->X += boss->Speed;
          }
          else {
              boss->Wall = 0;
          }
      }
      if (boss->Wally == 0) {
          if (boss->Y >= Border) {
              boss->Y -= boss->Speed;

          }
          else {
              boss->Wally = 1;
          }
      }
      else {
          if (boss->Y < Heigth - 50) {
              boss->Y += boss->Speed;
          }
          else {
              boss->Wally = 0;
          }
      }
   }
    if (*typeb == 2) {
      boss->Y -= 1.5 * sin((boss->Wally) * 3.1416 / 180);
      if (boss->Wally <= 360) {
          boss->Wally += 1;
      }
      else {
          boss->Wally = 0;
      }
      if (boss->Wall == 0) {
          if (boss->X >= Border) {
              boss->X -= boss->Speed;
          }
          else {
              boss->Wall = 1;
          }
      }
      else {
          if (boss->X < Border + Width - 40) {
              boss->X += boss->Speed;
          }
          else {
              boss->Wall = 0;
          }
      }
    }


      int prob6 = rand() % 500;
      if (prob6 == 120) {
          *typeb = 0;
      }

   }
}  

void GameController::Interaction::InizialiceRoom(Room^ Room,int Number)
{
    int type, amount,desfase;
    Room->LItem->Clear();
    Room->LTrap->Clear();
    Room->LMinion->Clear();
    Room->LBoss->Clear();
    if (Number < 3) {
        type = 0;
        amount = 5;
    }
    else if (Number <= 5) {
        amount = 7;
        type =1 ;
    }
    else if (Number < 9) {
        amount = 10;
        type = rand() % 2;
    }
    if (type == 1) {
        desfase = 86;
    }
    else {
        desfase = 0;
    }
    for (int i = 0; i < 10; i++) {
        Trap^ trp = gcnew Trap((float)((rand() % 10)) * 110 + 140, (float)((rand() % (7)) * 80) + Border, 40, 20);
        //Trap^ trp = gcnew Trap((float)Border+ rand()%Width, (float)Border+rand() % (Heigth-(Border+50)), 40, 20);
        Room->LTrap->Add(trp);
    }

    for (int i = 0; i < amount; i++) {
        Minion^ minion = gcnew Minion(5, (float)Border + rand() % Width, (float)Border + desfase + rand() % (Heigth - (Border + 50 + desfase)), 40, 20, 0, type);
        Room->LMinion->Add(minion);
    }

    //NUEVOO
    for (int i = 0; i < 3; i++) {
        Boss^ boss = gcnew Boss(50, (float)Border + rand() % Width, (float)Border + desfase + rand() % (Heigth - (Border + 50 + desfase)), 40, 20, 0, 1);
        Room->LBoss->Add(boss);
    }
    Boss^ boss = gcnew Boss(999, (float)Border + rand() % Width, (float)Border + desfase + rand() % (Heigth - (Border + 50 + desfase)), 40, 20, 0, 3);
    Room->LBoss->Add(boss);
    //



    for (int i = 0; i < 5; i++) {
        int p = rand() % 3;
        if (p == 0) {
            Health^ health = gcnew Health((float)Border + rand() % Width, (float)Border + rand() % (Heigth - (Border + 50)), p);
            Room->LItem->Add(health);
        }
        else if (p == 1) {
            Velocity^ velocity = gcnew Velocity((float)Border + rand() % Width, (float)Border + rand() % (Heigth - (Border + 50)), p);
            Room->LItem->Add(velocity);
        }
        else if (p == 2) {
            Attack^ attack = gcnew Attack((float)Border + rand() % Width, (float)Border + rand() % (Heigth - (Border + 50)), p);
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
        GameController::Interaction::InizialiceRoom(room,i);
        Level->LRoom->Add(room);
    }
}
void GameController::Interaction::ChangeRoom(Floor^ Level, Player^ player,int *state)
{
    RectangleShape Door(Vector2f(20, 100));
    Door.setFillColor(Color::Black);
    Door.setPosition(Width+Border-40, 335);
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
                player->Speed += 0.5;
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
void GameController::Interaction::FightMinion(Player^ player, sf::Sprite& chain, Minion^ minion,int *Hit)
{
    if ((player->X < (minion->X + minion->Size) && player->X >(minion->X - minion->Size)) && (player->Y < (minion->Y + minion->Size) && player->Y >(minion->Y - minion->Size))) {
        if (*Hit == 0) {
            *Hit = 1;
            player->Health -= minion->Attack;
            *Hit = 1;
        }

    }
    if (*Hit == 1) {
        if (!((player->X < (minion->X + minion->Size) && player->X >(minion->X - minion->Size)) && (player->Y < (minion->Y + minion->Size) && player->Y >(minion->Y - minion->Size)))) {
            *Hit = 0;
        }
    }
    //if (chain.getGlobalBounds().contains(minion->X, minion->Y) && !((player->X < (minion->X + minion->Size) && player->X >(minion->X - minion->Size)) && (player->Y < (minion->Y + minion->Size) && player->Y >(minion->Y - minion->Size)))) {
      //  minion->Health -= player->Attack;
    //}
    int i = 0;
    do {
        if (chain.getGlobalBounds().contains((minion->X) + i, (minion->Y) + i)) {
            minion->Health -= player->Attack;
        }
        i++;
    } while (i <= minion->Size);
}

void GameController::Interaction::FightBoss(Player^ player, sf::Sprite& chain, Boss^ boss, int* hit, int * flag_hit)
{
    if ((player->X < (boss->X + boss->Size) && player->X >(boss->X - boss->Size)) && (player->Y < (boss->Y + boss->Size) && player->Y >(boss->Y - boss->Size))) {
        if (*hit == 0) {
            player->Health -= boss->Attack;
            *hit = 1;
        }

    }
    if (*hit == 1) {
        if (!((player->X < (boss->X + boss->Size) && player->X >(boss->X - boss->Size)) && (player->Y < (boss->Y + boss->Size) && player->Y >(boss->Y - boss->Size)))) {
            *hit = 0;
        }
    }
    //if (*flag_hit==2) {
      //  if (chain.getGlobalBounds().contains(boss->X, boss->Y) && !((player->X < (boss->X + boss->Size) && player->X >(boss->X - boss->Size)) && (player->Y < (boss->Y + boss->Size) && player->Y >(boss->Y - boss->Size)))) {
       //     boss->Health -= player->Attack;
        //}
        //*flag_hit++;
        //if (*flag_hit == 100) {
         //   *flag_hit = 2;
        //}
    //}
    
    //SSS
    int i = 0;
    *flag_hit = 2;
    do {
        if ((chain.getGlobalBounds().contains((boss->X) + i, (boss->Y) + i)) && *flag_hit == 2 && !((player->X < (boss->X + boss->Size) && player->X >(boss->X - boss->Size)) && (player->Y < (boss->Y + boss->Size) && player->Y >(boss->Y - boss->Size)))) {
            //boss->Health -= player->Attack;
            boss->Health = boss->Health - 0.1- player->Attack/500 ;
            *flag_hit++;
        }
        i++;
    } while (i <= boss->Size);
   
    

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
	String^ strConn = "Server="+connParam->server +
		";Database=" + connParam->database + ";User ID=" + connParam->user + 
		";Password=" + connParam->password;
	conn->ConnectionString = strConn;
	conn->Open();
	return conn;
}


void GameController::DB::SavePlayerDB(Player^ player)
{
	SqlConnection^ conn = GetConnection();
	SqlCommand^ comm;
	String^ strCmd;
	strCmd = "dbo.usp_UpdatePlayer";
	comm = gcnew SqlCommand(strCmd, conn);
	comm->CommandType = System::Data::CommandType::PlayerProcedure;
	comm->Parameters->Add("@id", System::Data::SqlDbType::Int);
	comm->Parameters->Add("@health", System::Data::SqlDbType::Int);
	comm->Parameters->Add("@x", System::Data::SqlDbType::Float);
	comm->Parameters->Add("@y", System::Data::SqlDbType::Float);
	comm->Parameters->Add("@attack", System::Data::SqlDbType::Double);
	comm->Parameters->Add("@attackspeed", System::Data::SqlDbType::Double);
	comm->Parameters->Add("@speed", System::Data::SqlDbType::Float);
	comm->Parameters->Add("@expe", System::Data::SqlDbType::Int);
	comm->Parameters->Add("@llevel", System::Data::SqlDbType::Int);
	comm->Parameters->Add("@furypoints", System::Data::SqlDbType::Int);
	comm->Parameters->Add("@currentroom", System::Data::SqlDbType::Int);
	comm->Prepare();

	comm->Parameters["@id"]->Value = player->Id;
	comm->Parameters["@health"]->Value = player->Health;
	comm->Parameters["@x"]->Value = player->X;
	comm->Parameters["@y"]->Value = player->Y;
	comm->Parameters["@attack"]->Value = player->Attack;
	comm->Parameters["@attackspeed"]->Value = player->AttackSpeed;
	comm->Parameters["@speed"]->Value = player->Speed;
	comm->Parameters["@expe"]->Value = player->Exp;
	comm->Parameters["@llevel"]->Value = player->Level;
	comm->Parameters["@furypoints"]->Value = player->FuryPoints;
	comm->Parameters["@currentroom"]->Value = player->CurrentRoom;

	comm->ExecuteNonQuery();
	conn->Close();
}

void GameController::DB::Init()
{
	XmlSerializer^ reader = gcnew XmlSerializer(ConnectionParam::typeid);
	StreamReader^ file = nullptr;

	try {
		file = gcnew StreamReader("init.xml");
		connParam = (ConnectionParam^)reader->Deserialize(file);
	}
	catch (...) {
	}
	finally {
		if (file != nullptr) file->Close();
	}
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
