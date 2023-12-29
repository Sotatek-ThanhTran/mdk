#include <mdk.h>
#include "led7.h"

void dump()
{
	uint32_t *start;
	uint32_t *end;

	start = (uint32_t *)0x3FF44004u;
	end = (uint32_t *)0x3FF49090u;

	for (uint32_t *address = start; address < end; address++)
	{
		if (*address > 0)
			printf("%lx:%08lx\n", (unsigned long)address, *address);
	}
}

void test()
{
	uint32_t *add;

	add = (uint32_t *)0x3ff44020;
	// *add = 0x00000f90;
	*add = 0x00002f80;
	// add = (uint32_t *)0x3ff4403c;
	// *add = 0x0000caab;

	// add = (uint32_t *)0x3ff44134;
	// *add = 0x00000087;

	// add = (uint32_t *)0x3ff44138;
	// *add = 0x00000088;

	// add = (uint32_t *)0x3ff4413c;
	// *add = 0x00000089;

	// add = (uint32_t *)0x3ff44140;
	// *add = 0x0000008a;

	// add = (uint32_t *)0x3ff4454c;
	// *add = 0x00000001;

	// add = (uint32_t *)0x3ff44550;
	// *add = 0x00000002;

	// add = (uint32_t *)0x3ff44554;
	// *add = 0x00000003;

	// add = (uint32_t *)0x3ff44558;
	// *add = 0x00000004;

	// add = (uint32_t *)0x3ff4455c;
	// *add = 0x00000005;

	add = (uint32_t *)0x3ff49038;
	*add = 0x00002400;
	// add = (uint32_t *)0x3ff49054;
	// *add = 0x00002b00;
	// add = (uint32_t *)0x3ff49058;
	// *add = 0x00002b00;
	// add = (uint32_t *)0x3ff4905c;
	// *add = 0x00002b00;
	// add = (uint32_t *)0x3ff49060;
	// *add = 0x00001b00;
	// add = (uint32_t *)0x3ff49064;
	// *add = 0x00002b00;
	// add = (uint32_t *)0x3ff49068;
	// *add = 0x00002b00;

	add = (uint32_t *)0x3ff44004;
	*add = 0x00000000;
	*add = 1 << 13;
}

int main(void)
{
	uint64_t time = uptime_us();
	int32_t number = -10;

	struct led7_array leds = {
	    .type = led7_CA,
	    .size = 3,
	    .pins = {
		13, 12, 14, 27, 26, 25, 19, 21},
	    .common_pins = {2, 4, 15}};

	led7_init(&leds);
	// led7_display(81, 100000u);

	// test();
	// dump();

	for (;;)
	{
		led7_display(number, 20000u); // we display this number in 20ms, so we refresh about 50 times per second
		if (uptime_us() - time > 1000000)
		{
			time = uptime_us();
			number++;
		}
	}

	return 0;
}
