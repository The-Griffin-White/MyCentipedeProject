#ifndef _FleaFactory
#define _FleaFactory

#include <stack>
#include "Flea.h"

class MushroomField;
class CmdScore;
class CmdAudio;
class FleaSpawner;

class FleaFactory
{
private:
	static FleaFactory *ptrInstance;

	FleaFactory();
	FleaFactory(const FleaFactory&) = delete;
	FleaFactory& operator=(const FleaFactory&) = delete;
	~FleaFactory();

	static FleaFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FleaFactory;
		return *ptrInstance;
	}

	std::stack<Flea*> recycledFleas;
	std::list<Flea*> activeFleas;

	CmdScore* pDeath;
	CmdAudio* pFalling;
	CmdAudio* pAllFleasDead;


	int currNumFleas;
	int maxNumFleas;
	FleaSpawner* pSpawner;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateFlea();
	void privRecycleFlea(GameObject *b);
	void privReportFleaDeath();
	void privRecallFleas();

public:
	static void CreateFlea() { Instance().privCreateFlea(); };
	static void RecycleFlea(GameObject *b) { Instance().privRecycleFlea(b); };
	static void ReportFleaDeath() { Instance().privReportFleaDeath(); };
	static void RecallFleas() { Instance().privRecallFleas(); };

	static void GetMaxNumFleas(int num);
	static void GetSpawnerPointer(FleaSpawner* p);

	static void Terminate();

};

#endif