

#include "coms.h"

#define LOW_BATTERY_FLAG 0x1
#define SHUTDOWN_FLAG 0x2
#define UPDATE_TIME_FLAG 0x4

enum STATE {WORKING, MISSING, SHUTDOWN, INVALID};

#pragma DATA_SECTION(uid, ".uid")
int uid = -1;

volatile time_t deviceTime = 0;

int state = WORKING;

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
        int readings_removed = 0;
        int uid_test = (buf[0] | (buf[1] << 8) | ((buf[2] << 8) << 8) | (((buf[3] << 8) << 8) << 8));
        if(uid == -1)
                uid = uid_test;

        int flags = buf[4];
        if(flags & SHUTDOWN_FLAG) {
                state = SHUTDOWN;
        }
        if(flags & UPDATE_TIME_FLAG) {
                time_t temp = 0;
                int n;
                for(n = 0; n < 8; n++) {
                        temp |= ((buf[6+n] & 0x000000FF) << n*8);
                }
                deviceTime = temp;
        }
        int n_readings = buf[5];
        int i;
        for(i = 0; i < n_readings; i++) {
                time_t time = 0;
                int n;
                for(n = 0; n < 8; n++) {
                        time |= ((buf[6+(i*(8))+n] & 0x000000FF) << n*8);
                }
                if(RemoveTime(time) != -1)
                        readings_removed++;
        }
        return readings_removed;
}



int CreateReadingsRaw(char *buf, int size)
{
        int flags = 0;
        int n_readings = 0;
        if(uid == -1) {
                buf[0] = 0xFF;
                buf[1] = 0xFF;
                buf[2] = 0xFF;
                buf[3] = 0xFF;
        } else {
                buf[0] = uid;
                buf[1] = uid>>8;
                buf[2] = (uid>>8)>>8;
                buf[3] = ((uid>>8)>>8)>>8;
        }
        if(LowBattery())
                flags |= LOW_BATTERY_FLAG;
        if(state == SHUTDOWN)
                flags |= SHUTDOWN_FLAG;

        int n_temp = n_readings;
        if(n_readings > 9)
        	n_temp = 9;
        buf[4] = flags;
        buf[5] = n_temp;
        int i;
        for(i = 0; i < n_temp; i++) {
        		int n;
                for(n = 0; n < 8; n++) {
                		READING_PAIR temp_reading = GetReading(i);
                        buf[6+(i*(8+4))+n] = temp_reading.time >> n*8;
                        if (n < 4)
                                buf[6+(i*(8+4))+8+n] = temp_reading.reading >> n*8;
                }
        }
        return n_temp;
}
