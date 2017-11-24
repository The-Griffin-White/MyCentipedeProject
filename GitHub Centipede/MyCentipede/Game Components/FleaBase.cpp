#include "FleaBase.h"

#include "Constants.h"
#include "Flea.h"

sf::Vector2f FleaBase::Move(Flea* f) const
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

void FleaBase::DropMushroom(Flea* f) const
{
	ConsoleMsg::WriteLine("DropMushroom command in base");
	if (rand() % Flea_Mushroom_Likelihood == 1)
	{
		ConsoleMsg::WriteLine("should drop a mushroom now");
		f->DropMushrooms();
	}
}

void FleaBase::NextState(Flea* f, int row) const
{
	if (row > Flea_MaxCell)
	{
		f->DeactivateFlea();
	}
}

void FleaBase::FleaHit(Flea* f) const
{
	f->SetFleaHurt();
}