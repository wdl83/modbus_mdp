#include <unistd.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "Ensure.h"
#include "Master.h"
#include "json.h"

void help(const char *argv0, const char *message = nullptr)
{
    if(message) std::cout << "WARNING: " << message << '\n';

    std::cout
        << argv0
        << " -d device"
        << std::endl;
}

int main(int argc, char *argv[])
{
    std::string device;

    for(int c; -1 != (c = ::getopt(argc, argv, "hd:"));)
    {
        switch(c)
        {
            case 'h':
                help(argv[0]);
                return EXIT_SUCCESS;
                break;
            case 'd':
                device = optarg ? optarg : "";
                break;
            case ':':
            case '?':
            default:
                help(argv[0], "geopt() failure");
                return EXIT_FAILURE;
                break;
        }
    }

    if(device.empty())
    {
        help(argv[0]);
        return EXIT_FAILURE;
    }

    try
    {
        using namespace Modbus;
        RTU::Master master{device.c_str()};

        for(auto i = RTU::Addr::max; i >= RTU::Addr::min; --i)
        {
            RTU::JSON::json input
            {
                {"slave", i},
                {"fcode", 3}, /* READ HOLDING REGISTERS */
                {"addr", 0},
                {"count", 1},
                {"timeout_ms", 100}
            };

            RTU::JSON::json output;

            try
            {
                std::cout << " slave " << int(i) << " ";
                Modbus::RTU::JSON::dispatch(master, input, output);
            }
            catch(const RTU::TimeoutError &except)
            {
                std::cerr << "timeout" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds{25});
            }
            catch(const RuntimeError &except)
            {
                std::cerr << except.what() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds{100});
            }
            catch(...)
            {
                std::cerr << "unsupported exception addr " << i << std::endl;
                break;
            }
        }

    }
    catch(const std::exception &except)
    {
        std::cerr << except.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "unsupported exception" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
