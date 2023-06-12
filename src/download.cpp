#include "download.h"

bool download(const std::string url, const std::string outputFilePath) {
  const std::string cmd =
      "curl -# -o " + outputFilePath +
      " -w \"%{time_total};%{speed_download};%{http_code}\" " + url;
  const std::regex re("\\s+(\\d+)%.*");  // 匹配下载进度的正则表达式

  // 执行 curl 命令，并将输出重定向到文件流中
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                &pclose);
  if (!pipe) {
    fmt::print(stderr, "Error: failed to execute command {}\n", cmd);
    return 1;
  }

  // 将输出流设置为非缓冲流
  if (setvbuf(pipe.get(), nullptr, _IONBF, 0) != 0) {
    fmt::print(stderr,
               "Error: failed to set output stream to non-buffered mode\n");
    return 1;
  }

  // 获取文件大小
  std::ifstream outputFile(outputFilePath, std::ios::binary | std::ios::ate);
  if (!outputFile) {
    fmt::print(stderr, "Error: failed to open file {}\n", outputFilePath);
    return 1;
  }
  const std::int64_t fileSize = outputFile.tellg();
  outputFile.close();

  // 输出下载信息
  fmt::print("Downloading {}\n", url);
  const auto startTime = std::chrono::steady_clock::now();
  auto lastTime = startTime;
  std::int64_t lastBytes = 0;

  // 定义一些变量用于存储 curl 的内部变量
  double timeTotal = -1.0;
  double speedDownload = -1.0;
  int httpCode = -1;

  // 定义一个标志用于判断是否已经读取了 curl 的内部变量
  bool readCurlVars = false;

  // 定义一个字符串用于存储 curl 的内部变量
  std::string curlVars;

  // 定义一个缓冲区用于存储文件流中的数据
  char buffer[128];

  // 循环读取文件流中的数据
  while (std::fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
    std::string line(buffer);

    // 如果没有读取过 curl 的内部变量，尝试从最后一行中读取
    if (!readCurlVars) {
      auto pos = line.find_last_of(';');
      if (pos != std::string::npos) {
        curlVars = line;
        line.erase(pos + 1);
        readCurlVars = true;
      }
    }

    // 匹配下载进度，并输出下载进度和下载速度
    std::smatch match;
    if (std::regex_search(line, match, re)) {
      const int progress = std::stoi(match[1]);
      const std::int64_t bytes = progress * fileSize / 100;
      const auto currentTime = std::chrono::steady_clock::now();
      const double elapsedSeconds =
          std::chrono::duration_cast<std::chrono::duration<double>>(
              currentTime - startTime)
              .count();
      const double speed = static_cast<double>(bytes - lastBytes) /
                           (currentTime - lastTime).count() / 1024 / 1024;
      fmt::print("\r{:>3}% [{:<50}] {:.2f} MB/s", progress,
                 std::string(progress * 0.5, '#'), speed);
      lastBytes = bytes;
      lastTime = currentTime;
    }
  }

  // 关闭文件流
  pipe.reset();

  // 如果读取到了 curl 的内部变量，尝试解析它们
  if (readCurlVars) {
    auto pos1 = curlVars.find(';');
    auto pos2 = curlVars.find(';', pos1 + 1);
    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      timeTotal = std::stod(curlVars.substr(0, pos1));
      speedDownload = std::stod(curlVars.substr(pos1 + 1, pos2 - pos1 - 1));
      httpCode = std::stoi(curlVars.substr(pos2 + 1));
    }
  }

  // 输出文件保存的路径
  fmt::print("\nDownload completed! Saved as {}\n", outputFilePath);

  // 输出 curl 的内部变量
  fmt::print(fg(fmt::color::red),"Total time: {:.3f} seconds\n", timeTotal);
  fmt::print(fg(fmt::color::red),"Download speed: {:.2f} bytes/second\n", speedDownload);
  fmt::print(fg(fmt::color::red),"HTTP status code: {}\n", httpCode);

  return true;
}