#pragma once

#define F_CPU                       16000000
#define BLINK_DELAY_MS              1000
#define AMOUNT_OF_WORDS             21
#define DUTY_CYCLE_LOW              1
#define DUTY_CYCLE_HIGH             100
#define LOW_POWER_HOUR              16

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "pico/multicore.h"
#include "hardware/rtc.h"
#include "hardware/irq.h"
#include "hardware/adc.h"

#include "wordclock.h"
#include "register.h"
#include "singleregister.h"
#include "doubleregister.h"
#include "word.h"
