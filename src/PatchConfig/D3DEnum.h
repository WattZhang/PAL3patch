#ifndef PAL3PATCHCONFIG_D3DENUM
#define PAL3PATCHCONFIG_D3DENUM

extern int CheckDX90SDKVersion();
extern void InitD3DEnumeration();
extern void CleanupD3DEnumeration();

extern void EnumDisplayMode(std::vector<std::pair<CString, std::pair<CString, CString> > > &result);
extern void EnumDepthBuffer(std::vector<std::pair<CString, std::pair<CString, CString> > > &result);
extern void EnumMultisample(std::vector<std::pair<CString, std::pair<CString, CString> > > &result);
#endif
