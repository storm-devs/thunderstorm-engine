#include "modelr.h"
#include "..\common_h\messages.h"
#include "..\common_h\defines.h"
#include <stdio.h>

INTERFACE_FUNCTION
CREATE_CLASS(MODELR)

IDirect3DVertexBuffer9 *dest_vb;

MODELR::MODELR()
{
	bSetupFog = false;
	LightPath[0] = 0;
	lmPath[0] = 0;
	ani = null;
	memset(aniVerts, 0, sizeof(aniVerts));
	d3dDestVB = 0;
	for(long i = 0; i < ANI_MAX_ACTIONS; i++) aniPos[i] = -1.0f;
	root = null;
	useBlend = false;
	idxBuff = 0;
	nAniVerts = 0;
}

CMatrix *bones;

MODELR::~MODELR()
{
	if(d3dDestVB!=0)	d3dDestVB->Release();
	if(root) delete root;
	for(int i = 0; i < MODEL_ANI_MAXBUFFERS; i++)
		if(aniVerts[i].v) delete aniVerts[i].v;
	if(ani) delete ani;

	if(idxBuff!=0)	delete idxBuff;
}

bool MODELR::Init()
{
	GUARD(MODELR::Init)

	rs = (VDX8RENDER *)_CORE_API->CreateService("dx8render");
	if(!rs)	_THROW("No service: dx8render");

	GeometyService = (VGEOMETRY *)_CORE_API->CreateService("geometry");
	if(!GeometyService) _THROW("No service: geometry");

	UNGUARD
	return true;
}

bool alreadyTransformed;
void *VBTransform(void *vb, long startVrt, long nVerts, long totVerts)
{
	if(alreadyTransformed)	return dest_vb;
	alreadyTransformed = true;
	if(!totVerts) return dest_vb;

	GEOS::AVERTEX0 *src = (GEOS::AVERTEX0*)vb;

	GEOS::VERTEX0 *dst;
#ifndef _XBOX
	dest_vb->Lock(0, 0, (unsigned char**)&dst, D3DLOCK_DISCARD|D3DLOCK_NOSYSLOCK);
#else
	dest_vb->Lock(0, 0, (unsigned char**)&dst, 0);
#endif

	//dest_vb->Lock(sizeof(GEOS::VERTEX0)*startVrt, sizeof(GEOS::VERTEX0)*nVerts, (unsigned char**)&dst, D3DLOCK_DISCARD|D3DLOCK_NOSYSLOCK);
	//src += startVrt;
	//for(long v=0; v<nVerts; v++)
//if(GetAsyncKeyState('8') < 0)
//{
	/*
		//���������� ���������
		static float one = 1.0f;
		//�������
		_asm
		{
			mov eax, src
			mov ebx, dst
vrt_loop:	prefetcht0 [eax]
			prefetcht0 [eax + 32]
			xor ecx, ecx
			xor edx, edx
			mov esi, bones
			mov cl, [eax + 16]
			mov dl, [eax + 17]
			mov edi, esi
			shl ecx, 6
			shl edx, 6
			add esi, ecx
			add edi, edx
			movss  xmm0, [eax + 12]				//000w
			movss  xmm1, one					//0001
			shufps xmm0, xmm0, 00000000b		//xmm0 = wwww
			shufps xmm1, xmm1, 00000000b		//1111
			movups xmm4, [esi + 0]				//m1.vx
			movups xmm6, [edi + 0]				//m2.vx
			subps  xmm1, xmm0					//xmm1 = (1 - w)(1 - w)(1 - w)(1 - w)
			movups xmm5, [esi + 16]				//m1.vy
			movups xmm7, [edi + 16]				//m2.vy
			mulps  xmm4, xmm0					//m1.vx*w
			mulps  xmm6, xmm1					//m2.vx*(1 - w)
			mulps  xmm5, xmm0					//m1.vy*w
			mulps  xmm7, xmm1					//m2.vy*(1 - w)
			addps  xmm4, xmm6					//m1.vx*w + m2.vx*(1 - w)
			addps  xmm5, xmm7					//m1.vy*w + m2.vy*(1 - w)
			movups xmm6, [esi + 32]				//m1.vz
			movups xmm2, [edi + 32]				//m2.vz
			movups xmm7, [esi + 48]				//m1.pos
			movups xmm3, [edi + 48]				//m2.pos
			mulps  xmm6, xmm0					//m1.vz*w
			mulps  xmm2, xmm1					//m2.vz*(1 - w)
			mulps  xmm7, xmm0					//m1.pos*w
			mulps  xmm3, xmm1					//m2.pos*(1 - w)
			addps  xmm6, xmm2					//m1.vx*w + m2.vx*(1 - w)
			addps  xmm7, xmm3					//m1.vy*w + m2.vy*(1 - w)
			movss  xmm0, [eax + 0]				//000x
			movss  xmm1, [eax + 4]				//000y
			movss  xmm2, [eax + 8]				//000z
			shufps xmm0, xmm0, 01000000b		//0xxx
			shufps xmm1, xmm1, 01000000b		//0yyy
			shufps xmm2, xmm2, 01000000b		//0zzz
			mulps  xmm0, xmm4					//0xxx*m.vx
			mulps  xmm1, xmm5					//0yyy*m.vy
			mulps  xmm2, xmm6					//0zzz*m.vz
			addps  xmm0, xmm7					//0xxx*m.vx + m.pos
			addps  xmm1, xmm2					//0yyy*m.vx + 0zzz*m.vx
			movss  xmm2, [eax + 28]				//000z
			addps  xmm0, xmm1					//0xxx*m.vx + m.pos + 0yyy*m.vx + 0zzz*m.vx
			movups [ebx + 0], xmm0				//��������� �������
			shufps xmm2, xmm2, 01000000b		//0zzz
			movss  xmm0, [eax + 20]				//000x
			movss  xmm1, [eax + 24]				//000y
			mov    ecx, [eax + 36]				//vrt.tu0
			mov    edx, [eax + 40]				//vrt.tv0
			shufps xmm0, xmm0, 01000000b		//0xxx
			shufps xmm1, xmm1, 01000000b		//0yyy
			mov    [ebx + 28], ecx				//��������� u
			mulps  xmm0, xmm4					//0xxx*m.vx
			mov    [ebx + 32], edx				//��������� v
			mulps  xmm1, xmm5					//0yyy*m.vy
			mulps  xmm2, xmm6					//0zzz*m.vz
			addps  xmm0, xmm7					//0xxx*m.vx + m.pos
			addps  xmm1, xmm2					//0yyy*m.vx + 0zzz*m.vx
			mov    ecx, [eax + 32]				//vrt.color
			addps  xmm0, xmm1					//0xxx*m.vx + m.pos + 0yyy*m.vx + 0zzz*m.vx
			movups [ebx + 12], xmm0				//��������� �������
			mov    [ebx + 24], ecx				//��������� color
			add    eax, 44
			add    ebx, 36
			dec    totVerts
			jnz    vrt_loop
		};
*/
//}else{

	CMatrix mtx;
	for(long v=0; v<totVerts; v++)
	{
		//�������
		GEOS::AVERTEX0 & vrt = src[v];
		GEOS::VERTEX0 & dstVrt = dst[v];
		//�������
		CMatrix & m1 = bones[vrt.boneid & 0xff];
		CMatrix & m2 = bones[(vrt.boneid >> 8) & 0xff];
		//��������� ���������� ���������
		float wNeg = 1.0f - vrt.weight;
		mtx.matrix[0] = -(m1.matrix[0]*vrt.weight + m2.matrix[0]*wNeg);
		mtx.matrix[1] = m1.matrix[1]*vrt.weight + m2.matrix[1]*wNeg;
		mtx.matrix[2] = m1.matrix[2]*vrt.weight + m2.matrix[2]*wNeg;
		mtx.matrix[4] = -(m1.matrix[4]*vrt.weight + m2.matrix[4]*wNeg);
		mtx.matrix[5] = m1.matrix[5]*vrt.weight + m2.matrix[5]*wNeg;
		mtx.matrix[6] = m1.matrix[6]*vrt.weight + m2.matrix[6]*wNeg;
		mtx.matrix[8] = -(m1.matrix[8]*vrt.weight + m2.matrix[8]*wNeg);
		mtx.matrix[9] = m1.matrix[9]*vrt.weight + m2.matrix[9]*wNeg;
		mtx.matrix[10] = m1.matrix[10]*vrt.weight + m2.matrix[10]*wNeg;
		mtx.matrix[12] = -(m1.matrix[12]*vrt.weight + m2.matrix[12]*wNeg);
		mtx.matrix[13] = m1.matrix[13]*vrt.weight + m2.matrix[13]*wNeg;
		mtx.matrix[14] = m1.matrix[14]*vrt.weight + m2.matrix[14]*wNeg;
		//�������
		((CVECTOR &)dstVrt.pos) = mtx*(CVECTOR &)vrt.pos;
		//�������
		((CVECTOR &)dstVrt.nrm) = mtx*(CVECTOR &)vrt.nrm;
		//���������
		dstVrt.color = vrt.color;
		dstVrt.tu = vrt.tu0;
		dstVrt.tv = vrt.tv0;
	}
//}
	dest_vb->Unlock();
	return dest_vb;
}

void SetChildrenTechnique(NODE *_root, const char *_name)
{
	if (!_root || !_name)
		return;
	_root->SetTechnique(_name);
	for (int i=0; i<_root->nnext; i++)
		SetChildrenTechnique(_root->next[i],_name);
}

//-----------------------------------------------------------------------------------
//realize
//-----------------------------------------------------------------------------------
GEOS::PLANE ViewPlane[4];
void MODELR::Realize(dword Delta_Time)
{
	GUARD(MODELR::Realize)
	if(!root) return;

	dword dwOldFogEnable;
	float fOldFogDensity;
	if (bSetupFog)
	{
		rs->GetRenderState(D3DRS_FOGENABLE, &dwOldFogEnable);
		rs->GetRenderState(D3DRS_FOGDENSITY, (dword*)&fOldFogDensity);

		rs->SetRenderState(D3DRS_FOGENABLE, (bFogEnable) ? true : false);
		rs->SetRenderState(D3DRS_FOGDENSITY, F2DW(fFogDensity));
	}

	if(renderTuner) renderTuner->Set(this, rs);

	if (useBlend)
	{
		if (!passedTime)
			SetChildrenTechnique(root, blendTechnique);

		passedTime += Delta_Time;
		/*
		if (passedTime > blendTime)
			useBlend = false;
		else
		*/
		{
			static dword ambient;
			rs->GetRenderState(D3DRS_AMBIENT, &ambient);
			ambient &= 0x00FFFFFF;
			float timeK = ((float) passedTime)/blendTime;
			if (timeK > 1.0f)
				timeK = 1.0f;
			float alpha = alpha1+(alpha2-alpha1)*timeK;
			ambient |= ((unsigned char) (255.0*alpha)) << 24;
			//ambient |= 0x05 << 24;
			rs->SetRenderState(D3DRS_TEXTUREFACTOR, ambient);
		}
	}

	CMatrix view, proj;
	rs->GetTransform(D3DTS_VIEW, view);
	rs->GetTransform(D3DTS_PROJECTION, proj);
	FindPlanes(view, proj);

	CVECTOR tmp;
	root->Update(mtx, tmp);

	//if have animation - special render
	if(ani)
	{
		//create VB
		if(d3dDestVB==0)
		{
			//calculate total number of vertices
			GEOS::INFO gi;
			root->geo->GetInfo(gi);
			nAniVerts = 0;
			for(long vb=0; vb<gi.nvrtbuffs; vb++)
			{
				long avb = root->geo->GetVertexBuffer(vb);
				VGEOMETRY::ANIMATION_VB gavb = GeometyService->GetAnimationVBDesc(avb);
				nAniVerts += gavb.nvertices;
			}

			long fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE  | D3DFVF_TEXTUREFORMAT2| D3DFVF_TEX1;
			rs->CreateVertexBuffer(sizeof(GEOS::VERTEX0)*nAniVerts, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, fvf, D3DPOOL_DEFAULT, &d3dDestVB);
		}
		dest_vb = d3dDestVB;

		alreadyTransformed = true;
		for(long i = 0; i < 2; i++)
		{
			if(ani->Player(i).IsPlaying())
			{
				float ap = ani->Player(i).GetPosition();
				if(aniPos[i] != ap) alreadyTransformed = false;
				aniPos[i] = ap;
			}else{
				if(aniPos[i] != -1.0f) alreadyTransformed = false;
				aniPos[i] = -1.0f;
			}
		}

		GeometyService->SetVBConvertFunc(VBTransform);

		bones = &ani->GetAnimationMatrix(0);
		root->Draw();
		GeometyService->SetVBConvertFunc(0);
		if(!alreadyTransformed)
		{
			aniPos[0] = -2.0f;
			aniPos[1] = -2.0f;
		}
	}else root->Draw();

	if(renderTuner) renderTuner->Restore(this, rs);

	if (bSetupFog)
	{
		rs->SetRenderState(D3DRS_FOGENABLE, dwOldFogEnable);
		rs->SetRenderState(D3DRS_FOGDENSITY, F2DW(fOldFogDensity));
	}

	UNGUARD
}

Animation * MODELR::GetAnimation()
{
	return ani;
}


void MODELR::AniRender()
{
}


dword _cdecl MODELR::ProcessMessage(MESSAGE &message)
{
	char str[256];
	long code = message.Long();
	CVECTOR tmp;
	switch (code)
	{
		case MSG_SEA_REFLECTION_DRAW:
			Realize(0);
		break;
		case MSG_MODEL_SET_PARENT:
		{
			/*ENTITY_ID ParentID = message.EntityID();
			if (_CORE_API->ValidateEntity(&ParentID))
			{
				parent = (MODEL*)ParentID.pointer;
			}*/
		}
		break;
		case MSG_MODEL_SET_POSITION:
			{ //Pos,vx,vy,vz
				CVECTOR & vx = mtx.Vx();
				CVECTOR & vy = mtx.Vy();
				CVECTOR & vz = mtx.Vz();
				CVECTOR & vpos = mtx.Pos();

				vpos.x = message.Float();
				vpos.y = message.Float();
				vpos.z = message.Float();

				vx.x = message.Float();
				vx.y = message.Float();
				vx.z = message.Float();

				vy.x = message.Float();
				vy.y = message.Float();
				vy.z = message.Float();

				vz.x = message.Float();
				vz.y = message.Float();
				vz.z = message.Float();
			}
			break;
		case MSG_MODEL_BLEND:
			// blendTechnique, time, a1, a2
			useBlend = true;
			passedTime = 0;
			message.String(128, blendTechnique);
			blendTime = message.Long();
			alpha1 = message.Float();
			alpha2 = message.Float();
			break;
		case MSG_MODEL_LOAD_GEO:		// set geometry
			GUARD(MSG_MODEL_LOAD_GEO)

#ifndef _XBOX
			message.String(255,str);
			NODER::gs = GeometyService;
			NODER::rs = rs;
			root = NEW NODER();
			if(!root->Init(LightPath, str, "", CMatrix(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f), mtx, null, lmPath))
			{
				delete root;
				root = null;
				api->DeleteEntity(GetID());
				api->fio->SetDrive();
				return 0;
			}
			//CVECTOR tmp;
			root->Update(mtx, tmp);
			return 1;
#else
			//api->fio->SetDrive(XBOXDRIVE_CACHE);	// look in cache
			message.String(255,str);
			NODER::gs = GeometyService;
			NODER::rs = rs;
			root = NEW NODER();

			if(!root->Init(LightPath, str, "", CMatrix(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f), mtx, null, lmPath))
			{
				api->fio->SetDrive();	// try on dvd
				if(!root->Init(LightPath, str, "", CMatrix(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f), mtx, null, lmPath))
				{
					delete root;
					root = null;
					api->DeleteEntity(GetID());
					api->fio->SetDrive();
					return 0;
				}
			}

			root->Update(mtx, tmp);
			api->fio->SetDrive();
			return 1;

#endif
			UNGUARD
		break;
		case MSG_MODEL_LOAD_ANI:		// set animation
		{
			message.String(255,str);
			AnimationService * asr = (AnimationService *)_CORE_API->CreateService("AnimationServiceImp");
			ani = asr->CreateAnimation(str);
			if(ani) return 1;
			return 0;
		}
		break;
		case MSG_MODEL_SET_FOG:
			bSetupFog = message.Long() != 0;
			bFogEnable = message.Long() != 0;
			fFogDensity = message.Float();
		break;
		case MSG_MODEL_SET_LIGHT_PATH:
			GUARD(MSG_MODEL_SET_LIGHT_PATH)
			message.String(255,LightPath);
			UNGUARD
		break;
		case MSG_MODEL_SET_LIGHT_LMPATH:
			GUARD(MSG_MODEL_SET_LIGHT_LMPATH)
			message.String(255,lmPath);
			UNGUARD
		break;
		case MSG_MODEL_RELEASE:
			GUARD(MSG_MODEL_RELEASE)
			if(root) root->ReleaseGeometry();
			UNGUARD
			break;
		case MSG_MODEL_RESTORE:
			GUARD(MSG_MODEL_RESTORE)
			if(root) root->RestoreGeometry();
			UNGUARD
			break;
		case MSG_MODEL_SET_DIRPATH:
			{
				message.String(255,str);
				GeometyService->SetTexturePath(str);
			}
			break;
		case MSG_MODEL_SET_TECHNIQUE:
			{
				message.String(255,str);
			if (root)
				SetChildrenTechnique(root, str);
			}
			break;
		case MSG_MODEL_SET_MAX_VIEW_DIST:
			if( root ) root->SetMaxViewDist( message.Float() );
			break;
	}
	return 1;
}


NODE *MODELR::GetNode(long n)
{
	return root->GetNode(n);
}
NODE *MODELR::FindNode(const char *cNodeName)
{
	return root->FindNode(cNodeName);
}

void MODELR::Update()
{
	CVECTOR tmp;
	static_cast<NODER*>(root)->Update(mtx, tmp);
}

//-------------------------------------------------------------------
//clip functions
//-------------------------------------------------------------------
const PLANE *clip_p;
const CVECTOR *clip_c;
float clip_r;
ADD_POLYGON_FUNC clip_ap;
GEOS::ADD_POLYGON_FUNC clip_geosap;
long clip_nps;

bool _cdecl AddPolygon(const GEOS::VERTEX *vr, long nv);
//-------------------------------------------------------------------
bool MODELR::Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly)
{
	clip_p = planes;
	clip_nps = nplanes;
	clip_c = &center;
	clip_r = radius;
	clip_ap = addpoly;
	if(clip_ap==0)	clip_geosap = 0;	else	clip_geosap = AddPolygon;
	return root->Clip();
}
extern NODE *bestTraceNode;
//-------------------------------------------------------------------
const char *MODELR::GetCollideMaterialName()
{
	GEOS::TRACE_INFO ti;
	if(colideNode->geo->GetCollisionDetails(ti)==false)	return "";
	GEOS::OBJECT go;
	colideNode->geo->GetObj(ti.obj, go);
	static GEOS::MATERIAL gm;
	colideNode->geo->GetMaterial(go.material, gm);
	return gm.name;
}
//-------------------------------------------------------------------
bool MODELR::GetCollideTriangle(TRIANGLE &triangle)
{
	GEOS::TRACE_INFO ti;
	if(colideNode->geo->GetCollisionDetails(ti)==false)	return false;
	triangle.vrt[0] = colideNode->glob_mtx*CVECTOR(ti.vrt[0].x, ti.vrt[0].y, ti.vrt[0].z);
	triangle.vrt[1] = colideNode->glob_mtx*CVECTOR(ti.vrt[1].x, ti.vrt[1].y, ti.vrt[1].z);
	triangle.vrt[2] = colideNode->glob_mtx*CVECTOR(ti.vrt[2].x, ti.vrt[2].y, ti.vrt[2].z);
	return true;
}

//-------------------------------------------------------------------
CVECTOR cold[8192];
float MODELR::Trace(const CVECTOR &src, const CVECTOR &dst)
{
	//collision with skinned geometry
	if(ani)
	{
		//check for bounding spheres intersection
		CVECTOR lmn = dst - src;
		float dist2ray2 = ~((root->glob_mtx*root->center - src)^lmn);
		float dlmn = ~(lmn);
		//hierarchy test
		if(dist2ray2 > dlmn*root->radius*root->radius)	return 2.0f;
		//if(GetAsyncKeyState(0xC0)>=0)	return 2.0f;
		//if(GetAsyncKeyState(VK_SHIFT)<0 && dist2ray2 > dlmn*root->radius*root->radius)	return 2.0f;

		//get bones
		bones = &ani->GetAnimationMatrix(0);

		CVECTOR _src, _dst;
		root->glob_mtx.MulToInv(src, _src);
		root->glob_mtx.MulToInv(dst, _dst);
		CVECTOR dirvec = _dst - _src;

		float bd = 2.0f;
		GEOS::INFO gi;

		//load indices
		if(idxBuff==0)
		{
			unsigned short *idx = (unsigned short*)rs->LockIndexBuffer(root->geo->GetIndexBuffer());

			int nt = 0;
			root->geo->GetInfo(gi);
			for(long vb=0; vb<gi.nvrtbuffs; vb++)
			{
				long avb = root->geo->GetVertexBuffer(vb);
				VGEOMETRY::ANIMATION_VB gavb = GeometyService->GetAnimationVBDesc(avb);
				GEOS::AVERTEX0 *gsrc = (GEOS::AVERTEX0*)gavb.buff;

				//for all objects that refers to this vertexBuffer
				for(long o=0; o<gi.nobjects; o++)
				{
					GEOS::OBJECT go;
					root->geo->GetObj(o, go);
					if(go.vertex_buff!=(unsigned long)avb)	continue;

					nt += go.ntriangles;
				}
			}

			idxBuff = NEW unsigned short[nt*3];
			for(long vb=0; vb<gi.nvrtbuffs; vb++)
			{
				long avb = root->geo->GetVertexBuffer(vb);
				VGEOMETRY::ANIMATION_VB gavb = GeometyService->GetAnimationVBDesc(avb);
				GEOS::AVERTEX0 *gsrc = (GEOS::AVERTEX0*)gavb.buff;

				//for all objects that refers to this vertexBuffer
				for(long o=0; o<gi.nobjects; o++)
				{
					GEOS::OBJECT go;
					root->geo->GetObj(o, go);
					if(go.vertex_buff!=(unsigned long)avb)	continue;

					//for all triangles in object
					for(long gt=0; gt<go.ntriangles; gt++)
					{
						long t = gt*3 + go.striangle;
						//Tomas Moller and Ben Trumbore algorithm
						idxBuff[t + 0] = idx[t + 0];
						idxBuff[t + 1] = idx[t + 1];
						idxBuff[t + 2] = idx[t + 2];
					}
				}
			}
			rs->UnLockIndexBuffer(root->geo->GetIndexBuffer());
		}



		root->geo->GetInfo(gi);
		for(long vb=0; vb<gi.nvrtbuffs; vb++)
		{
			long avb = root->geo->GetVertexBuffer(vb);
			VGEOMETRY::ANIMATION_VB gavb = GeometyService->GetAnimationVBDesc(avb);
			GEOS::AVERTEX0 *gsrc = (GEOS::AVERTEX0*)gavb.buff;

			//transform vertices and trace
			for(long v=0; v<gavb.nvertices; v++)
			{
				cold[v] = *(CVECTOR *)(&gsrc->pos);
				CMatrix & m1 = bones[gsrc->boneid & 0xff];
				CMatrix & m2 = bones[(gsrc->boneid >> 8) & 0xff];

				CVECTOR pos(*(CVECTOR *)(&gsrc->pos));
				CVECTOR v1 = m1*pos;
				CVECTOR v2 = m2*pos;
				cold[v].x = -(gsrc->weight*v1.x + (1.0f - gsrc->weight)*v2.x);
				cold[v].y = gsrc->weight*v1.y + (1.0f - gsrc->weight)*v2.y;
				cold[v].z = gsrc->weight*v1.z + (1.0f - gsrc->weight)*v2.z;
				gsrc++;
			}

			//for all objects that refers to this vertexBuffer
			for(long o=0; o<gi.nobjects; o++)
			{
				GEOS::OBJECT go;
				root->geo->GetObj(o, go);
				if(go.vertex_buff!=(unsigned long)avb)	continue;

				//for all triangles in object
				for(long gt=0; gt<go.ntriangles; gt++)
				{
					long t = gt*3 + go.striangle;
					//Tomas Moller and Ben Trumbore algorithm
					CVECTOR a = cold[idxBuff[t + 1] + go.start_vertex] - cold[idxBuff[t + 0] + go.start_vertex];
					CVECTOR b = cold[idxBuff[t + 2] + go.start_vertex] - cold[idxBuff[t + 0] + go.start_vertex];
					CVECTOR pvec = dirvec^b;
					float det = a|pvec;
					float invdet = 1.0f/det;

					CVECTOR c = _src - cold[idxBuff[t + 0] + go.start_vertex];
					float U = (c|pvec)*invdet;
					if(U<0.0f || U>1.0)	continue;

					CVECTOR qvec = c^a;
					float V = (dirvec|qvec)*invdet;
					if(V<0.0f || U+V>1.0)	continue;

					float d = (b|qvec)*invdet;
					if(d>=0.0f && d<=1.0 && d<bd)
					{
						bd = d;
					}
				}
			}

		}

		return bd;
	}
	float d = root->Trace(src, dst);
	colideNode = bestTraceNode;
	return d;
}

//-------------------------------------------------------------------
NODE *MODELR::GetCollideNode()
{
	return colideNode;
}

void MODELR::FindPlanes(const CMatrix &view, const CMatrix &proj)
{
	CVECTOR v[4];
	//left
	v[0].x = proj.m[0][0]; v[0].y = 0.0f; v[0].z = 1.0f;
	//right
	v[1].x = -proj.m[0][0]; v[1].y = 0.0f; v[1].z = 1.0f;
	//top
	v[2].x = 0.0f; v[2].y = -proj.m[1][1]; v[2].z = 1.0f;
	//bottom
	v[3].x = 0.0f; v[3].y = proj.m[1][1]; v[3].z = 1.0f;
	v[0] = !v[0];
	v[1] = !v[1];
	v[2] = !v[2];
	v[3] = !v[3];

	CVECTOR pos;

	pos.x = -view.m[3][0]*view.m[0][0] - view.m[3][1]*view.m[0][1] - view.m[3][2]*view.m[0][2];
	pos.y = -view.m[3][0]*view.m[1][0] - view.m[3][1]*view.m[1][1] - view.m[3][2]*view.m[1][2];
	pos.z = -view.m[3][0]*view.m[2][0] - view.m[3][1]*view.m[2][1] - view.m[3][2]*view.m[2][2];

	ViewPlane[0].nrm.x = v[0].x*view.m[0][0] + v[0].y*view.m[0][1] + v[0].z*view.m[0][2];
	ViewPlane[0].nrm.y = v[0].x*view.m[1][0] + v[0].y*view.m[1][1] + v[0].z*view.m[1][2];
	ViewPlane[0].nrm.z = v[0].x*view.m[2][0] + v[0].y*view.m[2][1] + v[0].z*view.m[2][2];

	ViewPlane[1].nrm.x = v[1].x*view.m[0][0] + v[1].y*view.m[0][1] + v[1].z*view.m[0][2];
	ViewPlane[1].nrm.y = v[1].x*view.m[1][0] + v[1].y*view.m[1][1] + v[1].z*view.m[1][2];
	ViewPlane[1].nrm.z = v[1].x*view.m[2][0] + v[1].y*view.m[2][1] + v[1].z*view.m[2][2];

	ViewPlane[2].nrm.x = v[2].x*view.m[0][0] + v[2].y*view.m[0][1] + v[2].z*view.m[0][2];
	ViewPlane[2].nrm.y = v[2].x*view.m[1][0] + v[2].y*view.m[1][1] + v[2].z*view.m[1][2];
	ViewPlane[2].nrm.z = v[2].x*view.m[2][0] + v[2].y*view.m[2][1] + v[2].z*view.m[2][2];

	ViewPlane[3].nrm.x = v[3].x*view.m[0][0] + v[3].y*view.m[0][1] + v[3].z*view.m[0][2];
	ViewPlane[3].nrm.y = v[3].x*view.m[1][0] + v[3].y*view.m[1][1] + v[3].z*view.m[1][2];
	ViewPlane[3].nrm.z = v[3].x*view.m[2][0] + v[3].y*view.m[2][1] + v[3].z*view.m[2][2];

	ViewPlane[0].nrm.x = -ViewPlane[0].nrm.x;	ViewPlane[0].nrm.y = -ViewPlane[0].nrm.y;	ViewPlane[0].nrm.z = -ViewPlane[0].nrm.z;
	ViewPlane[1].nrm.x = -ViewPlane[1].nrm.x;	ViewPlane[1].nrm.y = -ViewPlane[1].nrm.y;	ViewPlane[1].nrm.z = -ViewPlane[1].nrm.z;
	ViewPlane[2].nrm.x = -ViewPlane[2].nrm.x;	ViewPlane[2].nrm.y = -ViewPlane[2].nrm.y;	ViewPlane[2].nrm.z = -ViewPlane[2].nrm.z;
	ViewPlane[3].nrm.x = -ViewPlane[3].nrm.x;	ViewPlane[3].nrm.y = -ViewPlane[3].nrm.y;	ViewPlane[3].nrm.z = -ViewPlane[3].nrm.z;

	ViewPlane[0].d = (pos.x*ViewPlane[0].nrm.x + pos.y*ViewPlane[0].nrm.y + pos.z*ViewPlane[0].nrm.z);
	ViewPlane[1].d = (pos.x*ViewPlane[1].nrm.x + pos.y*ViewPlane[1].nrm.y + pos.z*ViewPlane[1].nrm.z);
	ViewPlane[2].d = (pos.x*ViewPlane[2].nrm.x + pos.y*ViewPlane[2].nrm.y + pos.z*ViewPlane[2].nrm.z);
	ViewPlane[3].d = (pos.x*ViewPlane[3].nrm.x + pos.y*ViewPlane[3].nrm.y + pos.z*ViewPlane[3].nrm.z);

}

void MODELR::LostRender()
{
	rs->Release(d3dDestVB);
}

void MODELR::RestoreRender()
{
	long fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE  | D3DFVF_TEXTUREFORMAT2| D3DFVF_TEX1;
	if (nAniVerts) rs->CreateVertexBuffer(sizeof(GEOS::VERTEX0) * nAniVerts, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, fvf, D3DPOOL_DEFAULT, &d3dDestVB);
}