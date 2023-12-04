#include "Timer.h"
#include "TimerManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

std::string getCurrentTime() {
    // Get the current time as time_point
    auto now = std::chrono::system_clock::now();
    time_t timeNow = std::chrono::system_clock::to_time_t(now);

    // convert to tm struct
#ifdef WIN32
    tm localTime;
    localtime_s(&localTime, &timeNow);
#else
    tm localTime;
    localtime_r(&timeNow, &localTime);
#endif

    // Format time as HH:MM:SS
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%H:%M:%S");
    return timeStream.str();

}

void printPeriodicMessage() {
    std::cout << getCurrentTime() << " <=====Periodic Callback Executed=====>" << std::endl;
}

int main() {
    TimerManager timerManager;

    // Add a Periodic timer
    timerManager.addTimer(printPeriodicMessage, 3000, true); // Every 3 seconds

    timerManager.addTimer([](){
        std::cout << getCurrentTime() << " <====2nd Periodic callback======>" << std::endl;
    }, 4000, true);

    timerManager.addTimer([](){
        std::cout << getCurrentTime() << " <======One Shot Message callback Executed=======>" << std::endl;
    }, 5000, false); // After 5 seconds

    timerManager.addTimer([](){
        std::cout << getCurrentTime() << " <======One Shot Message callback Executed=======>" << std::endl;
    }, 10000, false); // After 5 seconds

    timerManager.addTimer([](){
        std::cout << getCurrentTime() << " <======One Shot Message callback Executed=======>" << std::endl;
    }, 15000, false); // After 5 seconds

    timerManager.addTimer([](){
        std::cout << getCurrentTime() << " <======One Shot Message callback Executed=======>" << std::endl;
    }, 20000, false); // After 5 seconds


    // Keep the main thread alive for a while to observe the timers
    std::this_thread::sleep_for(std::chrono::seconds(30));

    // The TimerManager's destructor will clean up the timers
    return 0;
}