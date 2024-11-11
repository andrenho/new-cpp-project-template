#include "ui.hh"

#include <string>
#include <glad/glad.h>
using namespace std::string_literals;

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include "battery/embed.hpp"

UI::UI()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window_ = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window_)
        throw std::runtime_error("Error: SDL_CreateWindow(): "s + SDL_GetError());

    ren_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!ren_)
        throw std::runtime_error("Error: SDL_CreateRenderer(): "s + SDL_GetError());

    gl_context_ = SDL_GL_CreateContext(window_);
    if (!gl_context_)
        throw std::runtime_error("OpenGL context creation failed: "s + SDL_GetError());
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        throw std::runtime_error("Could not initialize GLAD.");
    SDL_GL_MakeCurrent(window_, gl_context_);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    std::vector<uint8_t> face = b::embed<"resources/images/face.png">().vec();
    SDL_Surface* sf = IMG_Load_RW(SDL_RWFromMem(face.data(), (int) face.size()), 1);
    texture_ = SDL_CreateTextureFromSurface(ren_, sf);
    SDL_FreeSurface(sf);

    // init_imgui();
}

void UI::init_imgui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window_, gl_context_);
    ImGui_ImplOpenGL3_Init("#version 330");
}

UI::~UI()
{
    if (ren_)
        SDL_DestroyRenderer(ren_);
    if (window_)
        SDL_DestroyWindow(window_);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void UI::update(Duration timestep)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running_ = false;
                break;
            default: break;
        }
    }
}

void UI::draw()
{
    SDL_SetRenderDrawColor(ren_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ren_);

    int scr_w, scr_h;
    SDL_GetWindowSize(window_, &scr_w, &scr_h);

    int tx_w, tx_h;
    SDL_QueryTexture(texture_, nullptr, nullptr, &tx_w, &tx_h);

    SDL_Rect dest = {
        .x = (scr_w / 2) - (tx_w / 2),
        .y = (scr_h / 2) - (tx_h / 2),
        .w = tx_w,
        .h = tx_h,
    };
    SDL_RenderCopy(ren_, texture_, nullptr, &dest);

    SDL_RenderPresent(ren_);
}
