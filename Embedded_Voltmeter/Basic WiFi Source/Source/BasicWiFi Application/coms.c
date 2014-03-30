

#include "coms.h"

#define LOW_BATTERY_FLAG 0x1
#define SHUTDOWN_FLAG 0x2
#define UPDATE_TIME_FLAG 0x4

enum STATE {WORKING, MISSING, SHUTDOWN, INVALID};

#pragma DATA_SECTION(uid, ".uid")
int uid = -1;

volatile time_t deviceTime = 0;
extern volatile unsigned int n_readings;

int system_state = WORKING;

void FakeList()
{
	//InitializeList();
	time_t t = 0;
	int i = 0;
	for(i=0; i < 10; i++)
	{
		AddReading(t, i);
		t += 60;
	}

	AddReading(80, 0xabcd);

	RemoveTime(0);
	RemoveTime(t-60);

	RemoveTime(0);
	RemoveTime(60);
	RemoveTime(120);
	RemoveTime(180);
	RemoveTime(240);
	RemoveTime(300);
	RemoveTime(360);
	RemoveTime(420);
	RemoveTime(480);
	RemoveTime(540);
	RemoveTime(80);

	time_t j = t;

	for(i=0; i < 10; i++)
	{
		AddReading(t, i);
		t += 60;
	}

	RemoveTime(j);



}

int LowBattery()
{
	return 0;
}



int ProcessConfirmRaw(char *buf, int size)
{
		int readings_present = 0;
        int readings_removed = 0;
        int uid_test = (buf[0] | ((buf[1] & 0x000000FFL) << 8) | ((buf[2] & 0x000000FFL) << 16) | ((buf[3] & 0x000000FFL) << 24));
        if(uid == -1)
                uid = uid_test;

        int flags = buf[4];
        if(flags & SHUTDOWN_FLAG) {
                system_state = SHUTDOWN;
        }
        if(flags & UPDATE_TIME_FLAG) {
                time_t temp, lower, upper = 0;
				lower = ((buf[6] & 0x000000FFL) | ((buf[6+1] & 0x000000FFL) << 8));
				upper = (((buf[6+2] & 0x000000FFL) | ((buf[6+3] & 0x000000FFL) << 8)) << 16);
				temp = (lower & 0x0000FFFFL) | ((upper & 0xFFFF0000L));
                deviceTime = temp;
        }
        readings_present = buf[5];
        int i;
        for(i = 0; i < readings_present; i++) {
                time_t time = 0;
                int n;
                for(n = 0; n < 4; n++) {
                        time |= ((buf[6+(i*(4))+n] & 0x000000FFL) << n*8);
                }
                if(RemoveTime(time) != -1)
                        readings_removed++;
        }
        return readings_removed;
}



int CreateReadingsRaw(char *buf, int size)
{
        int flags = 0;
        if(uid == -1) {
                buf[0] = 0xFF;
                buf[1] = 0xFF;
                buf[2] = 0xFF;
                buf[3] = 0xFF;
        } else {
                buf[0] = uid;
                buf[1] = (uid & 0xFFFFFFFFL) >>8;
                buf[2] = (uid & 0xFFFFFFFFL) >>16;
                buf[3] = (uid & 0xFFFFFFFFL) >>24;
        }
        if(LowBattery())
                flags |= LOW_BATTERY_FLAG;
        if(system_state == SHUTDOWN)
                flags |= SHUTDOWN_FLAG;

        int n_temp = n_readings;
        if(n_readings > 9)
        	n_temp = 9;
        buf[4] = flags;
        buf[5] = n_temp;
        int i;
        for(i = 0; i < n_temp; i++) {
        		READING_PAIR temp_reading = GetReading(i);
        		int n;
                for(n = 0; n < 4; n++) {
                        buf[6+(i*(4+4))+n] = (temp_reading.time & 0xFFFFFFFFL) >> n*8;
                        buf[6+(i*(4+4))+4+n] = (temp_reading.reading & 0xFFFFFFFFL) >> n*8;
                }
        }
        return n_temp;
}
