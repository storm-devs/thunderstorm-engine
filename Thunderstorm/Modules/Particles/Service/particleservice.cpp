#include "particleservice.h"
#include "../Manager/particlemanager.h"
#include "../K2Wrapper/particles.h"


INTERFACE_FUNCTION
CREATE_SERVICE(ParticleService)
CREATE_CLASS(PARTICLES)

ParticleService::ParticleService ()
{
	pDefaultManager = nullptr;
	sysDelete = false;
}

ParticleService::~ParticleService ()
{
	if (pDefaultManager) pDefaultManager->Release();
	sysDelete = true;

	if (CreatedManagers.size() > 0) 
	{
		api->Trace("Unreleased particles managers found !\n");
	}
	for (int n = 0; n < CreatedManagers.size(); n++)
	{
		api->Trace("Manager created in %s, Line %d\n", CreatedManagers[n].FileName, CreatedManagers[n].Line);
		CreatedManagers[n].pManager->Release();
	}

}

IParticleManager* ParticleService::CreateManagerEx (const char* ProjectName, const char* File, int Line)
{
	ParticleManager* pManager = new ParticleManager (this);

	CreatedManager manager;
	manager.pManager = pManager;
	manager.Line = Line;
	manager.FileName = File;
	CreatedManagers.push_back(manager);

	if (ProjectName != nullptr)
	{
		pManager->OpenProject(ProjectName);
	}
	return pManager;
}

void ParticleService::RemoveManagerFromList (IParticleManager* pManager)
{
	if (sysDelete) return;
	for (int n = 0; n < CreatedManagers.size(); n++)
	{
		if (CreatedManagers[n].pManager == pManager)
		{
			//CreatedManagers.ExtractNoShift(n);
			CreatedManagers[n] = CreatedManagers.back();
			CreatedManagers.pop_back();
			return;
		}
	}
}

uint32_t ParticleService::GetManagersCount ()
{
	return CreatedManagers.size();
}

IParticleManager* ParticleService::GetManagerByIndex (uint32_t Index)
{
	return CreatedManagers[Index].pManager;
}

bool ParticleService::Init ()
{
	pDefaultManager = CreateManagerEx (nullptr, __FILE__, __LINE__);
	Assert (pDefaultManager);
	pDefaultManager->OpenDefaultProject();
	return true;
}

IParticleManager* ParticleService::DefManager ()
{
	return pDefaultManager;
}