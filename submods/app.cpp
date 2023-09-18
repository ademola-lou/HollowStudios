// #pragma once
// // #define RMLUI_STATIC_LIB
// #include <iostream>
// #include <bgfx/bgfx.h>
// #include <bgfx/platform.h>
// #include <bx/math.h>
// #include <SDL2/SDL.h>
// #include <GLFW/glfw3.h>
// #define GLFW_EXPOSE_NATIVE_X11
// // #define GLFW_EXPOSE_NATIVE_WIN32
// #include <RmlUi/Core.h>
// #include <GLFW/glfw3native.h>
// #include <SDL2/SDL_syswm.h>
// #define WNDW_WIDTH 1600
// #define WNDW_HEIGHT 900
// #include <stdio.h>
// #include <fstream>



// bgfx::ShaderHandle loadShader(const char* _name) {
//     char* data = new char[2048];
//     std::ifstream file;
//     size_t fileSize;
//     file.open(_name);
//     if(file.is_open()) {
//         file.seekg(0, std::ios::end);
//         fileSize = file.tellg();
//         file.seekg(0, std::ios::beg);
//         file.read(data, fileSize);
//         file.close();
//     }
//     const bgfx::Memory* mem = bgfx::copy(data,fileSize+1);
//     mem->data[mem->size-1] = '\0';
//     bgfx::ShaderHandle handle = bgfx::createShader(mem);
//     bgfx::setName(handle, _name);
//     return handle;
// }

// // Vertex structure
// struct Vertex
// {
//     float x, y, z;
//     uint32_t abgr;  // Color in ABGR format

//     static void init()
//     {
//         decl
//             .begin()
//             .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
//             .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
//             .end();
//     }

//     static bgfx::VertexLayout decl;
// };

// bgfx::VertexLayout Vertex::decl;

// // Mesh structure
// struct Mesh
// {
//     bgfx::VertexBufferHandle vbh;
//     bgfx::IndexBufferHandle ibh;
//     bgfx::ProgramHandle prog;

//     Mesh()
//     {
//         std::cout<<"Mesh created"<<std::endl;
//         // Define the triangle vertices
//         Vertex triangleVertices[3] =
//         {
//             { 0.0f,  0.9f, 0.0f, 0xFF0000FF },  // Red, top center
//             { 0.8f, -0.5f, 0.0f, 0xFF00FF00 },  // Green, bottom right
//             {-0.5f, -0.5f, 0.0f, 0xFFFF0000 }   // Blue, bottom left
//         };

//         const uint16_t triangleIndices[3] = { 0, 1, 2 };
//         // Create vertex buffer
//         // const bgfx::Memory* mem = bgfx::copy(triangleVertices, sizeof(triangleVertices));
//         vbh = bgfx::createVertexBuffer(bgfx::copy(triangleVertices, sizeof(triangleVertices)), Vertex::decl);
//         ibh = bgfx::createIndexBuffer(bgfx::copy(triangleIndices, sizeof(triangleIndices)));
//         bgfx::ShaderHandle vsh = loadShader("v_simple.bin");
//         bgfx::ShaderHandle fsh = loadShader("f_simple.bin");
//         prog = bgfx::createProgram(vsh,fsh,  true);
//     }

//     ~Mesh()
//     {
//         bgfx::destroy(vbh);
//     }

//     void draw()
//     {
//         bgfx::setVertexBuffer(0, vbh);
//         bgfx::setIndexBuffer(ibh);
//         bgfx::setState(BGFX_STATE_DEFAULT); // Set render states.
        
//         // Assuming you've already loaded shaders and have their handles in prog
//         bgfx::submit(0, prog);
//     }
// };


// struct PosColorVertex {
//     // 3d space position
//     float m_x;
//     float m_y;
//     float m_z;
//     // Color value
//     uint32_t m_abgr;

//     static void init() {
//         // start the attribute declaration
//         ms_decl
//             .begin()
//             // Has three float values that denote position
//             .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
//             // and a uint8 color value that denotes color
//             .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
//             .end();
//     };

//     static bgfx::VertexLayout ms_decl;
// };

// bgfx::VertexLayout PosColorVertex::ms_decl;

// // static PosColorVertex s_cubeVertices[] =
// // {
// //     {  0.5f,  0.5f, 0.0f, 0xff0000ff },
// //     {  0.5f, -0.5f, 0.0f, 0xff0000ff },
// //     { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
// //     { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
// // };

// // static const uint16_t s_cubeTriList[] =
// // {
// //     0,1,3,
// //     1,2,3
// // };

//   static PosColorVertex s_cubeVertices[] = {
//         {-1, 1, 0, 0xff0000ff},
//         {1, 1, 0, 0xff0000ff},
//         {1, -1, 0, 0xff0000ff},
//         {-1, -1, 0, 0xff0000ff}
//     };
//     static const uint16_t s_cubeTriList[] = {0, 1, 2, 0, 2, 3};

//         // Vertex triangleVertices[3] =
//         // {
//         //     { 0.0f,  5.f, 0.0f, 0xFF0000FF },  // Red, top center
//         //     { 0.5f, -0.5f, 0.0f, 0xFF00FF00 },  // Green, bottom right
//         //     {-0.5f, -0.5f, 0.0f, 0xFFFF0000 }   // Blue, bottom left
//         // };

//         // const uint16_t triangleIndices[3] = { 0, 1, 2 };

// int main () {
//     SDL_Init(SDL_INIT_EVERYTHING);
//     SDL_Window *window = SDL_CreateWindow("BgFx", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WNDW_WIDTH, WNDW_HEIGHT, SDL_WINDOW_OPENGL);

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

//     // Somewhere in your initialization code:
//     Vertex::init();

//     // To draw the triangle:
//     Mesh triangle;

//     bgfx::VertexBufferHandle m_vbh;
//     bgfx::IndexBufferHandle m_ibh;

//     PosColorVertex::init();

//     m_vbh = triangle.vbh;
//     m_ibh = triangle.ibh;
//     // m_vbh = bgfx::createVertexBuffer(
//     //         // Static data can be passed with bgfx::makeRef
//     //         bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
//     //         PosColorVertex::ms_decl
//     //     );

//     // m_ibh = bgfx::createIndexBuffer(
//     //         // Static data can be passed with bgfx::makeRef
//     //         bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
//     //     );
//     bgfx::ProgramHandle m_program;
    
//     bgfx::ShaderHandle vsh = loadShader("v_simple.bin");
//     bgfx::ShaderHandle fsh = loadShader("f_simple.bin");
//     m_program = bgfx::createProgram(vsh,fsh,  true);

//     unsigned int counter = 0;
//     SDL_Event event;
//     while(true) {   
//         if (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 break;
//             }
//         }

//         //start rendering
//         const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
//         const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };
//         float view[16];
//         bx::mtxLookAt(view, eye, at);

//         float proj[16];
//         bx::mtxProj(proj,
//                     60.0f,
//                     float(WNDW_WIDTH)/float(WNDW_HEIGHT),
//                     0.1f, 100.0f,
//                     bgfx::getCaps()->homogeneousDepth);

//         bgfx::setViewTransform(0, view, proj);

//         // Set view 0 default viewport.
//         bgfx::setViewRect(0, 0, 0,
//                         WNDW_WIDTH,
//                         WNDW_HEIGHT);

//         //end rendering
//         bgfx::touch(0);

        
//         //draw cube
//         float mtx[16];
//         bx::mtxRotateY(mtx, 0.0f);

//         // position x,y,z
//         mtx[12] = 0.0f;
//         mtx[13] = 0.0f;
//         mtx[14] = 0.0f;

//         // Set model matrix for rendering.
//         bgfx::setTransform(mtx);

//         // Set vertex and index buffer.
//         bgfx::setVertexBuffer(0, m_vbh);
//         bgfx::setIndexBuffer(m_ibh);

//         // Set render states.
//         bgfx::setState(BGFX_STATE_DEFAULT);

//         // Submit primitive for rendering to view 0.
//         bgfx::submit(0, triangle.prog);//m_program);
//         triangle.draw();

//         bgfx::frame();
//         counter++;
//         SDL_GL_SwapWindow(window);
//     }

//     bgfx::shutdown();
//     SDL_Quit();

//     std::cout << "Hello World!" << std::endl;
//     return 0;
// }
#define RMLUI_STATIC_LIB
#include <RmlUi/Core.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

// class MyRenderInterface : public Rml::RenderInterface
// {
// 	// RmlUi sends vertices, indices and draw commands through this interface for your
// 	// application to render how you'd like.
// 	/* ... */
// };

// class MySystemInterface : public Rml::SystemInterface
// {	
// 	// RmlUi requests the current time and provides various utilities through this interface.
// 	/* ... */
// };

struct ApplicationData {
	bool show_text = true;
	Rml::String animal = "dog";
} my_data;

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("RmlUi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return false;
    }


    // Rml::RenderInterface render_interface;
	// Rml::SystemInterface system_interface;

	// // Install the custom interfaces.
	// Rml::SetRenderInterface(&render_interface);
	// Rml::SetSystemInterface(&system_interface);

	// Now we can initialize RmlUi.
	Rml::Initialise();
    Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(800, 600));

    Rml::LoadFontFace("RmlUi/Samples/assets/LatoLatin-Regular.ttf");
	// Fonts can be registered as fallback fonts, as in this case to display emojis.
	Rml::LoadFontFace("RmlUi/Samples/assets/NotoEmoji-Regular.ttf", true);

    Rml::ElementDocument* document = context->LoadDocument("RmlUi/Samples/assets/demo.rml");
	document->Show();
    // Rml::Core::SetRenderInterface(new Rml::Core::RenderInterface);
    // Rml::Core::Initialise();
    // Rml::Core::LoadFontFace("RmlUi/Samples/assets/LatoLatin-Bold.ttf");
    //     //"assets/fonts/Delicious-Roman.otf");

    // Rml::Core::ElementDocument *doc = Rml::Core::LoadDocument("RmlUi/Samples/assets/demo.rml");
        //"assets/demo.rml");
    // if (doc != NULL) {
    //     doc->Show();
    // }

    SDL_Event event;
    while(true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
        context->Update();

		// Render the user interface. All geometry and other rendering commands are now
		// submitted through the render interface.
		context->Render();
        // Rml::Core::ProcessTimers();
        // Rml::Core::RenderInterface *renderInterface = Rml::Core::GetRenderInterface();
        // renderInterface->RenderGeometry();
        SDL_GL_SwapWindow(window);
    }

    Rml::Shutdown();
    SDL_Quit();
    
    std::cout << "Hello World!" << std::endl;
    return 0;
}