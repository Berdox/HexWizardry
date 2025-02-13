#pragma once

#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <string>
#include <vector>

class Platform {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImGuiViewport* viewport;

    Platform() : window(nullptr), renderer(nullptr), viewport(nullptr){}

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
       // ImGui::GetIO().ConfigDockingWithShift = true;  // Enable docking with Shift key
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

    void showCentralWindow()
    {
        // Get the main viewport (entire application window)
        viewport = ImGui::GetMainViewport();

        // Set window flags for the full central window
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoDocking;
        //ImGuiWindowFlags_NoTitleBar |

        // Set the position and size to cover the entire viewport
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // Begin the central window
        ImGui::Begin("CentralWindow", nullptr, window_flags);
    }

    void createDockingSpaceLayout() {
        // Create a docking space inside the central window
        ImGuiID dockspace_id = ImGui::GetID("CentralDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_None);

        ImGui::End();

        // Reset the docking layout
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        // Split the docking space into top (75%) and bottom (25%)
        ImGuiID top_id, bottom_id;
        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, &bottom_id, &top_id);

        // Split the top section into left (50%) and right (50%)
        ImGuiID left_id, right_id;
        ImGui::DockBuilderSplitNode(top_id, ImGuiDir_Left, 0.75f, &left_id, &right_id);

        // Dock windows in their respective places
        ImGui::DockBuilderDockWindow("LeftWindow", left_id);
        ImGui::DockBuilderDockWindow("RightWindow", right_id);
        ImGui::DockBuilderDockWindow("BottomWindow", bottom_id);

        // Finalize the layout
        ImGui::DockBuilderFinish(dockspace_id);
    }

    void dockingSpaceResizing() {
        // Create a docking space inside the central window
        ImGuiID dockspace_id = ImGui::GetID("CentralDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_None);

        ImGui::End();

        // Track viewport size to detect resizes
        static ImVec2 last_size = viewport->Size;
        if (last_size.x != viewport->Size.x || last_size.y != viewport->Size.y)
        {
            last_size = viewport->Size; // Update last size

            // Reset the docking layout
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            // Split the docking space into top (75%) and bottom (25%)
            ImGuiID top_id, bottom_id;
            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, &bottom_id, &top_id);

            // Split the top section into left (50%) and right (50%)
            ImGuiID left_id, right_id;
            ImGui::DockBuilderSplitNode(top_id, ImGuiDir_Left, 0.75f, &left_id, &right_id);

            // Dock windows in their respective places
            ImGui::DockBuilderDockWindow("LeftWindow", left_id);
            ImGui::DockBuilderDockWindow("RightWindow", right_id);
            ImGui::DockBuilderDockWindow("BottomWindow", bottom_id);

            // Finalize the layout
            ImGui::DockBuilderFinish(dockspace_id);
        }
    }

    void createDockedWindows() {
       // ImGui::SetNextWindowDockID(ImGui::GetID("LeftWindow"), ImGuiCond_Once);

        std::vector<std::string> strings = {
        "String 1", "String 2", "String 3", "String 4",
        "String 5", "String 6", "String 7", "String 8",
        "String 9", "String 10", "String 11", "String 12"
        };

        ImGui::Begin("LeftWindow", nullptr, ImGuiWindowFlags_NoCollapse);  // Prevent window from collapsing
            // Get the current window width
            float window_width = ImGui::GetContentRegionAvail().x;

            // Set the width of each child region to half of the window's width
            float child_width = window_width * 0.5f;

            // Begin the first child region (left side)
            ImGui::BeginChild("Child 1", ImVec2(window_width * 0.75f, 0), true);
                //ImGui::PushTextWrapPos(window_width * 0.75f);
                // Start a 4-column layout
                ImGui::Columns(4, NULL, false);  // 4 columns, no border

                // Loop through the list and display each string in a column
                for (size_t i = 0; i < strings.size(); ++i)
                {
                    ImGui::Text("%s", strings[i].c_str());

                    // Move to the next column
                    ImGui::NextColumn();
                }

                // End the columns and the child region
                ImGui::Columns(1);  // Reset to single column for the rest of the UI
                //ImGui::PopTextWrapPos();  // Reset the wrap position
            ImGui::EndChild();

            // Add some spacing between the children (optional)
            ImGui::SameLine();

            // Begin the second child region (right side)
            ImGui::BeginChild("Child 2", ImVec2(window_width * 0.25f, 0), true);
                ImGui::PushTextWrapPos(window_width * 0.25f);
                ImGui::Text("This is the second child region");
                ImGui::PopTextWrapPos();  // Reset the wrap position
            ImGui::EndChild();
        ImGui::End();

        // Right Panel
      //  ImGui::SetNextWindowDockID(ImGui::GetID("RightWindow"), ImGuiCond_Once);
        ImGui::Begin("RightWindow", nullptr, ImGuiWindowFlags_NoCollapse);  // Prevent window from collapsing
        ImGui::Text("This is the right Window.");
        ImGui::End();

        ImGui::Begin("BottomWindow", nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("This is the bottom dockable window");
        ImGui::End();
    }

    void mainLoop() {
        bool running = true;
        bool createLayout = true;
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


            showCentralWindow();
            if (createLayout) {
                createDockingSpaceLayout();
                createLayout = false;
            }
            else {
                dockingSpaceResizing();
            }
            createDockedWindows();

            // Render ImGui
            ImGui::Render();
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // Dark background
            SDL_RenderClear(renderer);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer);
        }
    }
};