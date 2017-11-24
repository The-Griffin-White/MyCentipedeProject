#include "WaveFactory.h"

#include "Wave.h"
#include "WaveLoader.h"

#include "TEAL/CommonElements.h"

WaveFactory* WaveFactory::ptrInstance = nullptr;

WaveFactory::~WaveFactory()
{
	ConsoleMsg::WriteLine("deleting wavefactory");
	while (!recycledWaves.empty())
	{
		delete recycledWaves.top();
		recycledWaves.pop();
	}
}

void WaveFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

Wave* WaveFactory::privCreateWave(WaveLoader* data)
{
	Wave* b;

	if (recycledWaves.empty())
	{
		b = new Wave;
	}

	else
	{
		b = recycledWaves.top();
		recycledWaves.pop();
	}

	b->Initialize(data);

	return b;
}

void WaveFactory::privRecycleWave(Wave* b)
{
	b->KillWave();
	recycledWaves.push(b);
}