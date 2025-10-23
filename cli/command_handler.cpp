#include <iostream>
#include <string>
#include <regex>

bool isValidPlatform(std::string platform) {
  return platform == "Win" || platform == "Mac" || platform == "Linux";
}

bool isValidURL(const std::string& url) {
  const std::regex url_pattern(
      R"(^(https?:\/\/)?([\w\-]+\.)+[\w\-]+(\/[\w\-._~:/?#[\]@!$&'()*+,;=]*)?$)",
      std::regex::icase
  );
  return std::regex_match(url, url_pattern);
}

// void command_handler(std::string website_url, std::string platform){ }