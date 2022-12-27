#include "precomp.h"

int main () {
    Wordclock::Wordclock* clock = new Wordclock::Wordclock();
    clock->setup();
    clock->test();

    datetime_t t = {
        .year  = 2022,
        .month = 12,
        .day   = 27,
        .dotw  = 3,
        .hour  = 8,
        .min   = 20,
        .sec   = 00
    };

    int hour = clock->getHour();
    int minutes = clock->getMinutes();

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

        if (minutes != clock->getMinutes() || hour != clock->getHour()) {
            clock->allOff();
            clock->decide_time();
            clock->commit();
            hour = clock->getHour();
            minutes = clock->getMinutes();
        }

        int randomNumber = rand() % ((3 + 1) - 0) + 0;
        int counter = 0;

        if (randomNumber == 1) {
            for (int i = 0; i < 50; i++) {
                clock->random();
                clock->commit();

                if (counter == 10) {
                    counter = 0;
                }

                sleep_ms(100);
                counter++;
            }

            clock->allOff();
            clock->decide_time();
            clock->commit();
        }

        sleep_ms(120000);
    }

    return 0;
}
