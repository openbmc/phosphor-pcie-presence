#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"
#include <log.hpp>
#include <systemd/sd-event.h>
#include <sys/epoll.h>
#include "interface.hpp"

int main(int argc, char *argv[])
{

    auto slot = phosphor::pcie::presence::slot_presence();

    // TODO: Involve sd_event here from another commit.

    return 0;
}
