#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> GetLargeFiles(const std::string& directoryPath, ULONGLONG minSize)
{
    std::vector<std::string> largeFiles;

    WIN32_FIND_DATAA fileInfo;
    HANDLE hFind = FindFirstFileA((directoryPath + "\\*").c_str(), &fileInfo);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                ULARGE_INTEGER fileSize;
                fileSize.LowPart = fileInfo.nFileSizeLow;
                fileSize.HighPart = fileInfo.nFileSizeHigh;

                if (fileSize.QuadPart >= minSize)
                {
                    largeFiles.push_back(directoryPath + "\\" + fileInfo.cFileName);
                }
            }
        } while (FindNextFileA(hFind, &fileInfo));

        FindClose(hFind);
    }

    return largeFiles;
}

int main()
{
    ULONGLONG minSize = 1024ull * 1024ull * 1024ull; // Minimum file size of 1 gigabyte

    std::vector<std::string> largeFiles = GetLargeFiles("C:\\", minSize);

    for (const auto& filePath : largeFiles)
    {
        std::cout << filePath << std::endl;
    }

    return 0;
}
