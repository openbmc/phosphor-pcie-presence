#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"
#include <systemd/sd-event.h>


int main(int argc, char *argv[])
{
    auto bus = sdbusplus::bus::new_default();

    while(true)
    {
        bus.process_discard();
        bus.wait();
    }
    return 0;
  
/*
    sd_bus *mybus;
    sd_event *myevent;

    sd_bus_eventdefault(&myevent);

    sd_bus_default_system(&mybus);

    auto adbus sdbusfd = sd_bus_get_fd(mybus);

    sd_event_add_io(myevent, sdbusfd, ...);

    sd_event_loop(myevent);
*/
 }
