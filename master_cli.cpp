#include <unistd.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include "Ensure.h"
#include "Master.h"
#include "json.h"

void help(const char *argv0, const char *message = nullptr)
{
    if(message) std::cout << "WARNING: " << message << '\n';

    std::cout
        << argv0
        << " -d device - input.json [-o output.json]"
        << std::endl;
}

int main(int argc, char *argv[])
{
    std::string device, iname, oname;

    for(char c; -1 != (c = ::getopt(argc, argv, "hd:i:o:"));)
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
            case 'i':
                iname = optarg ? optarg : "";
                break;
            case 'o':
                oname = optarg ? optarg : "";
                break;
            case ':':
            case '?':
            default:
                help(argv[0], "geopt() failure");
                return EXIT_FAILURE;
                break;
        }
    }

    if(device.empty() || iname.empty())
    {
        help(argv[0]);
        return EXIT_FAILURE;
    }

    try
    {
        Modbus::RTU::JSON::json input, output;

        std::ifstream(iname) >> input;

        ENSURE(input.is_array(), RuntimeError);

        Modbus::RTU::Master master{device.c_str()};

        for(const auto &i : input) Modbus::RTU::JSON::dispatch(master, i, output);

        if(oname.empty()) std::cout << output;
        else std::ofstream{oname} << output;
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
