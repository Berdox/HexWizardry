#pragma once

#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

class Platform {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Platform() : window(nullptr), renderer(nullptr) {}

    void init_SDL() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
        }
    }

    void init_SDL_Window(int width, int height) {
        // Create SDL Window
        window = SDL_CreateWindow("ImGui Docking Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        if (!window) {
            throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
        }
    }

    void init_SDL_Renderer() {
        // Create SDL Renderer
        if (!window) {
            throw std::runtime_error("SDL_Window is not initialized.");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
        }
    }

    void init_IMGUI() {
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable docking

        // Setup Dear ImGui for SDL2 + SDL_Renderer
        if (ImGui_ImplSDL2_InitForSDLRenderer(window, renderer) == false) {
            throw std::runtime_error("Failed to initialize ImGui_ImplSDL2.");
        }

        if (ImGui_ImplSDLRenderer2_Init(renderer) == false) {
            throw std::runtime_error("Failed to initialize ImGui_ImplSDLRenderer2.");
        }

        // Create a DockSpace and build the layout with specific docking positions
        ImGui::GetIO().ConfigDockingWithShift = true;  // Enable docking with Shift key
    }

    // Cleanup
    void cleanUp() {
        if (renderer) {
            ImGui_ImplSDLRenderer2_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }

    void init_hexEditor() {
        try {
            init_SDL();
            init_SDL_Window(800, 600);
            init_SDL_Renderer();
            init_IMGUI();
            mainLoop();
        }
        catch (const std::exception& e) {
            std::cerr << "Error during initialization or main loop: " << e.what() << std::endl;
            cleanUp();
        }
    }

    void mainLoop() {
        // Main loop
        bool running = true;
        SDL_Event event;
        while (running) {
            // Process SDL events
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT) running = false;
            }

            // Start ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // Create the windows
            ImGui::Begin("Left Window");
            ImGui::Text("This is the left docked window.");
            ImGui::End();

            ImGui::Begin("Right Window");
            ImGui::Text("This is the right docked window.");
            ImGui::End();

            ImGui::Begin("Bottom Window");
            ImGui::Text("This is the bottom docked window.");
            ImGui::End();

            // Render
            ImGui::Render();
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // Dark background
            SDL_RenderClear(renderer);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer);
        }
    }
};