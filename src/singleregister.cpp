#include "../include/precomp.h"

namespace Wordclock {
    SingleRegister::SingleRegister(int clock, int latch, int data) {
        this->setClockPin(clock);
        this->setLatchPin(latch);
        this->setDataPin(data);

        gpio_init(this->getClockPin());
        gpio_set_dir(this->getClockPin(), true);

        gpio_init(this->getLatchPin());
        gpio_set_dir(this->getLatchPin(), true);

        gpio_init(this->getDataPin());
        gpio_set_dir(this->getDataPin(), true);
    }

    SingleRegister::SingleRegister() : Register() {

    }

    void SingleRegister::shiftOut() {
        gpio_put(this->getLatchPin(), false);

        for (int i = 0; i < 8 ; i++){
            gpio_put(this->getDataPin(), this->getData() & (1 << (7 - i)));
            gpio_put(this->getClockPin(), true);
            sleep_us(5);
            gpio_put(this->getClockPin(), false);
            sleep_us(5);
        }

        gpio_put(this->getLatchPin(), true);
    }
}
