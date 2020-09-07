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

    out vec3 v_pos;

    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        v_pos = pos;
        gl_Position = vec4(pos, 1.0f) * view * proj;
    }
)""";

const char *fshader = R"""(
    #version 450 core

    in vec3 v_pos;

    layout (location = 0) out vec4 out_color;

    uniform vec3 cam_forward;

    void main()
    {
        float ambient_factor = 0.2f;
        vec3 ambient_color = ambient_factor * vec3(1.0f, 1.0f, 1.0f);

        const vec3 lights[5] = vec3[](
            vec3(   0.0f, -100.0f,    0.0f),
            vec3(-100.0f, -100.0f, -100.0f),
            vec3( 100.0f, -100.0f, -100.0f),
            vec3(-100.0f, -100.0f,  100.0f),
            vec3( 100.0f, -100.0f,  100.0f)
        );

        float diffuse_factor = 0;
        for (int i = 0; i < 1; ++i)
        {
            vec3 normal = normalize(v_pos);
            vec3 light_dir = normalize(lights[i] - v_pos);
            diffuse_factor += max(dot(normal, light_dir), 0.0f);
        }
        vec3 diffuse_color = diffuse_factor * vec3(1.0f, 1.0f, 1.0f);

        vec3 color = gl_FragCoord.xyz / 1000.0f;
        out_color.rgb = (ambient_color + diffuse_color) * color;
        out_color.a = 1.0f;
    }
)""";

static Sky_Gfx_Handle program;


static void
_sky_game_init(Sky_Game *self)
{
    *self = {};

    self->cam = sky_cam_init();

    glGenVertexArrays(1, &self->VAO);
    glBindVertexArray(self->VAO);

    glGenBuffers(1, &self->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, self->VBO);
    glBufferData(GL_ARRAY_BUFFER, SKY_GAME_MAX_VERTEX_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
}

static void
_sky_game_destroy(Sky_Game *self)
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

    for (int i = 0; i < SKY_GAME_MAP_WIDTH * SKY_GAME_MAP_HEIGHT; ++i)
        self->map[i] = i % 2;

    float cube[] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
    
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
    
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
    
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
    
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
    
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
    };

    self->map_cpu_vertex_count = 0;
    for (int j = 0; j < SKY_GAME_MAP_HEIGHT; ++j)
    {
        for (int i = 0; i < SKY_GAME_MAP_WIDTH; ++i)
        {
            char value = self->map[j * SKY_GAME_MAP_WIDTH + i];
            if (value == 1)
            {
                for (int k = 0; k < 108; k += 3)
                {
                    float x_offset = (float)((-SKY_GAME_MAP_WIDTH / 2 + i) * 2);
                    float y_offset = -2.0f;
                    float z_offset = (float)((-SKY_GAME_MAP_HEIGHT / 2 + j) * 2);
                    self->map_cpu[self->map_cpu_vertex_count++] = cube[k + 0] + x_offset;
                    self->map_cpu[self->map_cpu_vertex_count++] = cube[k + 1] + y_offset;
                    self->map_cpu[self->map_cpu_vertex_count++] = cube[k + 2] + z_offset;
                }
            }
        }
    }

    glNamedBufferSubData(self->VBO, 0, self->map_cpu_vertex_count * sizeof(float), self->map_cpu);

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

    // source: https://community.khronos.org/t/simple-camera-rotation-around-a-point/75219/2
    float rotation_speed = 0.05f;
    if (self->input.keys[SKY_KEY_MOUSE_RIGHT].down)
    {
        if (self->input.mouse_dx > 0)
        {
            self->cam.rotation.y += rotation_speed;
        }
        else if (self->input.mouse_dx < 0)
        {
            self->cam.rotation.y -= rotation_speed;
        } 
    }

    Mat4 view = sky_cam_view_mat(self->cam);
    Mat4 proj = sky_cam_proj_mat(self->cam);
    Vec3 cam_forward = mat4_axis_z(view);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SliderFloat3("cam position", &self->cam.position.x, -100.0f, 100.0f);
    ImGui::SliderFloat3("cam rotation", &self->cam.rotation.x, -100.0f, 100.0f);
    ImGui::SliderFloat("cam fov", &self->cam.fov, 1, 90);
    ImGui::SliderFloat("cam aspect", &self->cam.aspect, 0.1f, 90);
    ImGui::SliderFloat("cam near", &self->cam.znear, 0.1f, 1000.0f);
    ImGui::SliderFloat("cam far", &self->cam.zfar, 0.1f, 1000.0f);

    glViewport(0, 0, self->width, self->height);

    glClearColor(0.23f, 0.41f, 0.42f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sky_gfx_program_set_mat4f(program, "view", &view.m00);
    sky_gfx_program_set_mat4f(program, "proj", &proj.m00);
    sky_gfx_program_set_vec3f(program, "cam_forward", &cam_forward.x);

    glBindVertexArray(self->VAO);
    glDrawArrays(GL_TRIANGLES, 0, self->map_cpu_vertex_count / 3);

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Sky_Game_Api *
sky_game_api()
{
    static Sky_Game_Api api;

    api.init = _sky_game_init;
    api.destoy = _sky_game_destroy;
    api.reload = _sky_game_reload;
    api.loop = _sky_game_loop;

    return &api;
}