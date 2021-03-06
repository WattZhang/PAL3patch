#ifndef PAL3PATCH_TEXTUREHOOK_H
#define PAL3PATCH_TEXTUREHOOK_H
// PATCHAPI DEFINITIONS


enum texture_hook_type {
    TH_PRE_IMAGELOAD,
    TH_POST_IMAGELOAD,
};

struct texture_hook_info {
    // read only information
    char cpkname[MAXLINE]; // current CPK name, may be empty string if not using CPK
    char texpath[MAXLINE]; // original texture path, if texpath starts with ":some_special_magic:some_extra_info", other hooks should ignore it
    const struct memory_allocator *mem_allocator; // any memory allocation associated with this thinfo should use this allocator
    enum texture_hook_type type; // current callback type

    // pre-imageload hook only
    char loadpath[MAXLINE]; // loadpath might be ".", indicating no image should be automaticly loaded
    int interested; // MUST be set to non-zero in TH_PRE_IMAGELOAD stage if interested
    
    // image data
    void *bits;
    int width;
    int height;
    int bitcount; // either 32 or 24, for D3DFMT_A8R8G8B8 and D3DFMT_R8G8B8, respectively
    int div_alpha; // if set to zero, disable div-alpha operation
    int fakewidth; // if set to zero, no fake texture width will apply
    int fakeheight; // if set to zero, no fake texture height will apply
};
/*
  texture hook usage:
    if type == TH_PRE_IMAGELOAD:
        image is not currently loaded
        if interested, MUST set thinfo->interested to non-zero
        can change texture load path (set thinfo->loadpath, but tex->pName will not be changed)
        can load texture directly at this stage (set image data section)
        
    if type == TH_POST_IMAGELOAD:
        image is already loaded
        can do some image processing (modify image data section)

  callback example:
    void texhook_example(struct texture_hook_info *thinfo)
    {
        check_magic(thinfo);
        check_autoload(thinfo);
        if (is_interested(thinfo)) { 
            if (thinfo->type == TH_PRE_IMAGELOAD) {
                thinfo->interested = 1;
            } else if (thinfo->type == TH_POST_IMAGELOAD) {
                do_some_processing(thinfo);
            }
        }
    }
*/

// magic related functions
extern PATCHAPI int test_texture_hook_magic(struct texture_hook_info *thinfo);
extern PATCHAPI char *extract_texture_hook_magic(struct texture_hook_info *thinfo, const char *magic);
extern PATCHAPI const char *make_texture_hook_magic(const char *magic);

// autoload related functions
extern PATCHAPI int test_texture_hook_noautoload(struct texture_hook_info *thinfo);
extern PATCHAPI void mark_texture_hook_noautoload(struct texture_hook_info *thinfo);

// hook management functions
extern PATCHAPI void add_texture_hook(void (*funcptr)(struct texture_hook_info *));


#ifdef PATCHAPI_EXPORTS
// INTERNAL DEFINITIONS

#define MAX_TEXTURE_HOOKS 100
extern void init_texture_hooks(void);

#endif
#endif
