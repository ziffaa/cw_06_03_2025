#include "Header.h"

DWORD WINAPI ReadFromFiles(LPVOID lp);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
    HANDLE hThread = CreateThread(NULL, 0, ReadFromFiles, 0, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
}

DWORD WINAPI ReadFromFiles(LPVOID lp)
{
    MessageBox(0, TEXT("ReadFromFiles"), TEXT("ReadFromFiles"), MB_OK);
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));
    DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);

    std::ofstream result("result.txt");
    if (!result) {
        ReleaseMutex(hMutex);
        return 1;
    }

    if (dwAnswer == WAIT_OBJECT_0)
    {
        for (int i = 0; i < 3; i++)
        {
            char fname[10];
            sprintf_s(fname, "%d.txt", i);
            std::ifstream in(fname);

            if (in) {
                std::string line;
                while (std::getline(in, line)) {
                    result << line << "\n";
                }
                in.close();
            }
        }

        result.close();
        ReleaseMutex(hMutex);
    }
    return 0;
}
