#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"
#include <log.hpp>
#include <systemd/sd-event.h>
#include <sys/epoll.h>

using namespace phosphor::logging;

//int presenceHandler(sd_event_source* es, uint64_t usec, void* userData)
static int io_handler(sd_event_source *es, int fd, uint32_t revents, void *userdata)
{
   printf("io handler issued!\n");
   return 0;
}

int main(int argc, char *argv[])
{
        auto bus = sdbusplus::bus::new_default();

        sd_bus *conn = NULL;
        sd_event *presenceEvent = NULL;
        sd_event_source *event_source = NULL;

        auto fd = epoll_create(1);

        auto r = sd_bus_default_system(&conn);
        if (r < 0) {
            log<level::ERR>("pcie presence: connect to system bus error",
                         entry("ERROR=%s", strerror(-r)));
            goto finish;
        }

        r = sd_event_default(&presenceEvent);
        if (r < 0) {
            log<level::ERR>("pcie presence: obtain event loop  error",
                         entry("ERROR=%s", strerror(-r)));
            goto finish;
        }
        r = sd_bus_attach_event(conn, presenceEvent, SD_EVENT_PRIORITY_NORMAL);
        if (r < 0) {
            log<level::ERR>("pcie presence: attach system bus to event loop error",
                         entry("ERROR=%s", strerror(-r)));
            goto finish;
        }


        sd_event_add_io(presenceEvent,
               &event_source,
               fd,
               EPOLLIN,
               io_handler,
               NULL);

        sd_event_loop(presenceEvent);

finish:
        sd_event_source_unref(event_source);
//      bus.detach_event();
        sd_event_unref(presenceEvent);
}
