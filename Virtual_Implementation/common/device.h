#include "pugixml.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <mysql.h>
#include <string>
#include <cstdio>

#define LOG_FILENAME "device_log.txt"
#define SERVER "localhost"
#define USER "CHARM"
#define PASSWORD "5*Hotel"
#define DATABASE "testCHARM"

#define RAW_BUFFER 121
#define LOW_BATTERY_FLAG 0x1
#define SHUTDOWN_FLAG 0x2
#define UPDATE_TIME_FLAG 0x4
#define LOW_BATTERY_LEVEL 20

enum STATE {WORKING, MISSING, SHUTDOWN, INVALID};

volatile static int uid_counter = 0;

class Device {
        private:
                int uid;
                char msg_version[5]; // " 1.0"
                unsigned int reading_freq; // seconds
                STATE state;
                unsigned int battery;
                char fw_version[5];
                time_t last_reading;
                std::string reading_file;
                void log(std::string msg, std::string = LOG_FILENAME,  \
                        bool append = true, bool timestamp = true);
                void print_header(std::string filename);
                void print_readings(unsigned int num, std::string filename);
                void xml_header(pugi::xml_document &doc);
                void xml_readings(pugi::xml_document &doc, bool time_only = false, \
                        int n_readings = 0);
                void xml_latest_readings(pugi::xml_document &doc, bool time_only = false, \
                        int n_readings = 0);
                std::map<time_t,int> readings;
        public:
                Device(void);
                void update_uid(int new_uid);
                int get_uid(void);
                unsigned int get_battery(void);
                void set_battery(unsigned int new_bat);
                STATE get_state(void);
                void set_state(STATE new_state);
                void get_fw_version(char buff[4]);
                unsigned int get_frequency(void);
                int add_reading(time_t time, int reading);
                int get_reading(time_t time);
                bool rm_reading(time_t time);
                void clear_readings(void);
                void save_readings(void);
                int num_readings(void);
                bool is_missing(void);
                int process_readings_raw(char *buf);
                int process_readings_xml(pugi::xml_document &doc);
                int create_readings_raw(char *buf);
                void create_readings_xml(pugi::xml_document &doc, int n_readings);
                int process_confirm_raw(char *buf);
                int process_confirm_xml(pugi::xml_document &doc);
                int create_confirm_raw(char *buf, int n_readings);
                void create_confirm_xml(pugi::xml_document &doc, int n_readings);
                void print(unsigned int num = 5, std::string filename = "");
				int update_db_readings();
				int update_db_status();
};

void format_time(time_t time, char* buff);
double voltage_conversion(int reading);
