#include <p24FJ128GB206.h>
#include "config.h"
#include "common.h"
#include "ui.h"
#include "timer.h"

// Added two header files
#include "pin.h"
#include "oc.h"

int16_t main(void) {
    init_clock();
    init_ui();
    init_timer();
// Added pin and oc
	init_pin();
	init_oc();

// Set digital pin 13 as output to servo
	pin_digitalOut(&D[13]);
// Set analog pin 0 as input from pot
	pin_analogIn(&A[0]);
	
// range values from HK website
// note on hex: instead of 0-9, hex goes to 16, so it goes 0-9 and then a-f, f being 15
	oc_servo(&oc1, &D[13], &timer1, 0.02f, 0.0008f, 0.0022f, 0x8000);

// kept old blink code to show the board is working	
    led_on(&led1);
    timer_setPeriod(&timer2, 0.1);
    timer_start(&timer2);

    while (1) {
        if (timer_flag(&timer2)) {
            timer_lower(&timer2);
            led_toggle(&led1);
        }
        led_write(&led2, !sw_read(&sw2));
        led_write(&led3, !sw_read(&sw3));
		
		// Write value from analog 0 to digital 13
		pin_write(&D[13], pin_read(&A[0]));
    }
}

