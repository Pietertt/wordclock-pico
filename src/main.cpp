#include "precomp.h"

#define MONTH (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
: __DATE__ [2] == 'b' ? 2 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
: __DATE__ [2] == 'y' ? 5 \
: __DATE__ [2] == 'l' ? 7 \
: __DATE__ [2] == 'g' ? 8 \
: __DATE__ [2] == 'p' ? 9 \
: __DATE__ [2] == 't' ? 10 \
: __DATE__ [2] == 'v' ? 11 \
: 12)

Wordclock::Wordclock* wordclock;

void core1_main() {
    bool lowPower = false;

    while (true) {
        if (wordclock->getHour() <= 9 || wordclock->getHour() >= 17) {
            lowPower = true;
        } else {
            lowPower = false;
        }
        wordclock->sleep(lowPower ? 10 : 90);
    }
}

int main (void) {
    wordclock = new Wordclock::Wordclock();
    wordclock->setup();
    wordclock->test();

    char timeString[50] = __TIME__;
    char dateString[50] = __DATE__;
    
    char* token = strtok(timeString, ":");
    int hour = atoi(token);
    token = strtok(NULL, ":");
    int minutes = atoi(token);
    token = strtok(NULL, ":");
    int seconds = atoi(token);

    token = strtok(dateString, " ");
    char* month = token;
    token = strtok(NULL, " ");
    int day = atoi(token);
    token = strtok(NULL, " ");
    int year = atoi(token);

    datetime_t t = {
        .year  = year,
        .month = MONTH,
        .day   = day,
        .dotw  = 3,
        .hour  = hour,
        .min   = minutes,
        .sec   = seconds
    };

    rtc_init();
    rtc_set_datetime(&t);
    sleep_us(64);

    rtc_get_datetime(&t);
    wordclock->setHour(t.hour);
    wordclock->setMinutes(t.min);
    wordclock->setSeconds(t.sec);

    wordclock->allOff();
    wordclock->decide_time();
    wordclock->commit();

    multicore_launch_core1(core1_main);

    while (true) {
        rtc_get_datetime(&t);
        wordclock->setHour(t.hour);
        wordclock->setMinutes(t.min);
        wordclock->setSeconds(t.sec);

        wordclock->allOff();
        wordclock->decide_time();
        wordclock->commit();

        int randomNumber = rand() % ((3 + 1) - 0) + 0;
        int counter = 0;

        // if (randomNumber == 1) {
        //     for (int i = 0; i < 50; i++) {
        //         wordclock->random();
        //         wordclock->commit();

        //         if (counter == 10) {
        //             counter = 0;
        //         }

        //         sleep_ms(100);
        //         counter++;
        //     }
        // }

        sleep_ms(120000);
    }

    return 0;
}
