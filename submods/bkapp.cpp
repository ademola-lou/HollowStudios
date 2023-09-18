#include <iostream>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
// #define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <SDL2/SDL_syswm.h>
#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900
#include <stdio.h>
#include <fstream>

bgfx::ShaderHandle loadShader(const char* _name) {
    char* data = new char[2048];
    std::ifstream file;
    size_t fileSize;
    file.open(_name);
    if(file.is_open()) {
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        file.read(data, fileSize);
        file.close();
    }
    const bgfx::Memory* mem = bgfx::copy(data,fileSize+1);
    mem->data[mem->size-1] = '\0';
    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, _name);
    return handle;
}

struct PosColorVertex {
    // 3d space position
    float m_x;
    float m_y;
    float m_z;
    // Color value
    uint32_t m_abgr;

    static void init() {
        // start the attribute declaration
        ms_decl
            .begin()
            // Has three float values that denote position
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            // and a uint8 color value that denotes color
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexLayout ms_decl;
};

bgfx::VertexLayout PosColorVertex::ms_decl;

// static PosColorVertex s_cubeVertices[] =
// {
//     {  0.5f,  0.5f, 0.0f, 0xff0000ff },
//     {  0.5f, -0.5f, 0.0f, 0xff0000ff },
//     { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
//     { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
// };

// static const uint16_t s_cubeTriList[] =
// {
//     0,1,3,
//     1,2,3
// };

  static PosColorVertex s_cubeVertices[] = {
        {-1, 1, 0, 0xff0000ff},
        {1, 1, 0, 0xff0000ff},
        {1, -1, 0, 0xff0000ff},
        {-1, -1, 0, 0xff0000ff}
    };
    static const uint16_t s_cubeTriList[] = {0, 1, 2, 0, 2, 3};

int main () {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("BgFx", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WNDW_WIDTH, WNDW_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return false;
    }

    bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    std::cout << "Now Linux" << std::endl;
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
    pd.ndt = NULL;
    pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
    pd.ndt = NULL;
    pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_STEAMLINK
    pd.ndt = wmi.info.vivante.display;
    pd.nwh = wmi.info.vivante.window;
#endif // BX_PLATFORM_
    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData(pd);

    bgfx::renderFrame();

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = WNDW_WIDTH;
    bgfxInit.resolution.height = WNDW_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bgfx::init(bgfxInit);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e1e1e, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);
    bgfx::frame();

    bgfx::VertexBufferHandle m_vbh;
    bgfx::IndexBufferHandle m_ibh;

    PosColorVertex::init();
    m_vbh = bgfx::createVertexBuffer(
            // Static data can be passed with bgfx::makeRef
            bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
            PosColorVertex::ms_decl
        );

    m_ibh = bgfx::createIndexBuffer(
            // Static data can be passed with bgfx::makeRef
            bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
        );
    bgfx::ProgramHandle m_program;
    
    bgfx::ShaderHandle vsh = loadShader("v_simple.bin");
    bgfx::ShaderHandle fsh = loadShader("f_simple.bin");
    m_program = bgfx::createProgram(vsh,fsh,  true);

    unsigned int counter = 0;
    SDL_Event event;
    while(true) {   
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        //start rendering
        const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
        float view[16];
        bx::mtxLookAt(view, eye, at);

        float proj[16];
        bx::mtxProj(proj,
                    60.0f,
                    float(WNDW_WIDTH)/float(WNDW_HEIGHT),
                    0.1f, 100.0f,
                    bgfx::getCaps()->homogeneousDepth);

        bgfx::setViewTransform(0, view, proj);

        // Set view 0 default viewport.
        bgfx::setViewRect(0, 0, 0,
                        WNDW_WIDTH,
                        WNDW_HEIGHT);

        //end rendering
        bgfx::touch(0);


        //draw cube
        float mtx[16];
        bx::mtxRotateY(mtx, 0.0f);

        // position x,y,z
        mtx[12] = 0.0f;
        mtx[13] = 0.0f;
        mtx[14] = 0.0f;

        // Set model matrix for rendering.
        bgfx::setTransform(mtx);

        // Set vertex and index buffer.
        bgfx::setVertexBuffer(0, m_vbh);
        bgfx::setIndexBuffer(m_ibh);

        // Set render states.
        bgfx::setState(BGFX_STATE_DEFAULT);

        // Submit primitive for rendering to view 0.
        bgfx::submit(0, m_program);

        bgfx::frame();
        counter++;
        SDL_GL_SwapWindow(window);
    }

    bgfx::shutdown();
    SDL_Quit();

    std::cout << "Hello World!" << std::endl;
    return 0;
}