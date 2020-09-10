#include "sky_game.h"
#include "sky_gfx.h"
#include "sky_premitives.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

// unity build
#include "sky_gfx.cpp"
#include "sky_terrain.cpp"
#include "imgui/imgui.cpp"
#include "imgui/imgui_impl_opengl3.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"

const char *vshader = R"""(
    #version 450 core
    layout (location = 0) in vec3 pos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        gl_Position = vec4(pos, 1.0f) * model *view * proj;
    }
)""";

const char *fshader = R"""(
    #version 450 core

    layout (location = 0) out vec4 out_color;

    uniform vec4 color;

    const float near = 0.1; 
    const float far  = 100.0; 

    float linear_depth(float depth) 
    {
        float z = depth * 2.0 - 1.0; // back to NDC 
        return (2.0 * near * far) / (far + near - z * (far - near));
    }

    void main()
    {
        float depth = linear_depth(gl_FragCoord.z) / far;
        out_color.rgb = color.rgb * depth;
        out_color.a = color.a;
    }
)""";

// source: https://www.shadertoy.com/view/MsVSWt
const char *vshader_sky = R"""(
    #version 450 core
    layout (location = 0) in vec3 pos;

    out vec3 v_pos;

    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        gl_Position = vec4(pos * mat3(view), 1.0f) * proj;
        v_pos = pos;
    }
)""";

const char *fshader_sky = R"""(
    #version 450 core

    in vec3 v_pos;

    layout (location = 0) out vec4 out_color;

    void main()
    {
        vec3 pos = v_pos * 0.5f + vec3(0.5f);
        float atmosphere = 1.0f - pos.y;
        vec3 sky_color = vec3(0.2f, 0.4f, 0.8f);

        float scatter = pow(pos.y, 1.0f / 15.0f);
        scatter = 1.0f - clamp(scatter, 0.8f, 1.0f);

        vec3 scatter_color = mix(vec3(1.0f), vec3(1.0f, 0.3f, 0.0f) * 1.5f, scatter);
        vec3 sky = mix(sky_color, vec3(scatter_color), atmosphere / 1.3f);

        float sun = 1.0f - distance(v_pos, vec3(0.0f, 0.0f, -1.0f));
        sun = clamp(sun, 0.0f, 1.0f);

        float glow = sun;
        glow = clamp(glow, 0.0f, 1.0f);

        sun = pow(sun, 100.0f);
        sun *= 100.0f;
        sun = clamp(sun, 0.0f, 1.0f);

        glow = pow(glow, 6.0f);
        glow = pow(glow, pos.y);
        glow = clamp(glow, 0.0f, 1.0f);

        sun *= pow(dot(pos.y, pos.y), 1.0f / 1.65f);

        glow *= pow(dot(pos.y, pos.y), 1.0f / 2.0f);

        sun += glow;

        vec3 sun_color = vec3(1.0f, 0.6f, 0.05f) * sun;

        out_color.rgb = sky + sun_color;
        out_color.a = 1.0f;
    }
)""";

static Sky_Gfx_Handle program;
static Sky_Gfx_Handle program_sky;

static void
_sky_game_init(Sky_Game *self)
{
    *self = {};

    self->cam = sky_cam_init();
    self->iseland_terrain = sky_terrain_generate(200, 200, 200, 200);
    self->water_terrain = sky_terrain_generate(200, 200, 200, 200);

    {
        glGenVertexArrays(1, &self->skybox_VAO);
        glBindVertexArray(self->skybox_VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(premitive_cube), premitive_cube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }

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

    program = sky_gfx_program_new(vshader, fshader);
    program_sky = sky_gfx_program_new(vshader_sky, fshader_sky);

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    sky_gfx_program_use(program_sky);
    sky_gfx_program_set_mat4f(program_sky, "view", &view.m00);
    sky_gfx_program_set_mat4f(program_sky, "proj", &proj.m00);
    glBindVertexArray(self->skybox_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    Mat4 model = mat4_translation(0, -2, 0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    sky_gfx_program_use(program);
    sky_gfx_program_set_mat4f(program, "model", &model.m00);
    sky_gfx_program_set_mat4f(program, "view", &view.m00);
    sky_gfx_program_set_mat4f(program, "proj", &proj.m00);
    Vec4 color = Vec4{34.0f, 167.0f, 78.0f, 1.0f} / 255.0f;
    sky_gfx_program_set_vec4f(program, "color", &color.x);
    glBindVertexArray(self->iseland_terrain.mesh_gpu);
    glDrawArrays(GL_TRIANGLES, 0, self->iseland_terrain.pos_count);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    model = mat4_translation(0, 0, 0);
    Vec4 water_color = Vec4{115.0f, 182.0f, 254.0f, 200.0f} / 255.0f;
    sky_gfx_program_set_mat4f(program, "model", &model.m00);
    sky_gfx_program_set_vec4f(program, "color", &water_color.x);
    glBindVertexArray(self->water_terrain.mesh_gpu);
    glDrawArrays(GL_TRIANGLES, 0, self->water_terrain.pos_count);
    glDisable(GL_BLEND);

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