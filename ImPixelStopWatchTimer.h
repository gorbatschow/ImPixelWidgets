#pragma once
#include <algorithm>
#include <chrono>

enum class StopWatchType { Normal, Max };

template <StopWatchType timerType> class StopWatchTimer {
public:
  StopWatchTimer() {}

  inline void start() {
    _beginTime = std::chrono::high_resolution_clock::now();
  }

  inline void stop() {
    _endTime = std::chrono::high_resolution_clock::now();
    if constexpr (_timerType == StopWatchType::Normal) {
      _us = std::chrono::duration_cast<std::chrono::microseconds>(_endTime -
                                                                  _beginTime)
                .count();
    } else if constexpr (_timerType == StopWatchType::Max) {
      _us = std::max(_us, std::chrono::duration_cast<std::chrono::microseconds>(
                              _endTime - _beginTime)
                              .count());
    }
  }

  inline long microseconds() const { return _us; }

private:
  std::chrono::system_clock::time_point _beginTime{}, _endTime{};
  long _us{};
  static constexpr StopWatchType _timerType{timerType};
};
