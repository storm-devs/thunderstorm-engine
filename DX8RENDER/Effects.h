#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>


class Effects final
{
private:
	struct Technique
	{
		ID3DXEffect *fx;
		D3DXHANDLE handle;
		D3DXTECHNIQUE_DESC desc;
	};
	
	IDirect3DDevice9 *device_;

	std::vector<ID3DXEffect*> effects_;
	std::unordered_map<std::string, Technique*> techniques_;

	Technique *currentTechnique_;
	unsigned int currentPass_;

	inline bool Effects::ErrorHandler(HRESULT hr, const char * file, unsigned line, const char * func, const char * expr);

public:
	Effects(Effects &) = delete;
	Effects(Effects &&) = delete;
	Effects& operator=(Effects &) = delete;
	Effects& operator=(Effects &&) = delete;

	explicit Effects(IDirect3DDevice9 *d3dDevice = nullptr);
	~Effects();
	// Set device
	void setDevice(IDirect3DDevice9 * device);
	// Compile effect by path
	void compile(const char *fxPath);
	// Release all effects
	void release();
	// Begin technique
	bool begin(const std::string & techniqueName);
	// Execute next technique
	bool next();
};