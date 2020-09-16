#include "sky_gfx.h"

#include <GL/glew.h>
#include <stb/stb_image.h>

#include <assert.h>

void
sky_gfx_init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
}

void
sky_gfx_destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void
sky_gfx_frame_start()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void
sky_gfx_frame_end()
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Sky_Gfx_Handle
sky_gfx_program_new(const char *vshader, const char *fshader)
{
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vshader, nullptr);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (success == false)
    {
        glGetShaderInfoLog(vertex_shader, sizeof(info_log), nullptr, info_log);
        assert(false);
        return Sky_Gfx_Handle{};
    }

    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fshader, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (success == false)
    {
        glGetShaderInfoLog(fragment_shader, sizeof(info_log), nullptr, info_log);
        assert(false);
        return Sky_Gfx_Handle{};
    }

    int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == false)
    {
        glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
        assert(false);
        return Sky_Gfx_Handle{};
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    Sky_Gfx_Handle handle;
    handle.type = SKY_GFX_HANDLE_TYPE_PROGRAM;
    handle.handle = program;
    return handle;
}

void
sky_gfx_program_free(Sky_Gfx_Handle program)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glDeleteProgram(program.handle);
}

void
sky_gfx_program_use(Sky_Gfx_Handle program)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUseProgram(program.handle);
}

void
sky_gfx_program_set_bool(Sky_Gfx_Handle program, const char *name, bool value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform1i(glGetUniformLocation(program.handle, name), (int)value);
}

void
sky_gfx_program_set_int(Sky_Gfx_Handle program, const char *name, int value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform1i(glGetUniformLocation(program.handle, name), value);
}

void
sky_gfx_program_set_float(Sky_Gfx_Handle program, const char *name, float value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform1f(glGetUniformLocation(program.handle, name), value);
}

void
sky_gfx_program_set_vec2i(Sky_Gfx_Handle program, const char *name, int *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform2iv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_vec3i(Sky_Gfx_Handle program, const char *name, int *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform3iv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_vec4i(Sky_Gfx_Handle program, const char *name, int *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform3iv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_vec2f(Sky_Gfx_Handle program, const char *name, float *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform2fv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_vec3f(Sky_Gfx_Handle program, const char *name, float *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform3fv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_vec4f(Sky_Gfx_Handle program, const char *name, float *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    glUniform4fv(glGetUniformLocation(program.handle, name), 1, value);
}

void
sky_gfx_program_set_mat4f(Sky_Gfx_Handle program, const char *name, float *value)
{
    assert(program.type == SKY_GFX_HANDLE_TYPE_PROGRAM);
    // we transpose our matrix so OpenGL deeals with it as row major
    glUniformMatrix4fv(glGetUniformLocation(program.handle, name), 1, GL_TRUE, value);
}

Sky_Gfx_Handle
sky_gfx_texture_load(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    if (data == NULL)
    {
        fprintf(stderr, "failed to load '%s'\n", path);
        exit(EXIT_FAILURE);
    }

    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (channels == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (channels == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        assert(false && "unhandled texture format");
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    Sky_Gfx_Handle handle;
    handle.type = SKY_GFX_HANDLE_TYPE_TEXTURE;
    handle.handle = id;

    return handle;
}

void
sky_gfx_texture_free(Sky_Gfx_Handle texture)
{
    assert(texture.type == SKY_GFX_HANDLE_TYPE_TEXTURE);
    glDeleteTextures(1, &texture.handle);
}