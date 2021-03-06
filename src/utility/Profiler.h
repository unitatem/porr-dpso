#ifndef PORR_DPSO_PROFILER_H
#define PORR_DPSO_PROFILER_H

#include <vector>
#include <chrono>
#include <string>
#include <mutex>

using TimeContainer = std::vector<std::chrono::system_clock::time_point>;
using TimePoint = std::chrono::system_clock::time_point;

class Profiler {
public:
    static Profiler &getInstance();

    Profiler(const Profiler &) = delete;

    Profiler(Profiler &&) = delete;

    Profiler operator=(const Profiler &) = delete;

    Profiler operator=(Profiler &&) = delete;

    void registerStartPoint();

    void registerParallelisationStartPoint();

    void registerParallelisationStopPoint();

    void registerStopPoint();

    void setThreadNumber(uint8_t number);

    void setMode(const std::string &mode);

    uint8_t getThreadNumber() const;

    double getLastTotalDuration() const;

    double getLastCriticalLoopDuration() const;

    double getAvgTotalDuration() const;

    double getAvgCriticalLoopDuration() const;

    double getSynchronizationPartRatio() const;

    double getSpeedUpCoefficientEstimation() const;

    void saveToFile();

private:
    explicit Profiler();

    static Profiler *instance_;
    static std::mutex mutex_;

    uint8_t threadNumber_;
    std::string mode_;

    TimeContainer startTimePoint_;
    TimeContainer stopTimePoint_;
    TimeContainer startParallelisationTimePoint_;
    TimeContainer stopParallelisationTimePoint_;
};


#endif
