#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <iostream>
#include <string>
using namespace std;

#pragma comment(lib, "setupapi.lib")

int main() {
	HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, 0, 0, DIGCF_PRESENT);

	if (deviceInfoSet == INVALID_HANDLE_VALUE) {
		cout << "EROARE" << endl;
		return 1;
	}

	SP_DEVINFO_DATA deviceInfoData;
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	cout << "Dispozitive USB conectate:\n\n";

	for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
		char deviceName[256] = { 0 };

		if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL,
			(PBYTE)deviceName, sizeof(deviceName), NULL)) {
			cout << "Dispozitiv: " << deviceName << endl;
		}
	}

	SetupDiDestroyDeviceInfoList(deviceInfoSet);

	return 0;
}

