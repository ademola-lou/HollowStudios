// #ifdef HD
//     #define WNDW_WIDTH 1920
//     #define WNDW_HEIGHT 1080
// #else
//     #define WNDW_WIDTH 2560
//     #define WNDW_HEIGHT 1600
// #endif

#include "Viewport.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <memory>
#include <vector>
#include <primitives/Mesh.h>
#include <managers/SceneManager.h>
#include <controls/CameraController.h>


typedef CamController::OrbitControls OrbitControls;
typedef CamController::FirstPersonControls FirstPersonControls;

static int WNDW_WIDTH = 1080;
static int WNDW_HEIGHT = 720;
Viewport::Viewport(const char* title = "DemoScene")
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WNDW_WIDTH, WNDW_HEIGHT, SDL_WINDOW_OPENGL);

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    SDL_GetWindowSize(window, &WNDW_WIDTH, &WNDW_HEIGHT);

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return;
    }

    bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    std::cout << "Engine(Linux)" << std::endl;
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

    SceneManager::loadDemoScene(2);

    Viewport::update(window);
};

static int mouseX = 0, mouseY = 0;
static FirstPersonControls controls{zoom: 10.f};

static bool isMousePressed = false;
void Viewport::update(SDL_Window *window)
{
    SDL_Event event;
    unsigned int counter = 0;
    int quit = 0;
    while(quit == 0) {   
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if(event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &WNDW_WIDTH, &WNDW_HEIGHT);
                    bgfx::reset(WNDW_WIDTH, WNDW_HEIGHT, BGFX_RESET_VSYNC);
                }
            }

            controls.init(mouseX, mouseY);
        }
    Viewport::render();
    counter++;
    SDL_GL_SwapWindow(window);
    }

}

float deltaTime = 0.0f;
void Viewport::updateCamera(){

    auto viewMat = controls.update();

    float proj[16];
    bx::mtxProj(proj,
                60.0f,
                float(WNDW_WIDTH)/float(WNDW_HEIGHT),
                0.1f, 100.0f,
                bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(0, viewMat, proj);

    // Set view 0 default viewport.
    bgfx::setViewRect(0, 0, 0,
                    WNDW_WIDTH,
                    WNDW_HEIGHT);
}

void Viewport::render()
{
    Viewport::updateCamera();
    bgfx::touch(0);

    SceneManager::update();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "HollowStudios 1.0.0");
    bgfx::dbgTextPrintf(0, 3, 0x5f, "Press F1 to toggle stats.");
    //show fps
    auto stats = bgfx::getStats();
    // float frameTime = float(stats->cpuTimeFrame) / 1000000.0f; // Convert nanoseconds to milliseconds
    // float fps = 1.0f / frameTime; // Convert frame time to FPS
    bgfx::dbgTextPrintf(0, 4, 0x5f, "fps: %d", stats->cpuTimeFrame);

    bgfx::setDebug(
        false ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);

    bgfx::frame();
}
Viewport::~Viewport()
{
    std::cout << "app shutdown!" << std::endl;
    SceneManager::clean();
    SDL_Quit();
}