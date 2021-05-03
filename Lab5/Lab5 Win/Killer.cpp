#include <Windows.h>
#include <conio.h>
#include <tlhelp32.h>
#include <iostream>

//--id 18864
//--name gitkraken.exe

int endWithId(DWORD processId){
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS,
                                FALSE,
                                processId);
    TerminateProcess(handle,2);
    return 0;
}

int endWithName(char* name){
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, name) == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                TerminateProcess(hProcess, 2);
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}

int endWithNames(char* names){
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (strstr(names, entry.szExeFile) != NULL)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                TerminateProcess(hProcess, 2);
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc > 2){
        if(stricmp(argv[1], "--id") == 0){
            endWithId(atoi( argv[2]));
        }
        if(stricmp(argv[1], "--name") == 0){
            endWithName(argv[2]);
        }
    }

    char value[200];
    DWORD dword = GetEnvironmentVariable("PROC_TO_KILL", value, sizeof(value));
    if(dword){
        endWithNames(value);
    }
    return 0;
}