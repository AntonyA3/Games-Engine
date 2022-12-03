#include <dear_imgui_wrapper.hpp>


DearImGuiWrapper::DearImGuiWrapper(/* args */)
{
}

DearImGuiWrapper::~DearImGuiWrapper()
{
}

void DearImGuiWrapper::create(SDL_Window * window, SDL_GLContext& gl_context){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    m_io = &ImGui::GetIO();
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");
    LOG(
        std::cout << "Imgui Initialised" << std::endl;
    );
}

void DearImGuiWrapper::beginFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

bool DearImGuiWrapper::processEvent(SDL_Event& event){
    return ImGui_ImplSDL2_ProcessEvent(&event);
}


void DearImGuiWrapper::renderFrame(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
}
