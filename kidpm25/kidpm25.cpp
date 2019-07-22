#ifndef __KIDPM25_CPP__
#define __KidPM25_CPP__

#include "kidpm25.h"

KidPM25::KidPM25(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 300;
}

void KidPM25::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int KidPM25::prop_count(void) {
	// not supported
	return 0;
}

bool KidPM25::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool KidPM25::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool KidPM25::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool KidPM25::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool KidPM25::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void KidPM25::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;

				// Go to main state
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read: {
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();

				if (i2c->read(channel, address, NULL, 0, dataBuff, 13) == ESP_OK) {
					if (dataBuff[0] != 1) {
						PM_AE_UG_1_0 = (((uint16_t)dataBuff[7]) << 8) | dataBuff[8];
						PM_AE_UG_2_5 = (((uint16_t)dataBuff[9]) << 8) | dataBuff[10];
						PM_AE_UG_10_0 = (((uint16_t)dataBuff[11]) << 8) | dataBuff[12];
					} else {
						PM_AE_UG_1_0 = 9999;
						PM_AE_UG_2_5 = 9999;
						PM_AE_UG_10_0 = 9999;
					}
				} else {
					// ESP_LOGI("KidPM25", "read error!");
					PM_AE_UG_1_0 = 9999;
					PM_AE_UG_2_5 = 9999;
					PM_AE_UG_10_0 = 9999;

					state = s_error;
				}
			}
		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
					state = s_detect;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

// Method
int KidPM25::read(uint8_t size) {
	switch(size) {
		case 10:
			return PM_AE_UG_1_0;
		
		case 25:
			return PM_AE_UG_2_5;

		case 100:
			return PM_AE_UG_10_0;

		default:
			return 0;
		
	}
}

#endif