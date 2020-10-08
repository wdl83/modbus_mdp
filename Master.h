#pragma once


#include <chrono>
#include <cstdint>
#include <cstdlib>
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

    void wrRegister(Addr slaveAddr, uint16_t memAddr, uint16_t data, mSecs timeout);
    void wrRegisters(Addr slaveAddr, uint16_t memAddr, const DataSeq &data, mSecs timeout);
    DataSeq rdRegisters(Addr slaveAddr, uint16_t memAddr, uint8_t count, mSecs timeout);
    void wrBytes(Addr slaveAddr, uint16_t memAddr, const ByteSeq &data, mSecs timeout);
    ByteSeq rdBytes(Addr slaveAddr, uint16_t memAddr, uint8_t count, mSecs timeout);
};

} /* RTU */
} /* Modbus */
