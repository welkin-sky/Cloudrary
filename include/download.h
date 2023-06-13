#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#define FMT_HEADER_ONLY

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

void download(const std::string url, const std::string outputFilePath);

#endif