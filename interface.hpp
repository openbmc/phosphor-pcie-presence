#pragma once

#include <string>
#include <systemd/sd-event.h>
#include <sdbusplus/server.hpp>

namespace phosphor
{
namespace pcie
{
namespace presence
{

class SlotPresence
{
    public:
        SlotPresence() = delete;
        SlotPresence(const SlotPresence&) = delete;
        SlotPresence(SlotPresence&&) = default;
        SlotPresence operator=(const SlotPresence&) = delete;
        SlotPresence& operator=(SlotPresence&&) = default;
        ~SlotPresence() = default;


int ioHandler(sd_event_source*,
                        int,
                        uint32_t,
                        void*);

    private:
        //SlotPresence
        sdbusplus::bus::bus& bus;

        sd_event* ioEvent;
};

} // namespace presence
} // namespace pcie
} // namespace phosphor
