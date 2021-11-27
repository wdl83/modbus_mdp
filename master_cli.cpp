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
        << " -d device -i input.json|- [-o output.json] -r rate -p parity(O/E/N)"
        << std::endl;
}

Modbus::SerialPort::BaudRate toBaudRate(const std::string &rate)
{
    using BaudRate = Modbus::SerialPort::BaudRate;

    if("1200" == rate) return BaudRate::BR_1200;
    else if("2400" == rate) return BaudRate::BR_2400;
    else if("4800" == rate) return BaudRate::BR_4800;
    else if("9600" == rate) return BaudRate::BR_9600;
    else if("19200" == rate) return BaudRate::BR_19200;
    else if("38400" == rate) return BaudRate::BR_38400;
    else if("57600" == rate) return BaudRate::BR_57600;
    else if("11520" == rate) return BaudRate::BR_115200;

    TRACE(TraceLevel::Warning, "unsupported rate, ", rate);

    return BaudRate::BR_19200;
}

Modbus::SerialPort::Parity toParity(const std::string &parity)
{
    using Parity = Modbus::SerialPort::Parity;

    if("N" == parity) return Parity::None;
    else if("O" == parity) return Parity::Odd;
    else if("E" == parity) return Parity::Even;

    TRACE(TraceLevel::Warning, "unsupported parity, ", parity);

    return Parity::Even;
}

int main(int argc, char *argv[])
{
    std::string device, iname, oname, rate = "19200", parity = "Even";

    for(int c; -1 != (c = ::getopt(argc, argv, "hd:i:o:r:p:"));)
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
            case 'r':
                rate = optarg ? optarg : "";
                break;
            case 'p':
                parity = optarg ? optarg : "";
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

        if("-" == iname) std::cin >> input;
        else std::ifstream(iname) >> input;

        ENSURE(input.is_array(), RuntimeError);

        Modbus::RTU::Master master
        {
            device.c_str(),
            toBaudRate(rate),
            toParity(parity),
            Modbus::SerialPort::DataBits::Eight,
            Modbus::SerialPort::StopBits::One
        };

        for(const auto &i : input)
        {
            Modbus::RTU::JSON::dispatch(master, i, output);
            /* (silent interval) at least 3.5t character delay ~ 1750us @ 19200bps */
            std::this_thread::sleep_for(std::chrono::microseconds(1750 * 19200/9600));
        }

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
