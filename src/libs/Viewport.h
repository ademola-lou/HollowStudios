#include <SDL2/SDL.h>
class Viewport
{
public:
    Viewport(const char *);
    ~Viewport();

    // void setCamera(Camera* camera);
    // void setScene(Scene* scene);
    // void setRenderer(Renderer* renderer);
    
    void render();
    void updateCamera();
    void updateControls();
    void resize(int width, int height);
    void update(SDL_Window *window);
};