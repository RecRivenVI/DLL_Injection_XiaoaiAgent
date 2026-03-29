#include <windows.h>
#include <iostream>
#include <string>

// --- 1. 工具函数定义 (必须放在 main 之前) ---

// 从注册表获取安装路径
std::string GetExecutablePathFromRegistry(const std::string& subKey, const std::string& valueName) {
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) {
        return "";
    }

    char buffer[MAX_PATH];
    DWORD bufferSize = sizeof(buffer);
    if (RegQueryValueExA(hKey, valueName.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);
    return std::string(buffer);
}

// 获取当前注入器自己所在的目录
std::string GetCurrentModuleDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    std::string::size_type pos = path.find_last_of("\\/");
    return (pos != std::string::npos) ? path.substr(0, pos) : "";
}

// --- 2. 主逻辑 ---

int main() {
    // 设置控制台标题，方便用户识别
    SetConsoleTitleA("XiaoaiAgent Injector");

    // A. 确定要注入的 .dll 文件路径
    std::string dllName = "msimg32.dll"; 
    std::string dllAbsolutePath = GetCurrentModuleDir() + "\\" + dllName;

    // 检查文件是否存在
    DWORD dwAttrib = GetFileAttributesA(dllAbsolutePath.c_str());
    if (dwAttrib == INVALID_FILE_ATTRIBUTES || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        MessageBoxA(NULL, "错误：在当前目录下未找到 msimg32.dll 文件！你需要从 DLL 作者 ChsBuffer 处获取最新的 msimg32.dll 并放置于当前目录！", "注入失败", MB_ICONERROR);
        return 1;
    }

    // B. 获取小爱同学安装路径
    std::string regSubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\XiaoaiAgent.exe";
    std::string installPath = GetExecutablePathFromRegistry(regSubKey, "Path");
    
    if (installPath.empty()) {
        MessageBoxA(NULL, "错误：未能从小爱注册表获取安装路径，请检查程序是否安装！", "注入失败", MB_ICONERROR);
        return 1;
    }
    std::string exePath = installPath + "\\XiaoaiAgent.exe";

    // C. 启动进程
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    std::cout << "[+] Launching: " << exePath << std::endl;

    if (!CreateProcessA(NULL, (LPSTR)exePath.c_str(), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        std::cerr << "[-] CreateProcess Failed. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // D. 远程注入
    std::cout << "[+] Injecting: " << dllName << std::endl;

    LPVOID pRemoteMem = VirtualAllocEx(pi.hProcess, NULL, dllAbsolutePath.length() + 1, MEM_COMMIT, PAGE_READWRITE);
    if (!pRemoteMem) goto cleanup;

    if (!WriteProcessMemory(pi.hProcess, pRemoteMem, (LPVOID)dllAbsolutePath.c_str(), dllAbsolutePath.length() + 1, NULL)) goto cleanup;

    {
        FARPROC pLoadLib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
        HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLib, pRemoteMem, 0, NULL);

        if (hThread) {
            WaitForSingleObject(hThread, 3000); // 等待 DLL 加载完成
            CloseHandle(hThread);
        } else {
            std::cerr << "[-] CreateRemoteThread Failed." << std::endl;
        }
    }

    VirtualFreeEx(pi.hProcess, pRemoteMem, 0, MEM_RELEASE);

    // E. 恢复运行
    std::cout << "[+] Injection completed. Resuming process..." << std::endl;
    ResumeThread(pi.hThread);

    // 清理句柄并正常退出
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;

cleanup:
    std::cerr << "[-] Critical Error during injection." << std::endl;
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 1;
}