#include <unistd.h>

#include "mdp/Worker.h"
#include "json.h"


void help(const char *argv0, const char *message = nullptr)
{
    if(message) std::cout << "WARNING: " << message << '\n';

    std::cout
        << argv0
        << " -a broker_address -d device"
        << std::endl;
}

int main(int argc, char *const argv[])
{
    std::string
        address,
        device,
        service,
        rate = "19200",
        parity = "E";

    for(int c; -1 != (c = ::getopt(argc, argv, "ha:d:s:r:p:"));)
    {
        switch(c)
        {
            case 'h':
                help(argv[0]);
                return EXIT_SUCCESS;
                break;
            case 'a':
                address = optarg ? optarg : "";
                break;
            case 'd':
                device = optarg ? optarg : "";
                break;
            case 's':
                service = optarg ? optarg : "";
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

    if(address.empty() || device.empty())
    {
        help(argv[0], "missing required arguments");
        return EXIT_FAILURE;
    }

    if(service.empty()) service = "modbus_master_" + device;

    try
    {
        Modbus::RTU::Master master
        {
            device.c_str(),
            Modbus::toBaudRate(rate),
            Modbus::toParity(parity),
            Modbus::SerialPort::DataBits::Eight,
            Modbus::SerialPort::StopBits::One
        };

        Worker{}.exec(
            address,
            service,
            [&master](zmqpp::message message)
            {
                using json = Modbus::RTU::JSON::json;
                json output;

                for(auto i = 0u; i < message.parts(); ++i)
                {
                    auto input = json::parse(message.get<std::string>(i));

                    TRACE(TraceLevel::Info, input.dump());

                    ENSURE(input.is_array(), RuntimeError);

                    for(const auto &object : input)
                    {
                        ENSURE(object.is_object(), RuntimeError);
                        Modbus::RTU::JSON::dispatch(master, object, output);
                    }
                }

                //std::cout << " OUTOUT " << output.dump(2) << std::endl;
                return MDP::makeMessage(output.dump());
            });
    }
    catch(const std::exception &except)
    {
        TRACE(TraceLevel::Error, "std exception ", except.what());
        return EXIT_FAILURE;
    }
    catch(...)
    {
        TRACE(TraceLevel::Error, "unsupported exception");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
