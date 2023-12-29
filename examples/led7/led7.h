#ifndef _LED7_H
#define _LED7_H

#include <mdk.h>

#define PIN_COUNT 8	// number of pin for one led

#define DIGIT_SIGN 10
#define DIGIT_EMPTY 11

enum led7_type
{
	led7_CC, // common cathode
	led7_CA	 // common anode
};

struct led7_array
{
	enum led7_type type;
	uint8_t size;
	uint8_t pins[PIN_COUNT];
	uint8_t common_pins[10];
};

int led7_number_to_digits(int32_t number, uint8_t *digits, uint8_t size);

int led7_init(struct led7_array *leds);

int led7_display(int32_t number, uint32_t time);

int led7_clear();

#endif
