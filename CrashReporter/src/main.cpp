#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include "Dbghelp.h"
#include <fstream>
#include <locale>
//#include <codecvt> DEPRECATED
#include <string>
#include <chrono>
#include <ctime>
#include <filesystem>
namespace fs = std::filesystem;
using std::thread;
using std::mutex;
using std::lock_guard;
using std::pair;
using std::ofstream;
using std::string;

#define CRASHLOG_NAME "crashlog.log"
//codecvt is deprecated
//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//inline std::string wide2narrow(std::wstring& ws)
//{
//    return converter.to_bytes(ws);
//}
//inline std::wstring narrow2wide(std::string& s)
//{
//    return converter.from_bytes(s);
//}

inline std::string CurrDateTimeStr()
{
    std::time_t time = std::time({});
    char timeString[std::size("yyyymmddhhmmss")];
    struct tm tDest;
    gmtime_s(&tDest, &time);
    std::strftime(std::data(timeString), std::size(timeString), "%Y%m%d%H%M%S", &tDest);
    return timeString;
}

ofstream logfile(CRASHLOG_NAME, std::ofstream::out);
mutex logfile_mutex;
void PrintLog(const char* format, ...)
{
    lock_guard<mutex> lock(logfile_mutex);
    static int n = 256;
    static char* buffer = new char[n];
    va_list args;
    va_start(args, format);
    int sz = vsnprintf(buffer, n, format, args);
    if (sz > n - 1)
    {
        n = sz + 1;
        delete[] buffer;
        buffer = new char[n];
        vsnprintf(buffer, n, format, args);
    }
    logfile << CurrDateTimeStr() << ": ";
    logfile << buffer;
    logfile.flush();
    va_end(args);
}

void PrintLogW(const WCHAR* format, ...)
{
    lock_guard<mutex> lock(logfile_mutex);
    static int n = 256;
    static WCHAR* wbuffer = new WCHAR[n];
    static CHAR* buffer = new CHAR[n];
    va_list args;
    va_start(args, format);
    int sz = vswprintf_s(wbuffer, n, format, args);
    if (sz > n - 1)
    {
        n = sz + 1;
        delete[] wbuffer;
        delete[] buffer;
        wbuffer = new WCHAR[n];
        buffer = new char[n];
        vswprintf_s(wbuffer, n, format, args);
    }
    size_t temp;
    wcstombs_s(&temp, buffer, n, wbuffer, n);
    logfile << CurrDateTimeStr() << ": ";
    logfile << buffer;
    logfile.flush();
    va_end(args);
}

// pass hndl value (GetCurrentProcess()) from parent in command line via casting DWORD to string
// and use hndl = DuplicateHandle(hParentProc) in child
// cmdline string should contain only handle value
// method can be found here: https://stackoverflow.com/a/46348360
// example debugger code: https://stackoverflow.com/a/7439112
// check for hangs:  https://stackoverflow.com/a/1918257 (SendMessageTimeout + WM_NULL + SMTO_NOTIMEOUTIFNOTHUNG for 30 secs for example)
// extra links:
// https://learn.microsoft.com/en-us/windows/win32/debug/creating-a-basic-debugger
// https://mecanik.dev/en/posts/how-to-write-mini-dump-on-software-crash/
bool WriteCrashDump(EXCEPTION_DEBUG_INFO* pExceptionInfo, HANDLE hProcess, HANDLE hThread, DWORD dwProcessId, DWORD dwThreadId)
{
    CONTEXT c;
    memset(&c, 0, sizeof(c));

    c.ContextFlags = CONTEXT_ALL;
    
    if (!GetThreadContext(hThread, &c))
    {
        PrintLog("MiniDumpWriteDump - GetThreadContext FAILED: %u\n", GetLastError());
        return false;
    }

    EXCEPTION_POINTERS ep;

    ep.ContextRecord = &c;
    ep.ExceptionRecord = &pExceptionInfo->ExceptionRecord;

    MINIDUMP_EXCEPTION_INFORMATION minidump_exception;

    minidump_exception.ThreadId = dwThreadId;
    minidump_exception.ExceptionPointers = &ep;
    minidump_exception.ClientPointers = FALSE;
    
    WCHAR filename[] = L"dump.dmp";
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        PrintLogW(L"MiniDumpWriteDump - CreateFile FAILED to create file %s: %u\n", filename, GetLastError());
        return false;
    }

    BOOL  fSuccess;

    fSuccess = MiniDumpWriteDump(hProcess, dwProcessId, hFile, MiniDumpWithFullMemory, &minidump_exception, NULL, NULL);

    if (fSuccess == FALSE)
    {
        PrintLog("MiniDumpWriteDump - MiniDumpWriteDump FAILED: %u\n", GetLastError());
        CloseHandle(hFile);
        return false;
    }

    PrintLogW(L"MiniDumpWriteDump - dumped to %s\n", filename);
    CloseHandle(hFile);
    return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    auto lPair = (pair<DWORD, HWND*>*) lParam;//pair <[in]target pid, [out]hwnd*>
    
    DWORD pid = 0;

    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == lPair->first)
    {
        PrintLog("Found hWnd: %u.\n", (DWORD) hWnd);
        SetLastError(ERROR_SUCCESS);
        *(lPair->second) = hWnd;
        return FALSE;
    }

    return TRUE;
}

void HangLoop(HANDLE hProcess, DWORD dwTargetProcessId, DWORD pollDelay, DWORD hungDelay)
{
    HWND hWnd = 0;
    pair<DWORD, HWND*> lPair = { dwTargetProcessId, &hWnd };
    /*if (!EnumWindows(EnumWindowsProc, (LPARAM)&lPair))
    {
        DWORD err = GetLastError();
        if (err != ERROR_SUCCESS)
        {
            PrintLog("EnumWindows 0 - FAILED: %u\n", GetLastError());
            return;
        }
    }
    PrintLog("HangLoop - hWnd: %u\n", hWnd);*/

    DWORD dNull;

    PrintLog("HangLoop - listening for hangs...\n");
    DWORD err;
    while (true)
    {
        if (SendMessageTimeout(hWnd, WM_NULL, 0, 0, SMTO_BLOCK | SMTO_ABORTIFHUNG, pollDelay, &dNull))
        {
            //PrintLog("SendMessageTimeout 1 - success...\n");
            Sleep(pollDelay);
            continue;
        }
        err = GetLastError();
        if (err == ERROR_TIMEOUT)
        {
            PrintLog("SendMessageTimeout 1 - potential timeout...\n");
            while (true)
            {
                if (!SendMessageTimeout(hWnd, WM_NULL, 0, 0, SMTO_BLOCK, hungDelay, &dNull))
                {
                    err = GetLastError();
                    if (err == ERROR_TIMEOUT)
                    {
                        //breaktpoint will be caught inside DebugLoop
                        PrintLog("SendMessageTimeout 2 - timeout! Throwing remote break point...\n");
                        DebugBreakProcess(hProcess);
                        return;
                    }
                    else if(err == ERROR_INVALID_WINDOW_HANDLE)
                    {
                        if (!EnumWindows(EnumWindowsProc, (LPARAM)&lPair))
                        {
                            DWORD err = GetLastError();
                            if (err != ERROR_SUCCESS)
                            {
                                PrintLog("EnumWindows 2 - FAILED: %u\n", err);
                                return;
                            }
                            continue;
                        }
                        continue;
                    }
                    else
                    {
                        PrintLog("SendMessageTimeout 2 - FAILED: %u\n", err);
                        return;
                    }
                }
                else
                {
                    //PrintLog("SendMessageTimeout 2 - success...\n");
                    break;
                }
            }
            
            
        }
        else if (err == ERROR_INVALID_WINDOW_HANDLE)
        {
            if (!EnumWindows(EnumWindowsProc, (LPARAM)&lPair))
            {
                DWORD err = GetLastError();
                if (err != ERROR_SUCCESS)
                {
                    PrintLog("EnumWindows 1 - FAILED: %u\n", err);
                    return;
                }
                continue;
            }
            continue;
        }
        else
        {
            PrintLog("SendMessageTimeout 1 - FAILED: %u\n", err);
            break;
        }
    }
}
bool IsWINE()

{
    HMODULE hmod = GetModuleHandleA("ntdll.dll");
    if (!hmod)
        return false;
    if (!GetProcAddress(hmod, "wine_get_version"))
        return false;
    return true;

}

bool DebugLoop(DWORD dwTargetProcessId, DWORD pollDelay, DWORD hungDelay, bool &dumped)
{
    DEBUG_EVENT de;
    HANDLE hProcess;
    PrintLog("OpenProcess\n");
    bool is_wine = IsWINE();
    if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTargetProcessId)) == NULL)
    {
        PrintLog("OpenProcess - FAILED: %u\n", GetLastError());
        return false;
    }
    PrintLog("IsWINE: %u\n", is_wine);
    BOOL bDbgrPresent;
    PrintLog("CheckRemoteDebuggerPresent\n");
    if (CheckRemoteDebuggerPresent(hProcess, &bDbgrPresent) && bDbgrPresent)
    {
        PrintLog("Remote debugger already present, exiting...\n");
        return false;
    }
    PrintLog("DebugActiveProcess\n");
    if (!DebugActiveProcess(dwTargetProcessId))
    {
        PrintLog("DebugActiveProcess - FAILED: %u\n", GetLastError());
        return false;
    }
    PrintLog("Starting HangLoop thread\n");
    thread(HangLoop, hProcess, dwTargetProcessId, pollDelay, hungDelay).detach();
    PrintLog("Entering WaitForDebugEvent loop\n");
    unsigned int numBPs = 0;
    bool isHung;
    dumped = false;
    DWORD dwContinueStatus;
    while (1)
    {
        WaitForDebugEvent(&de, INFINITE);
        isHung = false;
        dwContinueStatus = DBG_CONTINUE;
        if (de.dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
        {
            //one EXCEPTION_BREAKPOINT occurs after DebugActiveProcess
            isHung = de.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT && numBPs++ >= 1;
            if ((de.u.Exception.ExceptionRecord.ExceptionCode != EXCEPTION_BREAKPOINT && !de.u.Exception.dwFirstChance) || isHung)
            {

                DWORD dwThreadId;
                HANDLE hThread;

                PrintLog("Exception caught with code: %u, dumping...\n", de.u.Exception.ExceptionRecord.ExceptionCode);

                dwThreadId = de.dwThreadId;
                hThread = OpenThread(THREAD_ALL_ACCESS, false, dwThreadId);
                if (hThread == NULL)
                {
                    PrintLog("Failed to open crashing thread: %u\n", GetLastError());
                    return false;
                }
                if (!WriteCrashDump(&de.u.Exception, hProcess, hThread, dwTargetProcessId, dwThreadId))
                {
                    PrintLog("Failed to write crash dump\n");
                    return false;
                }
                dumped = true;
                break;
            }
            else
            {
                dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
            }
        }
        else if(de.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
        {
            PrintLog("Parent process exiting with code: %u\n", de.u.ExitProcess.dwExitCode);
            break;
        }
        else if(de.dwDebugEventCode == RIP_EVENT)
        {
            PrintLog("Debugging system error: %u type: %u\n", de.u.RipInfo.dwError, de.u.RipInfo.dwType);
            return false;
        }
        ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
    }

    DebugActiveProcessStop(dwTargetProcessId);
    if (isHung)
    {
        PrintLog("Terminating hung game process...\n");
        TerminateProcess(hProcess, -1);
    }
    
    //WaitForSingleObject(hProcess, 10000);


    return true;
}

void CopyCrashFiles()
{
    auto mainPath = fs::current_path(); //should be main or mainta or maintt
    //PrintLogW(L"Current Path: %s\n", mainPath.c_str());
    auto nfPath = mainPath / "nightfall";
    //PrintLogW(L"NF dir Path: %s\n", nfPath.c_str());
    string dateTimeStr = CurrDateTimeStr();
    auto crashDmpPath = nfPath / "crashes" / dateTimeStr;
    PrintLogW(L"Crash dump Path: %s\n", crashDmpPath.c_str());
    std::error_code ec;
    if (!fs::create_directories(crashDmpPath, ec) && ec)
    {
        PrintLog("Failed to create crash dump path: %s\n", ec.message());
        return;
    }
    if (!fs::copy_file(mainPath / "qconsole.log", crashDmpPath / "qconsole.log", ec))
    {
        PrintLog("Failed to copy qconsole.log: %s\n", ec.message());
    }
    fs::rename(mainPath / "dump.dmp", crashDmpPath / "dump.dmp", ec);
    if (ec)
    {
        PrintLog("Failed to move crash dump: %s\n", ec.message());
    }
    if (!fs::copy_file(mainPath / CRASHLOG_NAME, crashDmpPath / CRASHLOG_NAME, ec))
    {
        PrintLog("Failed to copy crash log: %s\n", ec.message());
    }
}


//pCmdLine: 134321524       5000            30000
//          ^parent pid     ^polling delay  ^hung duration
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    DWORD dwParentPID;
    DWORD pollDelay, hungDelay;

    if (swscanf_s(pCmdLine, L"%u %u %u", &dwParentPID, &pollDelay, &hungDelay) != 3)
    {
        PrintLogW(L"Failed to parse CMDLine: %s", pCmdLine);
        return -1;
    }

    PrintLog("ParentPID: %u\n", dwParentPID);
    bool dumped;
    if (!DebugLoop(dwParentPID, pollDelay, hungDelay, dumped))
    {
        PrintLog("Ending crash reporter due to previous error.");
        return -3;
    }

    if(dumped)
        CopyCrashFiles();
    //PrintLog("Exiting crash reporter normally.");
    
    return 0;
}