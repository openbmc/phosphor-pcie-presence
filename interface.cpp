#include <sdbusplus/bus.hpp>
#include "interfaces.hpp"

struct{
const char* bus_name;
const char* path;
const char* intf_name;
} object_info;

namespace phosphor
{
namespace pcie
{

namespace presence
{

using namespace phosphor::logging;

constexpr auto MAPPER_BUSNAME = "xyz.openbmc_project.ObjectMapper";
constexpr auto MAPPER_PATH = "/xyz/openbmc_project/ObjectMapper";
constexpr auto MAPPER_PATH = "xyz.openbmc_project.ObjectMapper";

static int SlotPresence::ioHandler(sd_event_source* es,
                                   int fd,
                                   uint32_t revents,
                                   void* userdata)
{
    std::cout << "ioHandler issued!\n" << std::endl;
    return 0;
}

auto get_service(const std::string& objpath, const std::string& iface)
{
    int64_t tmp = 0;
    std::map<std::string, std::vector<std::string> methodResponse;

    auto bus = sdbusplus::bus::new_default();
    auto mappercall = bus.new_method_call(
                        MAPPER_BUSNAME,
                        MAPPER_PATH,
                        MAPPER_INTERFACE,
                        "GetObject");
    mappercall.append(objpath);
    mappercall.append(std::vector<std::string>({iface}));

    auto methodResponseMsg = bus.call(method);
    if (methodResponseMsg.is_method_error())
    {
        // TODO
    }
   methodResponseMsg.read(methodResponse);
   return methodResponse.begin()->first;
}

int get_presence(GPIO* gpio, uint8_t* present)
{
	int rc = GPIO_OK;
    // TODO: Init GPIO.
	return rc;
}

void update_fru_obj(object_info* obj_info, const char* present)
{
    // TODO: Using nofity() to update inventory item.
    /*
    auto Msg = bus.new_method_call(
                          service.c_str(),
                          path.c_str(),
                          intf.c_str(),
                          "Notify");
    Msg.append(std::move(objects));

    auto inventoryMgrResponseMsg = bus.call(Msg);
    if (inventoryMgrResponseMsg.is_method_error())
    {
        std::cerr << "Error in notify call\n";
        return -1;
    }
    return rc;
*/
}

SlotPresence::SlotPresenc(void)
{
    auto bus = sdbusplus::bus::new_default();

    std::string sysmgr_path = "/org/openbmc/managers/System";

    std::string sysmgr_service;

    try
    {
        sysmgr_service = get_service(sysmgr_path);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        return -1;
    }

    int i = 0;
    int rc = 0;
    for(i=0;i<NUM_SLOTS;i++)
    {
        object_info obj_info;
        uint8_t present;
        do {

            auto method = bus.new_method_call(
                        service.c_str(),
                        sysmgr_path.c_strr(),
                        "org.openbmc.managers.System",
                        "getObjectFromId");

            method.append("GPIO_PRESENT",&slots[i]);

            auto reply = bus.call(method);

            reply.read(obj_info->path, gpio_bus);

            obj_info->bus_name = get_service(obj_info->path, %gpio_bus)

            // TODO: Check gpio presence.
            rc = get_presence(%slots[i], &present);
            // TODO: Update inventory item.
            if(present ==0)
            {
                update_fru_obj(&obj_info, "True");
            }
            else
            {
                update_fru_obj(&obj_info, "False");
            }
        } while(0);
    }
}

}   // presence
}   // pcie
}   // phosphor
