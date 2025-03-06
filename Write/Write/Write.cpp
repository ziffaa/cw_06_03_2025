#include "Header.h"

DWORD WINAPI WriteToFiles(LPVOID lp);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
    HANDLE hThread = CreateThread(NULL, 0, WriteToFiles, 0, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
}

DWORD WINAPI WriteToFiles(LPVOID lp)
{
    MessageBox(0, TEXT("WriteToFiles"), TEXT("WriteToFiles"), MB_OK);
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));
    DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
    if (dwAnswer == WAIT_OBJECT_0)
    {

        std::ifstream in("source.txt");
        if (!in) {
            return 1;
        }

        std::string line;
        std::string content;

        while (std::getline(in, line)) {
            content += line + "\n";
        }
        in.close();

        for (int i = 0; i < 3; i++)
        {
            char fname[10];
            sprintf_s(fname, "%d.txt", i);
            std::ofstream out(fname);
            if (out) {
                out << content;
                out.close();
            }
        }

        ReleaseMutex(hMutex);
    }
    return 0;
}