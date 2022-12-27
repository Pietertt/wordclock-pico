#pragma once

#include "register.h"

namespace Wordclock {

    class SingleRegister : public Register {

        public: 
            SingleRegister(int clock, int latch, int data);
            SingleRegister();

            virtual void shiftOut();

        private:

        protected:
        
    };
}