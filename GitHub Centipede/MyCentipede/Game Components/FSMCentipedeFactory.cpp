#include "FSMCentipedeFactory.h"
#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

#include "ScoreManager.h"
#include "CmdScore.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

#include "MushroomField.h"
#include "Direction.h"

#include "CentipedeSpawner.h"

#include "GameManager.h"

FSMCentipedeFactory* FSMCentipedeFactory::ptrInstance = nullptr;

FSMCentipedeFactory::FSMCentipedeFactory()
{
	pHeadDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeHeadKilled);
	pBodyDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeBodyKilled);

	pWalking = AudioManager::GetAudioCommand(AudioManager::AudioEvents::CentipedeWalking);
	pAllHeadsDead = AudioManager::GetAudioCommand(AudioManager::AudioEvents::StopCentipedeWalking);

	HeadCount = 0;
}

FSMCentipedeHead* FSMCentipedeFactory::NewOrRecycledHead()
{
	FSMCentipedeHead* b;

	if (recycledHeads.empty())
	{
		ConsoleMsg::WriteLine("New Centipede Head"); // For illustration purposes

		b = new FSMCentipedeHead();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleCentipedeHead);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Centipede Head"); // For illustration purposes

		b = recycledHeads.top();
		recycledHeads.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void FSMCentipedeFactory::UpdateHeadCount(FSMCentipedeHead* b)
{
	activeHeads.push_back(b);

	if (HeadCount == 0)
	{
		AudioManager::SendAudioCmd(pWalking);
		ConsoleMsg::WriteLine("starting centipede sound");
	}

	HeadCount++;
}

Direction FSMCentipedeFactory::GiveLeftOrRight()
{
	Direction dir = Left;
	if (rand() % 2 == 1)
	{
		dir = Right;
	}

	return dir;
}

void FSMCentipedeFactory::privCreateCentipede(int row, int col, int numSegments)
{
	FSMCentipedeHead* b = NewOrRecycledHead();

	Direction dir = GiveLeftOrRight();

	b->Initialize(row, col, dir, Down);

	UpdateHeadCount(b);

	FSMCentipede* c;
	FSMCentipedeBody* d;

	c = b;

	for (int i = 0; i < numSegments; i++)
	{
		row--;

		if (recycledBodies.empty())
		{
			ConsoleMsg::WriteLine("New Centipede Body"); // For illustration purposes

			d = new FSMCentipedeBody();

			// Declares that this object should be returned here (rather than deleted) when destroyed
			d->SetExternalManagement(RecycleCentipedeBody);
		}
		else
		{
			ConsoleMsg::WriteLine("Recycled Centipede Body"); // For illustration purposes

			d = recycledBodies.top();
			recycledBodies.pop();	// Remember: top doesn't pop and pop returns void...

									// Tell the object to register itself to the scene
			d->RegisterToCurrentScene();
		}

		d->Initialize(c, row, col);
		c->SetFollower(d);

		activeBodies.push_back(d);

		c = d;
	}
}

void FSMCentipedeFactory::privConvertBodyToHead(FSMCentipedeBody* f)
{
	// Create new CentipedeHead with Pos, row/col, state, follower, itr
	FSMCentipedeHead* b = NewOrRecycledHead();

	b->Initialize(f->GetPos(), f->GetRow(), f->GetNextRow(), f->GetCol(), f->GetNextCol(), f->GetCurrentState(), f->GetFollower(), f->GetIterator());

	UpdateHeadCount(b);

	// Set follower to be led by new CentipedeHead
	if (f->GetFollower())
		f->GetFollower()->SetLeader(b);
}

void FSMCentipedeFactory::privConvertBodyToHead(sf::Vector2f pos, int row, int nextRow, int col, int nextCol,
												const MoveState* state, FSMCentipedeBody* follower, int itr)
{
	// Create new CentipedeHead with Pos, row/col, state, follower, itr
	FSMCentipedeHead* b = NewOrRecycledHead();

	b->Initialize(pos, row, nextRow, col, nextCol, state, follower, itr);

	UpdateHeadCount(b);

	// Set follower to be led by new CentipedeHead
	if (follower)
		follower->SetLeader(b);
}

void FSMCentipedeFactory::privCreateSoloHeadFromPlayerArea()
{
	FSMCentipedeHead* b = NewOrRecycledHead();

	Direction dir = GiveLeftOrRight();

	int row = FieldDimensions + 1;			// Should be offscreen
	int col = FieldDimensions / 2;			// Should be 16

	b->Initialize(row, col, dir, Up);

	UpdateHeadCount(b);
}

void FSMCentipedeFactory::privCreateSoloHeadFromTop()
{
	FSMCentipedeHead* b = NewOrRecycledHead();

	Direction dir = GiveLeftOrRight();

	int row = -1;								// Should be offscreen
	int col = FieldDimensions / 2 - 1;			// Next to where the main Centipede

	b->Initialize(row, col, dir, Down);

	UpdateHeadCount(b);
}

void FSMCentipedeFactory::privRecallCentipedes()
{
	for (std::list<FSMCentipedeBody*>::iterator it = activeBodies.begin(); it != activeBodies.end(); )
	{
		ConsoleMsg::WriteLine("recall centipede body");
		FSMCentipedeBody* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
	for (std::list<FSMCentipedeHead*>::iterator it = activeHeads.begin(); it != activeHeads.end(); )
	{
		ConsoleMsg::WriteLine("recall centipede head");
		FSMCentipedeHead* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
	AudioManager::SendAudioCmd(pAllHeadsDead);
	ConsoleMsg::WriteLine("stopping centipede sound");
}

void FSMCentipedeFactory::GetSpawnerPointer(CentipedeSpawner* p)
{
	Instance().pSpawner = p;
}

void FSMCentipedeFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void FSMCentipedeFactory::privRecycleCentipedeHead(GameObject* b)
{
	HeadCount--;

	if (HeadCount == 0)
	{
		AudioManager::SendAudioCmd(pAllHeadsDead);
		ConsoleMsg::WriteLine("stopping centipede sound");
	}

	activeHeads.remove((FSMCentipedeHead*)b);

	recycledHeads.push((FSMCentipedeHead*)b);

	// For illustration purposes
	ConsoleMsg::WriteLine("Centipede Recycled Stack Size: " + Tools::ToString(recycledHeads.size()));
}

void FSMCentipedeFactory::privRecycleCentipedeBody(GameObject* b)
{
	activeBodies.remove((FSMCentipedeBody*)b);

	recycledBodies.push((FSMCentipedeBody*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Centipede Recycled Stack Size: " + Tools::ToString(recycledBodies.size()));
}

void FSMCentipedeFactory::privReportHeadDeath()
{
//	ConsoleMsg::WriteLine("Centipede Factory: Sending Head death score command");
	ScoreManager::SendScoreCmd(Instance().pHeadDeath);

	if (HeadCount == 1)		// If this is the last centipede head, tell the spawner so we can move up the pipe and go to the next level
	{
		if (pSpawner)
			GameManager::GoToNextLevel();
	}
}
void FSMCentipedeFactory::privReportBodyDeath()
{
//	ConsoleMsg::WriteLine("Centipede Factory: Sending Body death score command");
	ScoreManager::SendScoreCmd(Instance().pBodyDeath);
}

FSMCentipedeFactory::~FSMCentipedeFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Centipede Heads (" + Tools::ToString(recycledHeads.size()) + ")");
	ConsoleMsg::WriteLine("Deleting Recycled Centipede Bodies (" + Tools::ToString(recycledBodies.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledHeads.empty())
	{
		delete recycledHeads.top();
		recycledHeads.pop();
	}
	while (!recycledBodies.empty())
	{
		delete recycledBodies.top();
		recycledBodies.pop();
	}

	delete pHeadDeath;
	delete pBodyDeath;

	delete pWalking;
	delete pAllHeadsDead;
}