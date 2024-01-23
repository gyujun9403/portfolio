#pragma once

#include <array>
#include <arpa/inet.h>
#include <map>
#include <errno.h>
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <vector>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <queue>
#include <thread>
#include <mutex>
#include <utility>
#include <atomic>
#include <optional>
#include <thread>
#include <cerrno>
#include <functional>

#define MAX_BUF_SIZE 512
using BuffVec = std::array<char, MAX_BUF_SIZE>;
#define MAX_DELAY_MSEC 3000