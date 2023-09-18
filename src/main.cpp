#include <iostream>
// #include <test.h>
#include <Viewport.h>
// #include <bgfx_utils.h>
#include <cstdio>
int main () {
    Viewport viewport("HollowStudios 1.0.0");
    return 0;
}

// #define RMLUI_STATIC_LIB
// #include <RmlUi/Core.h>
// #include <iostream>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_syswm.h>
// //image sdl2
// #include <SDL2/SDL_image.h>
// #include <bgfx/bgfx.h>
// #include <bgfx/platform.h>
// #include <SDL2/SDL_syswm.h>
// #include <gui/interface/RmlUi_Renderer_SDL.h>
// #include <gui/interface/RmlUi_Platform_SDL.h>
// #include <gui/interface/RmlUi_Backend.h>

// struct BackendData {
// 	BackendData(SDL_Renderer* renderer) : render_interface(renderer) {}

// 	SystemInterface_SDL system_interface;
// 	RenderInterface_SDL render_interface;

// 	SDL_Window* window = nullptr;
// 	SDL_Renderer* renderer = nullptr;

// 	bool running = true;
// };
// static Rml::UniquePtr<BackendData> data;

// struct ApplicationData {
// 	bool show_text = true;
// 	Rml::String animal = "dog";
// } my_data;

// static int WNDW_WIDTH = 800;
// static int WNDW_HEIGHT = 600;

// int main(){
//     // SDL_Init(SDL_INIT_EVERYTHING);
//     SDL_Window *window = SDL_CreateWindow("RmlUi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

//     SDL_SysWMinfo wmi;
//     SDL_VERSION(&wmi.version);
//     if (!SDL_GetWindowWMInfo(window, &wmi)) {
//         return false;
//     }

//     bgfx::PlatformData pd;
// #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
//     std::cout << "Now Linux" << std::endl;
//     pd.ndt = wmi.info.x11.display;
//     pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
// #elif BX_PLATFORM_OSX
//     pd.ndt = NULL;
//     pd.nwh = wmi.info.cocoa.window;
// #elif BX_PLATFORM_WINDOWS
//     pd.ndt = NULL;
//     pd.nwh = wmi.info.win.window;
// #elif BX_PLATFORM_STEAMLINK
//     pd.ndt = wmi.info.vivante.display;
//     pd.nwh = wmi.info.vivante.window;
// #endif // BX_PLATFORM_
//     pd.context = NULL;
//     pd.backBuffer = NULL;
//     pd.backBufferDS = NULL;
//     bgfx::setPlatformData(pd);

//     bgfx::renderFrame();

//     bgfx::Init bgfxInit;
//     bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
//     bgfxInit.resolution.width = WNDW_WIDTH;
//     bgfxInit.resolution.height = WNDW_HEIGHT;
//     bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

//     bgfx::init(bgfxInit);
//     bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e1e1e, 1.0f, 0);
//     bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);
//     bgfx::frame();

//     SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);


//     RenderInterface_SDL render_interface(sdlRenderer);
// 	SystemInterface_SDL system_interface;

// 	// // // Install the custom interfaces.
// 	Rml::SetRenderInterface(&render_interface);
// 	Rml::SetSystemInterface(&system_interface);

//     system_interface.SetWindow(window);
// 	// // Now we can initialize RmlUi.
// 	Rml::Initialise();
//     Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(800, 600));

//     Rml::LoadFontFace("assets/LatoLatin-Regular.ttf");
// 	// Fonts can be registered as fallback fonts, as in this case to display emojis.
// 	Rml::LoadFontFace("assets/NotoEmoji-Regular.ttf", true);

//     Rml::ElementDocument* document = context->LoadDocument("assets/demo.rml");
// 	document->Show();
    
//     SDL_RenderPresent(sdlRenderer);

//     SDL_Event event;
//     while(true) {
//         if (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 break;
//             }
//         }
//         context->Update();

//         //begin frame
//         SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
//         SDL_RenderClear(sdlRenderer);

//          //end rendering
        
//         render_interface.BeginFrame();

// 		// Render the user interface. All geometry and other rendering commands are now
// 		// submitted through the render interface.
// 		context->Render();

//         render_interface.EndFrame();

//         bgfx::touch(0);

//         bgfx::frame();
//         SDL_RenderPresent(sdlRenderer);

//         // SDL_GL_SwapWindow(window);
//     }

//     bgfx::shutdown();
//     Rml::Shutdown();
//     SDL_DestroyRenderer(sdlRenderer);
//     SDL_DestroyWindow(window);

//     SDL_Quit();
    
//     return 0;
// }