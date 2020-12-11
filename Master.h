#pragma once

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <vector>

#include "Ensure.h"
#include "SerialPort.h"

namespace Modbus {
namespace RTU {

struct Addr
{
    uint8_t value;

    static constexpr uint8_t min = 1;
    static constexpr uint8_t max = 255;

    Addr(uint8_t addr): value{addr}
    {}

    friend
    std::ostream &operator<<(std::ostream &os, Addr addr)
    {
        os << int(addr.value);
        return os;
    }
};

using mSecs = std::chrono::milliseconds;

struct Master
{
    using BaudRate = SerialPort::BaudRate;
    using Parity = SerialPort::Parity;
    using DataBits = SerialPort::DataBits;
    using StopBits = SerialPort::StopBits;
    using DataSeq = std::vector<uint16_t>;
    using ByteSeq = std::vector<uint8_t>;
private:
    std::string devName_;
    BaudRate baudRate_;
    Parity parity_;
    DataBits dataBits_;
    StopBits stopBits_;
    std::unique_ptr<SerialPort> dev_;

    void initDevice();
    void drainDevice();
    uint8_t *readDevice(uint8_t *begin, const uint8_t *const end, mSecs timeout);
    const uint8_t *writeDevice(const uint8_t *begin, const uint8_t *const end, mSecs timeout);
public:
    Master(
        std::string devName,
        BaudRate baudRate = BaudRate::BR_19200,
        Parity parity = Parity::Even,
        DataBits dataBits = DataBits::Eight,
        StopBits stopBits = StopBits::One):
            devName_{std::move(devName)},
            baudRate_{baudRate},
            parity_{parity},
            dataBits_{dataBits},
            stopBits_{stopBits}
    {}

    SerialPort &device();
    void wrRegister(Addr slaveAddr, uint16_t memAddr, uint16_t data, mSecs timeout);
    void wrRegisters(Addr slaveAddr, uint16_t memAddr, const DataSeq &data, mSecs timeout);
    DataSeq rdRegisters(Addr slaveAddr, uint16_t memAddr, uint8_t count, mSecs timeout);
    void wrBytes(Addr slaveAddr, uint16_t memAddr, const ByteSeq &data, mSecs timeout);
    ByteSeq rdBytes(Addr slaveAddr, uint16_t memAddr, uint8_t count, mSecs timeout);
};

} /* RTU */
} /* Modbus */
