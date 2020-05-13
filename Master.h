#pragma once


#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include <modbus/modbus.h>

#include "Ensure.h"

namespace Modbus {
namespace RTU {

enum class BaudRate
{
    BR_19200 = 19200
};

enum class Parity : char {None = 'N', Odd = 'O', Even = 'E'};
enum class DataBits {Five = 5, Six = 6, Seven = 7, Eight = 8};
enum class StopBits {One = 1, Two = 2};

struct Addr
{
    uint8_t value;
    Addr(uint8_t addr): value{addr}
    {}
};

using uSecs = std::chrono::microseconds;
using mSecs = std::chrono::milliseconds;

class Master
{
    modbus_t *context_ = nullptr;
public:
    using DataSeq = std::vector<uint16_t>;

    Master(
        const char *device,
        BaudRate baudRate = BaudRate::BR_19200,
        Parity parity = Parity::Even,
        DataBits dataBits = DataBits::Eight,
        StopBits stopBits = StopBits::One);

    ~Master();

    void wrRegister(Addr slaveAddr, uint16_t memAddr, uint16_t data, uSecs timeout)
    {
        setup(slaveAddr, timeout);
        wr16(memAddr, data);
    }

    void wrRegisters(Addr slaveAddr, uint16_t memAddr, const DataSeq &data, uSecs timeout)
    {
        setup(slaveAddr, timeout);
        wr_n16(memAddr, data);
    }

    DataSeq rdRegisters(Addr slaveAddr, uint16_t memAddr, uint8_t count, uSecs timeout)
    {
        setup(slaveAddr, timeout);
        return rd_n16(memAddr, count);
    }
private:
    void setup(Addr addr, uSecs timeout);
    DataSeq rd_n16(uint16_t addr, uint8_t count);
    void wr16(uint16_t addr, uint16_t data);
    void wr_n16(uint16_t addr, const DataSeq &);
};

} /* RTU */
} /* Modbus */
