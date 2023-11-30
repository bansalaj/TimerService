#include "Timer.h"



/**
 * Constructor
*/
Timer::Timer(std::function<void()> callback, unsigned long long time_ms,
                bool periodic)
    :callback(std::move(callback)), time_ms(time_ms), periodic(periodic) {
        calculateNextExecutionTime();
}


/**
 * Move constructor
*/
Timer::Timer(Timer&& other) noexcept
    : callback(std::move(other.callback)),
      time_ms(other.time_ms),
      periodic(other.periodic),
      nextExecutionTime(other.nextExecutionTime) {

}


/**
 * Move assignment operator
*/
Timer&
Timer::operator=(Timer&& other) noexcept {
    if (this != &other) {
        callback = std::move(other.callback);
        time_ms = other.time_ms;
        periodic = other.periodic;
        nextExecutionTime = other.nextExecutionTime;
    }

    return *this;
}


/**
 * isPeriodic
 *  returns True if timer object is periodic
 *  false if it is one-shot
*/
bool
Timer::isPeriodic() const {
    return periodic;
}


/**
 * reschedule
 *  reschedule the time for periodic timer
 * 
*/
void
Timer::reschedule() {
    if(periodic) {
        calculateNextExecutionTime();
    }
}


/**
 * getNextExecutionTime
 *  returns the time when next execution will happen
*/
std::chrono::steady_clock::time_point
Timer::getNextExecutionTime() const {
    return nextExecutionTime;
}


/**
 * executeCallBack
*/
void
Timer::executeCallback() const{
    if (callback) {
        callback();
    }
}


/**
 * calculateNextExecutionTime
*/
void
Timer::calculateNextExecutionTime() {
    nextExecutionTime = std::chrono::steady_clock::now() +
        std::chrono::milliseconds(time_ms);
}
