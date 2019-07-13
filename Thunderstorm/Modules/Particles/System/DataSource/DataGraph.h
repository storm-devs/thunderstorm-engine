#ifndef _PARTICLE_DATA_GRAPH_H_
#define _PARTICLE_DATA_GRAPH_H_

#include "../../ICommon/MemFile.h"

#include "../../ICommon/GraphVertex.h"
#include <string>
#include <vector>


class DataGraph
{
	std::string Name;


//� ������ ������� ��������� ��� �������� ��������
	float MaxCachedTime;
	float MinCachedTime;
//����� ��� ������ � ����� �������
	uint32_t MaxCachedIndex;
	uint32_t MinCachedIndex;

	std::vector<GraphVertex> MinGraph;
	std::vector<GraphVertex> MaxGraph;


	void ResetCachedTime ();

	float GetMinAtTime (float Time, float LifeTime);
	float GetMaxAtTime (float Time, float LifeTime);


	bool bRelative;
	bool bNegative;
	

public:

//�����������/����������
	DataGraph ();
	virtual ~DataGraph ();


	//����������/�������� ����� ���� ������������� �������� � ������� ��� ���...
	void SetNegative (bool _bNegative);
	bool GetNegative ();

	//����������/�������� ������������� ������ ��� ���...
	void SetRelative (bool _bRelative);
	bool GetRelative ();


//�������� �������� (������� �����, ��������� �������[0..1])
	float GetValue (float Time, float LifeTime, float K_rand);
	float GetRandomValue (float Time, float LifeTime);


//���������� ��������...
	void SetValues (const GraphVertex* MinValues, uint32_t MinValuesSize, const GraphVertex* MaxValues, uint32_t MaxValuesSize);

	//������������� "�������� �� ���������"
	void SetDefaultValue (float MaxValue, float MinValue);


//�������� ���-�� � ������� ��������
	uint32_t GetMinCount ();

//�������� ���-�� � ������� ���������
	uint32_t GetMaxCount ();

//�������� �������� �� ������� �� ������� ��������
	const GraphVertex& GetMinVertex (uint32_t Index);

//�������� �������� �� ������� �� ������� ���������
	const GraphVertex& GetMaxVertex (uint32_t Index);


	void Load (MemFile* File);
	void Write (MemFile* File);
	
	void SetName (const char* szName);
	const char* GetName ();


	float GetMaxTime ();


	void ConvertRadToDeg ();
	void ConvertDegToRad ();
	void MultiplyBy (float Val);
	void Clamp (float MinValue, float MaxValue);
	void Reverse ();  //Graphs = 1.0f - Graph
	void NormalToPercent ();
	void PercentToNormal ();
	void NormalToAlpha ();
	void AlphaToNormal ();




};


#endif