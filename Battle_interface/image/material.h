#ifndef BI_IMAGEMATERIAL_H
#define BI_IMAGEMATERIAL_H

#include "defines.h"
#include <string>
#include <vector>

class BIImage;
class BIImageRender;

class BIImageMaterial
{
public:
	BIImageMaterial( VDX9RENDER* pRS, BIImageRender* pImgRender );
	~BIImageMaterial();

	void Render(long nBegPrior, long nEndPrior);

	bool IsUseTexture( const char* pcTextureName ) {return (m_sTextureName==pcTextureName);}
	bool IsUseTechnique( const char* pcTechniqueName ) {return (m_sTechniqueName==pcTechniqueName);}

	const BIImage* CreateImage( BIImageType type, dword color, FRECT& uv, long nLeft,long nTop, long nRight,long nBottom, long nPrior );
	void DeleteImage( const BIImage* pImg );

	void SetTexture( const char* pcTextureName );
	void SetTechnique( const char* pcTechniqueName ) {if(pcTechniqueName) m_sTechniqueName = pcTechniqueName;}

	void UpdateFlagOn() {m_bMakeBufferUpdate=true;}

	long GetImageQuantity() {return m_apImage.size();}
	void ReleaseAllImages();

	long GetMinPrioritet() {return m_nMinPrioritet;}
	long GetMaxPrioritet() {return m_nMaxPrioritet;}

	BIImageRender* GetImgRender() {return m_pImageRender;}

protected:
	void Release();
	void UpdateImageBuffers( long nStartIdx, long nEndIdx );
	void RemakeBuffers();
	bool GetOutputRangeByPrioritet(long nBegPrior,long nEndPrior, long &nStartIndex,long &nTriangleQuantity);
	void RecalculatePrioritetRange();
	void InsertImageToList( BIImage* pImg );

	VDX9RENDER* m_pRS;
	BIImageRender* m_pImageRender;

	std::string m_sTextureName;
	std::string m_sTechniqueName;

	long m_nTextureID;
	long m_nVBufID;
	long m_nIBufID;
	long m_nVertexQuantity;
	long m_nTriangleQuantity;

	std::vector<BIImage*> m_apImage;

	long m_nMinPrioritet;
	long m_nMaxPrioritet;

	bool m_bMakeBufferUpdate;
	bool m_bDeleteEverythink;
};

#endif
