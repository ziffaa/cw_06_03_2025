#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <fstream>
#include <string>

CRITICAL_SECTION cs;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        CreateMutex(0, FALSE, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1)
        {
            CreateMutex(0, FALSE, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));
            STARTUPINFO st = { sizeof(st) };
            PROCESS_INFORMATION pr;
            TCHAR filename[20];
            wsprintf(filename, TEXT("%s"), TEXT("Read.exe"));
            if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
            {
                MessageBox(0, TEXT("ERROR_READ"), TEXT("ERROR_READ"), MB_OK | MB_ICONSTOP);
                return 0;
            }
            CloseHandle(pr.hThread);
            CloseHandle(pr.hProcess);
            ZeroMemory(&st, sizeof(st));
            st.cb = sizeof(st);
            wsprintf(filename, TEXT("%s"), TEXT("Write.exe"));
            if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
            {
                MessageBox(0, TEXT("ERROR_WRITE"), TEXT("ERROR_WRITE"), MB_OK | MB_ICONSTOP);
                return 0;
            }
            CloseHandle(pr.hThread);
            CloseHandle(pr.hProcess);
        }
    }
    return FALSE;
}
