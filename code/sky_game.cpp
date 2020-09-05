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

    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        gl_Position = vec4(pos, 1.0f) * view * proj;
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

static Sky_Gfx_Handle program;

static void
_sky_game_construct(Sky_Game *self)
{
    *self = {};

    self->cam.position = Vec3{0.0f, 0.0f, 3.0f};
    self->cam.forward = Vec3{0.0f, 0.0f, 1.0f};
    self->cam.fov = 45.0f;
    self->cam.aspect = (float)self->width / (float)self->height;
    self->cam.znear = 0.1f;
    self->cam.zfar = 100.0f;

    for (int i = 1; i < SKY_GAME_MAX_MESHES; ++i)
    {
        float pos[] = {
             1.5f / i, -1.5f / i, 0.0f,
            -1.5f / i, -1.5f / i, 0.0f,
             0.0f / i,  1.5f / i, 0.0f};

        float colors[] = {
            1.0f / i, 0.0f / i, 0.0f / i,
            0.0f / i, 1.0f / i, 0.0f / i,
            0.0f / i, 0.0f / i, 1.0f / i};

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

    program = sky_gfx_program_new(vshader, fshader);
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
    io.MouseWheel = self->input.mouse_wheel;

    self->cam.aspect = (float)self->width / (float)self->height;
    self->cam.position += self->input.mouse_wheel * self->cam.forward;

    static float yaw = -90;
    static float pitch = 0;
    if (self->input.keys[SKY_KEY_MOUSE_RIGHT].down)
    {
        yaw += self->input.mouse_dx * 0.1f;
        pitch += self->input.mouse_dy * 0.1f;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        self->cam.forward.x = (sky_cos(yaw * DEGREE_TO_RAD) * sky_cos(pitch * DEGREE_TO_RAD));
        self->cam.forward.y = (sky_sin(pitch * DEGREE_TO_RAD));
        self->cam.forward.z = (sky_sin(yaw * DEGREE_TO_RAD) * sky_cos(pitch * DEGREE_TO_RAD));
        self->cam.forward = vec3_normalize(self->cam.forward);
    }

    Mat4 view = sky_cam_view_mat(self->cam);
    Mat4 proj = sky_cam_proj_mat(self->cam);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SliderFloat3("cam position", &self->cam.position.x, -100.0f, 100.0f);
    ImGui::SliderFloat3("cam forward", &self->cam.forward.x, -1.0f, 1.0f);
    ImGui::SliderFloat("cam fov", &self->cam.fov, 1, 90);
    ImGui::SliderFloat("cam aspect", &self->cam.aspect, 0.1f, 90);
    ImGui::SliderFloat("cam near", &self->cam.znear, 0.1f, 1000.0f);
    ImGui::SliderFloat("cam far", &self->cam.zfar, 0.1f, 1000.0f);

    glViewport(0, 0, self->width, self->height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    sky_gfx_program_set_mat4f(program, "view", &view.m00);
    sky_gfx_program_set_mat4f(program, "proj", &proj.m00);
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