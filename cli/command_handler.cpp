#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <cctype>
#include "command_handler.h"

bool isValidPlatform(const std::string& platform) {
  std::string platform_ = platform;
  std::transform(platform_.begin(), platform_.end(), platform_.begin(), ::tolower);

  return platform_ == "win" || platform_ == "mac" || platform_ == "linux" || platform_ == "windows" || platform_ == "macos" || platform_ == "osx";
}

bool isValidURL(const std::string& url) {
  const std::regex url_pattern(
      R"(^(https?:\/\/)?([\w\-]+\.)+[\w\-]+(\/[\w\-._~:/?#[\]@!$&'()*+,;=]*)?$)",
      std::regex::icase
  );
  return std::regex_match(url, url_pattern);
}

std::string generateAppName(const std::string& url) {
  std::string domain = url.substr(url.find("://") + (url.find("://") != std::string::npos ? 3 : 0));
  domain = domain.substr(0, domain.find('.'));
  return domain.empty() ? "WebApp" : std::string(1, std::toupper(domain[0])) + domain.substr(1);
}

std::string findCEFExecutable() {
  const char* home_dir = std::getenv("HOME");
  std::string home_path = home_dir ? home_dir : "";
  
  std::vector<std::string> possible_paths = {
    // relative to current directory
    "./cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    "../cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    "../../cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    
    home_path + "/cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    
    // Common build locations
    "./build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    "../build/ILOVENATIVE/cef/Release/ILOVENATIVE",
    
    // Environment variable override
    std::getenv("ILOVENATIVE_CEF_PATH") ? std::getenv("ILOVENATIVE_CEF_PATH") : ""
  };
  
  // Check each path
  for (const auto& path : possible_paths) {
    if (!path.empty() && std::filesystem::exists(path)) {
      return path;
    }
  }
  
  return "";
}

bool createAppDirectory(const std::string& app_name) {
  try {
    if (std::filesystem::exists(app_name)) {
      return true;
    }

    std::filesystem::create_directory(app_name);
    return true;
  } catch (const std::exception& e) {
    std::cout << "Error creating app directory: " << e.what() << std::endl;
    return false;
  }
}

bool copyCEFExecutable(const std::string& app_name, const std::string& cef_executable) {
  try {
    std::string source = cef_executable;
    std::string destination = app_name + "/" + app_name;

    if (!std::filesystem::exists(source)) {
      std::cout << "CEF executable not found: " << source << std::endl;
      return false;
    }

    // copy the executable
    std::filesystem::copy_file(source, destination);

    // Make it executable
    std::string chmod_cmd = "chmod +x " + destination;
    system(chmod_cmd.c_str());

    return true;
  } catch (const std::exception& e) {
    std::cout << "Error copying CEF executable: " << e.what() << std::endl;
    return false;
  }
}

bool copyCEFRuntime(const std::string& app_name, const std::string& cef_executable) {
  try {
    // get the directory containing the CEF executable
    std::filesystem::path cef_path(cef_executable);
    std::string cef_dir = cef_path.parent_path().string();
    
    std::cout << "Copying CEF runtime from: " << cef_dir << std::endl;
    
    for (const auto& entry : std::filesystem::directory_iterator(cef_dir)) {
      std::string source_file = entry.path().string();
      std::string filename = entry.path().filename().string();
      std::string destination_file = app_name + "/" + filename;
      
      try {
        if (std::filesystem::is_regular_file(entry)) {
          std::filesystem::copy_file(source_file, destination_file);
          std::cout << "Copied: " << filename << std::endl;
        } else if (std::filesystem::is_directory(entry)) {
          std::filesystem::copy(source_file, destination_file, std::filesystem::copy_options::recursive);
          std::cout << "Copied directory: " << filename << std::endl;
        }
      } catch (const std::exception& e) {
        std::cout << "Warning: Could not copy " << filename << ": " << e.what() << std::endl;
      }
    }
    
    return true;
  } catch (const std::exception& e) {
    std::cout << "Error copying CEF runtime: " << e.what() << std::endl;
    return false;
  }
}

bool createPlatformLauncher(const std::string& app_name, const std::string& website_url, const std::string& platform) {
  std::string platform_lower = platform;
  std::transform(platform_lower.begin(), platform_lower.end(), platform_lower.begin(), ::tolower);

  try {
    if (platform_lower == "linux") {
      return createLinuxDesktopFile(app_name, website_url);
    } else if (platform_lower == "windows" || platform_lower == "win") {
      return createWindowsShortcut(app_name, website_url);
    } else if (platform_lower == "mac" || platform_lower == "macos" || platform_lower == "osx") {
      return createMacAppBundle(app_name, website_url);
    } else {
      std::cout << "Unsupported platform: " << platform << std::endl;
      return false;
    }
  } catch (const std::exception& e) {
    std::cout << "Error creating platform launcher: " << e.what() << std::endl;
    return false;
  }
}

// .desktop file for Linux
bool createLinuxDesktopFile(const std::string& app_name, const std::string& website_url) {
  std::string desktop_path = app_name + "/" + app_name + ".desktop";

  std::ofstream desktop_file(desktop_path);
  if (!desktop_file.is_open()) {
    std::cout << "Error creating desktop file" << std::endl;
    return false;
  }

  desktop_file << "[Desktop Entry]\n";
  desktop_file << "Name=" << app_name << "\n";
  desktop_file << "Comment=Native app for " << website_url << "\n";
  desktop_file << "Exec=./" << app_name << " --url=" << website_url << " %U\n";
  desktop_file << "Icon=" << app_name << "\n";
  desktop_file << "Terminal=false\n";
  desktop_file << "Type=Application\n";
  desktop_file << "Categories=Network;WebBrowser;\n";

  desktop_file.close();
  return true;
}

// Create Windows batch file
bool createWindowsShortcut(const std::string& app_name, const std::string& website_url) {
  std::string batch_path = app_name + "/" + app_name + ".bat";

  std::ofstream batch_file(batch_path);
  if (!batch_file.is_open()) {
    std::cout << "Error creating Windows batch file" << std::endl;
    return false;
  }

  batch_file << "@echo off\n";
  batch_file << "REM Native app for " << website_url << "\n";
  batch_file << "start ILOVENATIVE.exe --url=" << website_url << " %*\n";

  batch_file.close();
  return true;
}

// Create macOS shell script
bool createMacAppBundle(const std::string& app_name, const std::string& website_url) {
  std::string script_path = app_name + "/" + app_name;

  std::ofstream script_file(script_path);
  if (!script_file.is_open()) {
    std::cout << "Error creating macOS script" << std::endl;
    return false;
  }

  script_file << "#!/bin/bash\n";
  script_file << "# Native app for " << website_url << "\n";
  script_file << "./ILOVENATIVE --url=\"" << website_url << "\" \"$@\"\n";
  script_file.close();

  std::string chmod_cmd = "chmod +x " + script_path;
  system(chmod_cmd.c_str());

  return true;
}

// Package the generated app
bool packageApp(const std::string& app_name, const std::string& platform) {
  std::string platform_lower = platform;
  std::transform(platform_lower.begin(), platform_lower.end(), platform_lower.begin(), ::tolower);

  try {
    if (platform_lower == "linux") {
      return createLinuxPackage(app_name);
    } else if (platform_lower == "windows" || platform_lower == "win") {
      return createWindowsPackage(app_name);
    } else if (platform_lower == "mac" || platform_lower == "macos" || platform_lower == "osx") {
      return createMacPackage(app_name);
    } else {
      std::cout << "Unsupported platform for packaging: " << platform << std::endl;
      return false;
    }
  } catch (const std::exception& e) {
    std::cout << "Error packaging app: " << e.what() << std::endl;
    return false;
  }
}

// Create Linux package (tar.gz)
bool createLinuxPackage(const std::string& app_name) {
  std::string package_name = app_name + "-linux.tar.gz";
  std::string tar_cmd = "tar -czf " + package_name + " " + app_name;

  int result = system(tar_cmd.c_str());
  if (result == 0) {
    std::cout << "Created package: " << package_name << std::endl;
    return true;
  } else {
    std::cout << "Failed to create package" << std::endl;
    return false;
  }
}

// Create Windows package (zip)
bool createWindowsPackage(const std::string& app_name) {
  std::string package_name = app_name + "-windows.zip";
  std::string zip_cmd = "zip -r " + package_name + " " + app_name;

  int result = system(zip_cmd.c_str());
  if (result == 0) {
    std::cout << "Created package: " << package_name << std::endl;
    return true;
  } else {
    std::cout << "Failed to create package" << std::endl;
    return false;
  }
}

// Create macOS package (tar.gz)
bool createMacPackage(const std::string& app_name) {
  std::string package_name = app_name + "-macos.tar.gz";
  std::string tar_cmd = "tar -czf " + package_name + " " + app_name;

  int result = system(tar_cmd.c_str());
  if (result == 0) {
    std::cout << "Created package: " << package_name << std::endl;
    return true;
  } else {
    std::cout << "Failed to create package" << std::endl;
    return false;
  }
}

// Provide installation instructions
void provideInstallInstructions(const std::string& app_name, const std::string& platform, bool packaged) {
  std::string platform_lower = platform;
  std::transform(platform_lower.begin(), platform_lower.end(), platform_lower.begin(), ::tolower);

  std::cout << "\nApp generated successfully!" << std::endl;
  std::cout << "Location: " << app_name << "/" << std::endl;

  if (packaged && platform_lower == "linux") {
    std::cout << "Package: " << app_name << "-linux.tar.gz" << std::endl;
  }

  std::cout << "\nFiles created:" << std::endl;
  std::cout << "   - " << app_name << " (executable)" << std::endl;
  if (platform_lower == "linux") {
    std::cout << "   - " << app_name << ".desktop (desktop entry)" << std::endl;
  } else if (platform_lower == "windows" || platform_lower == "win") {
    std::cout << "   - " << app_name << ".bat (batch file)" << std::endl;
  } else if (platform_lower == "mac" || platform_lower == "macos" || platform_lower == "osx") {
    std::cout << "   - " << app_name << " (shell script)" << std::endl;
  }

  std::cout << "\nInstallation:" << std::endl;
  if (platform_lower == "linux") {
    if (packaged) {
      std::cout << "   1. Extract: tar -xzf " << app_name << "-linux.tar.gz" << std::endl;
      std::cout << "   2. Copy folder to ~/.local/share/applications/" << std::endl;
      std::cout << "   3. Or run: desktop-file-install " << app_name << ".desktop" << std::endl;
    } else {
      std::cout << "   1. Copy folder to ~/.local/share/applications/" << std::endl;
      std::cout << "   2. Or run: desktop-file-install " << app_name << ".desktop" << std::endl;
    }
    std::cout << "   3. Find in applications menu" << std::endl;
  } else if (platform_lower == "windows" || platform_lower == "win") {
    std::cout << "   1. Copy files to desired location" << std::endl;
    std::cout << "   2. Create Start Menu shortcut to " << app_name << ".bat" << std::endl;
  } else if (platform_lower == "mac" || platform_lower == "macos" || platform_lower == "osx") {
    std::cout << "   1. Copy script to Applications folder" << std::endl;
    std::cout << "   2. Make executable: chmod +x " << app_name << std::endl;
  }

  std::cout << "\nTest: cd " << app_name << " && ./" << app_name << std::endl;
}

void command_handler(const std::string& website_url, const std::string& platform) {
  
  std::cout << "Processing " << website_url << " for " << platform << std::endl;
  std::string app_name = generateAppName(website_url);
  std::cout << "App name: " << app_name << std::endl;

  // Create app directory
  if (!createAppDirectory(app_name)) {
    std::cout << "Failed to create app directory" << std::endl;
    return;
  }

  // copy CEF runtime (executable + all libraries and resources)
  std::string cef_executable_path = findCEFExecutable();
  if (cef_executable_path.empty()) {
    std::cout << "CEF executable not found. Please ensure the CEF project is built." << std::endl;
    std::cout << "Expected locations:" << std::endl;
    std::cout << "  - ~/cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE" << std::endl;
    std::cout << "  - ../cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE" << std::endl;
    std::cout << "  - ./cef-project/build/ILOVENATIVE/cef/Release/ILOVENATIVE" << std::endl;
    return;
  }
  
  std::cout << "Copying complete CEF runtime..." << std::endl;
  if (!copyCEFRuntime(app_name, cef_executable_path)) {
    std::cout << "Failed to copy CEF runtime from: " << cef_executable_path << std::endl;
    return;
  }

  // Create platform launcher
  if (!createPlatformLauncher(app_name, website_url, platform)) {
    std::cout << "Failed to create platform launcher" << std::endl;
    return;
  }

  // Package the app
  std::string platform_lower = platform;
  std::transform(platform_lower.begin(), platform_lower.end(), platform_lower.begin(), ::tolower);

  bool packaged = false;
  if (platform_lower == "linux") {
    if (packageApp(app_name, platform)) {
      packaged = true;
    }
  }

  // Provide instructions
  provideInstallInstructions(app_name, platform, packaged);

  std::cout << "\nApp generation completed" << std::endl;
}