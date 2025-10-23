#pragma once
#include <string>
#include <regex>
#include <iostream>

bool isValidPlatform(const std::string& platform);
bool isValidURL(const std::string& url);
void command_handler(const std::string& website_url, const std::string& platform);
