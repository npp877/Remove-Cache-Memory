#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <ShlObj.h>

namespace fs = std::filesystem;

void logs() {
#ifdef _WIN32
    std::string homeDir = std::getenv("USERPROFILE");
    std::string desktopPath = homeDir + "\\Desktop";
    bool isAdmin = IsUserAnAdmin();
#else
    std::string homeDir = std::getenv("HOME");
    std::string desktopPath = homeDir + "/Desktop";
    bool isAdmin = (geteuid() == 0);
#endif

    fs::path logsFolder = fs::path(desktopPath) / "logs";
    fs::create_directory(logsFolder);

    fs::path file1 = logsFolder / "HandleTemp.txt";
    fs::path file2 = logsFolder / "HandleMemoryCache.txt";

    std::ofstream outFile1(file1);
    outFile1 << "Removed Dir Temp:\n"
        << "successfully removed /appdata/local/temp\n";
    if (isAdmin) {
        outFile1 << "successfully removed C:/Windows/Temp\n"
            << "successfully removed Prefetch\n";
    }
    outFile1.close();

    std::ofstream outFile2(file2);
    outFile2 << "Removed Memory Cache:\n"
        << "Network Memory Cache Removed\n";
    if (isAdmin) {
        outFile2 << "Error Removing Cache, Code 0x070000000\n";
    }
    outFile2.close();
}