#pragma once
#ifndef HANDLETEMP_H
#define HANDLETEMP_H

#include <filesystem>

void HandleTemp();
bool IsRunningAsAdmin();
void cleanDirectory(const std::filesystem::path& directory);

#endif // HANDLETEMP_H
