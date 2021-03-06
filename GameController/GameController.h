

#pragma once
#include <SFML/Graphics.hpp>
//#include "ConnectionParam.h"
#pragma make_public(sf::Clock)
#pragma make_public(sf::Sprite)
using namespace System;
using namespace GameModel;
using namespace System::Collections::Generic;
//using namespace System::Data::SqlClient;
unsigned int Width = 1100, Heigth = 650,Border=(1280-Width)/2;
namespace GameController {
	public ref class Action
	{
	public:
		static void Move(Player^ player, int dir[2]);
		static void Hit(sf::Sprite &chain,sf::Clock &time,int *chainT);
		static void MinionMove(Minion^ minion);
		static void LevelUp(Player^ player);
		static void PickUP(Player^ player, Room^ room);
		static int CompleteTutorial(int t[8]);
		static void BossMove(Boss^ boss);
		static void BossMove1(Boss^ boss, int* prob, int* prob_vel, int* prob10);
		static void BossMove2(Boss^ boss, int* prob, int* prob_vel, int* prob10, int *typeb);
	};
	public ref class Interaction {
	public:
		static void InizialiceRoom(Room^ Room, int Number);
		static int RoomCleared(Room^ room);
		static void InizialiceFloor(Floor^ Level);
		static void ChangeRoom(Floor^ Level,Player^ player,int *state);
		static void UseItem(Player^ player);
		static void GetHit(Player^ player, Trap^ trp,int *hit);
		static void FightMinion(Player^ player, sf::Sprite& chain, Minion^ minion, int* Hit);
		static void FightBoss(Player^ player, sf::Sprite& chain, Boss^ boss, int* hit, int* flag_hit);
	};
	[Serializable]
	public ref class PlayerDB {
	public:
		List <Player^>^ ListDB = gcnew List<Player^>();
		PlayerDB();
	};
	[Serializable]
	public ref class FloorDB {
	public:
		List <Floor^>^ ListDB = gcnew List<Floor^>();
		FloorDB();
	};
	public ref class DB {
	public:
		static PlayerDB^ playerDB = gcnew PlayerDB();
		static FloorDB^ floorDB = gcnew FloorDB();
		//static ConnectionParam^ connParam;
	public:
		static void SavePlayer();
		static void SaveFloor();
		static void SaveGame(int id,Player^ player, Floor^ floor);
		static int Length();
		static void Remove(int id);
		static void LoadPlayer();
		static void LoadFloor();
		static void LoadGame(int id, Player^ player, Floor^ floor);
		//static SqlConnection^ GetConnection();
		//static void Init();
		//static void SavePlayerDB (Player^ player);
		//static Player^ LoadPlayerDB(int id);
		/*#pragma once va en un ConnectionParam.h
using namespace System;

namespace SalesController {
	[Serializable]
	public ref class ConnectionParam
	{
	public:
		property String^ server;
		property String^ database;
		property String^ user;
		property String^ password;
	};

}*/

	};
}
