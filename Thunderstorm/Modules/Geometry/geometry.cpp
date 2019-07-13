#include "geometry_R.h"
#include "geos.h"

INTERFACE_FUNCTION
CREATE_SERVICE(GEOMETRY)

IDirect3DVertexDeclaration9 * GEOM_SERVICE_R::vertexDecl_ = nullptr;

char technique[256] = "";
char RenderServiceName[] = "dx9render";
GEOM_SERVICE_R GSR;
char texturePath[256];

const long SHIFT_VALUE = 999999999;
#define AVB_MAX 1024
VGEOMETRY::ANIMATION_VB avb[AVB_MAX];	//!!! temporary

GEOMETRY::GEOMETRY()
{
	strcpy_s(texturePath, "");
}

const char *GEOMETRY::GetTexturePath()
{
	return &texturePath[0];
}
void GEOMETRY::SetTexturePath(const char *path)
{
	strcpy_s(texturePath, path);
}

//=================================================================================================
// Block 1
//=================================================================================================
void GEOMETRY::SetTechnique(const char *name)
{
	strcpy_s(technique, name);
}

GEOMETRY::ANIMATION_VB GEOMETRY::GetAnimationVBDesc(long vb)
{
	return avb[vb-SHIFT_VALUE];
}

VERTEX_TRANSFORM transform_func = nullptr;
void GEOMETRY::SetVBConvertFunc(VERTEX_TRANSFORM _transform_func)
{
	transform_func = _transform_func;
}

static bool geoLog = false;
bool GEOMETRY::Init()
{
	RenderService = (VDX9RENDER *)api->CreateService(RenderServiceName);
	if(!RenderService)
	{
		api->Trace("No service: %s",RenderServiceName);
	}
	GSR.SetRenderService(RenderService);

	INIFILE * ini;
	ini = fio->OpenIniFile(api->EngineIniFileName());
	if(ini)
	{
		geoLog = ini->GetLong(nullptr,"geometry_log",0)==1;
		delete ini;
	}

	return true;
}

void GEOMETRY::SetCausticMode(bool bSet)
{
	GSR.SetCausticMode(bSet);
}


bool GEOMETRY::LoadState(ENTITY_STATE * state)
{
	return true;
}

#include <stdio.h>
char lightPath[256];
int vrtSize;
GEOS * GEOMETRY::CreateGeometry(const char * file_name,const char * light_file_name, long flags, const char *lmPath)
{
	char fnt[256], lfn[256];
	if(light_file_name!=nullptr)
	{
		sprintf_s(lightPath, "%s\\%s", lmPath, file_name);
		//strcpy_s(lightPath, light_file_name);
		char *bs = strrchr(lightPath, '\\');
		if(bs!=nullptr)	*bs = 0;
	}

#ifndef _XBOX
	static int first = 0;
	FILE *fl;
	if(geoLog)
	{
		vrtSize = 0;
		if(first==0)	fl = fopen("geoLoad.txt", "w");
		else	fl = fopen("geoLoad.txt", "aw");
	}
#endif

	GEOS * gp;
	try
	{
		sprintf_s(fnt, "resource\\models\\%s.gm", file_name);
		if(light_file_name==nullptr || strlen(light_file_name)==0)
		{
			gp = ::CreateGeometry(fnt, nullptr, GSR,flags);
		}
		else
		{
			//sprintf_s(lfn, "resource\\lighting\\%s.col", light_file_name);
			const char *elf = light_file_name;
			if(elf[0] == '\\')	elf++;
			if(elf[0] == '\\')	elf++;
			sprintf_s(lfn, "resource\\models\\%s_%s.col", file_name, elf);
			gp = ::CreateGeometry(fnt, lfn,GSR,flags);
		}

	}
	catch(const char *ee)
	{
		api->Trace("%s: %s", fnt, ee);
		return nullptr;
	}
	catch(...)
	{
		api->Trace("Invalid model: %s", fnt);
		return nullptr;
	}

#ifndef _XBOX
	if(geoLog)
	{
		//---------------------------------------------------------------
		//print statistics
		//---------------------------------------------------------------
		GEOS::INFO gi;
		gp->GetInfo(gi);
		first += gi.ntriangles*2*3 + vrtSize;
		fprintf(fl, "%.2f, trgSize: %d, vrtSize: %d, tex: %d. obj: %d, %s\n", first/1024.0f/1024.0f, gi.ntriangles*2*3, vrtSize, gi.ntextures, gi.nobjects, file_name);
		fclose(fl);
	}
#endif

	return gp;
}

ANIMATION *GEOMETRY::LoadAnimation(const char *anim)
{
	return nullptr;
}

void GEOMETRY::DeleteGeometry(GEOS * gid)
{
	if(gid) delete gid;
}


//=================================================================================================
// Block 2
//=================================================================================================

void GEOM_SERVICE_R::SetRenderService(VDX9RENDER * render_service)
{
	bCaustic = false;
	RenderService = render_service;
	CurentIndexBuffer = INVALID_BUFFER_ID;
	CurentVertexBuffer = INVALID_BUFFER_ID;
	CurentVertexBufferSize = 0;

	const D3DVERTEXELEMENT9 VertexElements[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0},
		{0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0},
		{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		D3DDECL_END()
	};
	if(vertexDecl_ == nullptr)
		RenderService->CreateVertexDeclaration(VertexElements, &vertexDecl_);
}

GEOS::ID GEOM_SERVICE_R::OpenFile(const char *fname)
{
	if(RenderService) RenderService->ProgressView();
	HANDLE fl = fio->_CreateFile(fname,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
	if(fl==INVALID_HANDLE_VALUE)
		if(_strcmpi(&fname[strlen(fname)-4], ".col")==0);//	api->Trace("geometry::can't open file %s", fname);
		else	throw "can't open geometry file";
	return (GEOS::ID)fl;
}

int GEOM_SERVICE_R::FileSize(GEOS::ID file)
{
	if((HANDLE)file==INVALID_HANDLE_VALUE)	return 0;
	uint32_t sh;
	return fio->_GetFileSize((HANDLE)file, &sh);
}
void GEOM_SERVICE_R::ReadFile(GEOS::ID file, void *data, long bytes)
{
	fio->_ReadFile((HANDLE)file,data,bytes,nullptr);
}

void GEOM_SERVICE_R::CloseFile(GEOS::ID file)
{
	fio->_CloseHandle((HANDLE)file);
}

void * GEOM_SERVICE_R::malloc(long bytes)
{
	return new char[bytes];
}

void GEOM_SERVICE_R::free(void *ptr)
{
	if(ptr)	delete ptr;
}

GEOS::ID GEOM_SERVICE_R::CreateTexture(const char *fname)
{
	char tex[256];
	if(_strcmpi(fname, "shadow.tga")==0)
	{
		sprintf_s(tex, "lighting\\%s\\%s", lightPath, fname);
	}
	else
	{
		strcpy_s(tex, texturePath);
		strcat_s(tex, fname);
	}
	if(RenderService)
	{
		RenderService->ProgressView();
		return RenderService->TextureCreate(tex);
	}
	return INVALID_TEXTURE_ID;
}

void GEOM_SERVICE_R::SetCausticMode(bool bSet)
{
	bCaustic = bSet;
}

void GEOM_SERVICE_R::SetMaterial(const GEOS::MATERIAL &mt)
{
	RenderService->TextureSet(0, mt.texture[0]);

	if (bCaustic)
	{
		return;
	}

	if(mt.texture_type[1] != GEOS::TEXTURE_NONE)
	{
		//path BASE texture through
		RenderService->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);

		//stage #2
		RenderService->TextureSet(1,mt.texture[1]);
		// COLOR = BASE_C + DETAIL_C - 0.5
		RenderService->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);

		// COLOR = CURRENT_C * VERTEX_C * 2
		RenderService->TextureSet(2,0);
		RenderService->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE2X);

	}
	else
	{
		RenderService->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE2X);

		RenderService->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		RenderService->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	}

	RenderService->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	RenderService->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	RenderService->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	RenderService->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	RenderService->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
	RenderService->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

// ���� ��� ��� -->
	//RenderService->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    RenderService->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    RenderService->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    RenderService->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    RenderService->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    RenderService->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
    RenderService->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    RenderService->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    RenderService->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

    RenderService->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    RenderService->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
// ���� ��� ��� <--
	/*if(GetAsyncKeyState(0xc0)<0)
	{
		//RenderService->TextureSet(0, 0);
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MAGFILTER, D3DTEXF_POINT);
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MINFILTER, D3DTEXF_NONE);
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MIPFILTER, D3DTEXF_POINT);
	}
	else
	{
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MAGFILTER, D3DTEXF_LINEAR);
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MINFILTER, D3DTEXF_ANISOTROPIC);
		RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MIPFILTER, D3DTEXF_LINEAR);
	}*/

	/*RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MAGFILTER, D3DTEXF_LINEAR);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MINFILTER, D3DTEXF_ANISOTROPIC);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MIPFILTER, D3DTEXF_LINEAR);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_MAXANISOTROPY, 3);

	//unchanged texture stage states - both for base and detal texture
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_COLORARG1, D3DTA_DIFFUSE);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_COLORARG2, D3DTA_TEXTURE);
	RenderService->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	RenderService->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	RenderService->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
	RenderService->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_ALPHAARG1, D3DTA_DIFFUSE);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_ALPHAARG2, D3DTA_TEXTURE);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_ALPHAOP, D3DTOP_DISABLE);

	//general
	RenderService->SetRenderState(D3DRS_FOGENABLE, false);

	RenderService->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	RenderService->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	RenderService->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	RenderService->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	RenderService->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	RenderService->SetRenderState(D3DRS_ALPHAREF, 0xa0);
	RenderService->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//lighting effects
	RenderService->SetRenderState(D3DRS_AMBIENT, 0xa0a0a0);
	RenderService->SetRenderState(D3DRS_LIGHTING, FALSE);//TRUE);
	RenderService->SetRenderState(D3DRS_COLORVERTEX, TRUE);
	RenderService->SetRenderState(D3DRS_SPECULARENABLE, FALSE);//TRUE);

	//path BASE texture through
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_COLORARG1, D3DTA_DIFFUSE);
	RenderService->SetTextureStageState(0, D3DSAMP_COLOROPP_COLOROP, D3DTOP_SELECTARG1);
	RenderService->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);//*/

	D3DMATERIAL9 m;
	m.Diffuse.r = m.Diffuse.g = m.Diffuse.b = mt.diffuse;	m.Diffuse.a = 1.0f;
	m.Ambient.r = m.Ambient.g = m.Ambient.b = m.Ambient.a = 0.0f;
	m.Specular.r = m.Specular.g = m.Specular.b = mt.specular;	m.Specular.a = 1.0f;
	m.Emissive.r = m.Emissive.g = m.Emissive.b = m.Emissive.a = 0.0f;
	m.Power = mt.gloss;

	RenderService->SetMaterial(m);
	//RenderService->SetRenderState(D3DRS_LIGHTING,false);
}

void GEOM_SERVICE_R::ReleaseTexture(GEOS::ID tex)
{

	if(RenderService) RenderService->TextureRelease(tex);
}

GEOS::ID GEOM_SERVICE_R::CreateVertexBuffer(long type, long size)
{
	if(size==0)	return INVALID_BUFFER_ID;
	if(!RenderService) return INVALID_BUFFER_ID;

	long texset[4] = {D3DFVF_TEX1, D3DFVF_TEX2, D3DFVF_TEX3, D3DFVF_TEX4 };
	long fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE  | D3DFVF_TEXTUREFORMAT2;
	long FVF = fvf | texset[type&3];

	//animated vertices
	if(type&4)
	{
		long a;
		for(a=0; a<AVB_MAX; a++)
			if(avb[a].nvertices==0)
				break;
		avb[a].buff = new char[size];
		avb[a].stride = sizeof(GEOS::VERTEX0);
		avb[a].nvertices = size/sizeof(GEOS::AVERTEX0);
		avb[a].fvf = FVF;
		return a + SHIFT_VALUE;
	}

	vrtSize += size;
	return RenderService->CreateVertexBuffer(FVF, size, D3DUSAGE_WRITEONLY);
}

void * GEOM_SERVICE_R::LockVertexBuffer(GEOS::ID vb)
{
	if(vb==INVALID_BUFFER_ID)	return nullptr;
	if(RenderService==nullptr) return nullptr;
	if(vb>=SHIFT_VALUE)	return avb[vb-SHIFT_VALUE].buff;
	return RenderService->LockVertexBuffer(vb);
}

void GEOM_SERVICE_R::UnlockVertexBuffer(GEOS::ID vb)
{
	if(vb==INVALID_BUFFER_ID)	return;
	if(RenderService && vb<SHIFT_VALUE)	RenderService->UnLockVertexBuffer(vb);
}

void GEOM_SERVICE_R::ReleaseVertexBuffer(GEOS::ID vb)
{
	if(vb==INVALID_BUFFER_ID)	return;
	if(RenderService)
		if(vb>=SHIFT_VALUE)
		{
			delete avb[vb-SHIFT_VALUE].buff;
			avb[vb-SHIFT_VALUE].nvertices = 0;
		}
		else	RenderService->ReleaseVertexBuffer(vb);
}

GEOS::ID GEOM_SERVICE_R::CreateIndexBuffer(long size)
{
	if(RenderService) RenderService->ProgressView();
	if(size==0)	return INVALID_BUFFER_ID;
	if(RenderService) return RenderService->CreateIndexBuffer(size);
	return INVALID_BUFFER_ID;
}

void * GEOM_SERVICE_R::LockIndexBuffer(GEOS::ID ib)
{
	if(ib==INVALID_BUFFER_ID)	return nullptr;
	if(RenderService) return RenderService->LockIndexBuffer(ib);
	return nullptr;
}

void GEOM_SERVICE_R::UnlockIndexBuffer(GEOS::ID ib)
{
	if(ib==INVALID_BUFFER_ID)	return;
	if(RenderService) RenderService->UnLockIndexBuffer(ib);
}

void GEOM_SERVICE_R::ReleaseIndexBuffer(GEOS::ID ib)
{
	if(ib==INVALID_BUFFER_ID)	return;
	if(RenderService) RenderService->ReleaseIndexBuffer(ib);
}

void GEOM_SERVICE_R::SetIndexBuffer(GEOS::ID ibuff)
{
	CurentIndexBuffer = ibuff;
}

void GEOM_SERVICE_R::SetVertexBuffer(long vsize, GEOS::ID vbuff)
{
	CurentVertexBuffer = vbuff;
	CurentVertexBufferSize = vsize;
}

void GEOM_SERVICE_R::DrawIndexedPrimitive(long minv, long numv, long vrtsize, long startidx, long numtrg)
{
	if(!RenderService) return;

	//uint32_t oldZBias;

	if (bCaustic)
	{
		CMatrix mWorld, mView, mProjection;
		RenderService->GetTransform(D3DTS_WORLD, mWorld);
		RenderService->GetTransform(D3DTS_PROJECTION, mProjection);
		RenderService->GetTransform(D3DTS_VIEW, mView);

		CMatrix mWVP = (mWorld * mView) * mProjection;

		mWVP.Transposition4x4();

		// ���������
		// 0 - World * View * Projection
		// 4 - World

		RenderService->SetVertexShaderConstantF(0, mWVP, 4);
		RenderService->SetVertexShaderConstantF(4, mWorld, 4);

		RenderService->SetVertexDeclaration(vertexDecl_);

		//RenderService->GetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, &oldZBias);
		//float SSBias = -0.6f;
		//RenderService->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *(int*)&SSBias);
	}

	//draw animation
	if(transform_func!=nullptr)
	{
		VGEOMETRY::ANIMATION_VB *cavb = &avb[CurentVertexBuffer-SHIFT_VALUE];

		IDirect3DVertexBuffer9 *transformed_vb = (IDirect3DVertexBuffer9*)transform_func(cavb->buff, minv, numv, cavb->nvertices);
		if (!bCaustic)
		{
			RenderService->SetStreamSource(0, transformed_vb, cavb->stride);
			RenderService->SetFVF(cavb->fvf);

			RenderService->DrawBuffer(-1, cavb->stride,CurentIndexBuffer,minv,numv,startidx, numtrg, technique);
		}
		else
		{
			RenderService->SetStreamSource(0, transformed_vb, cavb->stride);
			RenderService->DrawIndexedPrimitiveNoVShader(D3DPT_TRIANGLELIST, CurentVertexBuffer, 0, CurentIndexBuffer, minv, numv, startidx, numtrg, "caustic");
		}
		return;
	}
	if(CurentIndexBuffer != INVALID_BUFFER_ID)
	{
		if (!bCaustic)
			RenderService->DrawBuffer(CurentVertexBuffer,vrtsize,CurentIndexBuffer,minv,numv,startidx, numtrg, technique);
		else
			RenderService->DrawIndexedPrimitiveNoVShader(D3DPT_TRIANGLELIST, CurentVertexBuffer, vrtsize, CurentIndexBuffer, minv, numv, startidx, numtrg, "caustic");
	}

	//if (bCaustic)
	//{
	//	RenderService->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, oldZBias);
	//}
}

GEOS::ID GEOM_SERVICE_R::CreateLight(const GEOS::LIGHT)
{
	if(!RenderService) return INVALID_LIGHT_ID;
	return INVALID_LIGHT_ID;
}

void GEOM_SERVICE_R::ActivateLight(GEOS::ID n)
{

}