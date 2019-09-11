#define SOKOL_IMPL

#if defined(_WIN32)
# define SOKOL_D3D11
#endif

#define SOKOL_WIN32_FORCE_MAIN

#include <sokol_app.h>
#include <sokol_gfx.h>


sapp_desc sokol_main(int argc, char* argv[])
{
    sapp_desc app_desc = { NULL };
    app_desc.width = 640;
    app_desc.height = 480;

    return app_desc;
}
