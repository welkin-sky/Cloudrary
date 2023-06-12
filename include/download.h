#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

bool download(const std::string url, const std::string outputFilePath);

#endif