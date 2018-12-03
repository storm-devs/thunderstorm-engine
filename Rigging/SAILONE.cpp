// SAILONE.cpp: implementation of the SAILONE class.
//
//////////////////////////////////////////////////////////////////////

#include "SAILONE.h"
#include "..\\common_h\defines.h"
#include "..\common_h\Matrix.h"
#include "..\common_h\model.h"
#include "..\common_h\sail_base.h"
#include "..\common_h\sd2_h\VAI_ObjBase.h"
#include "rigging_define.h"
#include "sail.h"

extern long g_iBallOwnerIdx;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SAILONE::SAILONE()
{
    RenderService = nullptr;

    ZERO(tm);
    ZERO(ss);
    ZERO(sgeo);
    ZERO(sailWind);
    ZERO(sailtrope);
    ZERO(SailPnt);
    WindUp=0;
    wind_incr=1; // ����� ������� ������� ������ ���������� � �������
    wind_add=1;  // ������ �� 1
    VertIdx=0;
    SumWind=0;
    sroll=nullptr;
    sailWidth=0;
    sailHeight=0;
    pMatWorld=nullptr;
    pp=nullptr;
    oldWindAngl=0;
    MaxSumWind=0;
    maxSpeed=0;
    mastNum=0;
    m_dwRow=0;
    m_dwCol=0;
    HostNum=0;
    hostNode=nullptr;
    HorzIdx=0;
    groupNum=0;
    curSpeed=0;
    bRolling=false;
    bFreeSail=false;
	bDeleted=false;

	surfaceTex = -1;

	ss.bYesLimitPoint = false;

	m_bIsGerald = false;
	m_nGeraldTex = -1;
	m_pGeraldTex = nullptr;

	m_fHorzGeraldScale = 1.f;
	m_fVertGeraldScale = 1.f;
}

SAILONE::~SAILONE()
{
	ROPE_BASE * prb = nullptr;
	ENTITY_ID eid;
	if( api->FindClass(&eid,"ROPE",0) )	prb = (ROPE_BASE*)eid.pointer;
	if( prb!= nullptr && (sailtrope.pnttie[0] || sailtrope.pnttie[1] || sailtrope.pnttie[2] || sailtrope.pnttie[3]) )
		prb->DoDeleteUntie(pp->gdata[HostNum].modelEI,hostNode,groupNum);

    PTR_STORM_DELETE(sroll);
    PTR_STORM_DELETE(sailtrope.rrs[0]);
    PTR_STORM_DELETE(sailtrope.rrs[1]);
	TEXTURE_RELEASE(pp->RenderService,surfaceTex);
	TEXTURE_RELEASE(pp->RenderService,m_nGeraldTex);
	RELEASE( m_pGeraldTex );
}

void SAILONE::goWave(SAILVERTEX* pv,DWORD Delta_Time)
{
    bool trigger=false;

    if( ss.eSailType==SAIL_TREANGLE )
    {
        wind_incr=pp->WINDVECTOR_TINCR;
        wind_add= (int)((float)pp->WINDVECTOR_TADD*(float)Delta_Time*.02f);
        while(wind_incr>=pp->WINDVECTOR_QUANTITY) wind_incr-=pp->WINDVECTOR_QUANTITY;
        while(wind_add>=pp->WINDVECTOR_QUANTITY) wind_add-=pp->WINDVECTOR_QUANTITY;

        // ����������� ������ ��������� �� ���
        if(bRolling)
            DoTRollSail(pv);
        // �������� ������� ������
        else if(bFreeSail)
            DoTFreeSail(pv);
        else
            GoTWave(pv);
    }
    else
    {
        wind_incr=pp->WINDVECTOR_SINCR;
        wind_add=(int)((float)pp->WINDVECTOR_SADD*(float)Delta_Time*.02f);
        while(wind_incr>=pp->WINDVECTOR_QUANTITY) wind_incr-=pp->WINDVECTOR_QUANTITY;
        while(wind_add>=pp->WINDVECTOR_QUANTITY) wind_add-=pp->WINDVECTOR_QUANTITY;

        // ������������� ������ ��������� �� ���
        if(bRolling)
            DoSRollSail(pv);

        // �������� ������� ������
        else if(bFreeSail)
            DoSFreeSail(pv);

        // ������������� ������������� ������
        else
        {
            // ���������� ������
            GoVWave(pv);

            if((HorzIdx+=wind_add)>=pp->WINDVECTOR_QUANTITY) HorzIdx-=pp->WINDVECTOR_QUANTITY;
            VertIdx=HorzIdx;
            if(!sroll)
            {
                float delta=(float)Delta_Time*pp->FLEXSPEED;
                if(WindUp)
                {
                    SumWind-=delta;
                    if(SumWind<-MaxSumWind)
                    {
                        SumWind=-MaxSumWind;
                        WindUp=false;
                    }
                }
                else
                {
                    SumWind+=delta;
                    if(SumWind>MaxSumWind)
                    {
                        SumWind=MaxSumWind;
                        WindUp=true;
                    }
                }
            }
        }
    }

    // ������ �����
    int pn=20;
    if(ss.eSailType==SAIL_TREANGLE) pn=15;
    ss.boxCenter = ss.boxSize = SailPnt[0];
    for(int i=1; i<pn; i++)
    {
        if( SailPnt[i].x<ss.boxCenter.x) ss.boxCenter.x=SailPnt[i].x;
        if( SailPnt[i].y<ss.boxCenter.y) ss.boxCenter.y=SailPnt[i].y;
        if( SailPnt[i].z<ss.boxCenter.z) ss.boxCenter.z=SailPnt[i].z;
        if( SailPnt[i].x>ss.boxSize.x) ss.boxSize.x=SailPnt[i].x;
        if( SailPnt[i].y>ss.boxSize.y) ss.boxSize.y=SailPnt[i].y;
        if( SailPnt[i].z>ss.boxSize.z) ss.boxSize.z=SailPnt[i].z;
    }
    ss.boxCenter = (ss.boxCenter+ss.boxSize)*.5f;
    ss.boxSize -= ss.boxCenter;
}

// ��������� �������
void SAILONE::FillIndex(WORD* pt)
{
    int   xIdxNum,yIdxNum;
    int   idx,iy,ix,jx,jy,cix,ciy,dix;
    int   holeI;
    int   holeStart,noholeStart;
    DWORD rtm;
    bool  ishole;
    int   xIdx[5],yIdx[5];
    int   tmpx,tmpy;

	RDTSC_B(rtm);
    switch(m_dwCol)
    {
        case 13:
            xIdx[0]=0; xIdx[1]=SAIL_ROW_MAX; xIdx[2]=SAIL_ROW_MAX*2; xIdx[3]=SAIL_ROW_MAX*3; xIdx[4]=SAIL_ROW_MAX*4;
            xIdxNum=4;
            break;
        case 10:
            xIdx[0]=0; xIdx[1]=SAIL_ROW_MAX; xIdx[2]=SAIL_ROW_MAX*3; xIdx[3]=SAIL_ROW_MAX*4;
            xIdxNum=3;
            break;
        case 7:
            xIdx[0]=0; xIdx[1]=SAIL_ROW_MAX*2; xIdx[2]=SAIL_ROW_MAX*4;
            xIdxNum=2;
            break;
        case 4:
            xIdx[0]=0; xIdx[1]=SAIL_ROW_MAX*4;
            xIdxNum=1;
            break;
    }
    switch(m_dwRow)
    {
        case 17:
            yIdx[0]=0; yIdx[1]=1; yIdx[2]=2; yIdx[3]=3; yIdx[4]=4;
            yIdxNum=4;
            break;
        case 13:
            yIdx[0]=0; yIdx[1]=1; yIdx[2]=3; yIdx[3]=4;
            yIdxNum=3;
            break;
        case 9:
            yIdx[0]=0; yIdx[1]=2; yIdx[2]=4;
            yIdxNum=2;
            break;
        case 5:
            yIdx[0]=0; yIdx[1]=4;
            yIdxNum=1;
            break;
    }

    holeI=idx=0;
    noholeStart=ss.sIndx;
    holeStart=ss.sIndx+ss.nIndx;

    if( pt )
    {
        if(bRolling && (ss.eSailType==SAIL_TREANGLE))
        {
            int v1=idx+6;
            int v2=idx+10;

            pt[noholeStart++]=v1;    pt[noholeStart++]=v2++;  pt[noholeStart++]=v2;
            pt[noholeStart++]=v1++;  pt[noholeStart++]=v2;    pt[noholeStart++]=v1;
            pt[noholeStart++]=v1;    pt[noholeStart++]=v2++;  pt[noholeStart++]=v2;
            pt[noholeStart++]=v1++;  pt[noholeStart++]=v2;    pt[noholeStart++]=v1;
            pt[noholeStart++]=v1;    pt[noholeStart++]=v2++;  pt[noholeStart++]=v2;
            pt[noholeStart++]=v1;    pt[noholeStart++]=v2++;  pt[noholeStart++]=v2;
            pt[noholeStart++]=v1++;  pt[noholeStart++]=v2;    pt[noholeStart++]=v1;
            v1++; v2+=22;
            int vd1=1; int vd2=2;

            for(ix=1; ix<4; ix++)
            {
                for(iy=0; iy<4; iy++)
                {
                    pt[noholeStart++]=v1;
                    pt[noholeStart++]=v2;
                    pt[noholeStart++]=v2+vd2;

                    pt[noholeStart++]=v1;
                    pt[noholeStart++]=v2+vd2;
                    pt[noholeStart++]=v1+vd1;

                    v1+=vd1; v2+=vd2;
                }

                vd1++; vd2++;
                v1+=ix*12+10;
                v2+=ix*12+22;
            }
        }
        // Fill indexes for triangle sail
        else if( ss.eSailType==SAIL_TREANGLE )
        {
            // Fill 2x2
            if(m_dwRow==3)
            {
                pt[noholeStart]=idx;
                pt[noholeStart+7]=pt[noholeStart+3]=pt[noholeStart+1]=idx+SAIL_ROW_MAX/2*(SAIL_ROW_MAX/2+1)/2;
                pt[noholeStart+9]=pt[noholeStart+6]=pt[noholeStart+2]=idx+SAIL_ROW_MAX/2*(SAIL_ROW_MAX/2+3)/2;
                pt[noholeStart+4]=idx+SAIL_ROW_MAX*(SAIL_ROW_MAX-1)/2;
                pt[noholeStart+10]=pt[noholeStart+8]=pt[noholeStart+5]=idx+SAIL_ROW_MAX*(SAIL_ROW_MAX-1)/2+SAIL_ROW_MAX/2;
                pt[noholeStart+11]=idx+(SAIL_ROW_MAX-1)*(SAIL_ROW_MAX+2)/2;

                noholeStart+=12;
            }
            // Fill from 4x4
            else
            {
                for(ix=0; ix<4; ix++)
                {
                    cix=ix*(SAIL_ROW_MAX/4);
                    for(iy=0; iy<=ix; iy++)
                    {
                        ishole=ss.hole[holeI];
                        holeI++;
                        ciy=(iy-1)*(SAIL_ROW_MAX/4);
                        idx=(cix*(cix+1))/2 + ciy;

                        for(jx=1;jx<=yIdxNum;jx++)
                        {
                            dix=cix*yIdx[jx]+(yIdx[jx]*(yIdx[jx]+3))/2;
                            tmpx=cix*yIdx[jx-1]+(yIdx[jx-1]*(yIdx[jx-1]+3))/2;
                            for(jy=1;jy<=yIdxNum;jy++)
                            {
                                tmpy=ciy+yIdx[jy]+yIdx[jx-1];
                                if(tmpy>0)
                                {
                                    if(ishole)
                                    {
                                        pt[holeStart-6]=pt[holeStart-3]=idx+yIdx[jy]+tmpx;
                                        pt[holeStart-2]=idx+yIdx[jy-1]+tmpx;
                                        pt[holeStart-5]=pt[holeStart-1]=idx+yIdx[jy-1]+dix;
                                        pt[holeStart-4]=idx+yIdx[jy]+dix;

                                        holeStart-=6;
                                    }
                                    else
                                    {
                                        pt[noholeStart+3]=pt[noholeStart]=idx+yIdx[jy]+tmpx;
                                        pt[noholeStart+1]=idx+yIdx[jy-1]+tmpx;
                                        pt[noholeStart+4]=pt[noholeStart+2]=idx+yIdx[jy-1]+dix;
                                        pt[noholeStart+5]=idx+yIdx[jy]+dix;

                                        noholeStart+=6;
                                    }
                                }
                                else if(tmpy==0)
                                {
                                    if(ishole)
                                    {
                                        pt[holeStart-3]=idx+yIdx[jy]+tmpx;
                                        pt[holeStart-2]=idx+yIdx[jy-1]+dix;
                                        pt[holeStart-1]=idx+yIdx[jy]+dix;

                                        holeStart-=3;
                                    }
                                    else
                                    {
                                        pt[noholeStart]=idx+yIdx[jy]+tmpx;
                                        pt[noholeStart+1]=idx+yIdx[jy-1]+dix;
                                        pt[noholeStart+2]=idx+yIdx[jy]+dix;

                                        noholeStart+=3;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // Fill indexes for square sail
        else
        {
            // Fill ?x2
            if( m_dwRow==3 )
            {
                for( ix=0; ix<(int)(m_dwCol-1); ix++ )
                {
                    pt[noholeStart]=idx;
                    pt[noholeStart+3]=pt[noholeStart+1]=idx+SAIL_ROW_MAX*(SAIL_COL_MAX/3);
                    pt[noholeStart+6]=pt[noholeStart+5]=pt[noholeStart+2]=idx+SAIL_ROW_MAX/2;
                    pt[noholeStart+9]=pt[noholeStart+7]=pt[noholeStart+4]=idx+SAIL_ROW_MAX*(SAIL_COL_MAX/3)+SAIL_ROW_MAX/2;
                    pt[noholeStart+11]=pt[noholeStart+8]=idx+SAIL_ROW_MAX-1;
                    pt[noholeStart+10]=idx+SAIL_ROW_MAX*(SAIL_COL_MAX/3)+SAIL_ROW_MAX-1;

                    idx+=SAIL_ROW_MAX*(SAIL_COL_MAX/3);
                    noholeStart+=12;
                }
            }
            // Fill from 3x4
            else
            {
                for( ix=0; ix<3; ix++ )
                    for( iy=0; iy<4; iy++ )
                    {
                        ishole=ss.hole[holeI];
                        holeI++;
                        idx = ix*((SAIL_COL_MAX/3)*SAIL_ROW_MAX) + iy*(SAIL_ROW_MAX/4);

                        for( jx=0; jx<xIdxNum; jx++ )
                            for( jy=0; jy<yIdxNum; jy++ )
                                if( ishole )
                                {
                                    pt[holeStart-6]=idx+xIdx[jx]+yIdx[jy];
                                    pt[holeStart-3]=pt[holeStart-5]=idx+xIdx[jx+1]+yIdx[jy];
                                    pt[holeStart-1]=pt[holeStart-4]=idx+xIdx[jx]+yIdx[jy+1];
                                    pt[holeStart-2]=idx+xIdx[jx+1]+yIdx[jy+1];

                                    holeStart-=6;
                                }
                                else
                                {
                                    pt[noholeStart]=idx+xIdx[jx]+yIdx[jy];
                                    pt[noholeStart+3]=pt[noholeStart+1]=idx+xIdx[jx+1]+yIdx[jy];
                                    pt[noholeStart+5]=pt[noholeStart+2]=idx+xIdx[jx]+yIdx[jy+1];
                                    pt[noholeStart+4]=idx+xIdx[jx+1]+yIdx[jy+1];

                                    noholeStart+=6;
                                }
                    }
            }
        }
        // set quantity of the holling and normal triangles
        ss.sholeIndx=holeStart;
        ss.nholeIndx=(ss.sIndx+ss.nIndx-holeStart)/3;
        ss.nnormIndx=(noholeStart-ss.sIndx)/3;
    }

    //_asm rdtsc	_asm sub eax,rtm	_asm mov rtm,eax
	RDTSC_E(rtm);
    tm.idx=rtm;
}

// ��������� �������� ��� ������
void SAILONE::FillVertex(SAILVERTEX *pv)
{
    WORD ix,iy,idx;
    CVECTOR pcur,dV,ddV,dddV;
    CVECTOR norm,dnorm;
    CVECTOR dStart;

    float tmpCol=1.f/(float)(SAIL_COL_MAX-1);
    float tmpRow=1.f/(float)(SAIL_ROW_MAX-1);

    CVECTOR pStart=ss.hardPoints[0];
    CVECTOR dVStart=sgeo.dVv;
    CVECTOR dVhStart=sgeo.dVh;

    if( ss.eSailType==SAIL_TREANGLE )
    {
        dStart=(ss.hardPoints[1]-pStart)*tmpRow;
        // ��������� ����� ����������� ��������
        dnorm=ss.boundSphere.c - sgeo.normL*ss.boundSphere.r;
        // ������� ������� ����� ������ � ������ �� ���
        //===============================================================
        for( idx=ix=0; ix<SAIL_ROW_MAX; ix++ )
        {
            // ��������� ���������� ��������� ����� � ���������� � ��� �� ������ ����
            pcur=pStart;
            dV=dVStart;

            // ������ ������ ����� ����� �������
            //|||||||||||||||||||||||||||||||||||
            for( iy=0; iy<=ix; iy++, idx++ )
            {
                // ������ ��������� � ����� ���������
                pv[idx].pos = pcur;
                pv[idx].norm = !(pcur-dnorm);
                // ������ ���������
                pcur+=dV;
            }
            pStart+=dStart;
            dVhStart+=sgeo.ddVh;
            dVStart+=dVhStart;
        }

        // ������ ��������� ����� ��������� ������
        pv[idx-SAIL_ROW_MAX].pos = ss.hardPoints[1];
        pv[idx-1].pos = ss.hardPoints[2];
    }
    else
    {
        dStart=(ss.hardPoints[1]-pStart)*tmpCol;
        dnorm=ss.boundSphere.c-sgeo.dnormL*ss.boundSphere.r;
		if(ss.eSailType == SAIL_TRAPECIDAL)
			dnorm=ss.boundSphere.c-sgeo.normL*ss.boundSphere.r;
        // ������� ������� ����� ������ � ������ �� ���
        //===============================================================
        for( idx=ix=0; ix<SAIL_COL_MAX; ix++ )
        {
            // ��������� ���������� ��������� ����� � ���������� � ��� �� ������ ����
            pcur=pStart;
            dV=dVStart;
            ddV=sgeo.ddVv;
            dddV=sgeo.dddVv;
            // ������ ������ ����� ����� �������
            //|||||||||||||||||||||||||||||||||||
            for( iy=0; iy<SAIL_ROW_MAX; iy++, idx++ )
            {
                // ������ ��������� � ����� ���������
                pv[idx].pos = pcur;
                pv[idx].norm = !(pcur-dnorm);
                // ������ ���������
                ddV+=dddV;
                dV+=ddV;
                pcur+=dV;
            }
            pStart+=dStart;
            dVhStart+=sgeo.ddVh;
            dVStart+=dVhStart;
        }

        // ������ ��������� ����� ��������� ������
        pv[idx-SAIL_ROW_MAX].pos = ss.hardPoints[1];
        pv[SAIL_ROW_MAX-1].pos = ss.hardPoints[2];
        pv[idx-1].pos = ss.hardPoints[3];
    }
}

void SAILONE::SetTexGrid(SAILVERTEX *pv)
{
    DWORD ix,iy,idx;
    float kx1,ky1,kx2,ky2,tvbeg1,tvbeg2;
    float tu1,tu2;

    /*ky=1.f/(float)(pp->texQuantity*(SAIL_ROW_MAX-1));
    switch(ss.eSailType)
    {
    case SAIL_TREANGLE:
        tvbeg=pp->texNumTreangle;
        break;
    case SAIL_SQUARE:
    case SAIL_TRAPECIDAL:
        tvbeg=pp->texNumCommon;
        break;
    case SAIL_GERBED:
        tvbeg=pp->texNumEnglish;
        break;
    }*/

    // ���������� ���������� ������� ��� ������������ ������
    if( ss.eSailType==SAIL_TREANGLE )
    {
		kx1 = 1.f/(float)(SAIL_ROW_MAX-1);
		ky1 = 1.f/(float)(SAIL_ROW_MAX-1);
		kx2 = .5f/(float)(SAIL_ROW_MAX-1);
		ky2 = .5f/(float)(SAIL_ROW_MAX-1);
		tvbeg1 = 0.f;
		tvbeg2 = .5f;
        for( ix=idx=0; ix<SAIL_ROW_MAX; ix++ )
        {
            tu1 = (float)ix*kx1;
            tu2 = (float)ix*kx2+1.f;
            for( iy=SAIL_ROW_MAX-ix-1; iy<SAIL_ROW_MAX; iy++,idx++ )
            {
                pv[idx].tu1 = tu1;
                pv[idx].tv1 = tvbeg1 + (float)iy*ky1;
				pv[idx].tu2 = (tu1-.75f)*m_fHorzGeraldScale + 0.5f;
				pv[idx].tv2 = (tvbeg1 + (float)iy*ky1 -.75f)*m_fVertGeraldScale + 0.5f;
				pv[idx].tu3 = tu2;
				pv[idx].tv3 = tvbeg2 + (float)iy*ky2;
            }
        }
    }
    // ��������� ��� �������������� ������
    else
    {
        kx1 = 1.f/(float)(SAIL_COL_MAX-1);
        ky1 = 1.f/(float)(SAIL_ROW_MAX-1);
        kx2 = .5f/(float)(SAIL_COL_MAX-1);
        ky2 = .5f/(float)(SAIL_ROW_MAX-1);
		tvbeg1 = 0.f;
		tvbeg2 = 0.f;
        for( ix=idx=0; ix<SAIL_COL_MAX; ix++ )
        {
            tu1=(float)ix*kx1;
            tu2=(float)ix*kx2+1.f;
            for( iy=0; iy<SAIL_ROW_MAX; iy++,idx++ )
            {
                pv[idx].tu1 = tu1;
                pv[idx].tv1 = tvbeg1 + (float)iy*ky1;
				pv[idx].tu2 = (tu1-.5f)*m_fHorzGeraldScale + 0.5f;
				pv[idx].tv2 = (tvbeg1 + (float)iy*ky1 - .5f)*m_fVertGeraldScale + 0.5f;
                pv[idx].tu3 = tu2;
                pv[idx].tv3 = tvbeg2 + (float)iy*ky2;
            }
        }
    }
}

void SAILONE::ClearVertex(SAILVERTEX* pv,DWORD maxIdx)
{
    DWORD idx;

    // Fill triangle buffer
    if( pv )
    {
        for( idx=0; idx<maxIdx; idx++ )
        {
            pv[idx].norm=CVECTOR(0.f,0.f,1.f);
            pv[idx].tu1=0;
            pv[idx].tv1=0;
            pv[idx].tu2=0;
            pv[idx].tv2=0;
			pv[idx].tu3=0;
			pv[idx].tv3=0;
            pv[idx].pos=CVECTOR(0.f,0.f,0.f);
        }
    }
}

bool SAILONE::SetSail()
{
    int hpq;

    // �� ��������� ��� ��������� ������ ��������
    sgeo.dopV=CVECTOR(0.f,0.f,0.f);

    // ���������� ���������� �������� � ����������� ������
    ss.maxAngle=PI/6.f; // ������������ ���� �������� ������ 30 ����.

    // ���������� ������� ������
    m_dwRow=SAIL_ROW_MAX;

    if( ss.eSailType==SAIL_TREANGLE )
    {
        hpq=10;
        m_dwCol=SAIL_ROW_MAX;
    }
    else
    {
        hpq=12;
        m_dwCol=SAIL_COL_MAX;
    }

    // ���������� ��������� �������� ��� �����
    VertIdx=rand()%pp->WINDVECTOR_QUANTITY;
    HorzIdx=rand()%pp->WINDVECTOR_QUANTITY;

    // ������ ������ � ������ ������
    if(ss.eSailType==SAIL_TREANGLE)
    {
        sailWidth=sqrtf(~(ss.hardPoints[2]-ss.hardPoints[0]));
        sailHeight=sqrtf(~(ss.hardPoints[1]-ss.hardPoints[2]));

        maxSpeed=sailWidth*sailHeight*.5f;
    }
    else
    {
        sailWidth=.5f*sqrtf(~(ss.hardPoints[0]+ss.hardPoints[2]-ss.hardPoints[1]-ss.hardPoints[3]));
        sailHeight=.5f*sqrtf(~(ss.hardPoints[0]+ss.hardPoints[1]-ss.hardPoints[2]-ss.hardPoints[3]));

        maxSpeed=sailWidth*sailHeight;
    }
    if(sailWidth<.1f || sailHeight<.1f) return false;

    // ���������� ������ � ������ ����� ������ � ���������� ������
    switch(ss.eSailType)
    {
    case SAIL_TREANGLE:
		if( ss.bYesLimitPoint )
			ss.fDeepZ = 0.5f * GetDistanceFromPointTo3Point( ss.LimitPoint, ss.hardPoints[0],ss.hardPoints[1],ss.hardPoints[2] );
		else
			ss.fDeepZ=.04f+.01f*(float)rand()/(float)RAND_MAX*sailHeight;
		ss.fDeepH=ss.fDeepZ;
        if(!ss.turningSail)
            ss.fDeepVh=.005f+.005f*(float)rand()/(float)RAND_MAX*sailWidth;
        else
            ss.fDeepVh=.0f;
        break;
    case SAIL_TRAPECIDAL:
		if( ss.bYesLimitPoint )
		{
			ss.fDeepZ = GetDistanceFromPointTo3Point( ss.LimitPoint, ss.hardPoints[0],ss.hardPoints[1],ss.hardPoints[2] );
			ss.fDeepH = sailWidth / (sailWidth+sailHeight+0.01f) * ss.fDeepZ;
			ss.fDeepZ *= sailHeight / (sailWidth+sailHeight+0.01f);
		}
		else
		{
			ss.fDeepZ=0.01f+.01f*(float)rand()/(float)RAND_MAX*sailHeight;
			ss.fDeepH=0.01f+.01f*(float)rand()/(float)RAND_MAX*sailWidth;
		}
        ss.fDeepVh=0.f;
        ss.fDeepVz=0.f;
        break;
    default:
		if( ss.bYesLimitPoint )
		{
			ss.fDeepZ = GetDistanceFromPointTo3Point( ss.LimitPoint, ss.hardPoints[0],ss.hardPoints[1],ss.hardPoints[2] );
			ss.fDeepH = sailWidth / (sailWidth+sailHeight+0.01f) * ss.fDeepZ;
			ss.fDeepZ *= sailHeight / (sailWidth+sailHeight+0.01f);
		}
		else
		{
			ss.fDeepZ=(.06f+.02f*(float)rand()/(float)RAND_MAX)*sailHeight;
			ss.fDeepH=(.06f+.02f*(float)rand()/(float)RAND_MAX)*sailWidth*.6f;
		}
        ss.fDeepVh=ss.fDeepZ*.1f;
        ss.fDeepVz=ss.fDeepZ*.1f;
    }

    // ��������� �������� ������ ������� � ��������
    if( ss.eSailType==SAIL_TREANGLE )
    {
        ss.nVert = (SAIL_ROW_MAX*(SAIL_ROW_MAX+1))/2;
        ss.nIndx = SQR(SAIL_ROW_MAX-1)*3;
    }
    else
    {
        ss.nVert = SAIL_ROW_MAX*SAIL_COL_MAX;
        ss.nIndx = 2*(SAIL_ROW_MAX-1)*(SAIL_COL_MAX-1)*3;
    }

    // ��������� �������� ������� ������
    ss.holeCount=0;
    for( int i=0; i<hpq; i++ )
    {
        ss.hole[i]=false;
        if( ss.hole[i] )
            ss.holeCount++;
    }
    CalculateMirrorSailIndex();

    // ��������� ���������� �����
    WindUp = (rand()&1)==1;
    MaxSumWind=sailHeight*pp->MAXSUMWIND;
    SumWind=MaxSumWind*(float)rand()/(float)RAND_MAX;

    oldWindAngl=0.f;

	// ���������� ����������� �� �������� ������
	m_fMaxAngle = pp->MAXTURNANGL;
	m_fMinAngle = pp->MAXTURNANGL;

    return true;
}

void SAILONE::releaseAll()
{
}

// ������� ����� �� ����������� �����
void SAILONE::GoTWave(SAILVERTEX *pv)
{
    int iy,ix,idx;

    float k=(sailWind.x*sgeo.normL.x + sailWind.y*sgeo.normL.y + sailWind.z*sgeo.normL.z);
    CVECTOR CenterFlex;
    if(k<0.f)
        CenterFlex=k*sgeo.normL*ss.fDeepH;
    else
        CenterFlex=k*sgeo.normL*ss.fDeepZ;

    CVECTOR pStart=ss.hardPoints[0];
    CVECTOR pStartDelta=(ss.hardPoints[1]-ss.hardPoints[0])/(float)(SAIL_ROW_MAX-1);

    float WindAmplitude=pp->TsailWindDepend*ss.boundSphere.r*(pp->globalWind.base+.3f)/(float)(SAIL_ROW_MAX-1)/(float)(SAIL_ROW_MAX-1);

    // ������ ��������� ������ � ������� ������
    WindAmplitude*=1.f-(float)ss.holeCount*pp->fTHoleFlexDepend;
    CenterFlex*=1.f-(float)ss.holeCount*pp->fTHoleFlexDepend;

    // Set rope point
    if(sailtrope.pnttie[0])
    {
        pStart+=WindAmplitude*sgeo.normL*pp->WindVect[VertIdx]*(float)SAIL_ROW_MAX;
        *sailtrope.pPos[0] = pStart;
    }

    int svNum=0;

    CVECTOR WindAdd,pcur,dV,ddV;
    for(ix=0; ix<SAIL_ROW_MAX;)
    {

        pcur=pStart;
        dV = sgeo.dVv + (float)ix*(sgeo.dVh+(float)(ix+1)*0.5f*sgeo.ddVh);
        WindAdd=(pp->WindVect[VertIdx]*WindAmplitude*(float)ix)*sgeo.normL+CenterFlex;
        dV+=WindAdd;
        if(sailtrope.pnttie[2])
            ddV = -WindAdd*1.8f/(float)(SAIL_ROW_MAX);
        else
            ddV = -WindAdd*2.f/(float)(SAIL_ROW_MAX);

        // Set rope point
        if(ix==SAIL_ROW_MAX-1)
            if(sailtrope.pnttie[1])
                *sailtrope.pPos[1] = pcur;

        idx=(ix*(ix+1))/2;
        // ������ ������ ����� ����� �������
        //|||||||||||||||||||||||||||||||||||
        for( iy=0; iy<=ix; iy++, idx++ )
        {
            // ������ ��������� � ����� ���������
            pv[idx].pos = pcur;

            // ���������� ������� ����� � ������� ��������� ������
            if(ix==0 || ix==4 || ix==8 || ix==12 || ix==16)
                if(iy==0 || iy==4 || iy==8 || iy==12 || iy==16)
                    SailPnt[svNum++]=pcur;

            // ������ ���������
            dV+=ddV;
            pcur+=dV;
        }

        if((VertIdx+=wind_incr)>=pp->WINDVECTOR_QUANTITY) VertIdx-=pp->WINDVECTOR_QUANTITY;

        switch(m_dwRow)
        {
        case 17:
            ix++;
            pStart+=pStartDelta;
            break;
        case 13:
            ix++;
            pStart+=pStartDelta;
            if((ix&3)==2)
            {
                ix++;
                pStart+=pStartDelta;
            }
            break;
        case 9:
            ix+=2;
            pStart+=pStartDelta+pStartDelta;
            break;
        case 5:
            ix+=4;
            pStart+=4.f*pStartDelta;
            break;
        case 3:
            ix+=8;
            pStart+=4.f*pStartDelta;
            break;
        }
    }

    // Set rope point
    if(sailtrope.pnttie[2])
        *sailtrope.pPos[2] = pcur-dV;

    if((HorzIdx+=wind_add)>=pp->WINDVECTOR_QUANTITY) HorzIdx-=pp->WINDVECTOR_QUANTITY;
    VertIdx=HorzIdx;
}

void SAILONE::GoVWave(SAILVERTEX *pv)
{
    WORD iy,ix,idx;
    CVECTOR pcur,dV,ddV,dddV;
    float k;
    bool trigger=false;

    float fWindBase=pp->globalWind.base;
    if(fWindBase>1.f) fWindBase=1.f;

    CVECTOR wind;
    wind.y=0;
    if(ss.eSailType==SAIL_TRAPECIDAL)
    {
        wind.x=fWindBase*.5f+0.1f;
        wind.z=wind.x*.2f;
    }
    else
    {
        wind.z=fWindBase*.5f+0.1f;
        wind.x=wind.z*.2f;
    }

    // ��������� �������� ������ ��� ������������ �����
    float WindAmplitude=pp->SsailWindDepend*sailHeight*(fWindBase+pp->fWindAdding)/(pp->fWindAdding+1.f)/(float)(SAIL_COL_MAX/2+2);
	if( ss.bYesLimitPoint )
	{
		WindAmplitude = (ss.fDeepH+ss.fDeepZ) * 0.15f;
	}

    // ������ ������ ��� ���������� �����
    float windFlex;
    if( ss.eSailType==SAIL_TRAPECIDAL )
        windFlex=.2f*(1.f-fWindBase*(1.f+sailWind.z)*.5f);
    else
        windFlex=.2f*(1.f-fWindBase*(1.f+sailWind.x)*.5f);
    if(sroll) windFlex*=sroll->delta;
    CVECTOR SailDownVect;
    SailDownVect.x=0.f;
    SailDownVect.y=-windFlex;
    SailDownVect.z=-windFlex*(ss.fDeepZ+ss.fDeepH);

    CVECTOR dVH=(ss.hardPoints[1]-ss.hardPoints[3])/(float)(SAIL_ROW_MAX+1)*ss.fDeepVh;//*(1.f-fWindBase);
    CVECTOR ddVH=sgeo.ddVh+dVH*2.f/(float)(SAIL_COL_MAX-1);
    dVH=sgeo.dVh-dVH;
    CVECTOR StartPoint = ss.hardPoints[0];
    CVECTOR StartDelta = (ss.hardPoints[1]-ss.hardPoints[0])/(float)(SAIL_COL_MAX-1);
    if(m_dwCol==7)  StartDelta*=2.f;
    else if(m_dwCol==4)  StartDelta*=4.f;
    dddV = sgeo.dddVv;

    if(sroll)
        SailDownVect.y-=SumWind*sroll->delta;
    else
        SailDownVect.y-=SumWind;

    // ��������� ����� �������� �������
    if(sailtrope.pnttie[0])
        *sailtrope.pPos[0]=StartPoint;

    int svNum=0;

    for(ix=0; ix<SAIL_COL_MAX;)
    {
        if(ix<=SAIL_COL_MAX/2)
            k=(float)ix/(float)SAIL_COL_MAX;
        else
            k=(float)(SAIL_COL_MAX-ix-1)/(float)SAIL_COL_MAX;
        if(sailtrope.pnttie[2]) k+=.2f;

        CVECTOR WindAdd=(pp->WindVect[VertIdx]*WindAmplitude*(k+1.f/(float)SAIL_COL_MAX))*wind;

        // ��������� ���������� ��������� ����� � ���������� � ��� �� ������ ����
        pcur=StartPoint;
        dV = sgeo.dVv + (float)ix*(dVH+(float)ix*0.5f*ddVH) + WindAdd+SailDownVect;
        ddV = sgeo.ddVv-WindAdd*(2.f-k)/(float)SAIL_ROW_MAX - SailDownVect*2.f/(float)SAIL_ROW_MAX;

        idx=ix*SAIL_ROW_MAX;

        // ������ ������ ����� ����� �������
        //|||||||||||||||||||||||||||||||||||
        for( iy=0; iy<SAIL_ROW_MAX; iy++, idx++ )
        {
            // ������ ��������� � ����� ���������
            pv[idx].pos = pcur;

            // ������ ������� ����� � ������ ����� ������
            if(ix==0 || ix==4 || ix==8 || ix==12)
                if(iy==0 || iy==4 || iy==8 || iy==12 || iy==16)
                {
                    SailPnt[svNum++]=pcur;
                }

            // ������ ���������
            dV+=ddV;
            pcur+=dV;
        }
        // ��������� ����� �������� �������
        if(ix==0 && sailtrope.pnttie[2])
            *sailtrope.pPos[2]=pcur-dV;

        if( trigger )
        {

            //VertIdx
            if((VertIdx+=wind_incr)>=pp->WINDVECTOR_QUANTITY) VertIdx-=pp->WINDVECTOR_QUANTITY;
        }
        trigger=!trigger;

        StartPoint+=StartDelta;

        switch(m_dwCol)
        {
        case 13:
            ix++;
            break;
        case 10:
            ix++;
            if((ix&3)==2)
            {
                ix++;
                StartPoint+=StartDelta;
            }
            break;
        case 7:
            ix+=2;
            break;
        case 4:
            ix+=4;
            break;
        }
    }

    // ��������� ����� �������� �������
    if(sailtrope.pnttie[3])
        *sailtrope.pPos[3] = pcur-dV;
}

void SAILONE::SetGeometry()
{
    CVECTOR p02,p13,p01,p23;
    CVECTOR normLD;

	SAILGEOMETRY * pG;
	if(sroll!= nullptr)	pG = &sroll->oldgeo;
	else pG = &sgeo;

    float tmpCol=1.f/(float)(SAIL_COL_MAX-1);
    float tmpRow=1.f/(float)(SAIL_ROW_MAX-1);

    if( ss.eSailType==SAIL_TREANGLE )
    {
        // Calculate sphere
        ss.boundSphere.c = ( ss.hardPoints[0] + ss.hardPoints[1] + ss.hardPoints[2] )/3.f;

        p01=ss.hardPoints[1]-ss.hardPoints[0];
        p13=ss.hardPoints[2]-ss.hardPoints[1];

        pG->normL=!(p13^p01);
        pG->dVv=p13*tmpRow;

        pG->dVh=p13*(-ss.fDeepVh*tmpRow);
        pG->ddVh=pG->dVh*(-2.f/(float)SAIL_ROW_MAX);
    }
    else
    {
        // Calculate sphere
        ss.boundSphere.c = ( ss.hardPoints[0] + ss.hardPoints[1] +
            ss.hardPoints[2] + ss.hardPoints[3] )*.25f;

        p02=ss.hardPoints[2]-ss.hardPoints[0];
        p13=ss.hardPoints[3]-ss.hardPoints[1];
        p01=ss.hardPoints[1]-ss.hardPoints[0];
        p23=ss.hardPoints[3]-ss.hardPoints[2];

        pG->normL=!(p02^p01);
        pG->normR=!(p13^p01);
        normLD=!(p02^p23);
        pG->dnormL=(normLD-pG->normL)*tmpRow;
        pG->dnormR=(!(p13^p23)-pG->normR)*tmpRow;

        pG->dddVv=CVECTOR(0.f,0.f,0.f);
        pG->dVv=pG->normL*ss.fDeepZ*(1.f-ss.holeCount*pp->fSHoleFlexDepend) + pG->dopV;
        pG->ddVv=pG->dVv*(-2.f/(float)SAIL_ROW_MAX);
        pG->dVv+=p02*tmpRow;

        pG->dVh=(normLD*ss.fDeepH-p13*ss.fDeepVh+pG->normR*ss.fDeepVz)*tmpRow*(1.f-ss.holeCount*pp->fSHoleFlexDepend);
        pG->ddVh=pG->dVh*(-2.f*tmpCol);
        pG->dVh+=(p13-p02)*tmpCol*tmpRow;
    }
    // Calculate sphere radius
    ss.boundSphere.r = sqrtf(
        ~(ss.hardPoints[0] - ss.boundSphere.c) );

	if(sroll!= nullptr)	sgeo.dopV = sroll->oldgeo.dopV;
}

void SAILONE::SetRolling(bool bRoll)
{
    if( sroll ){
        if( sroll->rollup==bRoll ) return; // �� ������ ��������
    }
    else
        if( bRoll==bRolling ) return; // �� ������ ��������

    bRolling=false;
	if(!bRoll) // ������� �������������� ������� ������ �� �����
	{
        CVECTOR locPos = hostNode->loc_mtx.Pos();
        hostNode->loc_mtx.SetPosition(0.f,0.f,0.f);
		if( oldWindAngl<0.f )
		{
			oldWindAngl += pp->TURNSTEPANGL;
	        hostNode->loc_mtx.RotateY(-pp->TURNSTEPANGL);
		}
		else
		{
			oldWindAngl -= pp->TURNSTEPANGL;
	        hostNode->loc_mtx.RotateY(pp->TURNSTEPANGL);
		}
        hostNode->loc_mtx.SetPosition(locPos);
	}

    // ������� ����� ���� ������������ ������
    if(!sroll){
        sroll=NEW SAILROLLING;
        memcpy(&sroll->oldgeo,&sgeo,sizeof(SAILGEOMETRY));
        if(bRoll)   sroll->delta=1.f;
        else   sroll->delta=0.f;
    }
    sroll->rollup=bRoll;
}

void SAILONE::DoRollingStep(DWORD Delta_Time)
{
    if( !sroll ) return; // ��� ������������ ������

    float delta=sroll->delta;

    // ����������� �����
    if( sroll->rollup )
    {
        delta-=(float)Delta_Time*pp->gdata[HostNum].fRollingSpeed;
        if(delta<0.f) {
            bRolling=true; // ������ ����� ��������� ��������� �� �����
            memcpy(&sgeo,&sroll->oldgeo,sizeof(SAILGEOMETRY)); // ������ ���������� ��������� ���������
            delete sroll; sroll=nullptr;
            return; // ������ �� ���� ����������� �����
        }
    }
    // ������������� �����
    else
    {
        delta+=(float)Delta_Time*pp->gdata[HostNum].fRollingSpeed;
        if(sroll->delta>1.f) {
            bRolling=false;
            memcpy(&sgeo,&sroll->oldgeo,sizeof(SAILGEOMETRY));
            delete sroll; sroll=nullptr;
            return;
        }
    }

    sgeo.dddVv =  sroll->oldgeo.dddVv*delta;
    sgeo.ddVh =   sroll->oldgeo.ddVh*delta;
    sgeo.ddVv =   sroll->oldgeo.ddVv*delta;
    sgeo.dVh =    sroll->oldgeo.dVh*delta;
    sgeo.dVv =    sroll->oldgeo.dVv*delta;
    sgeo.normL =  sroll->oldgeo.normL*delta;
    sgeo.normR =  sroll->oldgeo.normR*delta;
    sgeo.dnormL = sroll->oldgeo.dnormL*delta;
    sgeo.dnormR = sroll->oldgeo.dnormR*delta;

    sroll->delta=delta;
}

void SAILONE::TurnSail(float fTurnStep)
{
    CMatrix mtx = hostNode->parent->glob_mtx;
    CMatrix tmtx = hostNode->loc_mtx;
    // Get new local matrix
    float windAng=-sailWind.x;
    //windAng*=pp->MAXTURNANGL;
	if(windAng<0) windAng*=m_fMinAngle;
	else	windAng*=m_fMaxAngle;
    ENTITY_ID ropeEI;
    windAng-=oldWindAngl;

    // ���� ���� ����������� �������� ��� ��������
    if( windAng<-pp->WINDANGL_DISCRETE || windAng>pp->WINDANGL_DISCRETE )
    {
		if( windAng > fTurnStep ) windAng = fTurnStep;
		if( windAng < -fTurnStep ) windAng = -fTurnStep;
        oldWindAngl+=windAng;
        CVECTOR locPos = hostNode->loc_mtx.Pos();
        hostNode->loc_mtx.SetPosition(0.f,0.f,0.f);
        hostNode->loc_mtx.RotateY(-windAng);
        hostNode->loc_mtx.SetPosition(locPos);

        // Get new global matrix
        hostNode->glob_mtx.EqMultiply(hostNode->loc_mtx,mtx);

		if(bRolling)
		{
			if(sailtrope.pnttie[2])	*sailtrope.pPos[2] = ss.hardPoints[0];
			if(sailtrope.pnttie[3])	*sailtrope.pPos[3] = ss.hardPoints[1];
		}
		else if(_CORE_API->FindClass(&ropeEI,"rope",0))
        {
            bool bChange=false;
            for(int i=0; i<2; i++)
                if(sailtrope.rrs[i])
                {
                    int tieNum=sailtrope.rrs[i]->tiePoint;
                    CVECTOR endVect;
                    ((ROPE_BASE*)_CORE_API->GetEntityPointer(&ropeEI))->GetEndPoint(&endVect,sailtrope.rrs[i]->ropenum,pp->gdata[HostNum].modelEI);
                    CVECTOR medVect;
                    medVect=ss.hardPoints[tieNum];
                    CVECTOR begVect;
                    switch(tieNum)
                    {
                    case 1:
                        begVect=ss.hardPoints[0];
                        break;
                    case 2:
                        begVect=ss.hardPoints[0];
                        break;
                    case 3:
                        begVect=ss.hardPoints[1];
                        break;
                    }

                    float r1; r1=sailtrope.rrs[i]->r1;
                    float r2; r2=sailtrope.rrs[i]->r2;

                    if(ss.eSailType!=SAIL_TREANGLE)
                    {
                        medVect= (endVect*r1 + sailtrope.rrs[i]->b*r2)/(r1+r2);
                    }
                    else
                    {
                        medVect.x= (endVect.x*r1 + begVect.x*r2)/(r1+r2);
                        medVect.z= (endVect.z*r1 + begVect.z*r2)/(r1+r2);
                    }
                    *sailtrope.pPos[tieNum]=ss.hardPoints[tieNum]=medVect;

                    bChange=true;
                }
            if(bChange)
				SetGeometry();
        }
    }
}

void SAILONE::CalculateMirrorSailIndex()
{
    int num=0;

    if( ss.eSailType==SAIL_TREANGLE )
    {
        if( ss.hole[1] || ss.hole[2] ) num|=1;
        if( ss.hole[3] || ss.hole[7] ) num|=2;
        if( ss.hole[4] ) num|=4;
        if( ss.hole[9] ) num|=8;
    }
    else
    {
        if( ss.hole[0] || ss.hole[4] ) num|=1;
        if( ss.hole[5] || ss.hole[9] ) num|=2;
        if( ss.hole[2] || ss.hole[6] ) num|=4;
        if( ss.hole[7] || ss.hole[11]) num|=8;
    }

    switch(num)
    {
    case 0:
        ss.sni=0; ss.Nn=4;
        ss.Nh=0;
        break;
    case 1:
        ss.sni=0; ss.Nn=3;
        ss.shi=9; ss.Nh=1;
        break;
    case 2:
        ss.sni=9; ss.Nn=3;
        ss.shi=6; ss.Nh=1;
        break;
    case 3:
        ss.sni=0; ss.Nn=2;
        ss.shi=6; ss.Nh=2;
        break;
    case 4:
        ss.sni=15; ss.Nn=3;
        ss.shi=3; ss.Nh=1;
        break;
    case 5:
        ss.sni=21; ss.Nn=2;
        ss.shi=9; ss.Nh=2;
        break;
    case 6:
        ss.sni=15; ss.Nn=2;
        ss.shi=3; ss.Nh=2;
        break;
    case 7:
        ss.sni=0; ss.Nn=1;
        ss.shi=3; ss.Nh=3;
        break;
    case 8:
        ss.sni=3; ss.Nn=3;
        ss.shi=0; ss.Nh=1;
        break;
    case 9:
        ss.sni=3; ss.Nn=2;
        ss.shi=15; ss.Nh=2;
        break;
    case 10:
        ss.sni=9; ss.Nn=2;
        ss.shi=21; ss.Nh=2;
        break;
    case 11:
        ss.sni=3; ss.Nn=1;
        ss.shi=15; ss.Nh=3;
        break;
    case 12:
        ss.sni=6; ss.Nn=2;
        ss.shi=0; ss.Nh=2;
        break;
    case 13:
        ss.sni=6; ss.Nn=1;
        ss.shi=9; ss.Nh=3;
        break;
    case 14:
        ss.sni=9; ss.Nn=1;
        ss.shi=0; ss.Nh=3;
        break;
    case 15:
        ss.Nn=0;
        ss.shi=0; ss.Nh=4;
        break;
    }

    if(ss.eSailType!=SAIL_TREANGLE)
    {
        ss.shi+=27;
        ss.sni+=27;
    }
}

bool SAILONE::GetGrid(CVECTOR &cam,float perspect)
{
    CVECTOR pos;
    float distance;
    DWORD dwCol,dwRow;

    if(bRolling)
    {
        dwCol=13; dwRow=5;
    }
    else if(bFreeSail)
    {
        dwCol=4; dwRow=5;
    }
    else
    {
        pos=*pMatWorld*ss.boundSphere.c;
        ss.boundSphere.rc=pos;
        pos-=cam;

        distance = sqrtf(pos.x*pos.x+pos.y*pos.y+pos.z*pos.z)*tanf(perspect*.5f); // with perspective

        for( int i=0; i<SAIL_FAR_IDX; i++ )
        {
            dwCol=farGrid[i].col;
            dwRow=farGrid[i].row;
            if( distance < farGrid[i].len )
                break;
        }
    }

    if( (dwRow==m_dwRow) && (dwCol==m_dwCol) ) return false;
    m_dwRow=dwRow; m_dwCol=dwCol;
    return true;
}

void SAILONE::DoSRollSail(SAILVERTEX* pv)
{
    int i;

    CVECTOR pcur=ss.hardPoints[0];
    CVECTOR dp=(ss.hardPoints[1]-ss.hardPoints[0])/(float)(m_dwCol-1);

    int p1=(SAIL_ROW_MAX-1)/4;
    int p2=p1*2;
    int p3=p1*3;
    int p4=p1*4;

    float windVal = pp->WindVect[VertIdx];//sinf((float)VertIdx/(float)WINDVECTOR_QUANTITY*2.f*PI);
    float dz=pp->ROLL_Z_VAL*sailHeight;
    float dy=pp->ROLL_Y_VAL*sailHeight;

    int idx=0;
    CVECTOR dv1,dv2,dv3,dv4;
    dv1=sgeo.normL*(.5f*dz); dv1.y-=dy;
    dv2=CVECTOR(0.f,-dy*1.2f,0.f);
    dv3=sgeo.normL*(-1.f*dz); dv3.y-=dy;
    dv4=sgeo.normL*(-.5f*dz);
    for(i=0; i<(int)m_dwCol; i++)
    {
        windVal=1.f-pp->WindVect[VertIdx]*pp->ROLL_Z_DELTA;
        pv[idx].pos = pcur;
        pv[idx+p1].pos = pcur + dv1*(pp->SSailRollForm[i]*windVal);
        pv[idx+p2].pos = pcur + dv2*(pp->SSailRollForm[i]*windVal);
        pv[idx+p3].pos = pcur + dv3*(pp->SSailRollForm[i]*windVal);
        pv[idx+p4].pos = pcur + dv4*(pp->SSailRollForm[i]*windVal);

        if( (VertIdx+=wind_incr)>=pp->WINDVECTOR_QUANTITY ) VertIdx-=pp->WINDVECTOR_QUANTITY;
        pcur+=dp;
        idx+=SAIL_ROW_MAX;
    }

	if(sailtrope.pnttie[2])
		*sailtrope.pPos[2] = ss.hardPoints[0];
	if(sailtrope.pnttie[3])
		*sailtrope.pPos[3] = ss.hardPoints[1];
}

void SAILONE::DoTRollSail(SAILVERTEX* pv)
{
    int i;

    CVECTOR pcur=ss.hardPoints[0];
    CVECTOR dp=(ss.hardPoints[1]-ss.hardPoints[0])*.25f;

    float windVal = pp->WindVect[VertIdx];
    float dx=pp->ROLL_Z_VAL*sailHeight;
    float dy=pp->ROLL_Y_VAL*sailHeight;
    if(ss.turningSail) {dx*=pp->TR_FORM_MUL; dy*=pp->TR_FORM_MUL;}

    CVECTOR dv1,dv2,dv3,dv4;
    dv1=sgeo.normL*(.5f*dx); dv1.y-=dy;
    dv2=CVECTOR(0.f,-dy*1.2f,0.f);
    dv3=sgeo.normL*(-1.f*dx); dv3.y-=dy;
    dv4=sgeo.normL*(-.5f*dx);

    int idx=6;
    pv[idx++].pos = pcur;
    pv[idx++].pos = pcur+dv1*pp->TSailRollForm[0];
    pv[idx++].pos = pcur+dv3*pp->TSailRollForm[0];
    pv[idx++].pos = pcur+dv4*pp->TSailRollForm[0];

    pcur += dp;
    int pd=1;
    for(i=1; i<5; i++)
    {
        windVal=1.f-pp->WindVect[VertIdx]*pp->ROLL_Z_DELTA;
        pv[idx].pos = pcur;   idx+=pd;
        pv[idx].pos = pcur + dv1*(pp->TSailRollForm[i]*windVal);        idx+=pd;
        pv[idx].pos = pcur + dv2*(pp->TSailRollForm[i]*windVal);        idx+=pd;
        pv[idx].pos = pcur + dv3*(pp->TSailRollForm[i]*windVal);        idx+=pd;
        pv[idx].pos = pcur + dv4*(pp->TSailRollForm[i]*windVal);

        if( (VertIdx+=wind_incr)>=pp->WINDVECTOR_QUANTITY ) VertIdx-=pp->WINDVECTOR_QUANTITY;
        pcur+=dp;
        pd++;
        idx+=i*12+10;
    }

	if(sailtrope.pnttie[2])
		*sailtrope.pPos[2] = ss.hardPoints[1];
}

float SAILONE::Trace(const CVECTOR &src,const CVECTOR &dst,bool bCannonTrace)
{
    if( bRolling ) return 2.f;

    CVECTOR sv;
    pMatWorld->MulToInv(src,sv);
    CVECTOR dv;
    pMatWorld->MulToInv(dst,dv);

    CVECTOR minp = ss.boxCenter - ss.boxSize;
    CVECTOR maxp = ss.boxCenter + ss.boxSize;

    if(  !(sv.x<=maxp.x && sv.x>=minp.x &&
           sv.y<=maxp.y && sv.y>=minp.y &&
           sv.z<=maxp.z && sv.z>=minp.z)
         &&
         !(dv.x<=maxp.x && dv.x>=minp.x &&
           dv.y<=maxp.y && dv.y>=minp.y &&
           dv.z<=maxp.z && dv.z>=minp.z) )
    {
        bool bYesTrace=false;
        CVECTOR vmed;
        // ������� �� X:
        if(sv.x<minp.x)
            if(dv.x<minp.x) return 2.f;
            else
            {
                vmed = sv + (dv-sv)*(minp.x-sv.x)/(dv.x-sv.x);
                if( vmed.y>=minp.y && vmed.y<=maxp.y &&
                    vmed.z>=minp.z && vmed.z<=maxp.z )
                    bYesTrace=true;
            }
        if(!bYesTrace && sv.x>maxp.x)
            if(dv.x>maxp.x) return 2.f;
            else
            {
                vmed = sv + (dv-sv)*(maxp.x-sv.x)/(dv.x-sv.x);
                if( vmed.y>=minp.y && vmed.y<=maxp.y &&
                    vmed.z>=minp.z && vmed.z<=maxp.z )
                    bYesTrace=true;
            }
        // ������� �� Z:
        if(!bYesTrace && sv.z<minp.z)
            if(dv.z<minp.z) return 2.f;
            else
            {
                vmed = sv + (dv-sv)*(minp.z-sv.z)/(dv.z-sv.z);
                if( vmed.y>=minp.y && vmed.y<=maxp.y &&
                    vmed.x>=minp.x && vmed.x<=maxp.x )
                    bYesTrace=true;
            }
        if(!bYesTrace && sv.z>maxp.z)
            if(dv.z>maxp.z) return 2.f;
            else
            {
                vmed = sv + (dv-sv)*(maxp.z-sv.z)/(dv.z-sv.z);
                if( vmed.y>=minp.y && vmed.y<=maxp.y &&
                    vmed.x>=minp.x && vmed.x<=maxp.x )
                    bYesTrace=true;
            }
        // ������� �� Y:
        if(!bYesTrace && sv.y<minp.y)
            if(dv.y<minp.y) return 2.f;
            else
            {
                vmed = sv + (dv-sv)*(minp.y-sv.y)/(dv.y-sv.y);
                if( vmed.z>=minp.z && vmed.z<=maxp.z &&
                    vmed.x>=minp.x && vmed.x<=maxp.x )
                    bYesTrace=true;
            }

        if(!bYesTrace) return 2.f;
    }

    if(ss.eSailType==SAIL_TREANGLE)
        return TSailTrace(sv,dv,bCannonTrace);
    else
        return SSailTrace(sv,dv,bCannonTrace);
}

#define XQUANT 3
#define YQUANT 4
// ����������� ���� ������ ������������� �����
float SAILONE::SSailTrace(CVECTOR &src,CVECTOR &dst,bool bCannonTrace)
{
    float retVal=2.f;
    float tmpVal;
    bool DoHole=false;

    CVECTOR vReal,vDist;

    int i=0; int idx=0;
    for(int ix=0; ix<3; ix++,i++)
    {
        for(int iy=0; iy<4; iy++,i++,idx++)
        {
            CVECTOR vA=SailPnt[i];
            CVECTOR vB=SailPnt[i+5];
            CVECTOR vC=SailPnt[i+1];
            CVECTOR vD=SailPnt[i+6];

            if((tmpVal=CheckSailSquar(idx,vA,vB,vC,src,dst,bCannonTrace))<=1.f)
            {
                if(bCannonTrace) DoHole=true;
                if(retVal>tmpVal) retVal=tmpVal;
            }
            else if((tmpVal=CheckSailSquar(idx,vC,vB,vD,src,dst,bCannonTrace))<=1.f)
            {
                if(bCannonTrace) DoHole=true;
                if(retVal>tmpVal) retVal=tmpVal;
            }

        }
    }

    if(DoHole)
    {
        CalculateMirrorSailIndex(); // ����� ������������ ��� ��������� ������
		SetGeometry();
		if( pp->gdata[HostNum].bDeleted != true && pp->gdata[HostNum].bYesShip )
		{
			VAI_OBJBASE * pVai = (VAI_OBJBASE*)api->GetEntityPointer(&pp->gdata[HostNum].shipEI);
			int charIdx = -1;
			if(pVai!= nullptr && pVai->GetACharacter()!= nullptr)
				charIdx = pVai->GetACharacter()->GetAttributeAsDword("index");
			if(charIdx!=-1)
				api->Event("DoSailHole","llssllllf", g_iBallOwnerIdx, charIdx,"*",
							hostNode->GetName(),groupNum,
							ss.holeCount, GetHoleDword(), 12,
							(float)maxSpeed/pp->gdata[HostNum].speed_m);
		}
    }

    return retVal;
}

// ����������� ���� ������ ����������� �����
float SAILONE::TSailTrace(CVECTOR &src,CVECTOR &dst,bool bCannonTrace)
{
    float retVal=2.f;
    float tmpVal;

    CVECTOR vmin,vmax;
    bool DoHole=false;
    int i,ix,iy;

    //================================================
    // ��������� �� ��������������� ������ (10 ��.)
    //================================================
    for(i=0,ix=0; ix<4; ix++)
    {
        for(iy=0; iy<=ix; iy++,i++)
        {
            CVECTOR vA=SailPnt[i];
            CVECTOR vB=SailPnt[i+ix+1];
            CVECTOR vC=SailPnt[i+ix+2];
			CVECTOR vD; if(iy>0) vD=SailPnt[i-1];

            if((tmpVal=CheckSailSquar(i,vA,vB,vC,src,dst,bCannonTrace))<=1.f)
            {
                if(bCannonTrace) DoHole=true;
                if(retVal>tmpVal) retVal=tmpVal;
            }
            else if(iy>0)
				if((tmpVal=CheckSailSquar(i,vA,vD,vB,src,dst,bCannonTrace))<=1.f)
				{
					if(bCannonTrace) DoHole=true;
					if(retVal>tmpVal) retVal=tmpVal;
				}
        }
    }

    if(DoHole)
    {
        CalculateMirrorSailIndex(); // ����� ������������ ��� ��������� ������
		if( pp->gdata[HostNum].bDeleted != true && pp->gdata[HostNum].bYesShip )
		{
			VAI_OBJBASE * pVai = (VAI_OBJBASE*)api->GetEntityPointer(&pp->gdata[HostNum].shipEI);
			int charIdx = -1;
			if(pVai!= nullptr && pVai->GetACharacter()!= nullptr)
				charIdx = pVai->GetACharacter()->GetAttributeAsDword("index");
			if(charIdx!=-1)
				api->Event("DoSailHole","llssllllf", g_iBallOwnerIdx, charIdx,"*",
							hostNode->GetName(),groupNum,
							ss.holeCount, GetHoleDword(), 10,
							(float)maxSpeed/pp->gdata[HostNum].speed_m);
		}
    }

    return retVal;
}

void SAILONE::CalculateSailWind()
{
    // ������� ������� ����� � ������� ��������� ������
    pMatWorld->MulToInvNorm(*(CVECTOR*)&pp->globalWind.ang,sailWind);

    // ������ ��������� ������
	curSpeed = GetSailSpeed(ss.holeCount, GetMaxHoleCount(), maxSpeed);

    pp->gdata[HostNum].maxSpeed += curSpeed;

    // ��������� ������� ���� ������
    if(bRolling)
        curSpeed=0.f;
    else
    {
        // ������ ���� �����
        //curSpeed*=pp->globalWind.base*1.2f;

        float xtmp,ztmp;
        // ������ ����������� �����
        ztmp=sailWind.z*.5f+.5f;
        if(ztmp>1.f) ztmp=1.f;
        if(sailWind.x<0.f) xtmp=(ztmp-1.f)*sailWind.x;
        else xtmp=(1.f-ztmp)*sailWind.x;
        switch(ss.eSailType)
        {
        case SAIL_TREANGLE:
            curSpeed*=pp->ts_min+xtmp*pp->ts_xdep+ztmp*pp->ts_zdep;
            break;
        case SAIL_TRAPECIDAL:
            curSpeed*=pp->fs_min+xtmp*pp->fs_xdep+ztmp*pp->fs_zdep;
            break;
        default:
            curSpeed*=pp->ss_min+xtmp*pp->ss_xdep+ztmp*pp->ss_zdep;
        }

        // ������ ������������ �������
        if(sroll)
            curSpeed *= sroll->delta;
    }
}

float SAILONE::CheckSailSquar(int i,CVECTOR &va,CVECTOR &vb,CVECTOR &vc,CVECTOR &vsrc, CVECTOR &vdst, bool bCannonTrace)
{
    float retVal=2.f;

    CVECTOR d1=vb-va;
    CVECTOR d2=vc-va;

    // ������������ � ��-�� ���������
    float fA= d1.y*d2.z - d1.z*d2.y;
    float fB= d1.z*d2.x - d1.x*d2.z;
    float fC= d1.x*d2.y - d1.y*d2.x;
    float fD= fA*va.x+fB*va.y+fC*va.z;

    float srcDist= fA*vsrc.x + fB*vsrc.y + fC*vsrc.z - fD;
    float dstDist= fA*vdst.x + fB*vdst.y + fC*vdst.z - fD;

    if(srcDist==0.f) return 0.f;
    if(dstDist==0.f) return 1.f;

    if( (srcDist<0.f)^(dstDist<0.f) )
        retVal=srcDist/(srcDist-dstDist);
    else
        return 2.f;

    // �������� �� ��������� ����� ����������� � �����������
    if(retVal<=1.f)
    {
        CVECTOR cv = vsrc + (vdst-vsrc)*retVal;
		CVECTOR vab = vb-va;
		CVECTOR vbc = vc-vb;
		CVECTOR vca = va-vc;
        float kA,kB,kD; // ������������ � ��-�� ������ �� ��������� x*kA+y*kB=kD
		float d1,d2;
        //----------------------------------------------
        // �� ��������� XY
            // for ab
        kA=-vab.y; kB=vab.x; kD=va.y*vab.x-va.x*vab.y;
		d1=kA*cv.x+kB*cv.y; d2=kA*vc.x+kB*vc.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for bc
        kA=-vbc.y; kB=vbc.x; kD=vb.y*vbc.x-vb.x*vbc.y;
		d1=kA*cv.x+kB*cv.y; d2=kA*va.x+kB*va.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for ca
        kA=-vca.y; kB=vca.x; kD=vc.y*vca.x-vc.x*vca.y;
		d1=kA*cv.x+kB*cv.y; d2=kA*vb.x+kB*vb.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
        //----------------------------------------------
        // �� ��������� ZY
            // for ab
        kA=-vab.y; kB=vab.z; kD=va.y*vab.z-va.z*vab.y;
		d1=kA*cv.z+kB*cv.y; d2=kA*vc.z+kB*vc.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for bc
        kA=-vbc.y; kB=vbc.z; kD=vb.y*vbc.z-vb.z*vbc.y;
		d1=kA*cv.z+kB*cv.y; d2=kA*va.z+kB*va.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for ca
        kA=-vca.y; kB=vca.z; kD=va.y*vca.z-va.z*vca.y;
		d1=kA*cv.z+kB*cv.y; d2=kA*vb.z+kB*vb.y;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
        //----------------------------------------------
        // �� ��������� XZ
            // for ab
        kA=-vab.z; kB=vab.x; kD=va.z*vab.x-va.x*vab.z;
		d1=kA*cv.x+kB*cv.z; d2=kA*vc.x+kB*vc.z;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for bc
        kA=-vbc.z; kB=vbc.x; kD=vb.z*vbc.x-vb.x*vbc.z;
		d1=kA*cv.x+kB*cv.z; d2=kA*va.x+kB*va.z;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
            // for ca
        kA=-vca.z; kB=vca.x; kD=va.z*vca.x-va.x*vca.z;
		d1=kA*cv.x+kB*cv.z; d2=kA*vb.x+kB*vb.z;
        if( (d1!=kD) && (d2!=kD) &&
			( (d1>kD)^(d2>kD) ) )  return 2.f;
        //----------------------------------------------
    }

    // �������� � ������ �����
    if( retVal<=1.f && !ss.hole[i] && bCannonTrace )
    {
        ss.hole[i]=true;
        ss.holeCount++;
    }

    return retVal;
}

void SAILONE::DoSFreeSail(SAILVERTEX* pv)
{
    CVECTOR dirV;
    pMatWorld->MulToInvNorm(!(CVECTOR(0.f,-1.f,0.f) + sailWind*pp->globalWind.base),dirV);
    CVECTOR dv = dirV * (sailHeight*.25f);
    int gidx=0;

    for(int ix=0; ix<4; ix++)
    {
        CVECTOR cpos = ss.hardPoints[0] + (ss.hardPoints[1]-ss.hardPoints[0])*((float)ix/3.f);
        int idx = SAIL_ROW_MAX*ix*4;
        for(int iy=0; iy<5; iy++)
        {
            CVECTOR dvec = cpos - SailPnt[gidx];

            float mul;
            if(iy)
                mul = (pp->FALL_SSAIL_ADD_MIN+(float)rand()/(float)RAND_MAX*pp->FALL_SSAIL_ADD_RAND)/sqrtf(~dvec);
            else
                mul = 1.f;
            SailPnt[gidx] += dvec*mul;
            pv[idx].pos = SailPnt[gidx++];
            idx += 4;
            cpos += dv;
        }
    }
}

void SAILONE::DoTFreeSail(SAILVERTEX* pv)
{
    CVECTOR dirV;
    pMatWorld->MulToInvNorm(!(CVECTOR(0.f,-1.f,0.f) + sailWind*pp->globalWind.base),dirV);
    CVECTOR dv = dirV * (sailHeight*.25f);
    int gidx=0;

    for(int ix=0; ix<5; ix++)
    {
        CVECTOR cpos = ss.hardPoints[0] + (ss.hardPoints[1]-ss.hardPoints[0])*((float)ix*.25f);
        int idx = ix*(ix*8+2);
        for(int iy=0; iy<=ix; iy++)
        {
            CVECTOR dvec = cpos - SailPnt[gidx];

            float mul;
            if(iy)
                mul = (pp->FALL_TSAIL_ADD_MIN+(float)rand()/(float)RAND_MAX*pp->FALL_TSAIL_ADD_RAND)/sqrtf(~dvec);
            else
                mul = 1.f;
            SailPnt[gidx] += dvec*mul;
            pv[idx].pos = SailPnt[gidx++];
            idx += 4;
            cpos += dv;
        }
    }
}

void SAILONE::SetAllHole(DWORD holeData)
{
	int maxHoleQ = GetMaxHoleCount();
	ss.holeCount = 0;
	for(int i=0; i<maxHoleQ; i++,holeData>>=1)
	{
		ss.hole[i] = holeData&1;
		if(holeData&1) ss.holeCount++;
	}
	SetGeometry();
}

void SAILONE::SetTurnLimits()
{
	if(ss.eSailType!=SAIL_TREANGLE) return;
	if(!ss.turningSail) return;
	if(sailtrope.rrs[0]== nullptr) return;
	ENTITY_ID ropeEI;
	if( !api->FindClass(&ropeEI,"ROPE",0) ) return;
	ROPE_BASE * prbase = (ROPE_BASE*)api->GetEntityPointer(&ropeEI);
	if(prbase== nullptr) return;

	CVECTOR cv1,cv0;

	GEOS::INFO inf;
	hostNode->parent->geo->GetInfo(inf);
	//cv0 = CVECTOR(inf.boxsize.x,0.f,0.f);
	cv0 = CVECTOR(0.f,0.f,0.f);

	prbase->GetEndPoint(&cv1,sailtrope.rrs[0]->ropenum,pp->gdata[HostNum].modelEI);

	float kx = cv1.z - cv0.z;
	float ky = cv1.x - cv0.x;
	float kc = cv0.x*kx - cv0.z*ky;

	float x0 = ss.hardPoints[0].x;
	float y0 = ss.hardPoints[0].z;

	float minA = -1.f;
	float maxA = -1.f;
	bool bV = (x0*kx - y0*ky + kc) >= 0.f;
	bool bVADD = bV ^ (kx>=0.f);
	float nextV;

	float fstep = 0.01f;
	float fAdding = sqrtf(kx*kx+ky*ky)*
		(pp->TsailWindDepend*ss.boundSphere.r*1.3f + inf.boxsize.x + ss.fDeepH + ss.fDeepZ);

	for(float fA=pp->MAXTURNANGL; fA>0.f; fA-=fstep)
	{
		float ca = cosf(fA);
		float sa = sinf(fA);

		float x,y;
		if(minA<0.f)
		{
			x = x0*ca + y0*sa;
			y = -x0*sa + y0*ca;
			nextV = x*kx - y*ky + kc;
			if(bV)
			{
				if(nextV>fAdding)	minA = fA;
			}
			else
			{
				if(nextV<-fAdding)	minA = fA;
			}
		}
		if(maxA<0.f)
		{
			x = x0*ca - y0*sa;
			y = x0*sa + y0*ca;
			nextV = x*kx - y*ky + kc;
			if(bV)
			{
				if(nextV>fAdding)	maxA = fA;
			}
			else
			{
				if(nextV<-fAdding)	maxA = fA;
			}
		}
	}

	if(minA>=0.f)	m_fMinAngle = minA;
	if(maxA>=0.f)	m_fMaxAngle = maxA;
}

float SAILONE::GetDistanceFromPointTo3Point(const CVECTOR& v, const CVECTOR& vB1, const CVECTOR& vB2, const CVECTOR& vB3)
{
	CVECTOR vN = !( (vB1-vB2) ^ (vB3-vB2) );
	float fD = - (vN | vB2);

	float f = v|vN + fD;
	return f;
}
