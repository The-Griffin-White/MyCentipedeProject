#ifndef _MushroomRegeneratorFactory
#define _MushroomRegeneratorFactory

#include <stack>

class GameObject;
class Mushroom;
class MushroomRegenerator;
class CmdScore;
class CmdAudio;

class MushroomRegeneratorFactory
{
private:
	static MushroomRegeneratorFactory *ptrInstance;

	MushroomRegeneratorFactory();
	MushroomRegeneratorFactory(const MushroomRegeneratorFactory&) = delete;
	MushroomRegeneratorFactory& operator=(const MushroomRegeneratorFactory&) = delete;
	~MushroomRegeneratorFactory();

	static MushroomRegeneratorFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new MushroomRegeneratorFactory;
		return *ptrInstance;
	}

	std::stack<MushroomRegenerator*> recycledMushroomRegenerator;

	CmdScore* pInjuredScore;
	CmdAudio* pInjuredNoise;

	void privCreateMushroomRegenerator(Mushroom* m);
	void privRecycleMushroomRegenerator(GameObject* b);
	void privReportMushroomRegeneratorScore();
	void privReportMushroomHealed();

public:
	static void CreateMushroomRegenerator(Mushroom* m) { Instance().privCreateMushroomRegenerator(m); };
	static void RecycleMushroomRegenerator(GameObject* b) { Instance().privRecycleMushroomRegenerator(b); };
	static void ReportMushroomHealed() { Instance().privReportMushroomHealed(); };

	static void Terminate();

};

#endif