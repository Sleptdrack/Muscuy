
#pragma once
#include <SFML/Graphics.hpp>
#pragma make_public(sf::Clock)
#pragma make_public(sf::Sprite)
using namespace System;
using namespace GameModel;
using namespace System::Collections::Generic;
using namespace System::Data::SqlClient;
unsigned int Width = 960, Heigth = 550;
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
	};
	public ref class Interaction {
	public:
		static void InizialiceRoom(Room^ Room);
		static int RoomCleared(Room^ room);
		static void InizialiceFloor(Floor^ Level);
		static void ChangeRoom(Floor^ Level,Player^ player,int *state);
		static void UseItem(Player^ player);
		static void GetHit(Player^ player, Trap^ trp,int *hit);
		static void FightMinion(Player^ player, sf::Sprite& chain, Minion^ minion,int *hit);
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
	public:
		static void SavePlayer();
		static void SaveFloor();
		static void SaveGame(int id,Player^ player, Floor^ floor);
		static int Length();
		static void Remove(int id);
		static void LoadPlayer();
		static void LoadFloor();
		static void LoadGame(int id, Player^ player, Floor^ floor);
		static SqlConnection^ GetConnection();
		static void SavePlayerDB (Player^ player);
		static Player^ LoadPlayerDB(int id);

	};
}
