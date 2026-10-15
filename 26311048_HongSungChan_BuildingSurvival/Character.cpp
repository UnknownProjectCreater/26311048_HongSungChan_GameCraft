#include "Character.h"

int Character::Attack(Character* character)
{
    if (character == nullptr)
        return -1;

    character->GetDamage(stat.attackPower);

    return 0;
}