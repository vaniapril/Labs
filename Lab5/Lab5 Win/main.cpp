#include <Windows.h>
#include <string>

int main() {
    STARTUPINFO paintSi = {sizeof(paintSi)};
    PROCESS_INFORMATION paintPi;

    STARTUPINFO notepadSi = {sizeof(notepadSi)};
    PROCESS_INFORMATION notepadPi;

    STARTUPINFO killerSi = {sizeof(killerSi)};
    PROCESS_INFORMATION killerPi;

    // id
    CreateProcessA("c:\\Windows\\System32\\mspaint.exe", NULL, NULL, NULL, FALSE, NULL, NULL, "c:\\Windows\\System32",
                   &paintSi, &paintPi);
    Sleep(1000);
    CreateProcessA("Killer.exe", "Killer.exe --name mspaint.exe", NULL, NULL, TRUE, NULL, NULL, NULL, &killerSi,
                   &killerPi);
    WaitForSingleObject(killerPi.hProcess, INFINITE);
    CloseHandle(killerPi.hProcess);
    Sleep(1000);

    //Name
    CreateProcessA("c:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, "c:\\Windows\\System32",
                   &notepadSi, &notepadPi);

    Sleep(1000);
    std::string str = std::string("Killer.exe --id ").append(std::to_string(notepadPi.dwProcessId));
    CreateProcessA("Killer.exe", const_cast<char *>(str.c_str()), NULL, NULL, TRUE, NULL, NULL, NULL, &killerSi,
                   &killerPi);
    WaitForSingleObject(killerPi.hProcess, INFINITE);
    CloseHandle(killerPi.hProcess);
    Sleep(1000);

    // PROC_TO_KILL

    CreateProcessA("c:\\Windows\\System32\\mspaint.exe", NULL, NULL, NULL, FALSE, NULL, NULL, "c:\\Windows\\System32",
                   &paintSi, &paintPi);
    CreateProcessA("c:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, "c:\\Windows\\System32",
                   &notepadSi, &notepadPi);

    Sleep(1000);
    SetEnvironmentVariableA("PROC_TO_KILL", "notepad.exe,mspaint.exe");
    CreateProcessA("Killer.exe", "Killer.exe", NULL, NULL, TRUE, NULL, NULL, NULL, &killerSi, &killerPi);
    WaitForSingleObject(killerPi.hProcess, INFINITE);
    CloseHandle(killerPi.hProcess);
    SetEnvironmentVariableA("PROC_TO_KILL", NULL);
    Sleep(1000);

    return 0;
}
