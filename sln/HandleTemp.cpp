#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

bool IsRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&NtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &adminGroup))
    {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin == TRUE;
}

void cleanDirectory(const fs::path& directory) {

    if (!fs::exists(directory)) {
        return;
    }

    std::error_code ec;
    std::vector<fs::path> entries;
    for (auto it = fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied, ec);
        it != fs::recursive_directory_iterator(); it.increment(ec))
    {
        if (ec) {
            ec.clear();
            continue;
        }
        entries.push_back(it->path());
    }

    std::sort(entries.begin(), entries.end(), [](const fs::path& a, const fs::path& b) {
        return a.string().size() > b.string().size();
        });

    for (const auto& path : entries) {
        std::error_code remove_ec;
        fs::remove(path, remove_ec);
    }
}

void HandleTemp() {
    bool isAdmin = IsRunningAsAdmin();

    char* localAppData = std::getenv("LOCALAPPDATA");
    if (localAppData) {
        fs::path appDataTemp = fs::path(localAppData) / "Temp";
        cleanDirectory(appDataTemp);
    }

    if (isAdmin) {
        fs::path windowsTemp = "C:\\Windows\\Temp";
        cleanDirectory(windowsTemp);

        fs::path windowsPrefetch = "C:\\Windows\\Prefetch";
        cleanDirectory(windowsPrefetch);
    }
}