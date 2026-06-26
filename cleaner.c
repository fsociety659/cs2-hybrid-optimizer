#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>
#include <winternl.h>

static int silent_delete(const char* path) {
    DWORD attribs = GetFileAttributesA(path);
    if (attribs == INVALID_FILE_ATTRIBUTES) {
        return 0;
    }

    char double_null_path[32768];
    ZeroMemory(double_null_path, sizeof(double_null_path));

    char full_path[MAX_PATH];
    if (GetFullPathNameA(path, sizeof(full_path), full_path, NULL) == 0) {
        strncpy_s(full_path, sizeof(full_path), path, _TRUNCATE);
    }

    size_t len = snprintf(double_null_path, sizeof(double_null_path) - 1, "%s", full_path);
    if (len >= sizeof(double_null_path) - 1) {
        return 0;
    }

    SHFILEOPSTRUCTA fileOp = {0};
    fileOp.wFunc  = FO_DELETE;
    fileOp.pFrom  = double_null_path;
    fileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

    int result = SHFileOperationA(&fileOp);
    if (result == 0 && fileOp.fAnyOperationsAborted == 0) {
        if (GetFileAttributesA(full_path) == INVALID_FILE_ATTRIBUTES) {
            return 1;
        }
    }
    return 0;
}

__declspec(dllexport) int clear_gpu_cache() {
    char* localappdata = getenv("LOCALAPPDATA");
    if (localappdata == NULL) return 0;

    char path[MAX_PATH * 2];
    int any_success = 0;

    const char* subdirs[] = {
        "D3DSCache",
        "NVIDIA\\DXCache",
        "NVIDIA\\GLCache",
        "AMD\\DxCache",
        "AMD\\OglCache",
        "AMD\\VkCache"
    };
    for (int i = 0; i < sizeof(subdirs)/sizeof(subdirs[0]); i++) {
        snprintf(path, sizeof(path), "%s\\%s", localappdata, subdirs[i]);
        if (silent_delete(path)) any_success = 1;
    }
    return any_success;
}

__declspec(dllexport) int clear_steam_shader_cache_ex(const char* steam_path) {
    if (steam_path == NULL || steam_path[0] == '\0') return 0;
    char shader_cache[MAX_PATH * 2];
    snprintf(shader_cache, sizeof(shader_cache), "%s\\shadercache\\730", steam_path);
    return silent_delete(shader_cache);
}

typedef NTSTATUS (WINAPI *NtSetSystemInformation_t)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength
);

__declspec(dllexport) int clear_ram_standby_list() {
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return 0;
    }

    TOKEN_PRIVILEGES tkp = {0};
    if (!LookupPrivilegeValueA(NULL, "SeIncreaseQuotaPrivilege", &tkp.Privileges[0].Luid)) {
        CloseHandle(hToken);
        return 0;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0) || GetLastError() != ERROR_SUCCESS) {
        CloseHandle(hToken);
        return 0;
    }
    CloseHandle(hToken);

    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (ntdll == NULL) return 0;

    NtSetSystemInformation_t NtSetSysInfo =
        (NtSetSystemInformation_t)GetProcAddress(ntdll, "NtSetSystemInformation");
    if (NtSetSysInfo == NULL) return 0;

    ULONG sysInfoClass = 80;
    ULONG cmd = 4;
    NTSTATUS status = NtSetSysInfo(sysInfoClass, &cmd, sizeof(cmd));

    return (status == 0) ? 1 : 0;
}

typedef NTSTATUS (WINAPI *NtQueryTimerResolution_t)(
    PULONG MinimumResolution,
    PULONG MaximumResolution,
    PULONG CurrentResolution
);
typedef NTSTATUS (WINAPI *NtSetTimerResolution_t)(
    ULONG DesiredResolution,
    BOOLEAN SetResolution,
    PULONG CurrentResolution
);

__declspec(dllexport) int force_high_precision_timer() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (ntdll == NULL) return 0;

    NtQueryTimerResolution_t NtQueryTimerRes =
        (NtQueryTimerResolution_t)GetProcAddress(ntdll, "NtQueryTimerResolution");
    NtSetTimerResolution_t NtSetTimerRes =
        (NtSetTimerResolution_t)GetProcAddress(ntdll, "NtSetTimerResolution");
    if (NtQueryTimerRes == NULL || NtSetTimerRes == NULL) return 0;

    ULONG minRes, maxRes, curRes;
    if (NtQueryTimerRes(&minRes, &maxRes, &curRes) != 0) return 0;

    ULONG actual;
    NTSTATUS status = NtSetTimerRes(maxRes, TRUE, &actual);
    return (status == 0) ? 1 : 0;
}