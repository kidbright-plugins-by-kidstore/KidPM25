#ifndef __KIDPM25_H__
#define __KIDPM25_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"

class KidPM25 : public Device {
	private:		
		enum {
			s_detect,
			s_read,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;

		uint8_t dataBuff[12];
		uint16_t PM_AE_UG_1_0, PM_AE_UG_2_5, PM_AE_UG_10_0;

	public:
		// constructor
		KidPM25(int bus_ch, int dev_addr) ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		int read(uint8_t size) ;

		
};

#endif