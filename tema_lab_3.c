#include<windows.h>
#include<stdio.h>


int main() {
	HKEY hKey;
	LONG lResult;
	DWORD dwIndex = 0;
	WCHAR szSubKeyName[256];
	DWORD dwSubKeyNameSize;

	lResult = RegOpenKeyExW(
		HKEY_CURRENT_USER,
		L"Software",
		0,
		KEY_READ,
		&hKey
	);

	if (lResult != ERROR_SUCCESS)
	{
		printf("nu s a putut deschide cheia\n");
		return 1;
	}

	printf("subcheile din HKEY_CURRENT_USER\\Software sunt:\n\n");

	while (1)
	{
		dwSubKeyNameSize = 256;

		lResult = RegEnumKeyExW(
			hKey,
			dwIndex,
			szSubKeyName,
			&dwSubKeyNameSize,
			NULL,
			NULL,
			NULL,
			NULL
		);

		if (lResult == ERROR_NO_MORE_ITEMS)
		{
			break;
		}

		if (lResult == ERROR_SUCCESS)
		{
			wprintf(L"%lu. %ls\n", dwIndex + 1, szSubKeyName);
		}
		else
		{
			printf("eroare la citirea subcheii cu indexul %lu\n", dwIndex);
		}

		dwIndex++;
	}

	RegCloseKey(hKey);

	return 0;
}