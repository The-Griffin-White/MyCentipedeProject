#ifndef _SpawnerFactory
#define _SpawnerFactory

#include <stack>

class CentipedeSpawner;
class FleaSpawner;
class ScorpionSpawner;
class SpiderSpawner;
class GameObject;

class SpawnerFactory
{
private:
	static SpawnerFactory *ptrInstance;

	SpawnerFactory() {};
	SpawnerFactory(const SpawnerFactory&) = delete;
	SpawnerFactory& operator=(const SpawnerFactory&) = delete;
	~SpawnerFactory();

	static SpawnerFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpawnerFactory;
		return *ptrInstance;
	}

	std::stack<CentipedeSpawner*> recycledCentipedeSpawners;
	std::stack<FleaSpawner*> recycledFleaSpawners;
	std::stack<ScorpionSpawner*> recycledScorpionSpawners;
	std::stack<SpiderSpawner*> recycledSpiderSpawners;

	CentipedeSpawner* GrabCentipedeSpawner();
	CentipedeSpawner* privCreateCentipedeSpawner();
	CentipedeSpawner* privCreateCentipedeSpawner(bool soloHead, int numSegments);
	FleaSpawner* GrabFleaSpawner();
	FleaSpawner* privCreateFleaSpawner();
	FleaSpawner* privCreateFleaSpawner(int cap);
	ScorpionSpawner* GrabScorpionSpawner();
	ScorpionSpawner* privCreateScorpionSpawner();
	ScorpionSpawner* privCreateScorpionSpawner(int probability, int cap);
	SpiderSpawner* GrabSpiderSpawner();
	SpiderSpawner* privCreateSpiderSpawner();
	SpiderSpawner* privCreateSpiderSpawner(int probability, int cap);

	void privRecycleCentipedeSpawner(GameObject* b);
	void privRecycleFleaSpawner(GameObject* b);
	void privRecycleScorpionSpawner(GameObject* b);
	void privRecycleSpiderSpawner(GameObject* b);

public:
	static CentipedeSpawner* CreateCentipedeSpawner() { return Instance().privCreateCentipedeSpawner(); };
	static CentipedeSpawner* CreateCentipedeSpawner(bool soloHead, int numSegments) 
								{ return Instance().privCreateCentipedeSpawner(soloHead, numSegments); };
	static FleaSpawner* CreateFleaSpawner() { return Instance().privCreateFleaSpawner(); };
	static FleaSpawner* CreateFleaSpawner(int cap) 
							{ return Instance().privCreateFleaSpawner(cap); };
	static ScorpionSpawner* CreateScorpionSpawner() { return Instance().privCreateScorpionSpawner(); };
	static ScorpionSpawner* CreateScorpionSpawner(int probability, int cap) 
							{ return Instance().privCreateScorpionSpawner(probability, cap); };
	static SpiderSpawner* CreateSpiderSpawner() { return Instance().privCreateSpiderSpawner(); };
	static SpiderSpawner* CreateSpiderSpawner(int probability, int cap)
							{ return Instance().privCreateSpiderSpawner(probability, cap); };

	static void RecycleCentipedeSpawner(GameObject* b) { Instance().privRecycleCentipedeSpawner(b); };
	static void RecycleFleaSpawner(GameObject* b) { Instance().privRecycleFleaSpawner(b); };
	static void RecycleScorpionSpawner(GameObject* b) { Instance().privRecycleScorpionSpawner(b); };
	static void RecycleSpiderSpawner(GameObject* b) { Instance().privRecycleSpiderSpawner(b); };


	static void Terminate();
};

#endif