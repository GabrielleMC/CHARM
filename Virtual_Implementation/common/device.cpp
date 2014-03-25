#include "device.h"

// buff should be char[20]
void format_time(time_t time, char* buff)
{
        strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
}

void Device::log(std::string msg, std::string file, bool append, bool timestamp)
{
        std::ofstream logfile;
        if(append)
                logfile.open(file.c_str(), std::ios::app);
        else
                logfile.open(file.c_str());
        if(logfile.is_open()) {
                if(timestamp) {
                        time_t now = time(NULL);
                        char buff[20];
                        format_time(now, buff);
                        std::stringstream ss;
                        ss << buff << " " << msg;
                        logfile << ss.str();
                } else {
                        logfile << msg;
                }
                logfile.close();
        }
        else {
                printf("DEVICE ERROR OPENING FILE %s\n", file.c_str());
        }
}

Device::Device(void) 
{
        uid = -1;
        reading_freq = 30;
        state = MISSING;
        battery = 0;
        last_reading = 0;
        std::ostringstream cc;
        cc << "device_" << uid << "_readings.txt";
        reading_file = cc.str();
        std::stringstream ss;
        ss << "New device " << uid << " added" << std::endl;
        log(ss.str());
        strcpy(msg_version, " 1.0");
        strcpy(fw_version, " 1.0");
}

void Device::update_uid(int new_uid)
{
        uid = new_uid;
        std::ostringstream cc;
        cc << "device_" << uid << "_readings.txt";
        reading_file = cc.str();
        std::stringstream ss;
        ss << "Device uid now set to " << uid << std::endl;
        log(ss.str());
}

int Device::get_uid(void)
{
        return uid;
}

unsigned int Device::get_battery(void)
{
        return battery;
}

void Device::set_battery(unsigned int new_bat)
{
        battery = new_bat;
}

STATE Device::get_state(void)
{
        return state;
}

void Device::set_state(STATE new_state)
{
        state = new_state;
}

void Device::get_fw_version(char buff[4])
{
        strcpy(buff, fw_version);
}

int Device::add_reading(time_t time, int reading)
{
        char buff[20];
        std::stringstream ss;
        format_time(time, buff);
        if(readings[time]) {
                ss << "Device " << uid << ": Failed to enter reading, value at time " << buff <<" exists." << std::endl;
                log(ss.str());
                return -1;
        } else {
                readings[time] = reading;
                ss << "Device " << uid << ": Added reading, " << buff << " = " << reading << std::endl;
                log(ss.str());
                return 0;
        }
}

// could throw a out_of_range error
int Device::get_reading(time_t time)
{
        return readings[time];
}

bool Device::rm_reading(time_t time)
{
        char buff[20];
        std::stringstream ss;
        format_time(time, buff);
        if(readings.find(time) == readings.end()) {
                ss << "Device " << uid << ": Reading at time " << buff << " not found" << std::endl;
                log(ss.str());
                return false;
                
        } else {
                readings.erase(time);
                ss << "Device " << uid << ": Erased reading at time " << buff << std::endl;
                log(ss.str());
                return true;
        }
}

void Device::clear_readings(void)
{
        while(readings.size() > 0) {
                std::map<time_t, int>::iterator it = readings.begin();
                readings.erase(it->first);
        }
        std::stringstream ss;
        ss << "Device " << uid << ": All readings removed" << std::endl;
}

void Device::save_readings(void)
{
        if(uid == -1)
                return;
        print(readings.size(), reading_file);
}

int Device::num_readings(void)
{
        return readings.size();
}

bool Device::is_missing(void)
{
        if(state == MISSING)
                return true;
        return false;
}

unsigned int Device::get_frequency(void)
{
        return reading_freq;
}

int Device::process_readings_xml(pugi::xml_document &doc)
{
        std::stringstream ss;
        ss << "Device " << uid << ": Parsing client message" << std::endl;
        log(ss.str());
        ss.str(std::string());
        pugi::xml_node mother_node = doc.first_child();
        std::string msg_v = mother_node.child("msg_version").child_value();
        if((strcmp(mother_node.name(), "client") != 0) || \
                (strcmp(msg_v.c_str(), " 1.0") != 0)) {
                ss << "Device " << uid << ": Invalid message, parsing failed" << std::endl;
                log(ss.str());
                return 0;
        }
        int uid_test = atoi(mother_node.child("uid").child_value());
        if(uid_test == -1)
                update_uid(uid_counter++);
        
        battery = atoi(mother_node.child("battery").child_value());
        strncpy(fw_version, mother_node.child("fw").child_value(), 5);
        
        std::string shutdown = mother_node.child("shut_down").child_value();
        if(strcmp(shutdown.c_str(), "true") == 0) {
                std::cout << "Device shut down" << std::endl;
                state = SHUTDOWN;
        }
        int num_readings = atoi(mother_node.child("n_readings").child_value());
        pugi::xml_node readings = mother_node.child("readings");
        for(int i = 0; i < num_readings; i++) {
                ss << "reading" << i;
                std::string time_c = readings.child(ss.str().c_str()).child("time").child_value();
                int reading = atoi(readings.child(ss.str().c_str()).child("reading").child_value());
                
                struct tm tm;
                strptime(time_c.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
                tm.tm_isdst = -1; // dst not set by strptime
                time_t t = mktime(&tm);
                add_reading(t, reading);
                ss.str(std::string());
        }
        return num_readings;
}

int Device::process_confirm_xml(pugi::xml_document &doc)
{
        std::stringstream ss;
        ss << "Device " << uid << ": Parsing server message" << std::endl;
        log(ss.str());
        ss.str(std::string());
        pugi::xml_node mother_node = doc.first_child();
        std::string msg_v = mother_node.child("msg_version").child_value();
        if((strcmp(mother_node.name(), "server") != 0) || \
                (strcmp(msg_v.c_str(), " 1.0") != 0)) {
                ss << "Device " << uid << ": Invalid message, parsing failed" << std::endl;
                log(ss.str());
                return 0;
        }
        int uid_test = atoi(mother_node.child("uid").child_value());
        if(uid == -1)
                update_uid(uid_test);
        
        std::string shutdown = mother_node.child("shut_down").child_value();
        if(strcmp(shutdown.c_str(), "true") == 0) {
                std::cout << "Shutdown command received, shutting down." << std::endl;
                state = SHUTDOWN;
                save_readings();
        }
        
        int num_readings = atoi(mother_node.child("n_readings").child_value());
        pugi::xml_node readings = mother_node.child("readings");
        int readings_removed = 0;
        for(int i = 0; i < num_readings; i++) {
                ss << "reading" << i;
                std::string time_c = readings.child(ss.str().c_str()).child("time").child_value();
                
                struct tm tm;
                strptime(time_c.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
                tm.tm_isdst = -1; // dst not set by strptime
                time_t t = mktime(&tm);
                if(rm_reading(t))
                        readings_removed++;
                ss.str(std::string());
        }
        return readings_removed;
}

void Device::create_readings_xml(pugi::xml_document &doc, int n_readings)
{
        doc.reset();
        
        // client base node
        //pugi::xml_node node = doc.append_child("client");
        doc.append_child("client");
        
        xml_header(doc);
        xml_readings(doc, false, n_readings);
}

void Device::create_confirm_xml(pugi::xml_document &doc, int n_readings)
{
        doc.reset();
        
        // client base node
        //pugi::xml_node node = doc.append_child("server");
        doc.append_child("server");
        
        xml_header(doc);
        xml_latest_readings(doc, true, n_readings);
}

void Device::xml_header(pugi::xml_document &doc)
{
        char uid_c[sizeof(int)];
        sprintf(uid_c, "%d", uid);
        char battery_c[sizeof(int)];
        sprintf(battery_c, "%d", battery);

        pugi::xml_node node = doc.first_child();
        
        // UID
        pugi::xml_node node_uid = node.append_child("uid");
        node_uid.append_child(pugi::node_pcdata).set_value(uid_c);
        
        // msg_version
        pugi::xml_node node_msg_version = node.append_child("msg_version");
        node_msg_version.append_child(pugi::node_pcdata).set_value(msg_version);
        
        // fw
        pugi::xml_node node_fw = node.append_child("fw");
        node_fw.append_child(pugi::node_pcdata).set_value(fw_version);
        
        // battery
        pugi::xml_node node_battery = node.append_child("battery");
        node_battery.append_child(pugi::node_pcdata).set_value(battery_c);
        
        pugi::xml_node node_shutdown = node.append_child("shut_down");
        
        // shutdown
        if(state == SHUTDOWN)
                node_shutdown.append_child(pugi::node_pcdata).set_value("true");
        else
                node_shutdown.append_child(pugi::node_pcdata).set_value("false");
}

void Device::xml_readings(pugi::xml_document &doc, bool time_only, int n_readings)
{
        pugi::xml_node node = doc.first_child();
        
        
        pugi::xml_node node_readings = node.append_child("readings");

        // readings
        std::map<time_t,int>::iterator it = readings.begin();
        int i = 0;
        
        while((i < n_readings) && (it != readings.end())) {
                char time_c[20];
                char reading_c[32];
                std::stringstream ss;
                format_time(it->first, time_c);
                std::sprintf(reading_c, "%d", it->second);                
                
                ss << "reading" << i;
                pugi::xml_node readingn = node_readings.append_child(ss.str().c_str());
                
                pugi::xml_node time = readingn.append_child("time");
                time.append_child(pugi::node_pcdata).set_value(time_c);
                if(!time_only) {
                        pugi::xml_node reading = readingn.append_child("reading");
                        reading.append_child(pugi::node_pcdata).set_value(reading_c);
                }
                i++;
                it++;
        }
        
        char num_readings_c[sizeof(int)];
        sprintf(num_readings_c, "%d", i);
        
        // n_readings
        pugi::xml_node node_n_readings = node.append_child("n_readings");
        node_n_readings.append_child(pugi::node_pcdata).set_value(num_readings_c);
}

void Device::xml_latest_readings(pugi::xml_document &doc, bool time_only, int n_readings)
{
        pugi::xml_node node = doc.first_child();
        
        char num_readings_c[sizeof(int)];
        sprintf(num_readings_c, "%d", n_readings);
        
        // n_readings
        pugi::xml_node node_n_readings = node.append_child("n_readings");
        node_n_readings.append_child(pugi::node_pcdata).set_value(num_readings_c);
        
        pugi::xml_node node_readings = node.append_child("readings");

        // readings
        std::map<time_t,int>::iterator it = readings.end();
        int i = 0;
        while(i < n_readings) {
                --it;
                char time_c[20];
                char reading_c[32];
                std::stringstream ss;
                format_time(it->first, time_c);
                std::sprintf(reading_c, "%d", it->second);                
                
                ss << "reading" << i;
                pugi::xml_node readingn = node_readings.append_child(ss.str().c_str());
                
                pugi::xml_node time = readingn.append_child("time");
                time.append_child(pugi::node_pcdata).set_value(time_c);
                if(!time_only) {
                        pugi::xml_node reading = readingn.append_child("reading");
                        reading.append_child(pugi::node_pcdata).set_value(reading_c);
                }
                
                i++;
        }
}

int Device::process_readings_raw(char *buf)
{
        int uid_test = (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
        if(uid_test == -1)
                update_uid(uid_counter++);
        
        int flags = buf[4];
        int n_readings = buf[5];
        if(flags & LOW_BATTERY_FLAG)
                set_battery(LOW_BATTERY_LEVEL);
        if(flags & SHUTDOWN_FLAG) {
                set_battery(LOW_BATTERY_LEVEL);
        //        std::cout << "Device shut down" << std::endl;
        }
        //std::cout << "n_readings = " << n_readings << std::endl;
        for(int i = 0; i < n_readings; i++) {
                time_t time = 0;
                int reading = 0;
                for(int n = 0; n < 8; n++) {
                        time |= ((buf[6+(i*(8+4))+n] & 0x000000FF) << n*8);
                        if (n < 4)
                                reading |= ((buf[6+(i*(8+4))+8+n] & 0x000000FF) << n*8);
                }
                add_reading(time, reading);
        }
        return n_readings;
}

int Device::create_readings_raw(char *buf)
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
                buf[2] = uid>>16;
                buf[3] = uid>>24;
        }
        if(get_battery() < LOW_BATTERY_LEVEL)
                flags |= LOW_BATTERY_FLAG;
        if(state == SHUTDOWN)
                flags |= SHUTDOWN_FLAG;
        
        n_readings = num_readings();
        if(n_readings > 9)
                n_readings = 9;
        buf[4] = flags;
        buf[5] = n_readings;
        
        std::map<time_t,int>::iterator it = readings.begin();
        for(int i = 0; i < n_readings; i++) {
                for(int n = 0; n < 8; n++) {
                        buf[6+(i*(8+4))+n] = it->first >> n*8;
                        if (n < 4)
                                buf[6+(i*(8+4))+8+n] = it->second >> n*8;
                }
                it++;
        }
        return n_readings;
}

int Device::process_confirm_raw(char *buf)
{
        int readings_removed = 0;
        int uid_test = (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
        if(uid == -1)
                update_uid(uid_test);
        
        int flags = buf[4];
        if(flags & SHUTDOWN_FLAG) {
                state = SHUTDOWN;
        }
        if(flags & UPDATE_TIME_FLAG) {
                time_t temp = 0;
                for(int n = 0; n < 8; n++) {
                        temp |= ((buf[6+n] & 0x000000FF) << n*8);
                }
                std::cout << "Time update, now " << temp << std::endl;
        }
        int n_readings = buf[5];
        for(int i = 0; i < n_readings; i++) {
                time_t time = 0;
                for(int n = 0; n < 8; n++) {
                        time |= ((buf[6+(i*(8))+n] & 0x000000FF) << n*8);
                }
                if(rm_reading(time))
                        readings_removed++;
        }
        return readings_removed;
}

int Device::create_confirm_raw(char *buf, int n_readings)
{
        int flags = 0;
        
        buf[0] = uid;
        buf[1] = uid>>8;
        buf[2] = uid>>16;
        buf[3] = uid>>24;
        
        if(state == SHUTDOWN)
                flags |= SHUTDOWN_FLAG;
        if(n_readings == 0) {
                flags |= UPDATE_TIME_FLAG;
                time_t temp = time(NULL);
                for(int n = 0; n < 8; n++) {
                        buf[6+n] = temp >> n*8;
                }
        }
        if(n_readings > 9)
                n_readings = 9;
        buf[4] = flags;
        buf[5] = n_readings;
        // start with most recent readings
        std::map<time_t,int>::iterator it = readings.end();
        for(int i = 0; i < n_readings; i++) {
                --it;
                for(int n = 0; n < 8; n++) {
                        buf[6+(i*(8))+n] = it->first >> n*8;
                }
        }
        return n_readings;

}

void Device::print(unsigned int num, std::string filename)
{
        print_header(filename);
        print_readings(num, filename);
}

void Device::print_header(std::string filename)
{
        std::stringstream ss;
        ss << "Device uid " << uid << " settings:" << std::endl;
        ss << "  Message version = " << msg_version << std::endl;
        ss << "  Reading frequency = " << reading_freq << std::endl;
        
        switch(state) {
                case WORKING:
                        ss << "  State = WORKING" << std::endl;
                        break;
                case MISSING:
                        ss << "  State = MISSING" << std::endl;
                        break;
                case SHUTDOWN:
                        ss << "  State = SHUTDOWN" << std::endl;
                        break;
                default:
                        ss << "  State = INVALID" << std::endl;
        }
        ss << "  Battery level = " << battery << "%" << std::endl;
        if(filename.empty())
                printf("%s", ss.str().c_str());
        else
                log(ss.str(), filename, false, false);
}

void Device::print_readings(unsigned int num, std::string filename)
{
        //char temp[128];
        std::stringstream ss;
        if(num == readings.size())
                ss << "  Printing all the " << num << " readings:" << std::endl;
        else
                ss << "  Printing the latest " << num << " readings:" << std::endl;
        if(filename.empty())
                printf("%s", ss.str().c_str());
        else
                log(ss.str(), filename, true, false);

        std::map<time_t,int>::iterator it = readings.end();
        for(unsigned int i = 1; i < num+1; i++) {
                char buff[20];
                time_t time = 0;
                if(it != readings.begin())
                        time = (--it)->first;
                else
                        continue;
                format_time(time, buff);
                ss.str(std::string()); // clear the stream
                ss << "      " << buff << "\t" << get_reading(time) << std::endl;
                if(filename.empty())
                        printf("%s", ss.str().c_str());
                else
                        log(ss.str(), filename, true, false);
        }
}

int Device::update_db_readings(){
	
	MYSQL *connect;
	connect = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
	      fprintf(stderr, "%s\n", mysql_error(connect));
	      return 1;
	}
	
	//iterate through readings, then for each reading, construct a query
	while(readings.size() > 0) {
		std::stringstream ss;
		std::string str;
		std::map<time_t, int>::iterator it = readings.begin();
		time_t readtime = (it)->first;
		char buff[20];
		format_time(readtime, buff);
        ss.str(std::string()); // clear the stream
        ss << "INSERT INTO t1 (value, logtime) VALUES ('" << get_reading(readtime) << "', '" << buff << "')";
		str = ss.str();
		const char *query = str.c_str();
		//std::cout<< str;
		mysql_query(connect, query);
		readings.erase(it->first);
	}
		mysql_close(connect);
		return 0;	
}

int Device::update_db_status(){
	
	std::stringstream ss;
	std::string str;
	MYSQL *connect;
	connect = mysql_init(NULL);
	unsigned int battery = get_battery();
	STATE status = get_state();
	int id = get_uid();
	
	
	/* Connect to database */
	if (!mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
	      fprintf(stderr, "%s\n", mysql_error(connect));
	      return 1;
	}
	
	ss.str(std::string());
    ss << "SELECT * FROM Status WHERE device_id = " << id;
	str = ss.str();
	const char *query = str.c_str();
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	mysql_query(connect, query);
	res_set = mysql_store_result(connect);
	
	if (((row = mysql_fetch_row(res_set)) != NULL)){
		ss.str(std::string());
    	ss << "UPDATE Status SET battery_level = " << battery << ", current_state =" << status << " WHERE device_id = " << id;
		str = ss.str();
		const char *query = str.c_str();
		mysql_query(connect, query);
	}
	
	else {
		ss.str(std::string());
    	ss << "INSERT INTO Status (battery_level, current_state, device_id) VALUES (" << battery << ", " << status << ", " << id << ")";
		str = ss.str();
		const char *query = str.c_str();
		mysql_query(connect, query);
	}
	
	mysql_close(connect);
	return 0;
}
