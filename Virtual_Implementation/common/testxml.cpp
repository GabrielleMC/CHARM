#include "pugixml.hpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <time.h>
#include "device.h"


void send_xml(int uid, char* msg_v, int num_readings);

int main()
{
        std::map<time_t,int>::iterator it;
        
        Device device = Device();
        //device.print();
        time_t rawtime;
        
        time(&rawtime);
        for(int i = 0; i < 15; i++) {
                device.add_reading(rawtime-i, i);
        }
        
        //device.print(10);
        
        for(int i = 1; i < 6; i++)
                device.rm_reading(rawtime-i);
                
        //device.print(10);
        
        device.rm_reading(0);
        device.rm_reading(0);
        //device.print();
        device.save_readings();
        
        pugi::xml_document doc;
        device.xml(doc);
        
        //doc.print(std::cout);
        doc.save_file("xml_output.xml");
        
        device.clear_readings();
        
        //device.print();
        
        pugi::xml_document new_doc;
        pugi::xml_parse_result result = new_doc.load_file("xml_output.xml");
        if(result)
                device.process_msg(new_doc);
        
        //new_doc.print(std::cout);
        
}