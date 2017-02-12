#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"
#include <log.hpp>
#include <systemd/sd-event.h>
#include <sys/epoll.h>
#include "interface.hpp"
#include <sdbusplus/vtable.hpp>

int main(int argc, char *argv[])
{

    using namespace phosphor::logging;

    auto bus = sdbusplus::bus::new_default();

    phosphor::pcie::presence::SlotPresence SlotPresence();

    sd_event* ioEvent = NULL;
    sd_event_source *event_source = NULL;

    auto fd = epoll_create(1);

    auto r = sd_event_default(&ioEvent);

    if (r < 0) {
        log<level::ERR>("pcie presence: obtain event loop  error",
        entry("ERROR=%s", strerror(-r)));
        goto finish;
    }

    bus.attach_event(ioEvent, SD_EVENT_PRIORITY_NORMAL);

    if (r < 0) {
        log<level::ERR>("pcie presence: attach system bus to event loop error",
        entry("ERROR=%s", strerror(-r)));
        goto finish;
    }
    sd_event_add_io(ioEvent,
        &event_source,
        fd,
        EPOLLIN,
        phosphor::pcie::presence::SlotPresence::ioHandler, // SlotPresence
        NULL);

    sd_event_loop(ioEvent);

finish:
    sd_event_source_unref(event_source);
//      bus.detach_event();
    sd_event_unref(ioEvent);

    return 0;
}
