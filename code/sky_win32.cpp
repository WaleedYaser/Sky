#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/GL.h>
#include <assert.h>

#include "sky_game.h"

LRESULT CALLBACK
_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    };
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

inline bool
_hot_reload_sky_game(Sky_Game_Api **api)
{
	HANDLE hfile = CreateFile(L"sky_game.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	assert(hfile && "can't open sky_game.dll");

	FILETIME ftwrite;
	bool res = GetFileTime(hfile, nullptr, nullptr, &ftwrite);

	CloseHandle(hfile);
	if (res == false)
		return false;

    static FILETIME last_time;
	if (CompareFileTime(&last_time, &ftwrite) == 0)
		return false;

    static HMODULE sky_game_dll;
	if (sky_game_dll)
	{
		res = FreeLibrary(sky_game_dll);
		assert(res && "failed to unload sky_game.dll");
	}

	res = CopyFile(L"sky_game.dll", L"sky_game_tmp.dll", false);
	if (res == false)
		return false;

	sky_game_dll = LoadLibrary(L"sky_game_tmp.dll");
	assert(sky_game_dll && "failed to load kuro.dll");

    *api = ((sky_game_api_proc)GetProcAddress(sky_game_dll, SKY_GAME_API_PROC_NAME))();

	last_time = ftwrite;

    return true;
}

int
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    // set current directory to process directory
    wchar_t buffer[1024] = {};
    GetModuleFileName(0, buffer, sizeof(buffer));
    wchar_t *last_slash = buffer;
    wchar_t *iter = buffer;
    while (*iter++)
        if (*iter == L'\\')
            last_slash = ++iter;
    *last_slash = L'\0';
    bool res = SetCurrentDirectory(buffer);
    assert(res && "SetCurrentDirectory failed");

    // window creation
    WNDCLASSEX wcx = {};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_OWNDC;
    wcx.lpfnWndProc = _wnd_proc;
    wcx.hInstance = hInstance;
    wcx.lpszClassName = L"sky_window_class";
    ATOM class_atom = RegisterClassEx(&wcx);
    assert(class_atom != 0 && "RegisterClassExA failed");

    HWND hwnd = CreateWindowEx(
        0,
        MAKEINTATOM(class_atom),
        L"sky",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    // opengl context
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // flags
        PFD_TYPE_RGBA, // kind of framebuffer
        32, // colordepth of framebuffer
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, // number of bits for depthbuffer
        8, // number of bits for stencilbuffer
        0, // number of Aux buffers in the framebuffer
        PFD_MAIN_PLANE,
        0,
        0, 0, 0};

    HDC hdc = GetDC(hwnd);
    int pixel_format = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixel_format, &pfd);

    HGLRC context = wglCreateContext(hdc);
    wglMakeCurrent(hdc, context);

    const char *gl_version = (char *)glGetString(GL_VERSION);
    wchar_t *w_gl_version = buffer;
    while (true)
    {
        *w_gl_version++ = *gl_version++;
        if (*w_gl_version == 0)
            break;
    }
    OutputDebugString(L"opengl version: ");
    OutputDebugString(buffer);
    OutputDebugString(L"\n");

    // initialize game
    Sky_Game_Api *api = nullptr;
    _hot_reload_sky_game(&api);

    Sky_Game game;
    api->construct(&game);
    api->reload(&game);

    while (game.quit == false)
    {
        MSG msg = {};
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            switch (msg.message)
            {
            case WM_QUIT:
                game.quit = true;
                break;
            }
        }
        RECT rect;
        GetClientRect(hwnd, &rect);
        game.width = rect.right - rect.left;
        game.height = rect.bottom - rect.top;

        if (_hot_reload_sky_game(&api))
            api->reload(&game);
        api->loop(&game);

        SwapBuffers(hdc);
    }

    wglDeleteContext(context);
    DestroyWindow(hwnd);
    api->destruct(&game);

    return 0;
}