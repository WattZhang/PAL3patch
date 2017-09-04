#ifndef PAL3PATCHCONFIG_PATCHVERSIONINFO
#define PAL3PATCHCONFIG_PATCHVERSIONINFO

#define PATCH_VERSION_CSTR "v1.6"
#define PATCH_VERSION _T(PATCH_VERSION_CSTR)

#define PATCH_APPNAME _T("PAL3-PatchConfig")

#define PATCH_WEBSITE_BASE _T("https://pal3.zbyzbyzby.com")
#define PATCH_WEBSITE PATCH_WEBSITE_BASE _T("/?appname=") PATCH_APPNAME _T("&version=") PATCH_VERSION
#define PATCH_UPDATEUA PATCH_APPNAME _T("/") PATCH_VERSION

#ifdef _DEBUG
#define PATCH_UPDATEURL _T("http://127.0.0.1/check-updates.txt")
#else
#define PATCH_UPDATEURL _T("https://pal3.zbyzbyzby.com/pal3/check-updates.php")
#endif

extern const char pBuildDate[];
extern const char pVersionStr[];
extern const char pCompiler[];
extern const char *pFileHash[];


#endif