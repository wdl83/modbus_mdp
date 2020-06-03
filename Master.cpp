#include "Master.h"


namespace Modbus {
namespace RTU {

const auto gDebug = nullptr != ::getenv("DEBUG");

Master::Master(
    const char *device,
    BaudRate baudRate,
    Parity parity,
    DataBits dataBits,
    StopBits stopBits)
{
    context_ =
        modbus_new_rtu(
            device,
            int(baudRate),
            char(parity),
            int(dataBits),
            int(stopBits));

    ENSURE(context_, ModbusRuntimeError);
    ENSURE(0 == modbus_rtu_set_rts(context_, MODBUS_RTU_RTS_NONE), ModbusRuntimeError);
    ENSURE(0 == modbus_set_debug(context_, gDebug), ModbusRuntimeError);
    /* no inter-character delay required */
    modbus_set_byte_timeout(context_, 0, 0);
    modbus_set_error_recovery(context_, MODBUS_ERROR_RECOVERY_LINK);
    ENSURE(0 == modbus_connect(context_), ModbusRuntimeError);
}

Master::~Master()
{
    if(context_)
    {
        modbus_free(context_);
        context_ = nullptr;
    }
}

void Master::setup(Addr addr, uSecs timeout)
{
    using namespace std::chrono;

    ENSURE(microseconds{0} <= timeout, RuntimeError);

    const auto timeout_s = duration_cast<seconds>(timeout);
    const auto timeout_us = timeout - duration_cast<microseconds>(timeout_s);

    ENSURE(std::numeric_limits<uint32_t>::max() > timeout_s.count(), RuntimeError);
    ENSURE(1000000 > timeout_us.count(), RuntimeError);

    modbus_set_slave(context_, addr.value);
    modbus_set_response_timeout(context_, timeout_s.count(), timeout_us.count());
}

auto Master::rd_n16(uint16_t addr, uint8_t count) -> DataSeq
{
    ENSURE(0 < count, RuntimeError);
    ENSURE(0x7E > count, RuntimeError);

    std::vector<uint16_t> data(count, 0);

    ENSURE(
        count == modbus_read_registers(context_, addr, count, data.data()),
        ModbusRuntimeError);
    return data;
}

void Master::wr16(uint16_t addr, uint16_t data)
{
    ENSURE(
        1 == modbus_write_register(context_, addr, data),
        ModbusRuntimeError);
}

void Master::wr_n16(uint16_t addr, const std::vector<uint16_t> &data)
{
    if(data.empty()) return;

    ENSURE(
        int(data.size()) == modbus_write_registers(context_, addr, data.size(), data.data()),
        ModbusRuntimeError);
}

} /* RTU */
} /* Modbus */
