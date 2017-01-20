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
    std::string service, objpath;

    if(argc <= 1)
    {
        std::cerr << "usage: " << argv[0]
            << " <watchdog object path> "
            << "e.g /xyz/openbmc_project/State/Watchdog/Host" << std::endl;
        return -1;
    }

    objpath = argv[1];

    using namespace phosphor::logging;

    phosphor::pcie::presence::SlotPresence SlotPresence();

    auto bus = sdbusplus::bus::new_default();

    sd_event* ioEvent = nullptr;
    sd_event_source *eventSource = nullptr;

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
        &eventSource,
        fd,
        EPOLLIN,
        phosphor::pcie::presence::SlotPresence::ioHandler, // SlotPresence
        nullptr);

    sd_event_loop(ioEvent);

finish:
    sd_event_source_unref(eventSource);
//      bus.detach_event();
    sd_event_unref(ioEvent);

    return 0;
}
