#ifndef PAL3APATCH_PAL3A_H
#define PAL3APATCH_PAL3A_H
// PATCHAPI DEFINITIONS


extern PATCHAPI void *load_image_bits(void *filedata, unsigned filelen, int *width, int *height, int *bitcount, const struct memory_allocator *mem_allocator);
extern PATCHAPI void ensure_cooperative_level(int requirefocus);
extern PATCHAPI void clamp_rect(void *bits, int width, int height, int bitcount, int pitch, int left, int top, int right, int bottom);
extern PATCHAPI void copy_bits(void *dst, int dst_pitch, int dst_x, int dst_y, void *src, int src_pitch, int src_x, int src_y, int width, int height, int bitcount);
extern PATCHAPI void fill_texture(IDirect3DTexture9 *tex, D3DCOLOR color);
extern PATCHAPI void set_d3dxfont_matrices(IDirect3DDevice9 *pd3dDevice);


#ifdef USE_PAL3A_DEFINITIONS

struct member_function_pointer {
    union {
        struct {
            void *fp;
            BYTE gap4[12];
        };
        struct {
            unsigned long long gap0[2]; // force align
        };
    };
};

struct gbAudioMgrDesc {
    unsigned int frequence;
    unsigned int bits;
    unsigned int channels;
    char provider[256];
};

struct PtrArray {
    void **m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct gbColorQuad {
    union {
        struct {
            unsigned char Blue;
            unsigned char Green;
            unsigned char Red;
            unsigned char Alpha;
        };
        unsigned int Color;
    };
};

struct UIWnd {
    struct UIWndVtbl *vfptr;
    struct gbColorQuad m_fontcolor;
    struct gbColorQuad m_wndcolor;
    unsigned int m_id;
    RECT m_rect;
    struct UIWnd *m_pfather;
    struct PtrArray m_childs;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};

struct UIWndVtbl {
    MAKE_THISCALL(void, *ShowWindow, struct UIWnd *this, int);
    MAKE_THISCALL(void, *Render, struct UIWnd *this);
    MAKE_THISCALL(int, *Update, struct UIWnd *this, float, int);
    MAKE_THISCALL(void, *Destroy, struct UIWnd *this);
    MAKE_THISCALL(void, *Create, struct UIWnd *this, unsigned int, RECT *, struct UIWnd *, char);
    void *scalar_deleting_destructor;
    MAKE_THISCALL(int, *OnMessage, struct UIWnd *this, unsigned int, unsigned int, unsigned int);
};
#define UIWnd_vfptr_Render(this) THISCALL_WRAPPER((this)->vfptr->Render, this)
#define UIWnd_vfptr_Update(this, deltatime, haveinput) THISCALL_WRAPPER((this)->vfptr->Update, this, deltatime, haveinput)

struct gbMatrix4 {
    float m[4][4];
};

struct gbVec3D {
    float x;
    float y;
    float z;
};

struct gbColorFlt {
    float Red;
    float Green;
    float Blue;
    float Alpha;
};

struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};

struct gbClearParam {
    struct gbColorQuad color;
    float depth;
    int stencil;
    unsigned int clearflag;
};

struct gbGfxStatistic {
    int nRFaces;
    int nRVerts;
    int nStaticVerts;
    int nStaticIndex;
    int nSrcVerts;
    int nSrcIndex;
    int nTexSwitch;
    float FPS;
    double TimeAccum;
    unsigned int Frame;
    unsigned int PrevFrame;
};

enum gbLight_gbLightType {
    GBLIGHT_POINT = 0x1,
    GBLIGHT_SPOT = 0x2,
    GBLIGHT_DIRECT = 0x3,
};

struct gbLight {
    enum gbLight_gbLightType type;
    struct gbColorFlt diffuse;
    struct gbColorFlt specular;
    struct gbColorFlt ambient;
    struct gbVec3D position;
    struct gbVec3D direction;
    float range;
    float falloff;
    float attenuation0;
    float attenuation1;
    float attenuation2;
    float theta;
    float phi;
};

enum gbFogParam_gbFogType {
    FOGTYPE_NULL = 0x0,
    FOGTYPE_DIST = 0x1,
    FOGTYPE_PLANE = 0x2,
    FOGTYPE_SPHERE = 0x3,
};

enum gbFogParam_gbFogMode {
    FOGMODE_LINEAR = 0x0,
    FOGMODE_EXP = 0x1,
    FOGMODE_EXP2 = 0x2,
};

struct gbFogParam {
    enum gbFogParam_gbFogType type;
    struct gbColorFlt color;
    enum gbFogParam_gbFogMode mode;
    float start;
    float end;
    float density;
    float plane[4];
};

enum VertexProcessingType {
    SOFTWARE_VP = 0x0,
    MIXED_VP = 0x1,
    HARDWARE_VP = 0x2,
    PURE_HARDWARE_VP = 0x3,
};

struct CD3DEnumeration {
    struct IDirect3D9 *m_pD3D;
    struct CArrayList *m_pAdapterInfoList;
    char (__cdecl *ConfirmDeviceCallback)(D3DCAPS9 *, enum VertexProcessingType, D3DFORMAT, D3DFORMAT);
    unsigned int AppMinFullscreenWidth;
    unsigned int AppMinFullscreenHeight;
    unsigned int AppMinColorChannelBits;
    unsigned int AppMinAlphaChannelBits;
    unsigned int AppMinDepthBits;
    unsigned int AppMinStencilBits;
    char AppUsesDepthBuffer;
    char AppUsesMixedVP;
    char AppRequiresWindowed;
    char AppRequiresFullscreen;
    struct CArrayList *m_pAllowedAdapterFormatList;
};

struct D3DDriverBug {
    int Gamma_LowByte;
};

struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[128];
    DWORD hinst;
    HWND hgfxwnd;
    int newwindow;
    int waitforverticalblank;
};

struct gbDynArray_pgbResource {
    struct gbResource **pBuffer;
    int MaxNum;
    int CurNum;
};


struct gbRefObject {
    struct gbRefObjectVtbl *vfptr;
    int RefCount;
};

struct gbResource {
    struct gbRefObject;
    char *pName;
    unsigned int NameCrc32;
    int IsLoaded;
    struct gbResManager *pMgr;
};

struct gbResManager {
    struct gbDynArray_pgbResource;
};

struct CD3DSettings {
    char IsWindowed;
    struct D3DAdapterInfo *pWindowed_AdapterInfo;
    struct D3DDeviceInfo *pWindowed_DeviceInfo;
    struct D3DDeviceCombo *pWindowed_DeviceCombo;
    D3DDISPLAYMODE Windowed_DisplayMode;
    D3DFORMAT Windowed_DepthStencilBufferFormat;
    D3DMULTISAMPLE_TYPE Windowed_MultisampleType;
    unsigned int Windowed_MultisampleQuality;
    enum VertexProcessingType Windowed_VertexProcessingType;
    unsigned int Windowed_PresentInterval;
    int Windowed_Width;
    int Windowed_Height;
    struct D3DAdapterInfo *pFullscreen_AdapterInfo;
    struct D3DDeviceInfo *pFullscreen_DeviceInfo;
    struct D3DDeviceCombo *pFullscreen_DeviceCombo;
    D3DDISPLAYMODE Fullscreen_DisplayMode;
    D3DFORMAT Fullscreen_DepthStencilBufferFormat;
    D3DMULTISAMPLE_TYPE Fullscreen_MultisampleType;
    unsigned int Fullscreen_MultisampleQuality;
    enum VertexProcessingType Fullscreen_VertexProcessingType;
    unsigned int Fullscreen_PresentInterval;
};

struct gbGfxManager {
    struct gbGfxManagerVtbl *vfptr;
    DWORD gap4[1];
    unsigned int hGfxWnd;
    struct gbGfxDriverInfo DrvInfo;
    struct gbVertPoolMgr *pVertPoolMgr;
    struct gbEffectMgr *pEffectMgr;
    struct gbResManager *pTexResMgr;
    struct gbPrintFontMgr *pFontMgr;
    struct gbMatrixStack *pMatrixStack[4];
    struct gbMatrix4 ViewMatrix;
    struct gbMatrix4 InvViewMatrix;
    struct gbMatrix4 WorldMatrix;
    int CurZBias;
    int bWireMode;
    struct gbColorFlt AmbientLight;
    float fSelfIllum;
    struct gbSceneGraph *pSceneGraph;
    struct gbViewPort Viewport;
    struct gbClearParam ClearParam;
    double LastTime;
    double CurTime;
    unsigned int LastTick;
    unsigned int CurTick;
    struct gbGfxStatistic Stat;
    struct gbLight AllLight[8];
    int LightEnable[8];
    struct gbFogParam FogParam;
    struct gbTexture *m_pCurTexture[8];
};

struct gbGfxManager_D3D {
    struct gbGfxManager;
    struct CD3DEnumeration m_d3dEnumeration;
    int m_bWindowed;
    RECT m_rcWindowClient;
    RECT m_rcWindowBounds;
    unsigned int m_dwWindowStyle;
    HWND *m_hWnd;
    bool m_bMinimized;
    bool m_bMaximized;
    bool m_bClipCursorWhenFullscreen;
    bool m_bShowCursorWhenFullscreen;
    bool m_bActive;
    unsigned int m_dwCreateFlags;
    struct D3DDriverBug m_DriverBug;
    struct gbResManager m_CursorMgr;
    struct gbCursorRes *m_pActiveCursor;
    int m_bShowCursor;
    int m_bSoftVPMode;
    struct CD3DSettings m_d3dSettings;
    D3DPRESENT_PARAMETERS m_d3dpp;
    IDirect3D9 *m_pD3D;
    IDirect3DDevice9 *m_pd3dDevice;
    D3DCAPS9 m_d3dCaps;
    D3DSURFACE_DESC m_d3dsdBackBuffer;
    char m_strDeviceStats[90];
    int m_ErrorCode;
    int m_bDeviceLost;
    IDirect3DSurface9 *m_pBackBuffer;
    int m_DXTSupported[5];
    IDirect3DVertexBuffer9 *m_pCacheVB;
    IDirect3DIndexBuffer9 *m_pCacheIB;
};

struct gbUIQuad {
    float sx;
    float sy;
    float ex;
    float ey;
    float su;
    float sv;
    float eu;
    float ev;
    float z;
    struct gbColorQuad color;
};


struct CPKHeader {
    unsigned int dwLable;
    unsigned int dwVersion;
    unsigned int dwTableStart;
    unsigned int dwDataStart;
    unsigned int dwMaxFileNum;
    unsigned int dwFileNum;
    unsigned int dwIsFormatted;
    unsigned int dwSizeOfHeader;
    unsigned int dwValidTableNum;
    unsigned int dwMaxTableNum;
    unsigned int dwFragmentNum;
    unsigned int dwPackageSize;
    unsigned int dwReserved[20];
};

struct CPKTable {
    unsigned int dwCRC;
    unsigned int dwFlag;
    unsigned int dwFatherCRC;
    unsigned int dwStartPos;
    unsigned int dwPackedSize;
    unsigned int dwOriginSize;
    unsigned int dwExtraInfoSize;
};


enum ECPKMode {
    CPKM_Null = 0x0,
    CPKM_Normal = 0x1,
    CPKM_FileMapping = 0x2,
    CPKM_Overlapped = 0x3,
    CPKM_End = 0x4,
};

#define tagCPKHeader CPKHeader
#define tagCPKTable CPKTable

struct CPK {
    unsigned int m_dwAllocGranularity;
    enum ECPKMode m_eMode;
    struct tagCPKHeader m_CPKHeader;
    struct tagCPKTable m_CPKTable[32768];
    struct gbVFile *m_pgbVFile[8];
    bool m_bLoaded;
    unsigned int m_dwCPKHandle;
    unsigned int m_dwCPKMappingHandle;
    char m_szCPKFileName[260];
    int m_nOpenedFileNum;
};

struct gbBinkVideo {
    struct gbBinkVideoVtbl *vfptr;
    struct tagPOINT m_pos;
    struct BINK *m_hBink;
    struct CPK m_Cpk;
    struct CPK m_Cpk2;
};

enum GAME_STATE {
    GAME_NONE = 0x0,
    GAME_UI = 0x1,
    GAME_SCENE = 0x2,
    GAME_COMBAT = 0x3,
    GAME_CATCHGHOST = 0x4,
    GAME_WOLF = 0x5,
    GAME_HIDE_FIGHT = 0x6,
    GAME_COMPDONATE = 0x7,
    GAME_OVER = 0x8,
};

struct D3DAdapterInfo {
    int AdapterOrdinal;
    D3DADAPTER_IDENTIFIER9 AdapterIdentifier;
    struct CArrayList *pDisplayModeList;
    struct CArrayList *pDeviceInfoList;
};

enum CURSOR_TYPE {
    CURSOR_NORMAL = 0x0,
    CURSOR_TALK = 0x1,
    CURSOR_CHECK = 0x2,
    CURSOR_NUM = 0x3,
};

struct UICursor {
    unsigned int m_dwID[3];
    enum CURSOR_TYPE m_active;
    struct gbTexture *m_tex[3];
    char m_bShow;
    char m_bSoftMode;
};

struct gbQuaternion {
    float x;
    float y;
    float z;
    float w;
};

struct gbCamera {
    float fov;
    float OrthoSize;
    float Wscreen;
    float Hscreen;
    float zNear;
    float zFar;
    struct gbViewPort Viewport;
    float Plane[6][4];
    int numPlane;
    struct gbMatrix4 ViewMatrix;
    struct gbMatrix4 InvVMatrix;
    struct gbCamControler *pControl[16];
    int CurCtrl;
    struct gbGfxManager *pGfxMgr;
    struct gbVec3D eyeLoc;
    struct gbQuaternion eyeDir;
};

struct GRP_KEYREG {
    int Data;
    int HoldTime;
    int CountMode;
    int PressTime;
};

struct GRPinput {
    IDirectInput8A *m_lpDI;
    IDirectInputDevice8A *m_lpDIDKeyboard;
    IDirectInputDevice8A *m_lpDIDMouse;
    float m_mouseSensitivity;
    int m_mouseMinX;
    int m_mouseMinY;
    int m_mouseMaxX;
    int m_mouseMaxY;
    int m_joystickMinX;
    int m_joystickMinY;
    int m_joystickMaxX;
    int m_joystickMaxY;
    POINT m_mousept;
    int m_mouseX;
    int m_mouseY;
    int m_mouseFreeX;
    int m_mouseFreeY;
    int m_mouseDeltaX;
    int m_mouseDeltaY;
    int m_joystickX;
    int m_joystickY;
    int m_joystickFreeX;
    int m_joystickFreeY;
    int m_joystickDeltaX;
    int m_joystickDeltaY;
    BYTE m_keyStates[270];
    BYTE m_keyRaw[256];
    unsigned int m_keyPressTimes[270];
    unsigned int m_keyDragStartPositions[270][2];
    BYTE m_shiftedKeyStates[270];
    unsigned int m_DIKToKEY[256];
    DIMOUSESTATE2 MouseState;
    unsigned int charTOscan[256];
    int KeyTransformation[10];
    int m_bMouse;
    int m_bKeyboard;
    int m_bJoystick;
    struct GRP_KEYREG KeyInfo[270];
};

enum ECBStageLockFlag {
    CBSLF_Null = 0x0,
    CBSLF_SkillAct = 0x1,
    CBSLF_MagicWait = 0x2,
    CBSLF_MagicAct = 0x3,
    CBSLF_ItemAct = 0x4,
    CBSLF_FlingAct = 0x5,
    CBSLF_BFAAct = 0x6,
    CBSLF_End = 0x7,
};

struct tagAttackSequen {
    float fDeltaTime;
    float fLastTime;
    int nIndex;
    unsigned int dwID;
    struct UIStatic *pPic;
    int nSlot1;
    int nSlot2;
    int nRound;
    BYTE bySpeed1;
    BYTE bySpeed2;
    bool bSlot2Running;
    bool bPaused;
    bool bValid;
};

struct CCBAttackSequen {
    struct CCBSystem *m_pCBSystem;
    struct CCBUI *m_pUI;
    struct CCBRoleState *m_pRole;
    struct tagAttackSequen m_Sequen[11];
    bool m_bEnable;
    bool m_bPause;
    bool m_bVisible;
    bool m_bLocked;
    enum ECBStageLockFlag m_eLockFlag[11];
};

enum ECBCombatState {
    CBCS_Null = 0x0,
    CBCS_Deactive = 0x1,
    CBCS_Running = 0x2,
    CBCS_Paused = 0x3,
    CBCS_Flee = 0x4,
    CBCS_Counting = 0x5,
    CBCS_FleeCounting = 0x6,
    CBCS_LoseCounting = 0x7,
    CBCS_CombatEnd = 0x8,
    CBCS_End = 0x9,
};
enum ECBCombatResult {
    CBCR_Null = 0x0,
    CBCR_NoResult = 0x1,
    CBCR_Win = 0x2,
    CBCR_Lose = 0x3,
    CBCR_FleeOK = 0x4,
    CBCR_End = 0x5,
};

struct tagCmdData {
    unsigned int dwCmdKind;
    union {
        unsigned int dwCmdID;
        unsigned int dwItemID;
    };
    int nSrcRole;
    int nDestRole;
    bool bMultiSrcRole;
    bool bMultiDestRole;
    bool bSrcRole[11];
    bool bDestRole[11];
    bool bValid;
};

struct tagThread {
    struct member_function_pointer fp;
    unsigned int dwID;
    int nTaskIndex;
    unsigned int dwTaskID;
    unsigned int dwReturn;
    int nTemp;
    bool bValid;
    bool bExecuted;
    struct tagCmdData cmd;
};

struct tagPlayerSet {
    struct tagCmdData LastRoleCmd;
    int nMagicDefaultPage;
    int nItemDefaultPage;
};

struct CCBSystem {
    struct CUtil *m_pUtil;
    struct CCBUI *m_pUI;
    struct CCBControl *m_pControl;
    struct CCBAttackSequen *m_pAttackSequen;
    struct CCBRoleState *m_pRoleState;
    struct CCBStage *m_pStage;
    struct CCBAI *m_pAI;
    struct CCBEditor *m_pEditor;
    struct CEffectSystem *m_pES;
    struct CEffectSimple *m_pEffectSimple;
    struct TxtFile *m_pConfig;
    struct CEffMgr *m_pEffMgr;
    struct CEffMgr *m_pATSEffMgr;
    struct C2DSpark *m_p2DSpark;
    struct C3DSpark *m_p3DSpark;
    double m_DeltaTime;
    double m_dTimeFund;
    float m_fTimeFund;
    double m_AbsDeltaTime;
    double m_dAbsTimeFund;
    float m_fAbsTimeFund;
    float m_fTimeScale;
    struct FightInfo *m_pFightInfo;
    bool m_bQuitFlag;
    bool m_bPause;
    enum ECBCombatState m_eState;
    enum ECBCombatResult m_eResult;
    char m_bFiveNimbus;
    char m_bPXVariance;
    int m_nTimesOfCombat;
    bool m_bAuto;
    bool m_bEditor;
    bool m_bLockCam;
    bool m_bFirstRender;
    unsigned int m_dwIDHolder;
    int m_nThread;
    int m_nCurThread;
    struct tagThread m_Thread[1024];
    struct tagPlayerSet m_Player[11];
};

typedef struct BINK BINK, *HBINK;



struct std_basic_string { // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char allocator;
    char *_Ptr;
    unsigned int _Len;
    unsigned int _Res;
};

struct std_vector_int {
    char allocator;
    int *_First;
    int *_Last;
    int *_End;
};

struct std_vector_SoundItem {
    char allocator;
    struct SoundItem *_First;
    struct SoundItem *_Last;
    struct SoundItem *_End;
};

struct TxtFile {
    char m_token[512];
    char *m_buf;
    char *m_sectionstart;
    char *m_curpos;
};

struct SoundMgr {
    struct SoundMgrVtbl *vfptr;
    char m_bScriptMusic;
    struct std_basic_string m_szScriptMusic;
    int m_nScriptLoop;
    char m_szSceneMusic[256];
    struct TxtFile m_MusicTable;
    struct gbAudioManager *m_audiodrv;
    float DEF3DMasterVol;
    float DEF2DMasterVol;
    float DEFMusicMasterVol;
    char m_bValidDetectSceneMusic;
    struct std_vector_SoundItem m_cbbuf;
    int m_cbcursor;
    struct CPK m_Cpk;
};

typedef struct _SAMPLE *HSAMPLE;
typedef struct _STREAM *HSTREAM;
typedef struct _DIG_DRIVER *HDIGDRIVER;
typedef struct h3DPOBJECT *H3DPOBJECT;

struct SoundAttachObj {
    union {
        struct gbSound3DNode *p3d;
        struct gbSound2DNode *p2d;
    };
    union {
        H3DPOBJECT h3d;
        HSAMPLE h2d;
    };
    unsigned int time;
};

struct gbAudioManager {
    HSTREAM *hStreamArray[3];
    int StreamStatus[3];
    HDIGDRIVER *h2DDriver;
    unsigned int h3DProvider;
    struct SoundAttachObj Attach3D[10];
    struct SoundAttachObj Attach2D[4];
    unsigned int CurTime;
    float S_3DMasterVol;
    float S_2DMasterVol;
    float MusicMasterVol;
    H3DPOBJECT *hListener;
    struct gbVec3D ListenerPos;
    struct gbResManager SndDataMgr;
};

enum gbPixelFmtType { 
    GB_PFT_UNKNOWN,
    GB_PFT_R8G8B8,
    GB_PFT_A8R8G8B8,
    GB_PFT_R5G6B5,
    GB_PFT_A1R5G5B5,
    GB_PFT_A4R4G4B4,
    GB_PFT_P8,
    GB_PFT_A8,
    GB_PFT_X8R8G8B8,
    GB_PFT_X1R5G5B5,
    GB_PFT_X4R4G4B4,
};

struct gbSurfaceDesc {
    int width;
    int height;
    enum gbPixelFmtType format;
    int pitch;
    void *pbits;
};

struct gbPixelFormat {
    enum gbPixelFmtType Type;
    int Bpp;
    struct gbColorQuad *Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;
};

struct gbTexture {
    struct gbResource;
    int Width;
    int Height;
    struct gbImage2D *pTexImage;
    struct gbPixelFormat InFmt;
    int nLevels;
};
struct gbTexture_D3D {
    struct gbTexture;
    IDirect3DBaseTexture9 *pTex;
    IDirect3DSurface9 *pDS;
    unsigned int m_ImgFormat;
};

struct CTrail {
    float m_fTime;
    bool m_bSupport;
    bool m_bEnable;
    struct gbCamera *m_pCam;
    struct gbUIQuad m_ScreenQuad;
    unsigned int m_dwRenderCounter;
    unsigned int m_dwRT;
    char m_bReady;
    struct gbTexture_D3D m_texRT[8];
    struct gbRenderEffect *m_eft;
    struct IDirect3DSurface9 *m_OriginSurface;
};

struct gbTextureArray {
    struct gbTexture *pTexPt[16];
    int nTex;
};

enum gbPoolType {
    GB_POOL_STATIC = 0x0,
    GB_POOL_WRITEONLY = 0x1,
    GB_POOL_READONLY = 0x2,
};

struct gbDynVertBuf {
    struct gbDynVertBufVtbl *vfptr;
    enum gbPoolType Type;
    int VertNum;
    unsigned int VertType;
    int Stride;
    int BaseIndex;
    int LockVertNum;
    float *pXYZ;
    float *pNormal;
    struct gbColorQuad *pColor1;
    struct gbColorQuad *pColor2;
    float *pUV[4];
};

struct gbPrintFont {
    struct gbPrintFontVtbl *vfptr;
    struct FontPrintInfo *ptInfo;
    struct FontSortInfoObj *pSortInfo;
    int maxInfo;
    int numInfo;
    struct FontPrint3DInfo *pt3DInfo;
    int num3DInfo;
    int max3DInfo;
    char *strBuffer;
    int maxStrBuffer;
    int curStrLoc;
    struct gbColorQuad curColor;
    float ScaleX;
    float ScaleY;
    float PitchX;
    float PitchY;
    float ZValue;
    struct gbRenderEffect *pEffect[2];
};

struct RenderTarget {
    int m_iMode;
    struct gbTexture_D3D m_Texture;
    struct gbTexture_D3D m_ScreenPlane;
    int m_nState;
};

struct gbCachedChinaFont {
    struct gbPrintFont;
    int nCacheTex;
    unsigned char *pFontImage;
    struct gbTexture *pCacheTex[16];
    int maxChars;
    unsigned char *pCharPoint;
    unsigned short *pAllChar;
    int nCacheSlot;
    struct gbCharCacheSlot *pCacheSlots;
    unsigned int iFrame;
    union {
        int FONT_SIZE;
        int fontsize;
    };
    int FONT_BITCOUNT;
    int FONT_BYTES;
    int CACHE_TEX_SIZE;
    float FONT_TEX_SIZE;
    int TEX_NCHAR;
};
#define gbPrintFont_UNICODE gbCachedChinaFont

enum gbFontType {
    GB_FONT_UNICODE12 = 0x0,
    GB_FONT_UNICODE16 = 0x1,
    GB_FONT_UNICODE20 = 0x2,
    GB_FONT_NUMBER = 0x3,
    GB_FONT_ASC = 0x4,
};

struct UI3DObj {
    bool m_mouseoff;
    int m_enable;
    int m_needdel;
    int m_type;
    union {
        struct gbGeomNode *m_pol;
        struct Actor *m_actor;
    };
    struct gbVec3D m_pos;
};

struct UI3DCtrl {
    struct UIWnd;
    int m_numobj;
    struct UI3DObj m_obj[5];
    float m_orthosize;
    int m_rotatemode;
    bool m_isrotateto;
    int m_speed;
    float m_rotate;
    float m_rotatetarget;
    float m_rotx;
    float m_rotz;
    float m_dropx;
    float m_dropy;
    float m_dropz;
    float m_scalex;
    float m_scaley;
    float m_scalez;
    struct gbLightObj *m_lightobj;
    struct gbCamera *m_camera;
    struct gbVec3D m_raydir;
};

struct UIStatic {
    struct UIWnd;
    int m_bordersize;
    int m_align;
    float m_ratiow;
    float m_ratioh;
    int m_textx;
    int m_texty;
    enum gbFontType m_fonttype;
    struct std_basic_string m_text;
    struct gbTexture *m_pbk;
    struct _PlugInfo *m_pbkInfo;
    struct gbTexture *m_ppic;
    struct _PlugInfo *m_ppicInfo;
    struct gbTexture *m_disablepic;
    struct _PlugInfo *m_disablepicInfo;
    struct gbTexture *m_pbk2;
    bool m_mouseoff;
    int m_FVF;
    int m_nTextW;
    bool m_PureColor;
    int m_richtext;
};

struct UIStaticEX {
    struct UIStatic;
    float m_rotate;
    int m_rotmode;
    float m_rotdst;
    float m_rotspeed;
    int m_rotdir;
    bool m_isStoped;
    float m_accelerate;
    float m_notespeed;
};

struct UIStaticEXA {
    struct UIStaticEX;
    int center_x;
    int center_y;
};

struct UnderWater {
    bool m_bEnable;
    IDirect3DIndexBuffer9 *m_pIB;
    IDirect3DVertexBuffer9 *m_pVB;
    IDirect3DTexture9 *m_pBumpmapTex;
    int m_iMode;
    float m_fTime;
};

struct C2DSpark_tagSpark {
    float fx;
    float fy;
    float fVx;
    float fVy;
    float fAx;
    float fAy;
    float fLum;
    float fLumInc;
    float fSize;
    float fSizeInc;
    BYTE byColor;
    bool bValid;
    struct gbColorQuad color;
};

enum ECBShowItemKind {
    CBSIK_Null,
    CBSIK_Txt,
    CBSIK_RoleState,
    CBSIK_PrintTxt,
    CBSIK_Pic,
    CBSIK_FiveLineup,
    CBSIK_EnemyFiveLineup,
    CBSIK_CombatDialog,
    CBSIK_ScreenQuad,
    CBSIK_End,
};

struct tagShowItem {
    enum ECBShowItemKind eKind;
    char sTxt[256];
    struct tagRGBQUAD color;
    float fX;
    float fY;
    float fZ;
    float fSize;
};

struct UIFrameWnd {
    struct UIWnd;
    struct gbTexture *m_pbktex;
};

struct tagUIParam {
    struct UIWnd *pUI;
    float fFromX;
    float fFromY;
    float fEndX;
    float fEndY;
    float fSpeed;
    float fEnergy;
    int nTimes;
};

struct tagUITask {
    struct member_function_pointer fp;
    bool bValid;
    bool bExecuted;
    bool bFinished;
    unsigned int dwID;
    float fStartTime;
    float fExpectStartTime;
    float fExpectEndTime;
    struct tagUIParam param;
};

struct CCBUI {
    struct UIFrameWnd;
    struct UIStatic *m_pAttackSequenBack;
    struct UIStatic *pPanel;
    struct UIStatic *m_pBattleFieldAttr[6];
    struct UIStatic *m_pAttackSequenFace[11];
    struct UIStatic *m_pRoleStatePanel[4];
    struct UIStatic *m_pRoleStateFace[5];
    struct UIStatic *m_pRoleStateFaceName[5];
    union {
        struct {
            struct UIStatic *m_pRoleStateAttackInc[11];
            struct UIStatic *m_pRoleStateAttackDec[11];
            struct UIStatic *m_pRoleStateDefenceInc[11];
            struct UIStatic *m_pRoleStateDefenceDec[11];
            struct UIStatic *m_pRoleStateLuckInc[11];
            struct UIStatic *m_pRoleStateLuckDec[11];
            struct UIStatic *m_pRoleStateSpeedInc[11];
            struct UIStatic *m_pRoleStateSpeedDec[11];
            struct UIStatic *m_pRoleStateStable[11];
            struct UIStatic *m_pRoleStateBlank[11];
            struct UIStatic *m_pRoleStateForbid[11];
            struct UIStatic *m_pRoleStateSleep[11];
            struct UIStatic *m_pRoleStateChaos[11];
            struct UIStatic *m_pRoleStateMad[11];
            struct UIStatic *m_pRoleStateMirror[11];
            struct UIStatic *m_pRoleStateWall[11];
            struct UIStatic *m_pRoleStateBound[11];
            struct UIStatic *m_pRoleStateHermit[11];
            struct UIStatic *m_pRoleStateImmunity[11];
        };
        struct UIStatic *m_pRoleSpecState[19][11];
    };
    struct UIStatic *m_pWinPanel;
    struct UIStatic *m_pLosePanel;
    struct UIProgressBar *m_pRoleStateHP[4];
    struct UIProgressBar *m_pRoleStateGP[4];
    struct UIProgressBar *m_pRoleStateMP[4];
    struct UIProgressBar *m_pRoleStateSword;
    struct UIStaticCB *m_pTrickName;
    struct UIStaticCB *m_pTrickName2;
    struct UIStatic *m_pDialogBack;
    struct UIStatic *m_pResultLevelup;
    struct UIStatic *m_pResultWindLvup;
    struct UIStatic *m_pResultThunderLvup;
    struct UIStatic *m_pResultWaterLvup;
    struct UIStatic *m_pResultFireLvup;
    struct UIStatic *m_pResultEarthLvup;
    struct UIStatic *m_pResultDoubleLvup;
    struct UIStatic *m_pResultGetItem;
    struct CCBControlWindow *m_pMain;
    struct CCBItemWindow *m_pItemWindow;
    struct CCBParabolaWindow *m_pParabolaWindow;
    struct CCBMagicWindow *m_pMagicWindow;
    struct CCBSkillWindow *m_pSkillWindow;
    struct CCBAIWindow *m_pAIWindow;
    struct CCBLineupWindow *m_pLineupWindow;
    struct CCBProtectWindow *m_pProtectWindow;
    struct CCBResultWindow *m_pResultWindow[4];
    struct CCBFiveNimbusWindow *m_pFiveNimbusWindow;
    struct CCBSystem *m_pCBSystem;
    struct CUtil *m_pUtil;
    struct tagUITask m_Task[32];
    bool m_bShowResult;
    struct member_function_pointer m_fp;
    int m_nTask;
    int m_nCurTask;
    int mImbibeNimbusNum;
    struct tagImbibeNimbus *m_pImbibeNimbus;
};

struct CCBLineupWindow {
    struct UIFrameWnd;
    int m_nInitRoleFaceLineup[5];
    struct UIStatic *m_pBack;
    struct UIStatic *m_pFace[5];
    int m_nSelected;
    struct CCBUI *m_pUI;
};

enum ECBFiveNimbus {
    CBFN_Water = 0x0,
    CBFN_Fire = 0x1,
    CBFN_Thunder = 0x2,
    CBFN_Wind = 0x3,
    CBFN_Earth = 0x4,
    CBFN_Max = 0x5,
};

struct tagImbibeNimbus {
    struct UIStatic *mNimbus;
    enum ECBFiveNimbus mNimbustype;
    struct gbVec3D mVelocity;
    struct tagPOINT mPos;
    bool bAlive;
    float mAccelerate;
    float mFX;
    float mFY;
};

struct ObjectCamera {
    struct gbCamera *m_pCamera;
    struct gbVec3D m_camFrom;
    struct gbVec3D m_camTo;
    struct gbVec3D m_camUp;
    struct gbVec3D m_camDirect;
    float m_yaw;
    float m_pitch;
    float m_roll;
    float m_dist;
    float m_nyaw;
    float m_npitch;
    float m_nroll;
    struct gbVec3D m_forward;
    struct gbVec3D m_side;
    float m_stepRotSpeed;
    float m_stepRot;
    int m_stepRotMode;
    int m_stepRotAxis;
    bool m_bStepRot;
};

struct LineupUI;

struct LineupComp;

struct UIPar_Star {
    struct UIWnd;
    struct gbTexture *m_pTex;
    struct gbColorQuad m_color;
    int m_nFinalAlpha;
    int m_nMinAlpha;
    int m_nFade;
    int m_IsFadeRand;
    int m_IsFadeOut;
    int m_nLastTime;
    int m_IsLastTimeRand;
    int m_IsHighPoint;
    int m_IsInFlash;
    int m_nNextTime;
    int m_IsNextTimeRand;
    int m_nFrame;
};

struct UIPar_Meteor {
    struct UIWnd;
    struct gbTexture *m_pTex[2];
    struct gbColorQuad m_color;
    int m_nWidth;
    int m_nHeight;
    struct tagRECT m_StartToEnd;
    struct tagPOINT m_tmpPt;
    struct tagPOINT m_TailPt[16];
    int m_nTailNum;
    int m_ntmpTailNum;
    int m_nFrameNumBetweenTail;
    float m_fVelocityX;
    float m_fVelocityY;
    float m_passtime;
    int m_IsInMeteor;
    int m_nNextTime;
    int m_nFrame;
};

struct _CLOUD {
    struct UIStatic _cloud;
    struct tagRECT _cloudRc;
    float _cloudFX;
    int _width;
    int _height;
    float _cloudSpeed;
    float _alpha;
    float _fade;
    bool _isfade;
    int _up;
    int _yPt;
    int _fluctuate;
};


struct UITextureArray {
    struct gbTexture *m_ptex[16];
    int m_num;
};

enum UIButton_UIBUTTON_STATE {
    NORMAL = 0x0,
    MOUSEON = 0x1,
    MOUSEDOWN = 0x2,
    NUMSTATE = 0x3,
};

struct UIButton {
    struct UIWnd;
    bool m_hasDBclk;
    float m_ratiow;
    float m_ratioh;
    struct tagRECT m_drawrc;
    enum UIButton_UIBUTTON_STATE m_state;
    bool m_canctrl;
    bool m_bLockUpdate;
    int m_offsetx;
    int m_offsety;
    bool m_bBigFont;
    struct UITextureArray m_texarray;
    struct _PlugInfo *m_texarrayInfo[3];
    struct gbTexture *m_disablepic;
    struct _PlugInfo *m_disablepicInfo;
    bool m_mouseoff;
    bool m_mouseon;
    int m_alignmode;
    char m_caption[128];
    bool m_benable_snd;
};

struct _btnOPTDATA {
    char *pData;
    unsigned int width;
    unsigned int height;
    unsigned int bpp;
};

struct UIButtonEX {
    struct UIButton;
    struct _btnOPTDATA m_optData[3];
};


enum MENU_TYPE {
    MENU_COVER = 0x0,
    MENU_QCYM = 0x1,
    MENU_LEAVE = 0x2,
    MENU_JDHY = 0x3,
    MENU_SCENE = 0x4,
    MENU_YXXX = 0x5,
    MENU_XJTM = 0x6,
    MENU_ARCSAVE = 0x7,
    MENU_NONE = 0x8,
};

struct Average {
    unsigned int _size;
    float *_data;
    float ret;
    unsigned int _cur;
    unsigned int _real;
    bool _initialize;
    bool _invalid;
    bool _full;
};

#define UIStaticFlex_State UIButton_UIBUTTON_STATE
struct UIStaticFlex {
    struct UIWnd;
    float DURATION;
    struct std_basic_string m_text;
    struct tagRECT m_currect;
    struct UITextureArray m_texs;
    enum UIStaticFlex_State m_state;
    float m_statetime;
    enum gbFontType m_fonttype;
    int m_tilesize;
    int m_openstyle;
};

struct UIDialog {
    struct UIWnd;
    int m_bmodal;
};

enum DLG_TYPE {
    DLG_YES = 0x0,
    DLG_NO = 0x1,
    DLG_YESNO = 0x2,
    DLG_MSGBOX = 0x3,
    DLG_TYPENUM = 0x4,
};

enum DLG_MSG {
    DLG_MSG_NONE = 0xFFFFFFFF,
    DLG_BT_YES = 0x0,
    DLG_BT_NO = 0x1,
    DLG_MSG_END = 0x2,
    DLG_MSG_NUM = 0x3,
};

struct _TimeMgr {
    unsigned int newtick;
    unsigned int oldtick;
    bool bNote;
};

struct MUIDialog {
    struct UIDialog;
    //struct MUIDialogMgr;
    struct UIWnd *ptr_Dlg;
    unsigned int m_DlgId;
    struct tagRECT m_rect;
    struct tagRECT m_textRc;
    struct UIStaticFlex m_bk;
    struct UIStatic m_static;
    struct UIStatic m_text;
    int m_btnW;
    int m_btnH;
    struct tagRECT m_btRc;
    struct UIButton mb_Yes;
    struct UIButton mb_No;
    int Lacune;
    enum DLG_TYPE m_type;
    enum DLG_MSG m_getMsg;
    int dft_W;
    int dft_H;
    bool m_IsModel;
    bool m_isDoModel;
    int m_xOffset;
    int m_yOffset;
    struct _TimeMgr _m_timeMgr;
    bool _m_canEndDlg;
    bool _haveSound;
};

struct UICoverFrm {
    struct UIFrameWnd;
    struct tagRECT rc;
    char buf[256];
    struct UIStatic m_background;
    struct UIPar_Star m_Star[13];
    struct UIPar_Meteor m_Meteor;
    struct _CLOUD m_cloud[10];
    struct _CLOUD m_midCloud[5];
    struct _CLOUD m_smlCloud[5];
    struct _CLOUD m_testCloud[9];
    struct UIStatic m_mountainA;
    struct UIStatic m_mountainB;
    struct UIStatic m_frame;
    struct UIStatic m_Logo;
    bool m_isAlpha;
    float m_alpha;
    struct UIStaticEXA m_tjA;
    struct UIStaticEXA m_tjB;
    struct UIButtonEX m_XDGS;
    struct UIButtonEX m_QCYM;
    struct UIButtonEX m_XJTM;
    struct UIButtonEX m_LKYX;
    struct UIButtonEX m_YXXX;
    struct UIButtonEX m_JDHY;
    struct UIButtonEX *m_CtrlBtn[6];
    int m_SelBtn;
    bool m_ExitGame;
    struct UITitle_QCYM *pQCYM;
    struct UITitle_JDHY *pJDHY;
    struct UITitle_YXXX *pYXXX;
    struct UITitle_XJTM *pXJTM;
    struct UITitle_ArcSave *pArcSave;
    struct UILoadingFrm *pLoadingFrm;
    enum MENU_TYPE m_MenuType;
    struct Average m_timeAverage;
    bool m_gotogame;
    unsigned int m_flag;
    struct UIStatic m_test;
    struct MUIDialog m_ArcDlg;
    struct MUIDialog m_Not1stDlg;
    bool m_goingin;
    bool m_ArcSaveSuc;
    bool m_IsReadFinishSave;
};

struct gbImage2DInfo {
    int isdiskinfo;
    int goal;
    int ngrade;
    int detail[8];
    int wdiv[8];
    int hdiv[8];
    int wrap_u;
    int wrap_v;
    int mipmap;
    int minfilter;
    int magfilter;
};

struct gbImage2D {
    struct gbImage2DInfo ImgInfo;
    int Width;
    int Height;
    struct gbPixelFormat PixelFmt;
    int BitCount;
    char *pBits;
    struct gbColorQuad *pPalette;
    int numPalEntry;
    struct gbColorQuad ColorKey;
};

struct gbVFileSystem {
    int IsInit;
    char *rtDirectory;
    struct gbVFile *pFileBuffer;
    enum {
        VFSYS_DISKFILE = 0x0,
        VFSYS_PACKFILE = 0x1,
        VFSYS_MEMIMAGE = 0x2,
    } Type;
    struct _iobuf *m_pckfp;
    unsigned int m_itemcount;
    struct CPK m_cpk;
};

// GBENGINE functions
#define gbx2x(gbx) (((gbx) + 1.0) * PAL3_s_drvinfo.width / 2.0)
#define gby2y(gby) ((1.0 - (gby)) * PAL3_s_drvinfo.height / 2.0)
#define x2gbx(x) ((x) * 2.0 / PAL3_s_drvinfo.width - 1.0)
#define y2gby(y) (1.0 - (y) * 2.0 / PAL3_s_drvinfo.height)
#define dx2gbdx(dx) ((dx) * 2.0 / PAL3_s_drvinfo.width)
#define dy2gbdy(dy) (-(dy) * 2.0 / PAL3_s_drvinfo.height)
#define scale_gbxdiff(xdiff, scalefactor) ((double)(xdiff) * (scalefactor) * GAME_WIDTH_ORG / PAL3_s_drvinfo.width)
#define scale_gbydiff(ydiff, scalefactor) ((double)(ydiff) * (scalefactor) * GAME_HEIGHT_ORG / PAL3_s_drvinfo.height)
#define pUIWND(x) ((struct UIWnd *)(x))
#define gbmalloc ((malloc_funcptr_t) (gboffset + 0x100C5C87))
#define gbfree ((free_funcptr_t) (gboffset + 0x100C5D39))
#define gbGfxManager_D3D_EndScene(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x100188E0, void, struct gbGfxManager_D3D *), this)
#define gbGfxManager_D3D_BuildPresentParamsFromSettings(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10019A70, void, struct gbGfxManager_D3D *), this)
#define gbGfxManager_D3D_Reset3DEnvironment(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001A480, int, struct gbGfxManager_D3D *), this)
#define gbCrc32Compute ((unsigned (*)(const char *)) TOPTR(gboffset + 0x10026710))
#define gbCamera_GetViewSizeOnNearPlane(this, hw, hh) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10021480, void, struct gbCamera *, float *, float *), this, hw, hh)
#define gbTexture_D3D_CreateForRenderTarget(this, width, height, format) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001B950, int, struct gbTexture_D3D *, int, int, enum gbPixelFmtType), this, width, height, format)
#define gbTexture_D3D_Ctor(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001B440, struct gbTexture_D3D *, struct gbTexture_D3D *), this)
#define gbTexture_D3D_Dtor(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001B490, void, struct gbTexture_D3D *), this)
#define gbCamera_SetDimention(this, a2, a3) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10021680, void, struct gbCamera *, int, int), this, a2, a3)
#define gbPrintFont_PrintString(this, str, x, y, endx, endy) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10022510, void, struct gbPrintFont *, const char *, float, float, float, float), this, str, x, y, endx, endy)
#define gbVertPoolMgr_GetDynVertBuf(this, a2) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10021150, struct gbDynVertBuf *, struct gbVertPoolMgr *, unsigned int), this, a2)
#define gbPrintFontMgr_GetFont(this, fonttype) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x100045F0, struct gbPrintFont *, struct gbPrintFontMgr *, enum gbFontType), this, fonttype)
#define gbVFileSystem_OpenFile(this, filename, mode) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1002DB10, struct gbVFile *, struct gbVFileSystem *, const char *, unsigned int), this, filename, mode)
#define gbVFileSystem_GetFileSize(this, fp) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1002E170, long, struct gbVFileSystem *, struct gbVFile *), this, fp)
#define gbVFileSystem_Read(this, buf, size, fp) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1002DD70, void, struct gbVFileSystem *, void *, unsigned int, struct gbVFile *), this, buf, size, fp)
#define gbVFileSystem_CloseFile(this, fp) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1002DCF0, void, struct gbVFileSystem *, struct gbVFile *), this, fp)




// PAL3A functions
#define pal3amalloc ((malloc_funcptr_t) TOPTR(0x00541A65))
#define pal3afree ((free_funcptr_t) TOPTR(0x005404C9))
#define PrepareDir ((int (*)(void)) TOPTR(0x00523059))
#define PAL3_InitGFX ((void (*)(void)) TOPTR(0x00406F01))
#define PAL3_Create ((void (*)(HINSTANCE)) TOPTR(0x0040673A))
#define PAL3_Destroy ((void (*)(void)) TOPTR(0x00407C9D))
#define PAL3_Update ((void (*)(double)) TOPTR(0x004073B0))
#define gbBinkVideo_SFLB_OpenFile(this, szFileName, hWnd, bChangeScreenMode, nOpenFlag) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x005254C0, int, struct gbBinkVideo *, const char *, HWND, int, int), this, szFileName, hWnd, bChangeScreenMode, nOpenFlag)
#define gbBinkVideo_DoModal(this, bCanSkip) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00525382, int, struct gbBinkVideo *, int), this, bCanSkip)
#define WndProc ((LRESULT (CALLBACK *)(HWND, UINT, WPARAM, LPARAM)) TOPTR(0x00406C91))
#define UICursor_Inst ((struct UICursor *(*)(void)) TOPTR(0x0052B734))
#define UICursor_Show(this, bShow) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0052B800, void, struct UICursor *, bool), this, bShow)
#define GRPinput_AcquireMouse(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00402B25, void, struct GRPinput *this), this)
#define GRPinput_AcquireKeyboard(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00402B78, void, struct GRPinput *this), this)
#define CCBRoleState_IsAlive(this, nIndex) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004DEFFD, bool, struct CCBRoleState *, int), this, nIndex)
#define BinkDoFrame (*(int (__stdcall **)(HBINK)) 0x005581DC)
#define BinkCopyToBuffer (*(int (__stdcall **)(HBINK, void *, int, unsigned, unsigned, unsigned, unsigned)) 0x005581D4)
#define BinkSetVolume (*(void (__stdcall **)(HBINK, int)) 0x005581D8)
#define g_bink (*(struct gbBinkVideo *) TOPTR(0x00A3E898))
#define SoundMgr_Inst() ((struct SoundMgr *) TOPTR(0x021AE020))
#define SoundMgr_GetAudioMgr(this) ((this)->m_audiodrv)
#define gbAudioManager_GetMusicMasterVolume(this) ((this)->MusicMasterVol)
#define gbBinkVideo_Width(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x005254A9, int, struct gbBinkVideo *), this)
#define gbBinkVideo_Height(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x005254B4, int, struct gbBinkVideo *), this)
#define gbBinkVideo_DrawFrameEx(this, pDestBuf, nDestPitch, nDestHeight, nDestLeft, nDestTop, nDestSurfaceType) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0052532F, int, struct gbBinkVideo *, void *, int, int, int, int, int), this, pDestBuf, nDestPitch, nDestHeight, nDestLeft, nDestTop, nDestSurfaceType)
#define gbBinkVideo_BinkWait(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00525291, int, struct gbBinkVideo *), this)
#define CTrail_Begin(this, pCam) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004B7424, void, struct CTrail *, struct gbCamera *), this, pCam)
#define UICursor_IRender(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0052B769, void, struct UICursor *), this)
#define RenderTarget_Inst ((struct RenderTarget *(*)(void)) TOPTR(0x004ADCF5))
#define UIDrawTextEx ((void (*)(const char *, RECT *, struct gbPrintFont *, int, int)) TOPTR(0x0052A73C))
#define UIPrint ((void (*)(int, int, char *, struct gbColorQuad *, int)) TOPTR(0x0052A54C))
#define UI3DCtrl_SetOriginPt_XY(this, x, y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00441E73, void, struct UI3DCtrl *, int, int), this, x, y)
#define UI3DCtrl_SetOriginPt_XYFromY(this, x, y, from_y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00441F34, void, struct UI3DCtrl *, int, int, int), this, x, y, from_y)
#define UI3DCtrl_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00441ACA, void, struct UI3DCtrl *), this)
#define UI3DCtrl_Update(this, deltatime, haveinput) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00441FFA, int, struct UI3DCtrl *, float, int), this, deltatime, haveinput)
#define UIStaticEX_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0044B319, void, struct UIStaticEX *), this)
#define UIStaticEXA_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0044B611, void, struct UIStaticEXA *), this)
#define UnderWater_Inst ((struct UnderWater *(*)(void)) TOPTR(0x004AFA9E))
#define C2DSpark_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004CA00F, void, struct C2DSpark *), this)
#define C2DSpark_CreateSingle(this, pSpark) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004C9D01, bool, struct C2DSpark *, struct C2DSpark_tagSpark *), this, pSpark)
#define C2DSpark_CreateStars(this, x, y, nWidth, fStarSize) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004C9E96, void, struct C2DSpark *, int, int, int, float), this, x, y, nWidth, fStarSize)
#define C2DSpark_CreateMore(this, x, y, color) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004C9D66, void, struct C2DSpark *, int, int, struct gbColorQuad), this, x, y, color)
#define CCBUI_Create(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0050B5F6, bool, struct CCBUI *), this)
#define UIWnd_MoveWindow(this, x, y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0044D075, void, struct UIWnd *, int, int), this, x, y)
#define UIFrameWnd_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00445CF3, void, struct UIFrameWnd *), this)
#define CCBUI_GetNimbusArea(this, rc, nimbustype) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0050E7EC, RECT *, struct CCBUI *, RECT *, enum ECBFiveNimbus), this, rc, nimbustype)
#define ObjectCamera_Create(this, pMgr) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0047B079, void, struct ObjectCamera *, struct gbGfxManager *), this, pMgr)
#define LineupUI_Create(this, pWnd) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00480EBF, void, struct LineupUI *, struct UIWnd *), this, pWnd)
#define LineupComp_Create(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x005215DE, void, struct LineupComp *), this)
#define UICoverFrm_Create(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00451581, void, struct UICoverFrm *), this)


// global variables
#define GB_GfxMgr (*(struct gbGfxManager_D3D **) TOPTR(0x00C01CD4))
#define PAL3_s_drvinfo (*(struct gbGfxDriverInfo *) TOPTR(0x00C01788))
#define PAL3_s_flag (*(unsigned *) TOPTR(0x00574D38))
#define PAL3_s_gamestate (*(int *) TOPTR(0x00C01CE0))
#define PAL3_s_bActive (*(int *) TOPTR(0x00574D34))
#define xmusic ((PAL3_s_flag & 4) == 0)
#define ui_tex_color_gbf (*(struct gbRenderEffect **) TOPTR(0x0228F004))
#define ui_color_blend_tex_gbf (*(struct gbRenderEffect **) TOPTR(0x0228F01C))
#define g_pVFileSys (*(struct gbVFileSystem **) TOPTR(gboffset + 0x10131D08))


// structure selfcheck
#define PAL3A_STRUCT_SELFCHECK() do { \
    assert(sizeof(struct gbAudioMgrDesc) == 0x10C); \
    assert(sizeof(struct gbColorQuad) == 0x4); \
    assert(sizeof(struct UIWnd) == 0x44); \
    assert(sizeof(struct PtrArray) == 0x10); \
    assert(sizeof(struct gbMatrix4) == 0x40); \
    assert(sizeof(struct gbVec3D) == 0xC); \
    assert(sizeof(struct gbColorFlt) == 0x10); \
    assert(sizeof(struct gbViewPort) == 0x18); \
    assert(sizeof(struct gbClearParam) == 0x10); \
    assert(sizeof(struct gbGfxStatistic) == 0x30); \
    assert(sizeof(struct gbLight) == 0x68); \
    assert(sizeof(struct gbFogParam) == 0x34); \
    assert(sizeof(struct CD3DEnumeration) == 0x2C); \
    assert(sizeof(struct D3DDriverBug) == 0x4); \
    assert(sizeof(struct gbDynArray_pgbResource) == 0xC); \
    assert(sizeof(struct gbRefObject) == 0x8); \
    assert(sizeof(struct gbResource) == 0x18); \
    assert(sizeof(struct gbResManager) == 0xC); \
    assert(sizeof(struct CD3DSettings) == 0x6C); \
    assert(sizeof(struct gbGfxDriverInfo) == 0xB8); \
    assert(sizeof(struct gbGfxManager) == 0x5F0); \
    assert(sizeof(struct gbGfxManager_D3D) == 0x8F0); \
    assert(sizeof(struct gbUIQuad) == 0x28); \
    assert(sizeof(struct CPKHeader) == 0x80); \
    assert(sizeof(struct CPKTable) == 0x1C); \
    assert(sizeof(struct CPK) == 0xE01BC); \
    assert(sizeof(struct gbBinkVideo) == 0x1C0388); \
    assert(sizeof(struct D3DAdapterInfo) == 0x458); \
    assert(sizeof(struct UICursor) == 0x20); \
    assert(sizeof(struct gbCamera) == 0x178); \
    assert(sizeof(struct gbQuaternion) == 0x10); \
    assert(sizeof(struct GRP_KEYREG) == 0x10); \
    assert(sizeof(struct GRPinput) == 0x2958); \
    assert(sizeof(struct tagAttackSequen) == 0x28); \
    assert(sizeof(struct CCBAttackSequen) == 0x1F4); \
    assert(sizeof(struct tagCmdData) == 0x2C); \
    assert(sizeof(struct tagThread) == 0x58); \
    assert(sizeof(struct tagPlayerSet) == 0x34); \
    assert(sizeof(struct CCBSystem) == 0x162D8); \
    assert(sizeof(struct SoundMgr) == 0xE050C); \
    assert(sizeof(struct TxtFile) == 0x20C); \
    assert(sizeof(struct gbAudioManager) == 0xF4); \
    assert(sizeof(struct SoundAttachObj) == 0xC); \
    assert(sizeof(struct gbSurfaceDesc) == 0x14); \
    assert(sizeof(struct gbPixelFormat) == 0x2C); \
    assert(sizeof(struct gbTexture) == 0x54); \
    assert(sizeof(struct gbTexture_D3D) == 0x60); \
    assert(sizeof(struct CTrail) == 0x348); \
    assert(sizeof(struct gbTextureArray) == 0x44); \
    assert(sizeof(struct gbDynVertBuf) == 0x3C); \
    assert(sizeof(struct gbPrintFont) == 0x4C); \
    assert(sizeof(struct RenderTarget) == 0xC8); \
    assert(sizeof(struct gbCachedChinaFont) == 0xC4); \
    assert(sizeof(struct UI3DObj) == 0x20); \
    assert(sizeof(struct UI3DCtrl) == 0x134); \
    assert(sizeof(struct UIStatic) == 0xA0); \
    assert(sizeof(struct UIStaticEX) == 0xC0); \
    assert(sizeof(struct UIStaticEXA) == 0xC8); \
    assert(sizeof(struct UnderWater) == 0x18); \
    assert(sizeof(struct C2DSpark_tagSpark) == 0x30); \
    assert(sizeof(struct tagShowItem) == 0x118); \
    assert(sizeof(struct UIFrameWnd) == 0x48); \
    assert(sizeof(struct tagUIParam) == 0x20); \
    assert(sizeof(struct tagUITask) == 0x48); \
    assert(sizeof(struct CCBUI) == 0xDE0); \
    assert(sizeof(struct CCBLineupWindow) == 0x7C); \
    assert(sizeof(struct tagImbibeNimbus) == 0x2C); \
    assert(sizeof(struct ObjectCamera) == 0x7C); \
    assert(sizeof(struct UICoverFrm) == 0x3AE8); \
    assert(sizeof(struct UIPar_Star) == 0x7C); \
    assert(sizeof(struct UIPar_Meteor) == 0x114); \
    assert(sizeof(struct _CLOUD) == 0xD8); \
    assert(sizeof(struct UITextureArray) == 0x44); \
    assert(sizeof(struct UIButton) == 0x158); \
    assert(sizeof(struct _btnOPTDATA) == 0x10); \
    assert(sizeof(struct UIButtonEX) == 0x188); \
    assert(sizeof(struct Average) == 0x18); \
    assert(sizeof(struct UIStaticFlex) == 0xC0); \
    assert(sizeof(struct UIDialog) == 0x48); \
    assert(sizeof(struct _TimeMgr) == 0xC); \
    assert(sizeof(struct MUIDialog) == 0x568); \
    assert(sizeof(struct gbImage2DInfo) == 0x80); \
    assert(sizeof(struct gbImage2D) == 0xC8); \
    assert(sizeof(struct gbVFileSystem) == 0xE01D4); \
} while (0)


#endif


#ifdef PATCHAPI_EXPORTS
// INTERNAL DEFINITIONS

// self-written functions
extern enum gbPixelFmtType gbGfxManager_D3D_GetBackBufferFormat(struct gbGfxManager_D3D *this);
extern int gbGfxManager_D3D_GetBackBufferBitCount(struct gbGfxManager_D3D *this);
extern void gbGfxManager_D3D_EnsureCooperativeLevel(struct gbGfxManager_D3D *this, int requirefocus);
extern void *vfs_readfile(const char *filepath, unsigned *length, const struct memory_allocator *mem_allocator);
extern const char *vfs_cpkname(void);


#endif
#endif
