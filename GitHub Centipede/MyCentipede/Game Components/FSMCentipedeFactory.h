#ifndef _FSMCentipedeFactory
#define _FSMCentipedeFactory

#include <stack>
#include "FSMCentipede.h"

class FSMCentipedeHead;
class FSMCentipedeBody;

class CentipedeSpawner;

class MoveState;

class CmdScore;
class CmdAudio;

class FSMCentipedeFactory
{
private:
	static FSMCentipedeFactory *ptrInstance;

	FSMCentipedeFactory();
	FSMCentipedeFactory(const FSMCentipedeFactory&) = delete;
	FSMCentipedeFactory& operator=(const FSMCentipedeFactory&) = delete;
	~FSMCentipedeFactory();

	static FSMCentipedeFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FSMCentipedeFactory;
		return *ptrInstance;
	}

	std::stack<FSMCentipedeHead*> recycledHeads;
	std::stack<FSMCentipedeBody*> recycledBodies;

	std::list<FSMCentipedeHead*> activeHeads;
	std::list<FSMCentipedeBody*> activeBodies;

	CentipedeSpawner* pSpawner;
	int HeadCount;

	CmdScore* pHeadDeath;
	CmdScore* pBodyDeath;
	CmdAudio* pWalking;
	CmdAudio* pAllHeadsDead;

	FSMCentipedeHead* NewOrRecycledHead();
	void UpdateHeadCount(FSMCentipedeHead* b);
	Direction GiveLeftOrRight();

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateCentipede(int row, int col, int numSegments);
	void privConvertBodyToHead(FSMCentipedeBody* f);
	void privConvertBodyToHead(sf::Vector2f pos, int row, int nextRow, int col, int nextCol, 
								const MoveState* state, FSMCentipedeBody* follower, int itr);
	void privCreateSoloHeadFromPlayerArea();
	void privCreateSoloHeadFromTop();

	void privRecycleCentipedeHead(GameObject *b);
	void privRecycleCentipedeBody(GameObject *b);

	void privRecallCentipedes();

	void privReportHeadDeath();
	void privReportBodyDeath();

public:
	static void CreateCentipede(int row, int col, int numSegments = 0) { Instance().privCreateCentipede(row, col, numSegments); };
	static void ConvertBodyToHead(FSMCentipedeBody* f) { Instance().privConvertBodyToHead(f); };
	static void ConvertBodyToHead(sf::Vector2f pos, int row, int nextRow, int col, int nextCol, 
									const MoveState* state, FSMCentipedeBody* follower, int itr) 
		{ Instance().privConvertBodyToHead(pos, row, nextRow, col, nextCol, state, follower, itr); };

	static void CreateSoloHeadFromPlayerArea() { Instance().privCreateSoloHeadFromPlayerArea(); };
	static void CreateSoloHeadFromTop() { Instance().privCreateSoloHeadFromTop(); };

	static void RecycleCentipedeHead(GameObject *b) { Instance().privRecycleCentipedeHead(b); }
	static void RecycleCentipedeBody(GameObject *b) { Instance().privRecycleCentipedeBody(b); }

	static void RecallCentipedes() { Instance().privRecallCentipedes(); };

	static void ReportHeadDeath() { Instance().privReportHeadDeath(); };
	static void ReportBodyDeath() { Instance().privReportBodyDeath(); };

	static void GetSpawnerPointer(CentipedeSpawner* p);

	static void Terminate();

};

#endif