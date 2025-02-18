#include <iostream>
#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/periodic_signal/periodic_signal.hpp"
#include "utility/stopwatch/stopwatch.hpp"

int main() {

    // https://toolbox.cuppajoeman.com/programming/looping_in_time.html

    // if the sbffl runs at x Hz, and the inner loop
    // runs at y Hz, expect the inner loop's measured delta to be
    // on average: 1/y + 1/2 * 1/x
    // the faster the outer loop be higher quality the measured delta.
    bool test_sbffl_with_nested_taffl = false;

    // when running in measured delta mode, the deltas will be extremely accurate at the
    // cost of spinning your cpu
    bool test_while_loop_taffl = false;

    // on my system this runs at 400 000 Hz
    bool test_while_loop_speed = false;

    PeriodicSignal ps(60, OperationMode::MEASURED_DELTAS);

    if (test_sbffl_with_nested_taffl) {
        FixedFrequencyLoop ffl;
        double update_rate_hz = 1024;
        std::function<void(double)> rate_limited_func = [&](double dt) {
            if (test_sbffl_with_nested_taffl) {
                if (ps.process_and_get_signal()) {
                    std::cout << "taffl: " << ps.get_last_delta_time() << std::endl;
                }
            }
            /*std::cout << dt << std::endl; */
        };
        std::function<bool()> termination_condition_func = []() { return false; };
        ffl.start(update_rate_hz, rate_limited_func, termination_condition_func, true);
        return 0;
    }

    if (test_while_loop_taffl) {
        while (true) { // spin your cpu ...
            if (ps.process_and_get_signal()) {
                std::cout << "taffl: " << ps.get_last_delta_time() << std::endl;
            }
        }
        return 0;
    }

    if (test_while_loop_speed) {
        Stopwatch stopwatch;
        int count = 0;
        while (true) { // spin your cpu...
            stopwatch.press();
            if (count % 10000) {
                std::cout << "while loop running at: " << stopwatch.average_frequency << "Hz" << std::endl;
            }
            count++;
        }
        return 0;
    }
}
