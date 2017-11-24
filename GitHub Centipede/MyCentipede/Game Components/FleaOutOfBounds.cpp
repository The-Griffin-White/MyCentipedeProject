#include "FleaOutOfBounds.h"

#include "Constants.h"
#include "Flea.h"

sf::Vector2f FleaOutOfBounds::Move(Flea* f) const
{
	f->Iterate();
	if (f->GetIterator() == Flea_Base_Cell_Turns)
	{
		DropMushroom(f);
		f->NextRow();
		NextState(f, f->GetRow());
		f->ResetIterator();
	}
	return sf::Vector2f(0.0f, Flea_Base_Speed);
}

void FleaOutOfBounds::NextState(Flea* f, int row) const
{
	if (row <= Flea_MaxCell && row >= Flea_MinCell)
	{
		f->ActivateFlea();
	}
	if (row > Flea_Offscreen)
	{
//		ConsoleMsg::WriteLine("Destroying flea that is offscreen");
		f->MarkForDestroy();
	}
}

void FleaOutOfBounds::FleaHit(Flea* f) const
{
	f->SetFleaHurt();
}