
#pragma once
#include <SFML/Graphics.hpp>
#pragma make_public(sf::Clock)
#pragma make_public(sf::Sprite)
using namespace System;
using namespace GameModel;
using namespace System::Collections::Generic;
unsigned int Ancho = 1000, Alto = 600;
namespace GameController {
	public ref class Action
	{
	public:
		static void Move(Player &player, int dir[2]);
		static void Hit(sf::Sprite &chain,sf::Clock &time,int *chainT);
		static void MinionMove(Minion^ minion,int *wall, int* wally);
		static void LevelUp(Player& player);
		static void PickUP(Player& player, Room^ room);
	};
	public ref class Interaction {
	public:
		static void InizialiceRoom(Room^ Room);
		static int RoomCleared(Room^ room);
		static void UseItem(Player& player);
		static void GetHit(Player& player, Trap& trp,int *hit);
		static void FightMinion(Player& player, sf::Sprite& chain, Minion^ minion,int *hit);
	};
	[Serializable]
	public ref class PlayerDB {
	public:
		List <Player>^ ListDB = gcnew List<Player>();
		PlayerDB();
	};
	[Serializable]
	public ref class RoomDB {
	public:
		List <Room^>^ ListDB = gcnew List<Room^>();
		RoomDB();
	};
	public ref class DB {
	public:
		static PlayerDB^ playerDB = gcnew PlayerDB();
		static RoomDB^ roomDB = gcnew RoomDB();
	public:
		static void SavePlayer();
		static void SaveRoom();
		static void SaveGame(int id,Player& player, Room^ room);
		static int Length();
		static void Remove(int id);
		static void LoadPlayer();
		static void LoadRoom();
		static void LoadGame(int id, Player& player, Room^ room);
	};
}
