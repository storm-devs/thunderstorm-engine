//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
//	Grass
//--------------------------------------------------------------------------------------------
//
//============================================================================================

#include "Grass.h"
#include "geometry.h"
#include "Matrix.h"
#include "defines.h"
#include "Character.h"
#include "EntityManager.h"

//============================================================================================

#define GRASS_BLK_LOD	0.8f							//������� ��� kLod - ������, ���� �������������� �����
#define GRASS_MAX_DIST	50.0f							//������������ ��������� ���������
#define GRASS_MIN_DIST	10.0f							//����������� ��������� �������������� �����
#define GRASS_MAX_W		1.0f							//���������� ������
#define GRASS_MAX_H		0.2f							//���������� ������
#define GRASS_VEIW		((long)(m_fMaxVisibleDist/GRASS_BLK_DST/GRASS_BLK_DST + 0.5f) + 1)	//��������� ��������� � ������
#define GRASS_FRM_W		4								//���������� ������ �� ������ M = 2^N
#define GRASS_FRM_H		4								//���������� ������ �� ������ M = 2^N
#define GRASS_TEX_W		(1.0f/GRASS_FRM_W)
#define GRASS_TEX_H		(1.0f/GRASS_FRM_H)
#define GRASS_TEX_DELTA	(1.0f/256.0f)
#define GRASS_MAX_POINTS	8192

#define GRASS_DEFTEXTURE	"Grass\\grass.tga"

//============================================================================================
//���������������, ������������������
//============================================================================================

IDirect3DVertexDeclaration9 * Grass::vertexDecl_ = nullptr;

Grass::Grass()
{
	miniMap = nullptr;
	block = nullptr;
	numElements = 0;
	texture = -1;
	phase[0] = 0.1f;
	phase[1] = 0.51f;
	phase[2] = 0.01f;
	phase[3] = -0.2f;
	phase[4] = 0.03f;
	phase[5] = 0.04f;
	phase[6] = 0.08f;

	lodSelect = GRASS_BLK_LOD;
	winForce = 0.3f;
	winDir = !CVECTOR(0.0f, 0.0f, 1.0f);
	numCharacters = 0;

	strcpy_s(textureName, GRASS_DEFTEXTURE);

	vb = ib = -1;
	vbuffer = nullptr;

	quality = rq_full;
	windAng = 0.0f;
	initForce = 0;

	m_fDataScale = 1.0f;
	m_fMaxWidth = GRASS_MAX_W;
	m_fMaxHeight = GRASS_MAX_H;
	m_fMinVisibleDist = GRASS_MIN_DIST;
	m_fMaxVisibleDist = GRASS_MAX_DIST;
	m_fMinGrassLod = 0.f;
}

Grass::~Grass()
{
	if(miniMap) delete miniMap;
	if(block) delete block;
	if(rs)
	{
		if(texture >= 0) rs->TextureRelease(texture);
		if(vb >= 0)
		{
			if(vbuffer) rs->UnLockVertexBuffer(vb);
			vbuffer = nullptr;
			rs->ReleaseVertexBuffer(vb);
		}
		if(ib >= 0) rs->ReleaseIndexBuffer(ib);
	}

}


//�������������
bool Grass::Init()
{
	//Layers
	//api->LayerCreate("execute", true, false);
	EntityManager::SetLayerType(EXECUTE, EntityManager::Layer::Type::execute);
	EntityManager::AddToLayer(EXECUTE, GetId(), 1000);
	//api->LayerCreate("realize", true, false);
	EntityManager::SetLayerType(REALIZE, EntityManager::Layer::Type::realize);
	EntityManager::AddToLayer(REALIZE, GetId(), 1000);

    // boal ����� ������� -->
    isGrassLightsOn = 1;
    VDATA * param = api->Event("GOpt_isGrassLightsOn", nullptr);
	if (param)
	{
  		param->Get(isGrassLightsOn);
	}
	// boal ����� ������� <--

	//DX9 render
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if(!rs) throw std::exception("No service: dx9render");
	//Vertex declaration
	CreateVertexDeclaration();
	//����� ��� ������������ ������
	vb = rs->CreateVertexBuffer(0, GRASS_MAX_POINTS*4*sizeof(Vertex), D3DUSAGE_DYNAMIC);
	if(vb < 0) return false;
	//�������, ���������� �������
	ib = rs->CreateIndexBuffer(GRASS_MAX_POINTS*6*sizeof(uint16_t));
	if(ib < 0) return false;
	uint16_t * index = (uint16_t *)rs->LockIndexBuffer(ib);
	if(!index) return false;
	for(long i = 0, point = 0; i < GRASS_MAX_POINTS; i++, index += 6, point += 4)
	{
		index[0] = uint16_t(point + 0);
		index[1] = uint16_t(point + 1);
		index[2] = uint16_t(point + 2);
		index[3] = uint16_t(point + 2);
		index[4] = uint16_t(point + 1);
		index[5] = uint16_t(point + 3);
	}
	rs->UnLockIndexBuffer(ib);
	//���������
	static const float pi2 = 2.0f*3.141592653f;
	for(long i = 0; i < 16; i++)
	{
		//������� �����
		consts[i].x = sinf(i*pi2/16.0f);
		consts[i].y = cosf(i*pi2/16.0f);
		consts[i].z = 0.0f;
		consts[i].w = 1.0f;
		//������� uv
		consts[i + 16].x = (i & 3)*(1.0f/4.0f);
		consts[i + 16].y = ((i >> 2) & 3)*(1.0f/4.0f);
		consts[i + 16].z = 0.0f;
		consts[i + 16].w = 1.0f;
	}
	consts[36].w = 0.0f;
	consts[39] = VSConstant(0.9f, 1.0f, 0.245f, -0.245f);
	consts[40] = VSConstant(15.0f, -0.5f, 1.0f, 0.8f);
	consts[41] = VSConstant(0.3f*m_fMaxWidth, 0.4f*m_fMaxHeight, 0.7f*m_fMaxWidth, 0.6f*m_fMaxHeight);
	return true;
}

//��������� ������ ��� ����� �� ��������������� �����
bool Grass::LoadData(const char * patchName)
{
	//�������� �����
	texture = rs->TextureCreate(textureName);
	//������ ������
	if(miniMap) delete miniMap; miniMap = nullptr;
	if(block) delete block; block = nullptr;
	//��������� ���� � �������
	uint8_t * load = nullptr;
	uint32_t size = 0;
	if(!fio->LoadFile(patchName, (char**)&load, &size)) return false;
	try{
		//�������� ������
		if(size < sizeof(GRSHeader)) throw "invalide file size";
		GRSHeader & hdr = *(GRSHeader *)load;
		if(hdr.id != GRASS_ID) throw "invalide file id";
		if(hdr.ver != GRASS_VER) throw "invalide file version";
		long minisize = hdr.miniX*hdr.miniZ;
		long elements = hdr.numElements;
		if(size != sizeof(GRSHeader) + minisize*sizeof(GRSMiniMapElement) + elements*sizeof(GRSMapElement)) throw "incorrect file data -> file size";
		if(hdr.miniX <= 0 || hdr.miniX > 100000 || hdr.miniZ <= 0 || hdr.miniZ > 100000) throw "incorrect file data -> miniX, miniZ";
		//������ ���������
		miniMap = new GRSMiniMapElement[minisize];
		memcpy(miniMap, load + sizeof(GRSHeader), minisize*sizeof(GRSMiniMapElement));
		miniX = hdr.miniX;
		miniZ = hdr.miniZ;
		//��������� ��������
		for(long i = 0, pnt = 0; i < minisize; i++)
		{
			if(pnt != miniMap[i].start)  throw "incorrect file data -> minimap";
			pnt += miniMap[i].num[0];
		}
		//������ �����
		uint8_t translate[16];
		for(long i = 0; i < 16; i++)
		{
			translate[i] = uint8_t((i*255)/15);
		}
		block = new GRSMapElementEx[elements];
		GRSMapElement * src = (GRSMapElement *)(load + sizeof(GRSHeader) + minisize*sizeof(GRSMiniMapElement));
		for(long i = 0; i < elements; i++)
		{
			GRSMapElement & sb = src[i];
			GRSMapElementEx & b = block[i];
			b.x = sb.x*GRASS_STEP;
			b.y = sb.y;
			b.z = sb.z*GRASS_STEP;
			b.frame = translate[sb.frame];
			b.h = translate[sb.h];
			b.w = translate[sb.w];
			b.ang = translate[sb.ang];
		}
		startX = hdr.startX;
		startZ = hdr.startZ;
		numElements = elements;
		//������������ ������� �������� �� ��������� � �������
		for(long z = 0; z < miniZ; z++)
		{
			GRSMiniMapElement * line = &miniMap[z*miniX];
			float cz = startZ + z*GRASS_BLK_DST;
			for(long x = 0; x < miniX; x++)
			{
				float cx = startX + x*GRASS_BLK_DST;
				GRSMapElementEx * el = block + line[x].start;
				long count = line[x].num[0];
				for(long i = 0; i < count; i++)
				{
					el[i].x += cx;
					el[i].z += cz;
				}

			}
		}
	}catch(const char * error){
		api->Trace("Grass: incorrect grs file %s (%s)", patchName, error);
		if(miniMap) delete miniMap; miniMap = nullptr;
		if(block) delete block; block = nullptr;
	}
	delete load;
	return true;
}

//���������� ��������
void Grass::SetTexture(const char * texName)
{
	if(!texName || !texName[0] || strlen(texName) > 63)
	{
		strcpy_s(textureName, GRASS_DEFTEXTURE);
	}else{
		strcpy_s(textureName, texName);
	}
}

//������
void Grass::Execute(uint32_t delta_time)
{
	if(initForce < 20)
	{
		initForce++;
	}

	VDATA * param = api->Event("GOpt_GetGrassQuality", nullptr);
	long res = rq_full;
	if(param && param->Get(res))
	{
		if(res < rq_full) res = rq_full;
		if(res > rq_off) res = rq_off;
		quality = RenderQuality(res);
	}else{
		quality = rq_full;
	}
	if(quality == rq_off) return;
	//��������� �����
	param = api->Event("EWhr_GetWindAngle", nullptr);
	if(param)
	{
		float ang;
		if(!param->Get(ang)) ang = 0.0f;
		if(initForce < 20)
		{
			windAng = ang;
		}else{
			float k = delta_time*0.001f*0.001f;
			if(k > 1.0f) k = 1.0f;
			windAng += (ang - windAng)*k;
		}
		winDir.x = sinf(ang);
		winDir.z = cosf(ang);
	}
	param = api->Event("EWhr_GetWindSpeed", nullptr);
	if(param)
	{
		float spd;
		if(!param->Get(spd)) spd = 0.0f;
		if(spd < 0.0f) spd = 0.0f;
		if(spd > 30.0f) spd = 30.0f;
		float wf = powf(spd*(1.0f/30.0f), 0.5f);
		if(initForce < 20)
		{
			initForce++;
			winForce = wf;
		}else{
			float k = delta_time*0.001f*0.001f;
			if(k > 1.0f) k = 1.0f;
			winForce += (wf - winForce)*k;
		}
		if(winForce < 0.0f) winForce = 0.0f;
		if(winForce > 1.0f) winForce = 1.0f;
	}
	//����
	float dltTime = delta_time*0.001f;
	if(dltTime > 0.05f) dltTime = 0.05f;
	phase[0] += dltTime*(0.3f + powf(winForce, 10.0f)*0.0f);
	phase[1] += dltTime*0.21f;
	phase[2] += dltTime*0.01f;
	phase[3] += winDir.x*dltTime*(0.52f + powf(winForce, 3.0f)*0.0f);
	phase[4] += winDir.z*dltTime*(0.55f + powf(winForce, 2.5f)*0.0f);
	phase[5] += dltTime*0.019f;
	phase[6] += dltTime*0.057f;
	const float pi2 = 2.0f*3.141592653f;
	for(long i = 0; i < sizeof(phase)/sizeof(phase[0]); i++) if(phase[i] > pi2*256.0f) phase[i] -= pi2*256.0f;
	//����������� ��� ������� ����������
	cosPh1 = 0.4f + 0.15f*cosf(phase[1]);
	sinPh2 = 0.51f + 0.09f*sinf(phase[2]);
	sinPh5 = 0.1f*sinf(phase[5]);
	sinPh6 = 0.01f*sinf(phase[6]);
	winPow = 5.0f - powf(winForce, 4.0f)*4.5f;
	winF10 = powf(winForce, 10.0f)*0.5f;
	kAmpWF = powf(winForce, 2.0f)*0.8f;
	kDirWF = 0.8f*(1.0f - powf(winForce, 10.0f)*0.999f);
	kLitWF = 0.7f*(1.0f - powf(winForce, 4.0f)*0.7f);
}

void Grass::Realize(uint32_t delta_time)
{
	if(quality == rq_off) return;
	rs->SetTransform(D3DTS_WORLD, CMatrix());
	//����� ��������
	rs->TextureSet(0, -1);
	rs->TextureSet(1, -1);
	//������
	rs->SetRenderState(D3DRS_ZENABLE, false);
	rs->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	rs->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	rs->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	rs->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	rs->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�����
	uint32_t dwOldFogDensity;
	rs->GetRenderState(D3DRS_FOGDENSITY, &dwOldFogDensity);
	entid_t eidIsland = EntityManager::GetEntityId("ISLAND");
	if(eidIsland)
	{
		float fIslandFogDensity = (float)dwOldFogDensity;
		ATTRIBUTES* pA = api->Entity_GetAttributePointer( eidIsland );
		if( pA ) fIslandFogDensity = pA->GetAttributeAsFloat("FogDensity", 0.0f);
		rs->SetRenderState(D3DRS_FOGDENSITY, F2DW(fIslandFogDensity));
	}
	//�������� ������
	uint32_t cop, carg1, cop1, aop, aarg1;
	rs->GetTextureStageState(0, D3DTSS_COLOROP, &cop);
	rs->GetTextureStageState(1, D3DTSS_COLOROP, &cop1);
	rs->GetTextureStageState(0, D3DTSS_COLORARG1, &carg1);
	rs->GetTextureStageState(0, D3DTSS_ALPHAOP, &aop);
	rs->GetTextureStageState(0, D3DTSS_ALPHAARG1, &aarg1);

	rs->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	rs->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	rs->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	rs->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	rs->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

	struct SphVertex
	{
		CVECTOR v;
		uint32_t c;
	};

	SphVertex lineVertex[2];
	lineVertex[0].c = 0xff009f00;
	lineVertex[1].c = 0xff00ffff;

	//���������� ������
	rs->SetTextureStageState(0, D3DTSS_COLOROP, cop);
	rs->SetTextureStageState(0, D3DTSS_COLORARG1, carg1);
	rs->SetTextureStageState(1, D3DTSS_COLOROP, cop1);
	rs->SetTextureStageState(0, D3DTSS_ALPHAOP, aop);
	rs->SetTextureStageState(0, D3DTSS_ALPHAARG1, aarg1);
	//���������� ������
	rs->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	rs->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	rs->SetRenderState(D3DRS_ZENABLE, TRUE);

	//if(api->Controls->GetDebugAsyncKeyState('H') < 0) return;

	//���� ��� �����, �� ��� � ���������
	if(!block) return;
	//��������� ��������� ���������
	BOOL isLight = FALSE;
	rs->GetLightEnable(0, &isLight);
	D3DLIGHT9 light;
	if(isLight && rs->GetLight(0, &light))
	{
		//������������� ��������
		//�����������
		lDir.x = light.Direction.x;
		lDir.y = 0.0f;
		lDir.z = light.Direction.z;
		float len = ~lDir;
		if(len > 0.0f) lDir *= 1.0f/sqrtf(len); else lDir = !CVECTOR(0.9f, 0.0f, 0.5f);
		//���� �����������
		lColor.z = light.Diffuse.r;
		lColor.y = light.Diffuse.g;
		lColor.x = light.Diffuse.b;
		if(lColor.x < 0.0f) lColor.x = 0.0f;
		if(lColor.x > 1.0f) lColor.x = 1.0f;
		if(lColor.y < 0.0f) lColor.y = 0.0f;
		if(lColor.y > 1.0f) lColor.y = 1.0f;
		if(lColor.z < 0.0f) lColor.z = 0.0f;
		if(lColor.z > 1.0f) lColor.z = 1.0f;
		lColor.x = powf(lColor.x, 0.2f);
		lColor.y = powf(lColor.y, 0.2f);
		lColor.z = powf(lColor.z, 0.2f);
		//��������� ����
		uint32_t aclr;
		if(rs->GetRenderState(D3DRS_AMBIENT, &aclr) != D3D_OK) aclr = 0xffffffff;
		aColor.z = uint8_t(aclr >> 16)*1.0f/255.0f;
		aColor.y = uint8_t(aclr >> 8)*1.0f/255.0f;
		aColor.x = uint8_t(aclr >> 0)*1.0f/255.0f;
		if(aColor.x > 1.0f) aColor.x = 1.0f;
		if(aColor.y > 1.0f) aColor.y = 1.0f;
		if(aColor.z > 1.0f) aColor.z = 1.0f;
		float y = aColor.z*0.299f + aColor.y*0.587f + aColor.x*0.114f;
		aColor = y*0.7f + aColor*0.3f;
		aColor *= 0.8f;
	}else{
		//�������� �� ���������
		//��������� ����
		uint32_t aclr;
		if(rs->GetRenderState(D3DRS_AMBIENT, &aclr) != D3D_OK) aclr = 0xffffffff;
		aColor.z = uint8_t(aclr >> 16)*1.0f/255.0f;
		aColor.y = uint8_t(aclr >> 8)*1.0f/255.0f;
		aColor.x = uint8_t(aclr >> 0)*1.0f/255.0f;
		if(aColor.x > 1.0f) aColor.x = 1.0f;
		if(aColor.y > 1.0f) aColor.y = 1.0f;
		if(aColor.z > 1.0f) aColor.z = 1.0f;
		//�����������
		lDir = !CVECTOR(0.9f, 0.0f, 0.5f);
		//���� �����������
		lColor = 0.3f;
	}
	//����������� ��������� �����
	for(long i = 0; i < 16; i++)
	{
		consts[i].z = fabsf(-consts[i].y*lDir.x + consts[i].x*lDir.z);
		if(consts[i].z < 0.0f) consts[i].z = 0.0f;
		if(consts[i].z > 1.0f) consts[i].z = 1.0f;
	}
	//�������
	CMatrix view, prj;
	rs->GetTransform(D3DTS_VIEW, view);
	rs->GetTransform(D3DTS_PROJECTION, prj);
	CMatrix & cmtx = (CMatrix &)consts[32];
	cmtx.EqMultiply(view, prj);
	//��������� ���������
	consts[36].x = lDir.x;
	consts[36].y = lDir.z;
	consts[37].x = aColor.x;
	consts[37].y = aColor.y;
	consts[37].z = aColor.z;
	consts[37].w = 1.0f;
	consts[38].x = lColor.x;
	consts[38].y = lColor.y;
	consts[38].z = lColor.z;
	consts[38].w = m_fDataScale; // 1.f;
	consts[39].y = kLitWF;
	//������� ������
	CVECTOR pos, ang;
	float prs;
	rs->GetCamera(pos, ang, prs);
	//����� ���������
	PLANE * pln = rs->GetPlanes();
	PLANE plane[5];
	plane[0].Nx = plane[0].Ny = plane[0].Nz = 0.0f;
	for(long i = 0; i < 4; i++)
	{
		plane[i + 1] = pln[i];
		plane[0].Nx += pln[i].Nx;
		plane[0].Ny += pln[i].Ny;
		plane[0].Nz += pln[i].Nz;
	}
	plane[0].Nx *= 0.25f;
	plane[0].Ny *= 0.25f;
	plane[0].Nz *= 0.25f;
	plane[0].D = pos.x*plane[0].Nx + pos.y*plane[0].Ny + pos.z*plane[0].Nz;
	long numPlanes = 5;
	//������ ��������
	rs->TextureSet(0, texture);
	rs->TextureSet(1, texture);
	//������ ���������
	rs->SetVertexShaderConstantF(0, (const float*)consts, sizeof(consts) / sizeof(VSConstant));
	//rs->SetFVFConstant(0, consts, 40);
	//������� ������ �� �����
	long camx = long((pos.x/m_fDataScale - startX)/GRASS_BLK_DST);
	long camz = long((pos.z/m_fDataScale - startZ)/GRASS_BLK_DST);
	//�������, ������������ ���� ��������� �� �����
	long left = camx - GRASS_VEIW, right = camx + GRASS_VEIW;
	long top = camz - GRASS_VEIW, bottom = camz + GRASS_VEIW;
	//������� ��������� �����
	if(right < 0 || left >= miniX) return;
	if(bottom < 0 || top >= miniZ) return;
	if(left < 0) left = 0;
	if(right >= miniX) right = miniX - 1;
	if(top < 0) top = 0;
	if(bottom >= miniZ) bottom = miniZ - 1;

	if(camx < 0) camx = 0;
	if(camx >= miniX) camx = miniX - 1;
	if(camz < 0) camz = 0;
	if(camz >= miniZ) camz = miniZ - 1;
	//������� ����� ��� �������
	numPoints = 0;
	rs->SetTransform(D3DTS_WORLD, CMatrix());

	for(long mx = left, mz; mx <= camx; mx++)
	{
		for(mz = top; mz <= camz; mz++) RenderBlock(pos, plane, numPlanes, mx, mz);
		for(mz = bottom; mz > camz; mz--) RenderBlock(pos, plane, numPlanes, mx, mz);
	}
	for(long mx = right, mz; mx > camx; mx--)
	{
		for(mz = top; mz <= camz; mz++) RenderBlock(pos, plane, numPlanes, mx, mz);
		for(mz = bottom; mz > camz; mz--) RenderBlock(pos, plane, numPlanes, mx, mz);
	}
	//������ �����
	DrawBuffer();

	rs->SetRenderState(D3DRS_FOGDENSITY, dwOldFogDensity);

	for(long i = 0; i < numCharacters; i++)
	{
		if(characters[i].useCounter > 2)
		{
			characters[i].chr->SetGrassSound();
		}
	}
}

uint64_t Grass::ProcessMessage(MESSAGE &message)
{
	char ctmp[MAX_PATH];
	switch( message.Long() )
	{
	case MSG_GRASS_LOAD_DATA:
		message.String(sizeof(ctmp),ctmp);
		return LoadData(ctmp);
	break;
	case MSG_GRASS_SET_TEXTURE:
		message.String(sizeof(ctmp),ctmp);
		SetTexture(ctmp);
	break;
	case MSG_GRASS_SET_PARAM:
		m_fDataScale = message.Float();

		m_fMaxWidth = message.Float();
		m_fMaxHeight = message.Float();
		consts[41] = VSConstant(0.3f*m_fMaxWidth, 0.4f*m_fMaxHeight, 0.7f*m_fMaxWidth, 0.6f*m_fMaxHeight);

		m_fMinVisibleDist = message.Float();
		m_fMaxVisibleDist = message.Float();

		m_fMinGrassLod = message.Float();
		return 0;
	break;
	}
	return 0;
}

//���������� ���� � ������������ �� ���������
void Grass::RenderBlock(const CVECTOR & camPos, PLANE * plane, long numPlanes, long mx, long mz)
{
	//������ �����, ���� ����������
	if(numPoints >= GRASS_MAX_POINTS - (GRASS_CNT_MIN + GRASS_CNT_DLT)*3)
	{
		DrawBuffer();
	}
	CVECTOR min, max;
	//����, ������� ������
	GRSMiniMapElement & mm = miniMap[mz*miniX + mx];
	//��������� ������� �����
	if(mm.num[0] == 0) return;
	//��������� �� ������ �������� (�����) �� ������ � 2D
	float cx = m_fDataScale * (startX + (mx + 0.5f)*GRASS_BLK_DST);
	float cz = m_fDataScale * (startZ + (mz + 0.5f)*GRASS_BLK_DST);
	float dist = (cx - camPos.x)*(cx - camPos.x) + (cz - camPos.z)*(cz - camPos.z);
	//����������� �� ���������
	if(dist >= m_fMaxVisibleDist*m_fMaxVisibleDist) return;
	//����������� ���������
	min.x = cx - 0.5f*GRASS_BLK_DST*m_fDataScale - 2.0f*m_fMaxWidth;
	min.y = mm.minHeight*m_fDataScale;
	min.z = cz - 0.5f*GRASS_BLK_DST*m_fDataScale - 2.0f*m_fMaxWidth;
	max.x = cx + 0.5f*GRASS_BLK_DST*m_fDataScale + 2.0f*m_fMaxWidth;
	max.y = mm.maxHeight*m_fDataScale;
	max.z = cz + 0.5f*GRASS_BLK_DST*m_fDataScale + 2.0f*m_fMaxWidth;
	if(!VisibleTest(plane, numPlanes, min, max)) return;
	//����������� ����
	float kLod = (sqrtf(dist) - m_fMinVisibleDist)/(m_fMaxVisibleDist - m_fMinVisibleDist);
	//if(kLod < 0.0f) kLod = 0.0f;
	if(kLod < m_fMinGrassLod) kLod = m_fMinGrassLod;
	//��������� ���������� ���������� � ������� ����
	numBlockChr = 0;
	for(long i = 0; i < numCharacters; i++)
	{
		//��������� ������ ���������� ����������
		if(characters[i].pos.x + 0.9f < min.x) continue;
		if(characters[i].pos.x - 0.9f > max.x) continue;
		if(characters[i].pos.y + 0.9f < min.y) continue;
		if(characters[i].pos.y - 0.9f > max.y) continue;
		if(characters[i].pos.z + 0.9f < min.z) continue;
		if(characters[i].pos.z - 0.9f > max.z) continue;
		//��������� ������
		blockChrs[numBlockChr++] = i;
	}
	//������ �����
	RenderBlock(mm, kLod);
}

//�������� �� ��������� �����
inline bool Grass::VisibleTest(const PLANE * plane, long numPlanes, const CVECTOR & min, const CVECTOR & max)
{
	for(long i = 0; i < numPlanes; i++)
	{
		float d = plane[i].D;
		float minX = min.x*plane[i].Nx;
		float minY = min.y*plane[i].Ny;
		float minZ = min.z*plane[i].Nz;
		float maxX = max.x*plane[i].Nx;
		float maxY = max.y*plane[i].Ny;
		float maxZ = max.z*plane[i].Nz;
		if(minX + minY + minZ >= d) continue;
		if(minX + maxY + minZ >= d) continue;
		if(maxX + maxY + minZ >= d) continue;
		if(maxX + minY + minZ >= d) continue;
		if(minX + minY + maxZ >= d) continue;
		if(minX + maxY + maxZ >= d) continue;
		if(maxX + maxY + maxZ >= d) continue;
		if(maxX + minY + maxZ >= d) continue;
		return false;
	}
	return true;
}

//���������� ����
inline void Grass::RenderBlock(GRSMiniMapElement & mme, float kLod)
{
	//��������� �� ����
	if(!vbuffer)
	{
		vbuffer = (Vertex *)rs->LockVertexBuffer(vb);
		if(!vbuffer) return;
	}
	//������� � ������� ������
	Vertex * v = vbuffer + numPoints*4;
	//�����
	GRSMapElementEx * b = block + mme.start;
	//���������� ��������� ����
	kLod = kLod*3.9999f;
	long lod = long(kLod);
	if(lod < quality) lod = quality;
	Assert(lod >= 0 && lod < 4);
	float kBlend = 1.0f - (kLod - lod);
	if(kBlend > 1.0f) kBlend = 1.0f;
	if(kBlend < 0.0f) kBlend = 0.0f;
	//���������� �������� �����
	long num = mme.num[lod];
	Assert(num <= GRASS_CNT_MIN + GRASS_CNT_DLT);
	//���������� �������� ��� �����������
	long lodNum = lod < 3 ? mme.num[lod + 1] : 0;
	//��������� ����������
	float wAddX, wAddZ, kwDirX, kwDirZ;
	if(quality <= rq_middle)
	{
		wAddX = winDir.x*winForce*(1.0f + cosf(phase[1] + sinPh5))*0.25f;
		wAddZ = winDir.z*winForce*(1.0f + cosf(phase[1] + sinPh5))*0.25f;
		kwDirX = winDir.x*kDirWF;
		kwDirZ = winDir.z*kDirWF;
	}else{
		wAddX = 0.01f*winForce + 0.1f*winForce*winForce + 2.0f*winF10;
		if(wAddX > 1.0f) wAddX = 1.0f;
	}
	//���� �� ���������
	float alpha;
	for(long i = 0; i < num; i++)
	{
		//�����
		if(i < lodNum){ alpha = 1.0f; }else{ alpha = kBlend; }
		//��������� �����
		float winx = sinf(b[i].x*cosPh1 + b[i].z*0.06f + phase[0]);
		float winz = cosf(b[i].x*0.11f + b[i].z*sinPh2 + phase[0]);
		if(quality <= rq_middle)
		{
			//�������
			float x = b[i].x;
			float y = b[i].y;
			float z = b[i].z;
			//����� �����
			float dx = winDir.x*x*0.5f + phase[3];
			float dz = winDir.z*z*0.5f + phase[4];
			float k1 = sinf(dx + dz);
			float a1 = (0.001f + sinPh5*sinf((dx + dz)*0.5f));
			float k2 = cosf(winDir.z*x*(a1 + sinPh6) - winDir.x*z*a1);
			float kamp = powf(k1*k2*0.5f + 0.5f, winPow) + winF10 + winForce*0.7f;
			if(kamp > 1.0f) kamp = 1.0f;
			//�������������� ������ ��������
			kamp *= kAmpWF;
			winx = (0.9f*winx + kwDirX)*kamp + wAddX;
			winz = (0.9f*winz + kwDirZ)*kamp + wAddZ;
			//���� ����������
			for(long chr = 0; chr < numBlockChr; chr++)
			{
				CharacterPos & cp = characters[blockChrs[chr]];
				if(fabsf(cp.pos.y - y) < 0.7f)
				{
					float pldx = ((x - cp.pos.x) + (x - cp.lastPos.x))*0.5f;
					float pldz = ((z - cp.pos.z) + (z - cp.lastPos.z))*0.5f;
					float dst = pldx*pldx + pldz*pldz;
					if(dst < 0.8f*0.8f && dst > 0.0f)
					{
						//������������
						if(dst > 0.0f)
						{
							dst = sqrtf(dst);
							float k = 0.5f/dst;
							pldx *= k;
							pldz *= k;
						}
						dst *= 1.0f/0.8f;
						dst = 1.0f - dst;
						dst *= dst;
 						winx += (pldx - winx)*dst;
						winz += (pldz - winz)*dst;
						cp.useCounter++;
					}
				}
			}
			float wLen = sqrtf(winx*winx + winz*winz);
			if(wLen > 1.2f)
			{
				wLen = 1.2f/wLen;
				winx *= wLen;
				winz *= wLen;
			}
			winx *= 0.4f;
			winz *= 0.4f;
		}else{
			winx *= wAddX;
			winz *= wAddX;
		}
		//�������� ������
		GRSMapElementEx & el = b[i];
		//����������
		v[0].x = el.x; v[0].y = el.y; v[0].z = el.z;
		v[0].data = el.data;
		v[0].offset = 0x00000000;
		v[0].wx = winx; v[0].wz = winz;
		v[0].alpha = alpha;

		v[1].x = el.x; v[1].y = el.y; v[1].z = el.z;
		v[1].data = el.data;
		v[1].offset = 0x00ff0000;
		v[1].wx = winx; v[1].wz = winz;
		v[1].alpha = alpha;

		v[2].x = el.x; v[2].y = el.y; v[2].z = el.z;
		v[2].data = el.data;
		v[2].offset = 0x0000ff00;
		v[2].wx = winx; v[2].wz = winz;
		v[2].alpha = alpha;

		v[3].x = el.x; v[3].y = el.y; v[3].z = el.z;
		v[3].data = el.data;
		v[3].offset = 0x00ffff00;
		v[3].wx = winx; v[3].wz = winz;
		v[3].alpha = alpha;

		v += 4;
		numPoints++;
	}
}

//���������� ���������� ������
void Grass::DrawBuffer()
{
	if(vbuffer)
	{
		rs->UnLockVertexBuffer(vb);
		vbuffer = nullptr;
	}
	// boal ����� ������� -->
	if (numPoints > 0)
	{
		rs->SetVertexDeclaration(vertexDecl_);
		if (isGrassLightsOn == 1)
		{
			rs->DrawBuffer(vb, sizeof(Vertex), ib, 0, numPoints * 4, 0, numPoints * 2, "Grass");
		}
		else
		{
			rs->DrawBuffer(vb, sizeof(Vertex), ib, 0, numPoints * 4, 0, numPoints * 2, "GrassDark");
		}
	// boal ����� ������� <--
		numPoints = 0;
	}
}

long Grass::GetColor(CVECTOR color)
{
	if(color.x > 1.0f) color.x = 1.0f;
	if(color.x < 0.0f) color.x = 0.0f;
	if(color.y > 1.0f) color.y = 1.0f;
	if(color.y < 0.0f) color.y = 0.0f;
	if(color.z > 1.0f) color.z = 1.0f;
	if(color.z < 0.0f) color.z = 0.0f;
	long r = long(color.z*255.0f);
	long g = long(color.y*255.0f);
	long b = long(color.x*255.0f);
	return (r << 16) | (g << 8) | b;
}

void Grass::CreateVertexDeclaration()
{
	if (vertexDecl_ != nullptr)
		return;

	const D3DVERTEXELEMENT9 VertexElements[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0},
		{0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  1},
		{0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	rs->CreateVertexDeclaration(VertexElements, &vertexDecl_);
}
