#include "pch.h"
#include <iostream>
#include "GameModel.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace System;
using namespace System::Collections::Generic;
using namespace sf;
GameModel::Player::Player(int id,int health, float x, float y, double attack, double attackSpeed, float speed, int exp, int level, int furypoints)
{

	this->Id = id;
	this->CurrentRoom = 0;
	this->Health = health;
	this->X = x;
	this->Y = y;
	this->Attack = attack;
	this->AttackSpeed = attackSpeed;
	this->Speed = speed;
	this->Exp = exp;
	this->Level = level;
	this->Furypoints = furypoints;
	this->LItem = gcnew List<Item^>();
}

void GameModel::Player::Reset()
{
	this->Health = 100;
	this->X=140;
	this->Y=140;
	this->Attack = 20;
	this->AttackSpeed = 1;
	this->Speed = 1;
	this->Exp = 0;
	this->Level = 1;
	this->Furypoints = 0;
	this->CurrentRoom = 0;
}

GameModel::Trap::Trap(float x, float y,float size,int damage)
{
	this->X = x;
	this->Y = y;
	this->Size = size;
	this->Damage = damage;
}

GameModel::Minion::Minion(int health, float x, float y,float size,int attack, double attackspeed, int speed)
{
	this->Health = health;
	this->X = x;
	this->Y = y;
	this->Size = size;
	this->Attack = attack;
	this->AttackSpeed = attackspeed;
	this->Speed = speed;
}

GameModel::Room::Room()
{

	this->LTrap = gcnew List<Trap^>();
	this->LMinion = gcnew List<Minion^>();
	this->LItem = gcnew List<Item^>();
}

GameModel::Boss::Boss(int health, float x, float y, double attack, double attackspeed, float speed)
{

	this->Health = health;
	this->X = x;
	this->Y = y;
	this->Attack = attack;
	this->AttackSpeed = attackspeed;
	this->Speed = speed;
}

GameModel::Floor::Floor(Boss^lboss)
{
	this->Id = 0;
	this->LRoom = gcnew List<Room^>();
	this->LBoss = lboss;
}

GameModel::Game::Game(int difficulty)
{
	this->Difficulty = difficulty;
	this->LLevel = gcnew List<Floor^>();
}

GameModel::Health::Health(float x, float y, int type)
{
	this->X = x;
	this->Y = y;
	this->Type = type;
}

GameModel::Armor::Armor(float x, float y, int type)
{
	this->X = x;
	this->Y = y;
	this->Type = type;
}

GameModel::Attack::Attack(float x, float y, int type)
{
	this->X = x;
	this->Y = y;
	this->Type = type;
}

GameModel::Velocity::Velocity(float x, float y, int type)
{
	this->X = x;
	this->Y = y;
	this->Type = type;
}

