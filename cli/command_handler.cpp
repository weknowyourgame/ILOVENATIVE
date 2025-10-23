#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

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

void command_handler(const std::string& website_url, const std::string& platform) {
  std::cout << "Processing conversion for: " << website_url << " on " << platform << std::endl;
}