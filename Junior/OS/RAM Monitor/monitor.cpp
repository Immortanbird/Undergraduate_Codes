#include <iostream>
#include <iomanip>
#include <vector>
#include <shlwapi.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using namespace std;

const string CMD_Config = "config";
const string CMD_Memory = "memory";
const string CMD_Process = "process";
const string CMD_Pid = "PID";
const string CMD_Help = "help";
const string CMD_Exit = "exit";

void drawLine(vector<int> max, int col) {
	for (int i=0; i < col; i++) {
		cout << "+";
		for (int j=0; j < max[i]; j++) 
			cout << "-";
	}

	cout << "+" << endl;

	return;
}

void printHeader() {
	vector<int> width = {31, 12, 14, 25, 25, 10};
	vector<string> header = {"Page Address", "Region Size", "Type", "Allocation Protect", "Protect", "State"};

	drawLine(width, 6);

	for (int i=0; i < 6; i++) 
		cout << "|" << left << setw(width[i]) << header[i];

	cout << "|" << endl;
	drawLine(width, 6);

	return;
}

void showHelpMenu() {
	cout << "------------------Commandline Menu-----------------" << endl;
	cout << "'config'    Show system information." << endl;
	cout << "'memory'    Show memory situation." << endl;
	cout << "'process'   Show all process id." << endl;
	cout << "'PID id'    Show information of the process with the specific process ID 'id'." << endl;
	cout << "'exit'      Exit program." << endl;
	cout << "-------------------------End-----------------------" << endl;
	
	return;
}

void showSystemInfo() {
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);

	cout << "--------------------System Info--------------------" << endl;
   	cout << "OEM ID:                        " << si.dwOemId << endl;
   	cout << "Number of processors:          " << si.dwNumberOfProcessors << endl;
   	cout << "Processor type:                " << si.dwProcessorType << endl;
   	cout << "Virtual memory page size:      " << si.dwPageSize << endl;
   	printf( "Minimum application address:   0x%08lx\n", si.lpMinimumApplicationAddress);
   	printf( "Maximum application address:   0x%08lx\n", si.lpMaximumApplicationAddress);
  	cout << "Active processor mask:         " << si.dwActiveProcessorMask << endl;
	cout << "-------------------------End-----------------------" << endl;

	return;
}

void showMemoryStatus() {
	MEMORYSTATUSEX stat;
	stat.dwLength = sizeof(stat);

	GlobalMemoryStatusEx(&stat);

	cout << "---------------Memory Status---------------" << endl;
	printf("Memory in use:           %lu%\n", stat.dwMemoryLoad);
	printf("Physical memory(total):  %llu KB\n", stat.ullTotalPhys/1024);
	printf("Physical memory(free):   %llu KB\n", stat.ullAvailPhys/1024);
	printf("Virtual memory(total):   %llu KB\n", stat.ullTotalVirtual/1024);
	printf("Virtual memory(free):    %llu KB\n", stat.ullAvailVirtual/1024);
	printf("Extended memory(free):   %llu KB\n", stat.ullAvailExtendedVirtual/1024);
	printf("Paging file(total):      %llu KB\n", stat.ullTotalPageFile/1024);
	printf("Paging file(free):       %llu KB\n", stat.ullAvailPageFile/1024);
	cout << "--------------------End--------------------" << endl;

	return;
}

void showRunningProcess() {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		printf("WARNING: Create snapshot failed with error %lu.\n", GetLastError());
		return;
	}

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	if (!Process32First(snapshot, &entry)) {
		printf("WARNING: Get first process failed with error %lu.\n", GetLastError());
		CloseHandle(snapshot);
		return;
	}
	cout << GetCurrentProcessId() << endl;
	cout << "-----------------Processes-----------------" << endl;
	cout << "	PROCESS NAME		PROCESS ID" << endl;

	do {
		printf("%-30s		%ld\n", entry.szExeFile, entry.th32ProcessID);
	} while (Process32Next(snapshot, &entry));

	cout << "--------------------End--------------------" << endl;

	return;
}

void showProcessInfo (int pid) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL) {
		printf("WARNING: Open process failed with error %lu.\n", GetLastError());
		CloseHandle(hProcess);
		return;
	}
	
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);

	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));
	LPVOID pBlock = si.lpMinimumApplicationAddress;

	printHeader();
	while (pBlock < si.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(hProcess, pBlock, &mbi, sizeof(mbi)) == 0) {
			printf("WARNING: Virtual query failed with error %lu.\n", GetLastError());
			return;
		}

		/* Print address */
		LPVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;
		printf("| 0x%012lx-0x%012lx", pBlock, pEnd);

		TCHAR buffer[100];
		StrFormatByteSize(mbi.RegionSize, buffer, 100);
		cout << " | " << right << setw(10) << buffer;
		
		switch (mbi.Type) {
			case MEM_IMAGE:
				cout << " | MEM_IMAGE   ";
				break;
			case MEM_MAPPED:
				cout << " | MEM_MAPPED  ";
				break;
			case MEM_PRIVATE:
				cout << " | MEM_PRIVATE ";
				break;
			default:
				cout << " |             ";
		}

		switch (mbi.AllocationProtect) {
			case PAGE_EXECUTE:
				cout << " | PAGE_EXECUTE           ";
				break;
			case PAGE_EXECUTE_READ:
				cout << " | PAGE_EXECUTE_READ      ";
				break;
			case PAGE_EXECUTE_READWRITE:
				cout << " | PAGE_EXECUTE_READWRITE ";
				break;
			case PAGE_EXECUTE_WRITECOPY:
				cout << " | PAGE_EXECUTE_WRITECOPY ";
				break;
			case PAGE_NOACCESS:
				cout << " | PAGE_NOACCESS          ";
				break;
			case PAGE_READONLY:
				cout << " | PAGE_READONLY          ";
				break;
			case PAGE_READWRITE:
				cout << " | PAGE_READWRITE         ";
				break;
			case PAGE_WRITECOPY:
				cout << " | PAGE_WRITECOPY         ";
				break;
			case PAGE_GUARD:
				cout << " | PAGE_GUARD             ";
				break;
			case PAGE_NOCACHE:
				cout << " | PAGE_NOCACHE           ";
				break;
			case PAGE_WRITECOMBINE:
				cout << " | PAGE_WRITECOMBINE      ";
				break;
			default:
				cout << " |                        ";
		}

		switch (mbi.Protect) {
			case PAGE_EXECUTE:
				cout << " | PAGE_EXECUTE           ";
				break;
			case PAGE_EXECUTE_READ:
				cout << " | PAGE_EXECUTE_READ      ";
				break;
			case PAGE_EXECUTE_READWRITE:
				cout << " | PAGE_EXECUTE_READWRITE ";
				break;
			case PAGE_EXECUTE_WRITECOPY:
				cout << " | PAGE_EXECUTE_WRITECOPY ";
				break;
			case PAGE_NOACCESS:
				cout << " | PAGE_NOACCESS          ";
				break;
			case PAGE_READONLY:
				cout << " | PAGE_READONLY          ";
				break;
			case PAGE_READWRITE:
				cout << " | PAGE_READWRITE         ";
				break;
			case PAGE_WRITECOPY:
				cout << " | PAGE_WRITECOPY         ";
				break;
			case PAGE_GUARD:
				cout << " | PAGE_GUARD             ";
				break;
			case PAGE_NOCACHE:
				cout << " | PAGE_NOCACHE           ";
				break;
			case PAGE_WRITECOMBINE:
				cout << " | PAGE_WRITECOMBINE      ";
				break;
			default:
				cout << " |                        ";
		}
		
		switch (mbi.State) {
			case MEM_COMMIT:
				cout << " | Commited |" << endl;
				break;
			case MEM_FREE:
				cout << " | Free     |" << endl;
				break;
			case MEM_RESERVE:
				cout << " | Reserved |" << endl;
				break;
			default:
				cout << " |          |" << endl;
		}

		pBlock = pEnd;
	}

	return;
}

int main() {
	cout << "___________________Memory monitor___________________" << endl << endl;

	string input;

	while (true) {
		cout << "Monitor $ ";
		
		cin.sync();
		cin >> input;

		if (input == CMD_Config)
			showSystemInfo();
		else if (input == CMD_Memory)
			showMemoryStatus();
		else if (input == CMD_Process)
			showRunningProcess();
		else if (input == CMD_Pid) {
			int pid;
			scanf("%d", &pid);
			showProcessInfo(pid);
		}
		else if (input == CMD_Help)
			showHelpMenu();
		else if (input == CMD_Exit){
			cout << "Program exited." << endl;
			exit(0);
		}
		else
			cout << "Command not found, use 'help' for more information.\n";
	}

	return 0;
}