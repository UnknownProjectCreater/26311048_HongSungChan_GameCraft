#pragma once
#include <string>

struct Stat
{
	int hp;
	int attackPower;
	int defensePower;
	int avoidRange;

};

class Character
{
private:
	Stat stat;
public:
	virtual int Attack(Character* character);

	void GetDamage(int amount)		{ stat.hp += amount; };

	Stat GetStat() const			{ return stat; };
};