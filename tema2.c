#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	SC_HANDLE hSCM;
	DWORD bytesNeeded = 0;
	DWORD servicesCount = 0;
	DWORD resumeHandle = 0;
	DWORD bufferSize = 0;
	LPENUM_SERVICE_STATUS_PROCESS lpServices = NULL;
	BOOL result;
	DWORD i;

	hSCM = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ENUMERATE_SERVICE
	);

	if (hSCM == NULL) {
		printf("Eroare la OpenSCManager. Cod eroare: %lu\n", GetLastError());
		return 1;
	}

	result = EnumServicesStatusEx(
		hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		NULL,
		0,
		&bytesNeeded,
		&servicesCount,
		&resumeHandle,
		NULL
	);

	if (GetLastError() != ERROR_MORE_DATA) {
		printf("Eroare la prima apelare EnumServicesStatusEx. Cod eroare: %lu\n", GetLastError());
		CloseServiceHandle(hSCM);
		return 1;
	}

	bufferSize = bytesNeeded;
	lpServices = (LPENUM_SERVICE_STATUS_PROCESS)malloc(bufferSize);

	if (lpServices == NULL) {
		printf("Eroare la alocarea memoriei\n");
		CloseServiceHandle(hSCM);
		return 1;
	}

	resumeHandle = 0;

	result = EnumServicesStatusEx(
		hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		(LPBYTE)lpServices,
		bufferSize,
		&bytesNeeded,
		&servicesCount,
		&resumeHandle,
		NULL
	);

	if (!result) {
		printf("Eroare la a doua apelare EnumServicesStatusEx. Cod eroare: %lu\n", GetLastError());
		free(lpServices);
		CloseServiceHandle(hSCM);
		return 1;
	}

	printf("Serviciile care ruleaza in acest moment sunt:\n\n");

	for (i = 0; i < servicesCount; i++) {
		if (lpServices[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING) {
			wprintf(L"Nume serviciu: %ls\n", lpServices[i].lpServiceName);
			wprintf(L"Nume afisat: %ls\n", lpServices[i].lpDisplayName);
			printf("PID : %lu\n", lpServices[i].ServiceStatusProcess.dwProcessId);
			printf("\n");
		}
	}

	free(lpServices);
	CloseServiceHandle(hSCM);

	return 0;
}