#ifndef AI_FLOW_GRAPH_HPP
#define AI_FLOW_GRAPH_HPP

#include "..\common_h\vmodule_api.h"
#include "..\common_h\defines.h"
#include <vector>
#include <string>
#include <algorithm>

#define INVALID_ARRAY_INDEX			0xFFFFFFFF

class AIFlowGraph
{
friend class IslandED;
	enum AIFLOWGRAPH_FLAGS
	{
		ALREADY_USED_IN_PATHFINDING = 1,
		AIFLOWGRAPH_UNKNOWN = 0x7FFFFFFF
	};
public:
	struct edge_t
	{
		dword	dw1,dw2;	// first and second point index
		float	fLen;		// edge len

		edge_t() {};
		edge_t(dword _dw1, dword _dw2, float _fLen) { dw1 = _dw1; dw2 = _dw2; fLen = _fLen; };
		inline bool operator == (const edge_t & e) const { return ((e.dw1 == dw1 && e.dw2 == dw2) || (e.dw1 == dw2 && e.dw2 == dw1)); }
	};

	struct npoint_t 
	{
		dword		dwPnt;
		float		fDistance;
		float		fTemp;
		inline bool operator < (const npoint_t & n) const { return (fDistance < n.fDistance); };
	};

	struct point_t
	{
		CVECTOR				vPos;
		dword				dwFlags;
		std::vector<dword>		aEdges;

		point_t() {};
		point_t(CVECTOR _vPos) { vPos = _vPos; };
		inline bool operator == (const point_t & p) const { return ((~(p.vPos - vPos))<1e-5f); }
	};

	class VectorPath
	{
		public:
			std::vector<CVECTOR>		aPoints;

			VectorPath() {};
			~VectorPath() {};

			void AddPoint(CVECTOR vPos) { aPoints.push_back(vPos); };
	};

	class Path
	{
		private: 
			struct point_t
			{
				dword		dwPnt;
				float		fDistance;
			};

			float			fDistance;

		public:
			std::vector<point_t>	aPoints;

			float	GetPathDistance() { return fDistance; }
			float	GetDistance(dword dwPnt)
			{
				float fDist = 0.0f;
				for (dword i=0;i<aPoints.size();i++) 
				{
					point_t * pP = &aPoints[i];
					fDist += pP->fDistance;
					if (dwPnt == pP->dwPnt) return fDist;
				}
				return -1.0f;
			}
			bool	FindPoint(dword dwPnt) { return (GetDistance(dwPnt) >= 0.0f); }
			dword	GetLastPoint() { Assert(aPoints.size()); return aPoints.back().dwPnt; };
			void	DelLastPoint() { fDistance -= aPoints.back().fDistance; aPoints.pop_back(); };
			void	AddPoint(dword dwP, float _fDistance)
			{
				aPoints.push_back(point_t{ dwP, _fDistance });
				fDistance += _fDistance;
			}

			Path(Path * pPath = null)
			{ 
				fDistance = 0.0f; 
				if (pPath)
				{
					aPoints = pPath->aPoints;
					fDistance = pPath->fDistance;
				}
			};
			~Path() {};
	};

private:
	std::vector<Path*>		aPaths;

	bool	FindPath(Path *pPath, dword dwP1, dword dwP2);

protected:
	dword				dwIteration;

	std::vector<edge_t>		aEdges;
	std::vector<point_t>		aPoints;
	//std::vector<npoint_t>		aNearestPoints;
	std::string				sSectionName;

struct table_t
{
	dword	p;
	float	d;
};

	table_t				* pTable;
public:
	AIFlowGraph() //: aPaths(_FL_, 64), aEdges(_FL_), aPoints(_FL_)//, aNearestPoints(200)
	{
		pTable = null;
		sSectionName = "GraphPoints";
	};
	~AIFlowGraph() 
	{
		STORM_DELETE(pTable);
	};

	// save/load/release section
	void	ReleaseAll();
	bool	Load(INIFILE * pIni);
	bool	Save(INIFILE * pIni);

	// point/edge/Path function section
	dword	GetNumPoints() { return aPoints.size(); };
	dword	GetNumEdges() { return aEdges.size(); };
	CVECTOR	GetPointPos(dword dwPnt)
	{
		Assert(dwPnt < aPoints.size());
		return aPoints[dwPnt].vPos;
	}
	point_t		* GetPoint(dword dwPntIdx);
	edge_t		* GetEdge(dword dwEdgeIdx);
	VectorPath	* GetVectorPath(dword dwP1, dword dwP2);
	Path		* GetPath(dword dwP1, dword dwP2);
	float		GetPathDistance(dword dwP1, dword dwP2);
	float		GetDistance(dword dwP1, dword dwP2);
	dword		GetOtherEdgePoint(dword dwEdgeIdx, dword dwPnt);
	std::vector<npoint_t> * GetNearestPoints(CVECTOR & vP);

	dword	AddPoint(CVECTOR vPos);
	dword	AddEdge(dword dwEdgePnt1, dword dwEdgePnt2);
	dword	AddEdge2Point(dword dwPnt, dword dwEdgePnt1, dword dwEdgePnt2);

	void	BuildTable();

private:
};

inline void AIFlowGraph::ReleaseAll()
{
	aEdges.clear();
	aPoints.clear();
}

inline bool AIFlowGraph::Save(INIFILE * pIni)
{
	Assert(pIni);

	std::string		sTemp,sKey;
	pIni->DeleteSection((char*)sSectionName.c_str());
	for (dword i=0;i<aPoints.size();i++)
	{
		sTemp = "";
		sTemp += aPoints[i].vPos.x; sTemp += ",";
		sTemp += aPoints[i].vPos.z; sTemp += ",";
		sTemp += (long)aPoints[i].aEdges.size(); sTemp += ",";
		for (dword j=0;j<aPoints[i].aEdges.size();j++)
		{
			sTemp += (long)aEdges[aPoints[i].aEdges[j]].dw1; sTemp += ",";
			sTemp += (long)aEdges[aPoints[i].aEdges[j]].dw2; sTemp += ",";
		}
		sKey = "pnt" + std::to_string(i);
		pIni->WriteString((char*)sSectionName.c_str(),(char*)sKey.c_str(),(char*)sTemp.c_str());
	}
	return true;
}

inline bool AIFlowGraph::Load(INIFILE * pIni)
{
	char cTemp[32768];
	Assert(pIni);
	ReleaseAll();

	std::string sKey;
	while(true) //~!~ Optimize?
	{
		sKey = "pnt" + std::to_string(aPoints.size());
		cTemp[0] = 0;
		pIni->ReadString((char*)sSectionName.c_str(),(char*)sKey.c_str(),cTemp,32768,"\0"); if (!cTemp[0]) break;

		//point_t *pP = &aPoints[aPoints.Add()];
		point_t p;
		p.vPos.y = 0.0f;
		sscanf(cTemp,"%f,%f",&p.vPos.x,&p.vPos.z);
		aPoints.push_back(p);
	}
	for (dword i=0;i<aPoints.size();i++)
	{
		float	x,z;
		dword	dwNum;
		sKey = "pnt" + std::to_string(i);
		cTemp[0] = 0;
		pIni->ReadString((char*)sSectionName.c_str(),(char*)sKey.c_str(),cTemp,32768); if (!cTemp[0]) continue;

		const char *buf = cTemp;
		int offset;
		sscanf(buf, "%f,%f,%d,%n", &x, &z, &dwNum, &offset);
		buf += offset;

		for (dword j=0;j<dwNum;j++)
		{
			dword dw1, dw2;
			sscanf(buf, "%d,%d,%n", &dw1, &dw2, &offset);;
			buf += offset;
			aPoints[i].aEdges.push_back(AddEdge(dw1,dw2));
		}
	}
	
	return false;
}

inline dword AIFlowGraph::AddPoint(CVECTOR vPos)
{
	point_t p(vPos);

	auto it = std::find(aPoints.begin(), aPoints.end(), p);
	if (it != aPoints.end())
		return it - aPoints.begin();

	aPoints.push_back(p);
	return aPoints.size() - 1;
}

inline dword AIFlowGraph::AddEdge(dword dwEdgePnt1, dword dwEdgePnt2)
{
	Assert(dwEdgePnt1 < aPoints.size() && dwEdgePnt2 < aPoints.size());

	edge_t e(dwEdgePnt1,dwEdgePnt2,sqrtf(~(GetPointPos(dwEdgePnt1) - GetPointPos(dwEdgePnt2))));

	auto it = std::find(aEdges.begin(), aEdges.end(), e);
	if (it != aEdges.end())
		return it - aEdges.begin();

	aEdges.push_back(e);
	return aEdges.size() - 1;
}

inline dword AIFlowGraph::AddEdge2Point(dword dwPnt, dword dwEdgePnt1, dword dwEdgePnt2)
{
	Assert(dwPnt < aPoints.size() && dwEdgePnt1 < aPoints.size() && dwEdgePnt2 < aPoints.size());

	dword dwEdge = AddEdge(dwEdgePnt1,dwEdgePnt2);
	aPoints[dwPnt].aEdges.push_back(dwEdge);
	return aPoints[dwPnt].aEdges.size()-1;
}

inline AIFlowGraph::point_t	* AIFlowGraph::GetPoint(dword dwPntIdx)
{
	Assert(dwPntIdx < aPoints.size());
	return &aPoints[dwPntIdx];
}

inline AIFlowGraph::edge_t	* AIFlowGraph::GetEdge(dword dwEdgeIdx)
{
	Assert(dwEdgeIdx < aEdges.size());
	return &aEdges[dwEdgeIdx];
}

inline dword AIFlowGraph::GetOtherEdgePoint(dword dwEdgeIdx, dword dwPnt)
{
	Assert(dwEdgeIdx < aEdges.size());
	if (aEdges[dwEdgeIdx].dw1 == dwPnt) return aEdges[dwEdgeIdx].dw2;
	return aEdges[dwEdgeIdx].dw1;
}

inline void AIFlowGraph::BuildTable()
{
	dword i,j,k,x,y;
	dword dwNumPoints = aPoints.size();

	STORM_DELETE(pTable);
	pTable = new table_t[SQR(dwNumPoints)];
	for (i=0;i<SQR(dwNumPoints);i++) 
	{
		pTable[i].p = INVALID_ARRAY_INDEX;
		pTable[i].d = 1e8f;
	}
	for (i=0;i<dwNumPoints;i++)
	{
		point_t * pP = &aPoints[i];
		table_t * pTableRow = &pTable[i * dwNumPoints];
		for (j=0;j<pP->aEdges.size();j++)
		{
			dword dwPnt = GetOtherEdgePoint(pP->aEdges[j],i);
			pTableRow[dwPnt].p = dwPnt;
			pTableRow[dwPnt].d = aEdges[pP->aEdges[j]].fLen;
		}
	}
	for (k=0;k<dwNumPoints;k++)
	{
		bool bF = true;
		for (y=0;y<dwNumPoints;y++)
		{
			for (x=0;x<dwNumPoints;x++) if (x != y)
			{
				point_t * pP = &aPoints[y];
				float d = pTable[x + y * dwNumPoints].d;
				for (j=0;j<pP->aEdges.size();j++)
				{
					dword dwPnt = GetOtherEdgePoint(pP->aEdges[j],y);
					float d1 = pTable[dwPnt + y * dwNumPoints].d;
					float d2 = pTable[x + dwPnt * dwNumPoints].d;
					if (d1+d2 < d && fabsf((d1+d2) - d)>0.01f) 
					{
						d = d1+d2;
						pTable[x + y * dwNumPoints].d = d;
						pTable[x + y * dwNumPoints].p = dwPnt;
						bF = false;
					}
				}
				
			}
		}
		if (bF) break;
	}
}

inline float AIFlowGraph::GetDistance(dword dwP1, dword dwP2)
{
	return sqrtf(~(GetPointPos(dwP2) - GetPointPos(dwP1)));
}

inline float AIFlowGraph::GetPathDistance(dword dwP1, dword dwP2)
{
	Assert(dwP1 < aPoints.size() && dwP2 < aPoints.size());
	if (dwP1 == dwP2) return 0.0f;
	dword dwNumPoints = aPoints.size();

	float fDistance = 0.0f;
	dword dwPnt = pTable[dwP2 + dwP1 * dwNumPoints].p;
	while(dwPnt != INVALID_ARRAY_INDEX)
	{
		fDistance += GetDistance(dwP1, dwPnt);
		dwP1 = dwPnt;
		dwPnt = pTable[dwP2 + dwPnt * dwNumPoints].p;
	}

	return fDistance;
}

inline AIFlowGraph::VectorPath * AIFlowGraph::GetVectorPath(dword dwP1, dword dwP2)
{
	VectorPath	* pVPath = new VectorPath();
	Path		* pPath = GetPath(dwP1,dwP2);
	if (pPath)
	{
		for (dword i=0;i<pPath->aPoints.size();i++)
			pVPath->AddPoint(GetPointPos(pPath->aPoints[i].dwPnt));
	}
	STORM_DELETE(pPath);
	return pVPath;
}

inline AIFlowGraph::Path * AIFlowGraph::GetPath(dword dwP1, dword dwP2)
{
	Assert(dwP1 < aPoints.size() && dwP2 < aPoints.size());
	dword dwNumPoints = aPoints.size();

	Path *pP = new Path(null);
	pP->AddPoint(dwP1,0.0f);
	dword dwPnt = pTable[dwP2 + dwP1 * dwNumPoints].p;
	while(dwPnt != INVALID_ARRAY_INDEX)
	{
		float fDistance = GetDistance(dwP1, dwPnt);
		pP->AddPoint(dwPnt,fDistance);
		dwPnt = pTable[dwP2 + dwPnt * dwNumPoints].p;
	}

	return pP;
}

inline std::vector<AIFlowGraph::npoint_t> * AIFlowGraph::GetNearestPoints(CVECTOR & vP)
{
	std::vector<npoint_t>* aNearestPoints = new std::vector<npoint_t>(aPoints.size());
	for (dword i = 0;i<aPoints.size();i++)
	{
		//npoint_t * pN = &(*aNearestPoints)[(*aNearestPoints).Add()];
		//pN->fDistance = sqrtf(~(vP - aPoints[i].vPos));
		//pN->dwPnt = i;
		(*aNearestPoints)[i].fDistance = sqrtf(~(vP - aPoints[i].vPos));
		(*aNearestPoints)[i].dwPnt = i;
	}
	//(*aNearestPoints).Sort();
	std::sort(aNearestPoints->begin(), aNearestPoints->end());

	return aNearestPoints;
}

#endif