#include "led7.h"

uint8_t led7_segment_values[11][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {1, 1, 1, 1, 0, 1, 1, 0}, // 9
    {0, 0, 0, 0, 0, 0, 1, 0}  // -
};

static struct led7_array *led7_leds = NULL;

#define segment_value(x) (led7_leds->type == led7_CC ? x : !x)

int led7_init(struct led7_array *leds)
{
	led7_leds = leds;
	for (uint8_t i = 0; i < leds->size; i++)
	{
		gpio_output(leds->common_pins[i]);
	}
	for (uint8_t i = 0; i < PIN_COUNT; i++)
	{
		gpio_output(leds->pins[i]);
	}
	return 0;
}

int led7_number_to_digits(int32_t number, uint8_t *digits, uint8_t size)
{
	int8_t is_negative = number < 0;
	int8_t index = (int8_t)size - 1;

	if (number < 0)
	{
		number = -number;
	}

	if (number == 0)
	{
		digits[index--] = 0;
	}

	while (number > 0 && index >= 0)
	{
		uint8_t digit = (uint8_t)(number % 10);
		digits[index--] = digit;
		number /= 10;
	}

	if (index >= 0 && is_negative)
	{
		digits[index--] = DIGIT_SIGN;
	}

	while (index >= 0)
	{
		digits[index--] = DIGIT_EMPTY;
	}

	return 0;
}

int led7_clear_led(struct led7_array *leds, uint8_t index)
{
	for (uint8_t i = 0; i < PIN_COUNT; i++)
	{
		gpio_write(leds->pins[i], 0);
	}

	gpio_write(leds->common_pins[index], 0);
	return 0;
}

int led7_display_led(struct led7_array *leds, uint8_t index, uint8_t digit)
{
	if (digit == DIGIT_EMPTY)
	{
		return led7_clear_led(leds, index);
	}

	uint8_t *values = led7_segment_values[digit];

	for (uint8_t i = 0; i < PIN_COUNT; i++)
	{
		gpio_write(leds->pins[i], segment_value(values[i]));
	}

	gpio_write(leds->common_pins[index], segment_value(0));

	return 0;
}

/*
	@param time: in microseconds
*/
int led7_display(int32_t number, uint32_t time)
{
	if (!led7_leds)
	{
		// printf("Uninitailized leds\n");
		return 1;
	}
	printf("Display number: %ld\n", number);

	uint8_t digits[led7_leds->size];
	led7_number_to_digits(number, digits, led7_leds->size);

	/*
	  Example: number = 45, time = 20ms
	  The number 45 has 2 digits, so time for each digit is 10ms
	  So we display number 45 by do the following steps:
	  1. Display 4 in led 1
	  2. Sleep 10ms
	  3. Clear led 1
	  4. Display 5 in led 2
	  5. Sleep 10ms
	  6. Clear led 2
	*/
	uint32_t time_for_1_led = time / led7_leds->size;
	for (uint8_t i = 0; i < led7_leds->size; i++)
	{
		led7_display_led(led7_leds, i, digits[i]);
		delay_us(time_for_1_led);
		led7_clear_led(led7_leds, i);
	}

	return 0;
}

int led7_clear()
{
	if (!led7_leds)
	{
		printf("Uninitailized leds\n");
		return 1;
	}

	return 0;
}
