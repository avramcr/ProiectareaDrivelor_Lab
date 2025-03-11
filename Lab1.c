#include <windows.h>
#include <stdio.h>


void ListServicesImagePath() {
    HKEY hKey;
    TCHAR serviceName[256];
    DWORD serviceNameSize;
    DWORD index = 0;
    TCHAR imagePath[1024];
    DWORD imagePathSize;
    DWORD type;

    
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("Eroare la deschiderea registrului!\n");
        return;
    }

   
    while (1) {
        serviceNameSize = sizeof(serviceName) / sizeof(serviceName[0]);
        if (RegEnumKeyEx(hKey, index, serviceName, &serviceNameSize, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
            break;  
        }

       
        TCHAR servicePath[512];
        wsprintf(servicePath, TEXT("SYSTEM\\CurrentControlSet\\Services\\%s"), serviceName);

        HKEY hServiceKey;
        
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, servicePath, 0, KEY_READ, &hServiceKey) == ERROR_SUCCESS) {
            imagePathSize = sizeof(imagePath);
           
            if (RegQueryValueEx(hServiceKey, TEXT("ImagePath"), NULL, &type, (LPBYTE)imagePath, &imagePathSize) == ERROR_SUCCESS) {
                printf("%S: %S\n", serviceName, imagePath);
            }
            RegCloseKey(hServiceKey);
        }

        index++;
    }

    RegCloseKey(hKey);
}

int main() {
    ListServicesImagePath();
    return 0;
}