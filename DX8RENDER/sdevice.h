#ifndef __SDEVICE_H__
#define __SDEVICE_H__


#include "..\common_h\vmodule_api.h"
#include "..\common_h\dx9render.h"
#include "..\common_h\defines.h"
#include "..\common_h\VideoTexture.h"
#include <vector>
#include <stack>

#include "Technique.h"
#include "font.h"

#define MAX_STEXTURES	1024
#define MAX_BUFFERS		1024
#define MAX_FONTS       256

struct D3DERRORS
{
	HRESULT		err;
	char		* descrition;
};

struct texpaths_t
{
	char str[_MAX_PATH];
};

struct STEXTURE
{
	IDirect3DBaseTexture9	* d3dtex;
	char					* name;
	unsigned long			hash;
	long					ref;
	uint32_t					dwSize;
	bool					isCubeMap;
	bool					loaded;
};

//-----------buffers-----------
struct VERTEX_BUFFER
{
	uint32_t					dwNumLocks;
	uint32_t					dwUsage;
	long					type;
	long					size;
	IDirect3DVertexBuffer9	* buff;
};

struct INDEX_BUFFER
{
	uint32_t					dwNumLocks;
	uint32_t					dwUsage;
	long					size;
	IDirect3DIndexBuffer9	* buff;
};

struct FONTENTITY
{
	char			* name;
    unsigned long	hash;
    FONT			* font;
    long			ref;
};

struct VideoTextureEntity
{
	char				* name;
	unsigned long		hash;
    long				ref;
	ENTITY_ID			videoTexture_id;
	CVideoTexture		* VideoTexture;
	VideoTextureEntity	* next;
};


// ----- Sound statistics -----
extern uint32_t dwSoundBuffersCount;
extern uint32_t dwSoundBytes;
extern uint32_t dwSoundBytesCached;

//-----------SDEVICE-----------
class DX9RENDER  : public VDX9RENDER
{

#define RS_RECT_VERTEX_FORMAT	(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
	struct RECT_VERTEX
	{
		CVECTOR pos;
		uint32_t	color;
		float	u, v;
	};


	struct RenderTarget
	{
		IDirect3DSurface9 * pRenderTarget;
		IDirect3DSurface9 * pDepthSurface;
		D3DVIEWPORT9		ViewPort;
	};

	IDirect3DDevice9	* d3d9;
	IDirect3D9			* d3d;
	HWND				hwnd;

	CVECTOR				Pos, Ang;
	float				Fov;

	CTechnique			* pTechnique;

    char				* fontIniFileName;
    long				nFontQuantity;
    FONTENTITY			FontList[MAX_FONTS];
    long				idFontCurrent;

	VideoTextureEntity	* pVTL;

	long				nTextureDegradation;
	float				aspectRatio;
	float				m_fHeightDeformator;

	bool				bSafeRendering;
	bool				bShowFps, bShowExInfo;
	bool				bInsideScene;

	PLANE				viewplane[4];

	STEXTURE			Textures[MAX_STEXTURES];
	INDEX_BUFFER		IndexBuffers[MAX_BUFFERS];
	VERTEX_BUFFER		VertexBuffers[MAX_BUFFERS];

	bool				MakeAvi;
	IDirect3DSurface9	* ImageBuffer;

	// VideoCapture section
	HDC					hDesktopDC, hCaptureDC;
	HBITMAP				hCaptureBitmap;
	LPBITMAPINFO		lpbi;
	long				iCaptureFrameIndex;
	bool				bPreparedCapture;
	bool				bVideoCapture;
	float				fFixedFPS;
	std::vector<char*>		aCaptureBuffers;
	uint32_t				dwCaptureBuffersReady;

//-------- post process

	struct QuadVertex
	{
		Vector4 vPos;

		float u0;
		float v0;

		float u1;
		float v1;

		float u2;
		float v2;

		float u3;
		float v3;
	};

	QuadVertex	PostProcessQuad[4];
	QuadVertex	qv[32 * 32];
	uint16_t		qi[31 * 31 * 2 * 3];

	float fSmallWidth;
	float fSmallHeight;
	IDirect3DTexture9* pPostProcessTexture;
	IDirect3DSurface9* pPostProcessSurface;


	IDirect3DTexture9* pSmallPostProcessTexture;
	IDirect3DSurface9* pSmallPostProcessSurface;

	IDirect3DTexture9* pSmallPostProcessTexture2;
	IDirect3DSurface9* pSmallPostProcessSurface2;


	IDirect3DSurface9* pOriginalScreenSurface;
	IDirect3DSurface9* pOriginalDepthSurface;

	D3DVIEWPORT9 OriginalViewPort;

	void CreateRenderQuad (float fWidth, float fHeight, float fSrcWidth, float fSrcHeight, float fMulU = 1.0f, float fMulV = 1.0f);

	void ClearPostProcessSurface (IDirect3DSurface9* pSurf);
	void BlurGlowTexture ();
	void CopyGlowToScreen ();
	void CopyPostProcessToScreen();

	void SetPostProcessTextureAsRenderTarget ();
	void SetScreenAsRenderTarget ();

	float fBlurSize;
	int GlowIntensity;
	int iBlurPasses;

	bool bNeedCopyToScreen;


	bool bPostProcessEnabled;
	bool bPostProcessError;


	bool bSeaEffect;
	float fSeaEffectSize;
	float fSeaEffectSpeed;
	uint32_t dwBackColor;

//-------- post process


	// state save/load ex
	POINT			screen_size;
	D3DFORMAT		screen_bpp;
	D3DFORMAT		stencil_format;

	bool			bMakeShoot;
	bool			bWindow;
	bool			bBackBufferCanLock;

	IDirect3DVertexBuffer9	* aniVBuffer;
	long					numAniVerteces;

	IDirect3DVertexBuffer9	* pDropConveyorVBuffer;

	uint32_t			dwNumDrawPrimitive, dwNumLV, dwNumLI;
	float			fG, fB, fC;
	D3DGAMMARAMP	DefaultRamp;

	float			fNearClipPlane, fFarClipPlane;

	bool			bLoadTextureEnabled;

	bool			bTrace;
	long			iSetupPath;
	uint32_t			dwSetupNumber;
	texpaths_t		TexPaths[4];

	bool			bDropVideoConveyor;

	std::stack<RenderTarget>		stRenderTarget;

	bool TextureLoad(long texid);
	bool ErrorHandler(HRESULT hr, const char * file, unsigned line, const char * func, const char * expr);

	bool MakeCapture();
	void SaveCaptureBuffers();
	void PrepareCapture();

public:
	static DX9RENDER	* pRS;

	DX9RENDER();
	~DX9RENDER();

	// DX9Render: Init/Release
	bool InitDevice(bool windowed, HWND hwnd, long width, long height) override;
	bool ReleaseDevice() override;

	// DX9Render: Animation
	void RenderAnimation(long ib, void * src, long numVrts, long minv, long numv,  long startidx, long numtrg, bool isUpdateVB) override;

	// DX9Render: Return d3d9 device
		virtual void * GetDevice() { return d3d9; };
	void * GetD3DDevice() override { return d3d9; };

	// DX9Render: Render Target/Begin/End/Clear
	bool DX9Clear(long type) override;	//D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
	bool DX9BeginScene() override;
	bool DX9EndScene() override;

	// DX9Render: Materials/Lights Section
	bool	SetLight(uint32_t dwIndex, const D3DLIGHT9 * pLight) override;
	bool	LightEnable(uint32_t dwIndex, bool bOn) override;
	bool	SetMaterial(D3DMATERIAL9 & material) override;
	bool	GetLightEnable(uint32_t dwIndex, BOOL * pEnable) override;
	bool	GetLight(uint32_t dwIndex, D3DLIGHT9 * pLight) override;

	// DX9Render: Screenshot Section
	void SaveShoot() override;

	// DX9Render: Clip Planes Section
	HRESULT SetClipPlane( uint32_t Index, CONST float * pPlane ) override;
	PLANE * GetPlanes() override;

	// DX9Render: Camera Section
	void SetTransform(long type, D3DMATRIX * mtx) override;
	void GetTransform(long type, D3DMATRIX * mtx) override;

	bool SetCamera(CVECTOR * pos, CVECTOR * ang, float perspective) override;
	bool SetCamera(CVECTOR * pos, CVECTOR * ang) override;
	bool SetCamera(CVECTOR lookFrom, CVECTOR lookTo, CVECTOR up) override;
	bool SetPerspective(float perspective, float fAspectRatio = -1.0f) override;
	void GetCamera(CVECTOR & pos, CVECTOR & ang, float & perspective) override;

	bool SetCurrentMatrix(D3DMATRIX * mtx) override;

	// DX9Render: Textures Section
	long TextureCreate(const char * fname) override;
	bool TextureSet(long stage, long texid) override;
	bool TextureRelease(long texid) override;

	// DX9Render: Fonts Section
	long _cdecl Print(long x, long y,char * format,...) override;
	long _cdecl Print(long nFontNum, uint32_t color, long x, long y,char * format,...) override;
	long _cdecl ExtPrint(long nFontNum, uint32_t foreColor, uint32_t backColor, int wAlignment,
							 bool bShadow, float fScale, long scrWidth, long scrHeight,
							 long x, long y,char * format,...) override;
	long StringWidth(char * string, long nFontNum=0, float fScale=1.f, long scrWidth=0) override;
	long CharWidth(char ch, long nFontNum=0, float fScale=1.f, long scrWidth=0) override;
	long CharHeight(long fontID) override;
	long LoadFont(char * fontName) override; // ���������� �����\������������� ������ ��� -1 � ������ ������
	bool UnloadFont(char * fontName) override; // ���������� ������ ���� ����� ������� � �������������
	bool UnloadFont(long fontID) override; // ���������� ������ ���� ����� ������� � �������������
	bool SetCurFont(char * fontName) override; // ���������� ������ ���� ���������� ������ �����
	bool SetCurFont(long fontID) override; // ���������� ������ ���� ���������� ������ �����
	long GetCurFont() override;
	char * GetFontIniFileName() override;
	bool SetFontIniFileName(char * iniName) override;

	// DX9Render: Techniques Section
	bool TechniqueSetParamsAndStart(const char * cBlockName, uint32_t _dwNumParams = 0, void * pParams = nullptr) override;
	bool _cdecl TechniqueExecuteStart(const char * cBlockName, uint32_t _dwNumParams = 0, ...) override;
	bool TechniqueExecuteNext() override;

	// DX9Render: Draw Section
	void _cdecl DrawRects(RS_RECT * pRSR, uint32_t dwRectsNum, const char * cBlockName = nullptr, uint32_t dwSubTexturesX = 1, uint32_t dwSubTexturesY = 1, float fScaleX = 1.0f, float fScaleY = 1.0f, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawSprites(RS_SPRITE * pRSS, uint32_t dwSpritesNum, const char * cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawLines(RS_LINE * pRSL, uint32_t dwLinesNum, const char * cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawLines2D(RS_LINE2D * pRSL2D, uint32_t dwLinesNum, const char * cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;

	void _cdecl DrawBuffer(long vbuff, long stride, long ibuff, long minv, long numv, long startidx, long numtrg, const char *cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawIndexedPrimitiveNoVShader(D3DPRIMITIVETYPE dwPrimitiveType, long iVBuff, long iStride, long iIBuff, long iMinV, long iNumV, long iStartIdx, long iNumTrg, const char *cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawPrimitive(D3DPRIMITIVETYPE dwPrimitiveType, long iVBuff, long iStride, long iStartV, long iNumPT, const char *cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawPrimitiveUP(D3DPRIMITIVETYPE dwPrimitiveType, uint32_t dwVertexBufferFormat, uint32_t dwNumPT, void *pVerts, uint32_t dwStride, const char *cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;
	void _cdecl DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE dwPrimitiveType, uint32_t dwMinIndex, uint32_t dwNumVertices, uint32_t dwPrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexData, uint32_t dwVertexStride, const char *cBlockName = nullptr, uint32_t dwNumParams = 0, ...) override;

   	// DX9Render: Video Section
	void				PlayToTexture() override;
	CVideoTexture *		GetVideoTexture(char * sVideoName) override;
	void				ReleaseVideoTexture(CVideoTexture * pVTexture) override;

	// DX9Render: Vertex/Index Buffers Section
	long CreateVertexBuffer(long type, long nverts,uint32_t usage) override;
	long CreateIndexBuffer(long ntrgs, uint32_t dwUsage = D3DUSAGE_WRITEONLY) override;

	IDirect3DVertexBuffer9 * GetVertexBuffer(long id) override;
	long	GetVertexBufferFVF(long id) override;
	void *	LockVertexBuffer(long id, uint32_t dwFlags = 0) override;
	void	UnLockVertexBuffer(long id) override;
	long	GetVertexBufferSize(long id) override;
	void *	LockIndexBuffer(long id, uint32_t dwFlags = 0) override;
	void	UnLockIndexBuffer(long id) override;
	void	ReleaseVertexBuffer(long id) override;
	void	ReleaseIndexBuffer(long id) override;

	// DX9Render: Render/Texture States Section
	uint32_t SetRenderState(uint32_t State, uint32_t Value) override;
	uint32_t GetRenderState(uint32_t State, uint32_t * pValue) override;
	uint32_t GetSamplerState(uint32_t Sampler, D3DSAMPLERSTATETYPE  Type, uint32_t * pValue) override;
	uint32_t SetSamplerState(uint32_t Sampler, D3DSAMPLERSTATETYPE Type, uint32_t Value) override;
	uint32_t SetTextureStageState(uint32_t Stage, uint32_t Type, uint32_t Value) override;
	uint32_t GetTextureStageState(uint32_t Stage, uint32_t Type, uint32_t * pValue) override;

	// aspect ratio section
	float GetHeightDeformator() override {return m_fHeightDeformator;}
	POINT GetScreenSize() override { return screen_size; }
// ===============================================================================================
// --------------------===================== D3D SECTION =====================--------------------
// ===============================================================================================

	// D3D Device/Viewport Section
	HRESULT GetViewport(D3DVIEWPORT9 * pViewport) override;
	HRESULT SetViewport(const D3DVIEWPORT9 * pViewport) override;
	HRESULT GetDeviceCaps(D3DCAPS9 * pCaps) override;

	// D3D
	HRESULT SetStreamSource(UINT StreamNumber, void * pStreamData, UINT Stride) override;
	HRESULT SetIndices(void * pIndexData) override;
	HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) override;
#ifndef _XBOX
	HRESULT Release(IUnknown *pSurface) override;
#else
		virtual HRESULT Release(IDirect3DResource8 *pSurface);
#endif

	// Vertex/Index Buffers Section
	HRESULT CreateVertexBuffer(UINT Length, uint32_t Usage, uint32_t FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer) override;
	HRESULT VBLock(IDirect3DVertexBuffer9 * pVB, UINT OffsetToLock, UINT SizeToLock, uint8_t** ppbData, uint32_t Flags) override;
	void VBUnlock(IDirect3DVertexBuffer9 * pVB) override;

	// D3D Textures/Surfaces Section
	HRESULT GetDepthStencilSurface( IDirect3DSurface9** ppZStencilSurface ) override;
	HRESULT GetCubeMapSurface( IDirect3DCubeTexture9* ppCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface9** ppCubeMapSurface ) override;
	HRESULT CreateTexture( UINT Width, UINT Height, UINT  Levels, uint32_t Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture ) override;
	HRESULT CreateCubeTexture( UINT EdgeLength, UINT Levels, uint32_t Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture ) override;
	HRESULT CreateOffscreenPlainSurface( UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface9 ** ppSurface) override;
	HRESULT CreateDepthStencilSurface( UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface9 ** ppSurface ) override;
	HRESULT SetTexture(uint32_t Stage, IDirect3DBaseTexture9* pTexture ) override;
	HRESULT GetLevelDesc( IDirect3DTexture9* ppTexture, UINT Level, D3DSURFACE_DESC* pDesc ) override;
	HRESULT GetLevelDesc( IDirect3DCubeTexture9* ppCubeTexture, UINT Level, D3DSURFACE_DESC* pDesc ) override;
	HRESULT LockRect( IDirect3DCubeTexture9* ppCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, uint32_t Flags ) override;
	HRESULT LockRect( IDirect3DTexture9* ppTexture, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, uint32_t Flags ) override;
	HRESULT UnlockRect( IDirect3DCubeTexture9 *pCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level ) override;
	HRESULT UnlockRect( IDirect3DTexture9 *pTexture, UINT Level ) override;
	HRESULT GetSurfaceLevel( IDirect3DTexture9* ppTexture, UINT Level, IDirect3DSurface9** ppSurfaceLevel ) override;
	HRESULT UpdateSurface( IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPointsArray ) override;
	HRESULT StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter) override;
	HRESULT GetRenderTargetData(IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface) override;

	// D3D Pixel/Vertex Shaders Section
	HRESULT CreateVertexDeclaration(CONST D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 ** ppDecl) override;
	HRESULT SetVertexDeclaration(IDirect3DVertexDeclaration9 * pDecl) override;
	HRESULT CreatePixelShader(CONST uint32_t * pFunction, IDirect3DPixelShader9 ** ppShader) override;
	HRESULT CreateVertexShader(CONST uint32_t * pFunction, IDirect3DVertexShader9 ** ppShader) override;
		/*virtual HRESULT DeletePixelShader( DWORD Handle );
		virtual HRESULT DeleteVertexShader( DWORD Handle );*/
	HRESULT SetVertexShader(IDirect3DVertexShader9 * pShader) override;
	HRESULT SetPixelShader(IDirect3DPixelShader9 * pShader) override;
		/*virtual HRESULT SetFVFConstant(DWORD Register, CONST void* pConstantData, DWORD  ConstantCount );*/
	HRESULT SetVertexShaderConstantF(UINT StartRegister, CONST float * pConstantData, UINT Vector4iCount) override;
	HRESULT SetPixelShaderConstantF(UINT StartRegister, CONST float * pConstantData, UINT Vector4iCount) override;
	HRESULT SetFVF(uint32_t handle) override;
	HRESULT GetVertexShader(IDirect3DVertexShader9** ppShader) override;
	HRESULT GetPixelShader(IDirect3DPixelShader9** ppShader) override;


	// D3D Render Target/Begin/End/Clear
	HRESULT GetRenderTarget(IDirect3DSurface9** ppRenderTarget) override;
	HRESULT SetRenderTarget( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pNewZStencil ) override;
	HRESULT Clear( uint32_t Count, CONST D3DRECT* pRects, uint32_t Flags, D3DCOLOR Color, float Z, uint32_t Stencil ) override;
	HRESULT BeginScene() override;
	HRESULT EndScene() override;

	HRESULT ImageBlt(const char * pName, RECT * pDstRect, RECT * pSrcRect) override;
	HRESULT ImageBlt(long nTextureId, RECT * pDstRect, RECT * pSrcRect) override;


	void MakeScreenShot();
	bool LoadTextureSurface(HANDLE file, IDirect3DSurface9 * suface, uint32_t mipSize, uint32_t width, uint32_t height, bool isSwizzled);
	uint32_t LoadCubmapSide(HANDLE file, IDirect3DCubeTexture9 * tex, D3DCUBEMAP_FACES face, uint32_t numMips, uint32_t mipSize, uint32_t size, bool isSwizzled);

	// core interface
	bool  Init() override;
	void  RunStart() override;
	void  RunEnd() override;
	uint32_t RunSection() override {return SECTION_REALIZE;};
	bool  LoadState(ENTITY_STATE * state) override;
	bool  CreateState(ENTITY_STATE_GEN * state_gen) override;

	void ProcessScriptPosAng(CVECTOR & vPos, CVECTOR & vAng);
	void FindPlanes(IDirect3DDevice9 * d3dDevice);

	void SetCommonStates();

	/*bool InitDevice(bool windowed, HWND hwnd, long width, long height);
	bool ReleaseDevice();

	bool DX9Clear(long type);	//D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
	bool DX9BeginScene();
	bool DX9EndScene();

	long TextureCreate(const char *fname);
	bool TextureSet(long stage, long texid);
	bool TextureRelease(long texid);
	//-----------------------------
	bool SetCamera(CVECTOR *pos, CVECTOR *ang, float perspective);
	bool SetCamera(CVECTOR *pos, CVECTOR *ang);
	bool SetCamera(CVECTOR lookFrom, CVECTOR lookTo, CVECTOR up);
	bool SetPerspective(float perspective, float fAspectRatio = -1.0f);

	void ProcessScriptPosAng(CVECTOR & vPos, CVECTOR & vAng);

	bool SetCurrentMatrix(D3DMATRIX *mtx);
	//-----------------------------
	bool SetLight(long l, D3DLIGHT9 &lt);
	bool LightEnable(long l, bool onf);
	bool SetMaterial(D3DMATERIAL9 &m);

	//-----------------------------
	long CreateVertexBuffer(long type, long nverts,uint32_t usage);
	long CreateIndexBuffer(long ntrgs, uint32_t dwUsage = D3DUSAGE_WRITEONLY);
	void _cdecl DrawBuffer(long vbuff, long stride, long ibuff, long minv, long numv, long startidx, long numtrg, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawIndexedPrimitiveNoVShader(D3DPRIMITIVETYPE dwPrimitiveType, long iVBuff, long iStride, long iIBuff, long iMinV, long iNumV, long iStartIdx, long iNumTrg, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawPrimitive(D3DPRIMITIVETYPE dwPrimitiveType, long iVBuff, long iStride, long iStartV, long iNumPT, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawPrimitiveUP(D3DPRIMITIVETYPE dwPrimitiveType, uint32_t dwVertexBufferFormat, uint32_t dwNumPT, void *pVerts, uint32_t dwStride, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE dwPrimitiveType, uint32_t dwMinIndex, uint32_t dwNumVertices, uint32_t dwPrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexData, uint32_t dwVertexStride, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);

	void RenderAnimation(long ib, void * src, long numVrts, long minv, long numv,  long startidx, long numtrg, bool isUpdateVB);

	bool TechniqueSetParamsAndStart(char *cBlockName = 0, uint32_t _dwNumParams = 0, void *pParams = 0);
	bool _cdecl TechniqueExecuteStart(char *cBlockName = 0, uint32_t _dwNumParams = 0, ...);
	bool TechniqueExecuteNext();

	void* LockVertexBuffer(long id, uint32_t dwFlags = 0);
	void UnLockVertexBuffer(long id);
	long GetVertexBufferSize(long id);
	void* LockIndexBuffer(long id, uint32_t dwFlags = 0);
	void UnLockIndexBuffer(long id);
	void ReleaseVertexBuffer(long id);
	void ReleaseIndexBuffer(long id);
	void SetTransform(long type, D3DMATRIX *mtx);
	void GetTransform(long type, D3DMATRIX *mtx);

	// fonts
	//DX9FONTS Fonts;
	long _cdecl Print(long x, long y,char * format,...);
	long _cdecl Print(long nFontNum, DWORD color, long x, long y,char * format,...);
	long _cdecl ExtPrint(long nFontNum, DWORD foreColor, DWORD backColor, int wAlignment,
				         bool bShadow, float fScale, long scrWidth, long scrHeight,
				         long x, long y,char * format,...);
	long StringWidth(char * string, long nFontNum=0, float fScale=1.f, long scrWidth=0);
    long CharWidth(char ch, long nFontNum=0, float fScale=1.f, long scrWidth=0);
    long CharHeight(long fontID); // ���������� ������ ������
    long LoadFont(char * fontName); // ���������� �����\������������� ������ ��� -1 � ������ ������
    bool UnloadFont(char * fontName); // ���������� ������ ���� ����� ������� � �������������
    bool UnloadFont(long fontID); // ���������� ������ ���� ����� ������� � �������������
    bool SetCurFont(char * fontName); // ���������� ������ ���� ���������� ������ �����
    bool SetCurFont(long fontID); // ���������� ������ ���� ���������� ������ �����
    long GetCurFont();
    char *GetFontIniFileName();
    bool SetFontIniFileName(char * iniName);

	void * DX9RENDER::GetD3DDevice() { return d3d9; }

	HRESULT GetViewport(D3DVIEWPORT9 * pViewport);
	HRESULT SetViewport(const D3DVIEWPORT9 * pViewport);

	//
	uint32_t SetRenderState(uint32_t State, uint32_t Value);
	uint32_t GetRenderState(uint32_t State, uint32_t* pValue);
	uint32_t SetTextureStageState(uint32_t Stage,uint32_t Type,uint32_t Value);
	uint32_t GetTextureStageState(uint32_t Stage,uint32_t Type,uint32_t* pValue);

	void GetCamera(CVECTOR& pos, CVECTOR& ang, float& perspective);
	void SaveShoot();




	// core interface
	bool  Init();
	void  RunStart();
	void  RunEnd();
	uint32_t RunSection(){return SECTION_REALIZE;};
	bool  LoadState(ENTITY_STATE * state);
	bool  CreateState(ENTITY_STATE_GEN * state_gen);

	//
	void MakeScreenShot();

	void FindPlanes(IDirect3DDevice9 * d3dDevice);
	PLANE * GetPlanes();

	void _cdecl DrawRects(RS_RECT *pRSR, uint32_t dwRectsNum, char *cBlockName = 0, uint32_t dwSubTexturesX = 1, uint32_t dwSubTexturesY = 1, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawSprites(RS_SPRITE *pRSS, uint32_t dwSpritesNum, char *cBlockName, uint32_t dwNumParams, ...);
	void _cdecl DrawLines(RS_LINE *pRSL, uint32_t dwLinesNum, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);
	void _cdecl DrawLines2D(RS_LINE2D *pRSL2D, uint32_t dwLinesNum, char *cBlockName = 0, uint32_t dwNumParams = 0, ...);

	//------------------
	HRESULT CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer);
	void VertexBufferRelease(void * VB_pointer);
	HRESULT VertexBufferLock(void * VB_pointer, UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData, DWORD Flags);
	void VertexBufferUnlock(void * VB_pointer);
	HRESULT SetFVF(DWORD handle);
	HRESULT SetStreamSource(UINT StreamNumber, void * pStreamData, UINT Stride);
	HRESULT SetIndices(void * pIndexData, UINT BaseVertexIndex);
	HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);

	HRESULT Release(IUnknown *pSurface);
	HRESULT GetRenderTarget(IDirect3DSurface9** ppRenderTarget);
	HRESULT GetDepthStencilSurface( IDirect3DSurface9** ppZStencilSurface );
	HRESULT GetCubeMapSurface( IDirect3DCubeTexture9* ppCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface9** ppCubeMapSurface );
	HRESULT SetRenderTarget( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pNewZStencil );
	HRESULT Clear( DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil );
	HRESULT BeginScene();
	HRESULT EndScene();
	HRESULT SetClipPlane( DWORD Index, CONST float* pPlane );
	HRESULT CreateTexture( UINT Width, UINT Height, UINT  Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture );
	HRESULT CreateCubeTexture( UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture );
	HRESULT CreateDepthStencilSurface( UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface9** ppSurface );
	HRESULT CreatePixelShader(CONST DWORD * pFunction, DWORD * pHandle);
	HRESULT CreateVertexShader(CONST DWORD * pDeclaration, CONST DWORD * pFunction, DWORD * pHandle, DWORD Usage);
	HRESULT SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture );
	HRESULT GetLevelDesc( IDirect3DTexture9* ppTexture, UINT Level, D3DSURFACE_DESC* pDesc );
	HRESULT GetLevelDesc( IDirect3DCubeTexture9* ppCubeTexture, UINT Level, D3DSURFACE_DESC* pDesc );
	HRESULT LockRect( IDirect3DCubeTexture9* ppCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags );
	HRESULT LockRect( IDirect3DTexture9* ppTexture, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags );
	HRESULT UnlockRect( IDirect3DCubeTexture9 *pCubeTexture, D3DCUBEMAP_FACES FaceType, UINT Level );
	HRESULT UnlockRect( IDirect3DTexture9 *pTexture, UINT Level );
	HRESULT GetSurfaceLevel( IDirect3DTexture9* ppTexture, UINT Level, IDirect3DSurface9** ppSurfaceLevel );
	HRESULT UpdateSurface( IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPointsArray );
	HRESULT DeletePixelShader( DWORD Handle );
	HRESULT DeleteVertexShader( DWORD Handle );
	HRESULT SetPixelShader( DWORD Handle );
	HRESULT SetFVFConstant(DWORD Register, CONST void* pConstantData, DWORD  ConstantCount );
	HRESULT SetPixelShaderConstant( DWORD Register, CONST void* pConstantData, DWORD ConstantCount );
	HRESULT GetVertexShader(DWORD * pHandle);
	HRESULT GetPixelShader(DWORD * pHandle);

	// PLAY VIDEO TO TEXTURE
	void	PlayToTexture();
	IDirect3DTexture9* GetVideoTexture(char* sVideoName);
	void ReleaseVideoTexture(IDirect3DTexture9* pTexture);


	virtual IDirect3DVertexBuffer9 * GetVertexBuffer(long id);
	virtual long GetVertexBufferFVF(long id);

	bool LoadTextureSurface(HANDLE file, IDirect3DSurface9 * suface, uint32_t mipSize, uint32_t width, uint32_t height, bool isSwizzled);
	uint32_t LoadCubmapSide(HANDLE file, IDirect3DCubeTexture9 * tex, D3DCUBEMAP_FACES face, uint32_t numMips, uint32_t mipSize, uint32_t size, bool isSwizzled);*/

	void SetProgressImage(const char * image) override;
	void SetTipsImage(const char * image) override;
	void StartProgressView() override;
	void ProgressView() override;
	void EndProgressView() override;

	static const uint32_t rectsVBuffer_SizeInRects;
	IDirect3DVertexBuffer9	* rectsVBuffer;

	char * progressImage;
	long progressImageSize;
	long backTexture;
	long progressTexture;
	char * progressTipsImage;
	long progressTipsImageSize;
	long progressTipsTexture;

	long loadFrame;
	long progressSafeCounter;
	bool isInPViewProcess;
	uint32_t progressUpdateTime;
	float progressFramesPosX;
	float progressFramesPosY;
	float progressFramesWidth;
	float progressFramesHeight;
	long progressFramesCountX;
	long progressFramesCountY;

	D3DPRESENT_PARAMETERS d3dpp;
	bool bDeviceLost;

	CMatrix mView, mWorld, mProjection;

	CVECTOR vWordRelationPos;
	CVECTOR vViewRelationPos;

	bool bUseLargeBackBuffer;

	bool IsInsideScene() override {return bInsideScene;}

	char * GetTipsImage() override;

	void SetColorParameters(float fGamma, float fBrightness, float fContrast) override;
	void DrawSphere(const CVECTOR & vPos, float fRadius, uint32_t dwColor) override;

	void GetNearFarPlane(float & fNear, float & fFar) override;
	void SetNearFarPlane(float fNear, float fFar) override;

	void SetLoadTextureEnable(bool bEnable = true) override;
	bool ResetDevice();

	void MakeDrawVector(RS_LINE * pLines, uint32_t dwNumSubLines, const CMatrix & mMatrix, CVECTOR vUp, CVECTOR v1, CVECTOR v2, float fScale, uint32_t dwColor);
	void _cdecl DrawVector(const CVECTOR & v1, const CVECTOR & v2, uint32_t dwColor, const char * pTechniqueName = "DX9Vector", uint32_t dwNumParams = 0, ...) override;
	IDirect3DBaseTexture9 * GetBaseTexture(long iTexture) override;

	IDirect3DBaseTexture9 * CreateTextureFromFileInMemory(const char * pFile, uint32_t dwSize) override;

	bool PushRenderTarget() override;
	bool PopRenderTarget() override;
	bool SetRenderTarget(IDirect3DCubeTexture9 * pCubeTex, uint32_t dwFaceType, uint32_t dwLevel, IDirect3DSurface9* pNewZStencil) override;
	void SetView(const CMatrix & mView) override;
	void SetWorld(const CMatrix & mView) override;
	void SetProjection(const CMatrix & mView) override;
	const CMatrix & GetView() override;
	const CMatrix & GetWorld() override;
	const CMatrix & GetProjection() override;

	IDirect3DVolumeTexture9 * CreateVolumeTexture(uint32_t Width, uint32_t Height, uint32_t Depth, uint32_t Levels, uint32_t Usage, D3DFORMAT Format, D3DPOOL Pool) override;

	void MakePostProcess() override;
	void SetGLOWParams (float _fBlurBrushSize, long _GlowIntensity, long _GlowPasses) override;

	IDirect3DBaseTexture9* GetTextureFromID(long nTextureID) override;

	void LostRender();
	void RestoreRender();
};

#endif