#define OEMRESOURCE

#include <vector>
#include <thread>
#include <windows.h>
#include <iostream>

#define MIN_ALL        419
#define MIN_ALL_UNDO   416
#pragma comment(lib, "winmm.lib")

using namespace std;

HWND lHwnd = FindWindow(L"Shell_TrayWnd", NULL);
HWND hDesktopWnd = FindWindow(L"Progman", NULL);
std::wstring exeFolder;
wchar_t exePath[MAX_PATH];

void fondoPred() {
	const wchar_t* path = L"C:\\Windows\\Web\\Wallpaper\\Windows\\img0.jpg";
	int result;
	result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE);
	cout << result;
}

void showWindows() {

	SendMessage(lHwnd, WM_COMMAND, MIN_ALL_UNDO, 0);
}

void mouseSwapPred() {
	SwapMouseButton(FALSE);
}

void cursorPred()
{
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
}

void showTaskBarPred() {

	ShowWindow(lHwnd, SW_SHOW);
}

void showIconsPred() {

	// Mostrar iconos escritorio.
	ShowWindow(hDesktopWnd, SW_SHOW);
}

void antidoto() {
	MessageBoxA(NULL, "Espero que te vayas concienciado, soy un hacker white hat y te dejo el PC como estaba. Podria haber sido peor... ;)", "Info", MB_ICONINFORMATION | MB_OK);
	cursorPred();
	fondoPred();
	mouseSwapPred();
	showTaskBarPred();
	showWindows();
	showIconsPred();
	exit(0);

}

void playAlarm() {

	std::wstring soundFile = exeFolder + L"\\Content\\alarma.wav";
	PlaySound(soundFile.c_str(), NULL, SND_ASYNC | SND_FILENAME);

}

void hideWindows() {

	//Minimiza las ventanas que estén abiertas

	SendMessage(lHwnd, WM_COMMAND, MIN_ALL, 0);
}

void hideIcons() {

	// Oculta iconos escritorio
	ShowWindow(hDesktopWnd, SW_HIDE);

}

void showMessageBox() {

	MessageBox(NULL, L"HACKED! Te dejaste el PC abierto te fuiste y... PWNED!", L"ERROR", MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);
	antidoto();

}

// Método de la API de Windows que detecta cuando la ventana del programa se cierra.
BOOL WINAPI ConsoleHandler(DWORD signal) {
	if (signal == CTRL_CLOSE_EVENT)
	{
		// Si el usuario cierra la aplicación su escritorio vuelve a la normalidad.
		antidoto();
	}
	return TRUE;
}

void hideTaskBar()
{

	ShowWindow(lHwnd, SW_HIDE);
}

void changeCursor()
{

	wstring cursorFile = exeFolder + L"\\Content\\cursor.cur";

	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");

	string(buffer).substr(0, pos);

	HICON I = (HICON)LoadImage(0, cursorFile.c_str(), IMAGE_ICON, 80, 80, LR_LOADFROMFILE);

	ICONINFO Ico;
	GetIconInfo(I, &Ico);
	Ico.xHotspot = 0;
	Ico.yHotspot = 0;

	HCURSOR c = CreateIconIndirect(&Ico);

	SetSystemCursor(c, OCR_NORMAL);
}

void swapCursor()
{
	BOOL swapButtons = TRUE;
	SwapMouseButton(swapButtons);

	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

int main()
{

	GetModuleFileName(NULL, exePath, MAX_PATH);
	exeFolder = exePath;
	exeFolder = exeFolder.substr(0, exeFolder.find_last_of(L"\\/"));

	// Play Alarm
	playAlarm();

	// Hide Desktop
	hideWindows();

	// Hide Task Bar

	hideTaskBar();

	// Cursor Payload

	changeCursor();

	// Swap mouse buttons

	swapCursor();

	// Wallpaper payload

	//You can add as many as you want or make a .*
	vector<wstring> wallpapers = { exeFolder + L"\\Content\\wallpaper.jpg", exeFolder + L"\\Content\\hacked.jpg", exeFolder + L"\\Content\\hacked2.jpg", exeFolder + L"\\Content\\hacked3.jpg" };
	int currentWallpaper = 0;

	std::thread messageThread(showMessageBox);
	messageThread.detach();


	while (true)
	{
		hideIcons();
		ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)wallpapers[currentWallpaper].c_str(), SPIF_UPDATEINIFILE);
		currentWallpaper = (static_cast<unsigned long long>(currentWallpaper) + 1) % wallpapers.size();
		Sleep(2000);
		showIconsPred();
		Sleep(2000);
		hideWindows();

		if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
			std::cout << L"Error setting console event handler" << std::endl;
			return 1;
		}
		//getchar();
	}

	return 0;

}