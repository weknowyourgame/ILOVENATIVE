#pragma once
#include <string>
#include <regex>
#include <iostream>

bool isValidPlatform(const std::string& platform);
bool isValidURL(const std::string& url);
std::string generateAppName(const std::string& url);
bool createAppDirectory(const std::string& app_name);
bool copyCEFExecutable(const std::string& app_name, const std::string& cef_executable);
bool createPlatformLauncher(const std::string& app_name, const std::string& website_url, const std::string& platform);
bool createLinuxDesktopFile(const std::string& app_name, const std::string& website_url);
bool createWindowsShortcut(const std::string& app_name, const std::string& website_url);
bool createMacAppBundle(const std::string& app_name, const std::string& website_url);
bool packageApp(const std::string& app_name, const std::string& platform);
bool createLinuxPackage(const std::string& app_name);
bool createWindowsPackage(const std::string& app_name);
bool createMacPackage(const std::string& app_name);
void provideInstallInstructions(const std::string& app_name, const std::string& platform, bool packaged);
void command_handler(const std::string& website_url, const std::string& platform);
