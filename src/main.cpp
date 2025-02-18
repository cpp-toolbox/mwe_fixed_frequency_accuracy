#include <iostream>
#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/periodic_signal/periodic_signal.hpp"

int main() {

    // https://toolbox.cuppajoeman.com/programming/looping_in_time.html
    bool test_taffl = true;

    PeriodicSignal ps(60);

    FixedFrequencyLoop ffl;
    double update_rate_hz = 512;
    std::function<void(double)> rate_limited_func = [&](double dt) {
        if (test_taffl) {
            if (ps.process_and_get_signal()) {
                std::cout << "taffl: " << ps.get_last_delta_time() << std::endl;
            }
        }
        /*std::cout << dt << std::endl; */
    };
    std::function<bool()> termination_condition_func = []() { return false; };
    ffl.start(update_rate_hz, rate_limited_func, termination_condition_func, true);
}
