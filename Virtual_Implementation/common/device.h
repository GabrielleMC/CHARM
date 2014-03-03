#include "pugixml.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdexcept>
#include <sstream>

#define LOG_FILENAME "device_log.txt"

enum STATE {WORKING, MISSING, SHUTDOWN, INVALID};

static int uid_counter = 0;

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
                int process_readings_xml(pugi::xml_document &doc);
                void create_readings_xml(pugi::xml_document &doc, int n_readings);
                int process_confirm_xml(pugi::xml_document &doc);
                void create_confirm_xml(pugi::xml_document &doc, int n_readings);
                void print(unsigned int num = 5, std::string filename = "");
};

void format_time(time_t time, char* buff);
