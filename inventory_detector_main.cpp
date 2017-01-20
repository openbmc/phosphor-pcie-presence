#include <cstdlib>
#include <iostream>
#include <exception>
#include <sdbusplus/bus.hpp>
#include "config.h"

int main(int argc, char *argv[])
{
    auto bus = sdbusplus::bus::new_default();

    while(true)
    {
        bus.process_discard();
        bus.wait();
    }
    return 0;
 }
