#include <iostream>
#include <windows.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "Ru");

	const char* registryPath = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
	const char* valueName = "DefaultTTL";

	DWORD valueData = 65;

	HKEY hKey;
	LONG openRes = RegOpenKeyExA(HKEY_LOCAL_MACHINE, registryPath, 0, KEY_SET_VALUE, &hKey);


    if (openRes == ERROR_SUCCESS) {

    }
    else {
        cerr << "Ошибка при открытии ключа: " << openRes << endl;
    }


	try
	{
		if (openRes != ERROR_SUCCESS) {
			throw runtime_error("Ошибка при открытии ключа: ");
		}
		try
		{
			LONG setRes = RegSetValueExA(hKey, valueName, 0, REG_DWORD, (const BYTE*)&valueData, sizeof(valueData));

			if (setRes == ERROR_SUCCESS) {
				cout << "DWORD значение успешно создано." << endl;
			}
			else {
				throw runtime_error("Ошибка при установке значения : ");
			}

			RegCloseKey(hKey);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	catch (const exception& e)
	{
		cout << openRes << endl << e.what() << endl;
	}
	
	return 0;
}