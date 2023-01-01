#include "precomp.h"

int main () {
    Wordclock::Wordclock* clock = new Wordclock::Wordclock();
    clock->setup();
    clock->test();

    char string[50] = __TIME__;
    char* token = strtok(string, ":");
    int hour = atoi(token);
    token = strtok(NULL, ":");
    int minutes = atoi(token);
    token = strtok(NULL, ":");
    int seconds = atoi(token);

    datetime_t t = {
        .year  = 2022,
        .month = 12,
        .day   = 27,
        .dotw  = 3,
        .hour  = hour,
        .min   = minutes,
        .sec   = seconds
    };

    clock->allOff();
    clock->decide_time();
    clock->commit();

    rtc_init();
    rtc_set_datetime(&t);
    sleep_us(64);

    while (true) {
        rtc_get_datetime(&t);
        clock->setHour(t.hour);
        clock->setMinutes(t.min);
        clock->setSeconds(t.sec);

        clock->allOff();
        clock->decide_time();
        clock->commit();

        sleep_ms(120000);
    }

    return 0;
}
