#ifndef _WaveFactory
#define _WaveFactory

#include <stack>

class Wave;
class WaveLoader;

class WaveFactory
{
private:
	static WaveFactory *ptrInstance;

	WaveFactory() {};
	WaveFactory(const WaveFactory&) = delete;
	WaveFactory& operator=(const WaveFactory&) = delete;
	~WaveFactory();

	static WaveFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new WaveFactory;
		return *ptrInstance;
	}

	std::stack<Wave*> recycledWaves;

	Wave* privCreateWave(WaveLoader* data);
	void privRecycleWave(Wave* b);

public:
	static Wave* CreateWave(WaveLoader* data) { return Instance().privCreateWave(data); };
	static void RecycleWave(Wave* b) { Instance().privRecycleWave(b); };

	static void Terminate();
};

#endif