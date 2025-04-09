#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void setRegistryValue(const string& registryPath, const string& valueName, DWORD valueData) {
	HKEY hKey;
	LONG openRes = RegOpenKeyExA(HKEY_LOCAL_MACHINE, registryPath.c_str(), 0, KEY_SET_VALUE, &hKey);

	if (openRes != ERROR_SUCCESS) {
		cerr << "Ошибка при открытии ключа: " << openRes << endl;
		return;
	}

	LONG setRes = RegSetValueExA(hKey, valueName.c_str(), 0, REG_DWORD, (const BYTE*)&valueData, sizeof(valueData));

	if (setRes == ERROR_SUCCESS) {
		cout << "DWORD значение успешно создано." << endl;
	}
	else {
		cerr << "Ошибка при установке значения: " << setRes << endl;
	}

	RegCloseKey(hKey);
}

int main() {
	setlocale(LC_ALL, "Ru");

	const string registryPath = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
	const string valueName = "DefaultTTL";

	DWORD valueData = 65;

	setRegistryValue(registryPath, valueName, valueData);
	
	return 0;
}
