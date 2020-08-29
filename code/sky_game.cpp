#include "sky_game.h"
#include "sky_gfx.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

// unity build
#include "sky_gfx.cpp"
#include "imgui/imgui.cpp"
#include "imgui/imgui_impl_opengl3.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"

const char *vshader = R"""(
    #version 450 core
    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec3 color;

    layout (location = 0) out vec3 v_color;

    void main()
    {
        gl_Position = vec4(pos, 1.0f);
        v_color = color;
    }
)""";

const char *fshader = R"""(
    #version 450 core
    in vec3 v_color;

    layout (location = 0) out vec4 out_color;

    void main()
    {
        out_color = vec4(v_color, 1.0f);
    }
)""";

static void
_sky_game_construct(Sky_Game *self)
{
    *self = {};

    for (int i = 0; i < SKY_GAME_MAX_MESHES; ++i)
    {
        float pos[] = {
             0.5f / i, -0.5f / i, 0.0f / i,
            -0.5f / i, -0.5f / i, 0.0f / i,
             0.0f / i,  0.5f / i, 0.0f / i};

        float colors[] = {
            1.0f / i, 1.0f / i, 0.0f / i,
            0.0f / i, 1.0f / i, 1.0f / i,
            1.0f / i, 0.0f / i, 1.0f / i};

        unsigned int VBO[2], VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(2, VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(1);

        self->mesh_gpu[self->mesh_count].handle = VAO;
        self->mesh_gpu[self->mesh_count].vertex_count = 3;
        self->mesh_count += 1;
    }
}

static void
_sky_game_destruct(Sky_Game *self)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

static void
_sky_game_reload(Sky_Game *self)
{
    // imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();

    Sky_Gfx_Handle program = sky_gfx_program_new(vshader, fshader);
    sky_gfx_program_use(program);
}

static void
_sky_game_loop(Sky_Game *self)
{
    ImGuiIO &io = ImGui::GetIO();
    io.DeltaTime = 1.0f / 60.0f;
    io.DisplaySize.x = (float)self->width;
    io.DisplaySize.y = (float)self->height;
    io.MousePos = {(float)self->input.mouse_x, (float)self->input.mouse_y};
    io.MouseDown[0] = self->input.keys[SKY_KEY_MOUSE_LEFT].down;
    io.MouseDown[1] = self->input.keys[SKY_KEY_MOUSE_RIGHT].down;
    io.MouseDown[2] = self->input.keys[SKY_KEY_MOUSE_MIDDLE].down;
    io.MouseWheel = (float)self->input.mouse_wheel;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    glViewport(0, 0, self->width, self->height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::ShowDemoWindow();

    for (int i = 0; i < self->mesh_count; ++i)
    {
        glBindVertexArray(self->mesh_gpu[i].handle);
        glDrawArrays(GL_TRIANGLES, 0, self->mesh_gpu[i].vertex_count);
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Sky_Game_Api *
sky_game_api()
{
    static Sky_Game_Api api;

    api.construct = _sky_game_construct;
    api.destruct = _sky_game_destruct;
    api.reload = _sky_game_reload;
    api.loop = _sky_game_loop;

    return &api;
}