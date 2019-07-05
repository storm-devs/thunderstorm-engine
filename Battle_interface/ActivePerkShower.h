#ifndef _ACTIVEPERKSHOWER_H_
#define _ACTIVEPERKSHOWER_H_

#include "../Common_h/dx9render.h"
#include "../Common_h/defines.h"

class	ActivePerkShower : public Entity
{
	class ATTRIBUTES;

	VDX9RENDER *rs;

public:
	ActivePerkShower();
	~ActivePerkShower();
	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);

protected:
	void	ReleaseAll();

	long	m_idVBuf;
	long	m_idIBuf;
	void	FillVIBuffers();
	void	FillRectData(void * vbuf,FRECT & rectPos,FRECT & rectTex);

	int		m_nTextureQ;
	struct _TEXTURE_DESCR {
		long m_idTexture;
		long m_nCol;
		long m_nRow;

		long m_nPicsQ;
		long m_nVertStart;
		long m_nIndxStart;
	} *m_pTexDescr;
	bool CreateTextures(ATTRIBUTES * pATextureRoot);
	FRECT GetTextureRect(int textIdx, int picIdx);

	int		m_nIconWidth;
	int		m_nIconHeight;
	int		m_nSpaceHorz;
	int		m_nSpaceVert;

	int		m_nShowPlaceQ;
	typedef FRECT _SHOW_PLACE;
	_SHOW_PLACE *m_pShowPlaces;
	bool CreateShowPlaces(ATTRIBUTES * pAPlacesRoot);

	int		m_nIShowQ;
	struct	_PICTURE_DESCR {
		long m_nPicNum;
		long m_nPicTexIdx;
	} * m_pIconsList;
	bool InitIconsList(ATTRIBUTES * pAIconsRoot);
	void AddIconToList(ATTRIBUTES * pAIconDescr);
	void DelIconFromList(ATTRIBUTES * pAIconDescr);

	bool InitCommonBuffers();
};

#endif
