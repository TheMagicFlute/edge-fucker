#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <WinBase.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

bool process_is_exist(const std::string& process_name)  
{  
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  
   if (hSnapshot == INVALID_HANDLE_VALUE)  
       return false;  
   PROCESSENTRY32 pe;  
   pe.dwSize = sizeof(PROCESSENTRY32);  
   if (!Process32First(hSnapshot, &pe))  
   {  
       CloseHandle(hSnapshot);  
       return false;  
   }  
   do  
   {  
       // Convert WCHAR to std::string for comparison  
       std::wstring wstrExeFile(pe.szExeFile);  
       std::string strExeFile(wstrExeFile.begin(), wstrExeFile.end());  
       if (process_name == strExeFile)  
       {  
           CloseHandle(hSnapshot);  
           return true;  
       }  
   } while (Process32Next(hSnapshot, &pe));  
   CloseHandle(hSnapshot);  
   return false;  
}

int main()
{
    while (true)
    {
        // none-stop fuck the edge & ie
        if (process_is_exist("msedge.exe"))
        {
            system("taskkill /f /im msedge.exe");
        }
        // ie
        if (process_is_exist("iexplore.exe"))
        {
            system("taskkill /f /im iexplore.exe");
        }
        Sleep(1000);
    }

    return 0;
}
