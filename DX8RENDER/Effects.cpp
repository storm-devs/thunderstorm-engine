#include "Effects.h"
#include "../Common_h/vmodule_api.h"
#include <DxErr.h>

#define CHECKD3DERR(expr) ErrorHandler(expr, __FILE__, __LINE__, __func__, #expr)

inline bool Effects::ErrorHandler(HRESULT hr, const char * file, unsigned line, const char * func, const char * expr) const
{
	if (hr != D3D_OK && hr != S_FALSE)
	{
		api->Trace("[%s:%s:%d] %s: %s (%s) (%.*s)", file, func, line, DXGetErrorString(hr), DXGetErrorDescription(hr), expr, debugMsg_.size(), debugMsg_.data());
		return true;
	}

	return false;
}

Effects::Effects(IDirect3DDevice9 *d3dDevice) : device_(d3dDevice), currentTechnique_(nullptr), currentPass_(0u)
{
}

Effects::~Effects()
{
	release();
}

void Effects::setDevice(IDirect3DDevice9 * device)
{
	device_ = device;
}

void Effects::compile(const char * fxPath)
{
	debugMsg_ = fxPath;
	ID3DXEffect *fx;
	ID3DXBuffer *errors = nullptr;
	CHECKD3DERR(D3DXCreateEffectFromFile(device_, fxPath, 
		nullptr, nullptr, D3DXSHADER_OPTIMIZATION_LEVEL3, nullptr, &fx, &errors));

	if (errors) {
		api->Trace(static_cast<const char*>(errors->GetBufferPointer()));
		return;
	}

	effects_.push_back(fx);

	D3DXHANDLE technique = nullptr;
	CHECKD3DERR(fx->FindNextValidTechnique(nullptr, &technique));
	while(technique != nullptr)
	{
		D3DXTECHNIQUE_DESC desc;
		CHECKD3DERR(fx->GetTechniqueDesc(technique, &desc));

		if (techniques_.count(desc.Name) > 0)
		{
			api->Trace("Warning: duplicate technique (%s)", desc.Name);
		}
		else 
		{
			techniques_[desc.Name] = new Technique{ fx, technique, desc };
		}

		CHECKD3DERR(fx->FindNextValidTechnique(technique, &technique));
	}
}

void Effects::release()
{
	for(const auto fx : effects_)
		fx->Release();
	effects_.clear();
	techniques_.clear();
	currentTechnique_ = nullptr;
}

bool Effects::begin(const std::string & techniqueName)
{
	debugMsg_ = techniqueName;
	const auto technique = techniques_.find(techniqueName);
	if (technique == techniques_.end())
	{
		api->Trace("Warning: technique (%s) not found!", techniqueName.c_str());
		return false;
	}

	currentTechnique_ = technique->second;
	auto fx = currentTechnique_->fx;
	CHECKD3DERR(fx->SetTechnique(currentTechnique_->handle));

	UINT passes = 0;
	CHECKD3DERR(fx->Begin(&passes, 0));
	if (passes == 0)
	{
		api->Trace("Warning: empty technique (%s)!", techniqueName.c_str());
		return false;
	}

	currentPass_ = 0;
	CHECKD3DERR(fx->BeginPass(currentPass_++));
	return true;
}

bool Effects::next()
{
	if (currentTechnique_) 
	{
		debugMsg_ = currentTechnique_->desc.Name;
		auto fx = currentTechnique_->fx;
		CHECKD3DERR(fx->EndPass());

		if (currentPass_ < currentTechnique_->desc.Passes)
		{
			CHECKD3DERR(fx->BeginPass(currentPass_++));
			return true;
		}

		CHECKD3DERR(fx->End());
		currentTechnique_ = nullptr;
	}
	return false;
}

ID3DXEffect * Effects::getEffectPointer(const std::string & techniqueName)
{
	const auto technique = techniques_.find(techniqueName);
	return technique != techniques_.end()? technique->second->fx : nullptr;
}
