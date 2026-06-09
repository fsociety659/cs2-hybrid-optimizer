#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>

int silent_delete(const char* path) {
    DWORD attribs = GetFileAttributesA(path);
    if (attribs == INVALID_FILE_ATTRIBUTES) return 1;

    char double_null_path[MAX_PATH + 2] = {0};
    snprintf(double_null_path, MAX_PATH, "%s", path);

    int len = strlen(double_null_path);
    double_null_path[len] = '\0';
    double_null_path[len + 1] = '\0';

    SHFILEOPSTRUCTA fileOp = {0};
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = double_null_path;
    fileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

    return (SHFileOperationA(&fileOp) == 0);
}

__declspec(dllexport) int clear_gpu_cache() {
    char* localappdata = getenv("LOCALAPPDATA");
    int success = 1;

    if (localappdata != NULL) {
        char path[MAX_PATH];

        snprintf(path, sizeof(path), "%s\\D3DSCache", localappdata);
        success = success && silent_delete(path);

        snprintf(path, sizeof(path), "%s\\NVIDIA\\DXCache", localappdata);
        success = success && silent_delete(path);

        snprintf(path, sizeof(path), "%s\\NVIDIA\\GLCache", localappdata);
        success = success && silent_delete(path);


        snprintf(path, sizeof(path), "%s\\AMD\\DxCache", localappdata);
        success = success && silent_delete(path);
    }
    return success;
}

__declspec(dllexport) int clear_steam_shader_cache() {
    char* programfiles = getenv("ProgramFiles(x86)");
    if (programfiles != NULL) {
        char steam_cache[MAX_PATH];
        snprintf(steam_cache, sizeof(steam_cache), "%s\\Steam\\shadercache\\730", programfiles);
        return silent_delete(steam_cache);
    }
    return 0;
}

__declspec(dllexport) int clear_ram_standby_list() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_INCREASE_QUOTA_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
        CloseHandle(hToken);
    }

    int result = SetProcessWorkingSetSize(GetCurrentProcess(), (SIZE_T)-1, (SIZE_T)-1);
    return (result != 0) ? 1 : 0;
}
