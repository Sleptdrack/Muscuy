#pragma once

#include <iostream>
#include <string>
#include<array>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#pragma make_public(sf::Clock)
#pragma make_public(sf::Sprite)
using namespace std;
using namespace System;
using namespace System::Collections::Generic;
const int xy = 2;
namespace GameModel {
	[Serializable]
	public ref class Item {
	public:
		float X;
		float Y;
		int Used=0;
		float Size=40;
		int Type;
	};
	[Serializable]
	public  ref class Health: public Item{
	public:
		Health(float x, float y,int type);
	};
	[Serializable]
	public ref class Armor : public Item {
	public:
		Armor(float x, float y, int type);
	};
	[Serializable]
	public ref class Attack : public Item {
	public:
		Attack(float x, float y, int type);
	};
	[Serializable]
	public ref class Velocity : public Item {
	public:
		Velocity(float x, float y, int type);
	};
	[Serializable]
	public ref class Player{
	public:
		property int Id;
		property int Health;
		property float X;
		property float Y;
		property double Attack;
		double AttackSpeed;
		property float Speed;
		property int Exp;
		property int Level;
		property int Furypoints;
		property int CurrentRoom;
		property List<Item^>^ LItem;
		Player(int id, int health, float x, float y, double attack, double attackspeed, float speed, int exp, int level, int furypoints);
		void Reset();
	};
	[Serializable]
	public ref class Trap {
	public:
		property float X;
		property float Y;
		property float Size;
		property int Damage;
		Trap(float x, float y,float size,int damage);
	};
	[Serializable]
	public ref class Minion{
	public:
		property int Health;
		property float X;
		property float Y;
		property float Size;
		property double Attack;
		property double AttackSpeed;
		property int Speed;
		Minion(int health, float x, float y,float size,int attack, double attackspeed, int speed);
	};
	[Serializable]
	public ref class Room {
	public:
		property List<Trap^>^ LTrap;
		property List<Minion^>^ LMinion;
		property List<Item^>^ LItem;
		Room();
	};
	[Serializable]
	public ref class Boss {
	public:
		property int Health;
		property float X;
		property float Y;
		property double Attack;
		property double AttackSpeed;
		property float Speed;
		Boss(int health, float x, float y, double attack, double attackspeed, float speed);
	};
	[Serializable]
	public ref class Floor {
	public:
		property int Id;
		property List<Room^>^ LRoom;
		property Boss^ LBoss;
		Floor(Boss^lBoss);
	};
	[Serializable]
	public ref class Game {
	public:
		property int Difficulty;
		property List<Floor^>^ LLevel;
		Game(int difficulty);
	};



}