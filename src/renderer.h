#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "tetris.h"
class Renderer {
    public:
    Renderer(const std::size_t screen_width,const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Tetris &tetris);
    void UpdateWindowTitle(int score, int fps);
    private:
    int _r = 0;
    int _g= 0;
    int _b=0;
    int _heapSize;
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::vector<std::vector<int>> _rgbVec;
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};
#endif