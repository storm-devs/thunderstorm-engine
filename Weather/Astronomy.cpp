#include "Astronomy.h"

VDX9RENDER * Astronomy::pRS = nullptr;
VGEOMETRY * Astronomy::pGS = nullptr;

Astronomy::Astronomy()
{
	dTimeScale = 0.0;
	dHour = 0.0f;
}

Astronomy::~Astronomy()
{
}

bool Astronomy::Init()
{
	SetDevice();

	return true;
}

void Astronomy::SetDevice()
{
	pRS = (VDX9RENDER *)api->CreateService("dx9render"); Assert(pRS);
	pGS = (VGEOMETRY *)api->CreateService("geometry");
}

void Astronomy::Realize(dword Delta_Time)
{
	double dDeltaTime = double(Delta_Time) * 0.001;
	dHour += dDeltaTime / (60.0 * 60.0);

	Stars.Realize(dDeltaTime, dHour);
	Planets.Realize(dDeltaTime, dHour);
}

dword Astronomy::AttributeChanged(ATTRIBUTES * pA)
{
	if (*pA == "isDone")
	{ 
		Stars.Init(AttributesPointer);
		Planets.Init(AttributesPointer);
		return 0;
	}
	
	if (*pA == "TimeScale")
	{
		dTimeScale = double(pA->GetAttributeAsFloat());
		return 0;
	}

	if (*pA == "TimeUpdate")
	{
		Planets.TimeUpdate(AttributesPointer);
		Stars.TimeUpdate(AttributesPointer);
		return 0;
	}

	return 0;
}
