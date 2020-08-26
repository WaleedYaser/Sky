#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <assert.h>

#include "sky_game.h"

inline void
_hot_reload_sky_game(Sky_Game_Api **api)
{
	HANDLE hfile = CreateFile(L"sky_game.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	assert(hfile && "can't open sky_game.dll");

	FILETIME ftwrite;
	bool res = GetFileTime(hfile, nullptr, nullptr, &ftwrite);

	CloseHandle(hfile);
	if (res == false)
		return;

    static FILETIME last_time;
	if (CompareFileTime(&last_time, &ftwrite) == 0)
		return;

    static HMODULE sky_game_dll;
	if (sky_game_dll)
	{
		res = FreeLibrary(sky_game_dll);
		assert(res && "failed to unload sky_game.dll");
	}

	res = CopyFile(L"sky_game.dll", L"sky_game_tmp.dll", false);
	if (res == false)
		return;

	sky_game_dll = LoadLibrary(L"sky_game_tmp.dll");
	assert(sky_game_dll && "failed to load kuro.dll");

    *api = ((sky_game_api_proc)GetProcAddress(sky_game_dll, SKY_GAME_API_PROC_NAME))();

	last_time = ftwrite;
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

    // initialize game
    Sky_Game_Api *api = nullptr;
    _hot_reload_sky_game(&api);

    Sky_Game game;
    api->construct(&game);

    while (game.quit == false)
    {
        _hot_reload_sky_game(&api);

        api->loop(&game);

        wsprintf(buffer, L"%d\n", game.count);
        OutputDebugString(buffer);

        Sleep(16);
    }

    api->destruct(&game);

    return 0;
}