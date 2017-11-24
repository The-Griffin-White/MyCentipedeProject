#include "FleaHurt.h"

#include "Constants.h"
#include "Flea.h"

sf::Vector2f FleaHurt::Move(Flea* f) const
{
	f->Iterate();
	if (f->GetIterator() == Flea_Hurt_Cell_Turns)
	{
		DropMushroom(f);
		f->NextRow();
		NextState(f, f->GetRow());
		f->ResetIterator();
	}
	return sf::Vector2f(0.0f, Flea_Hurt_Speed);
}

void FleaHurt::NextState(Flea* f, int row) const
{
	if (row > Flea_MaxCell)
	{
		f->DeactivateFlea();
	}
}

void FleaHurt::FleaHit(Flea* f) const
{
	f->KillFlea();
}