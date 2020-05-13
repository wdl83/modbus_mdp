#include "json.h"

namespace Modbus {
namespace RTU {
namespace JSON {

const char *const SLAVE = "slave";
const char *const FCODE = "fcode";
const char *const COUNT = "count";
const char *const ADDR = "addr";
const char *const VALUE = "value";
const char *const TIMEOUT_MS = "timeout_ms";

constexpr auto FCODE_RD_HOLDING_REGISTERS = 3;
constexpr auto FCODE_WR_REGISTER = 6;
constexpr auto FCODE_WR_REGISTERS = 16;

template <typename T, typename V>
bool inRange(V value)
{
    return
        std::numeric_limits<T>::min() <= value
        && std::numeric_limits<T>::max() >= value;
}

json rdRegisters(Master &master, Addr slave, mSecs timeout, const json &input)
{
    ENSURE(input.count(ADDR), RuntimeError);
    ENSURE(input[ADDR].is_number(), RuntimeError);

    const auto addr = input[ADDR].get<int>();

    ENSURE(inRange<uint16_t>(addr), RuntimeError);

    ENSURE(input.count(COUNT), RuntimeError);
    ENSURE(input[COUNT].is_number(), RuntimeError);

    const auto count = input[COUNT].get<int>();

    ENSURE(inRange<uint8_t>(count), RuntimeError);

    const auto data = master.rdRegisters(slave, addr, count, timeout);

    return json
    {
        {SLAVE, slave.value},
        {ADDR, addr},
        {COUNT, count},
        {VALUE, data}
    };
}

json wrRegister(Master &master, Addr slave, mSecs timeout, const json &input)
{
    ENSURE(input.count(ADDR), RuntimeError);
    ENSURE(input[ADDR].is_number(), RuntimeError);

    const auto addr = input[ADDR].get<int>();

    ENSURE(inRange<uint16_t>(addr), RuntimeError);

    ENSURE(input.count(VALUE), RuntimeError);

    ENSURE(input[VALUE].is_number(), RuntimeError);

    const auto value = input[VALUE].get<int>();

    ENSURE(inRange<uint8_t>(value), RuntimeError);

    master.wrRegister(slave, addr, value, timeout);

    return json
    {
        {SLAVE, slave.value},
        {ADDR, addr}
    };
}

json wrRegisters(Master &master, Addr slave, mSecs timeout, const json &input)
{
    ENSURE(input.count(ADDR), RuntimeError);
    ENSURE(input[ADDR].is_number(), RuntimeError);

    const auto addr = input[ADDR].get<int>();

    ENSURE(inRange<uint16_t>(addr), RuntimeError);

    ENSURE(input.count(COUNT), RuntimeError);
    ENSURE(input[COUNT].is_number(), RuntimeError);

    const auto count = input[COUNT].get<int>();

    ENSURE(inRange<uint8_t>(count), RuntimeError);

    ENSURE(input.count(VALUE), RuntimeError);

    ENSURE(input[VALUE].is_array(), RuntimeError);

    const auto value = input[VALUE].get<std::vector<int>>();

    ENSURE(int(value.size()) == count, RuntimeError);

    Master::DataSeq seq(std::begin(value), std::end(value));

    master.wrRegisters(slave, addr, seq, timeout);

    return json
    {
        {SLAVE, slave.value},
        {ADDR, addr},
        {COUNT, count}
    };
}

void dispatch(Master &master, const json &input, json &output)
{
    ENSURE(input.count(SLAVE), RuntimeError);
    ENSURE(input[SLAVE].is_number(), RuntimeError);

    const auto slave = input[SLAVE].get<int>();

    ENSURE(inRange<uint8_t>(slave), RuntimeError);

    /* default timeout */
    mSecs timeout{200};

    if(input.count(TIMEOUT_MS))
    {
        /* if timeout in milliseconds is provided - use it */
        ENSURE(input[TIMEOUT_MS].is_number(), RuntimeError);

        const int timeout_ms = input[TIMEOUT_MS].get<int>();

        ENSURE(0 < timeout_ms, RuntimeError);

        timeout = mSecs{timeout_ms};
    }

    ENSURE(input.count(FCODE), RuntimeError);
    ENSURE(input[FCODE].is_number(), RuntimeError);

    const auto fcode = input[FCODE].get<int>();

    ENSURE(
        FCODE_RD_HOLDING_REGISTERS == fcode
        || FCODE_WR_REGISTER == fcode
        || FCODE_WR_REGISTERS == fcode,
        RuntimeError);

    switch(fcode)
    {
        case FCODE_RD_HOLDING_REGISTERS:
        {
            output.push_back(rdRegisters(master, {uint8_t(slave)}, timeout, input));
            break;
        }
        case FCODE_WR_REGISTER:
        {
            output.push_back(wrRegister(master, {uint8_t(slave)}, timeout, input));
            break;
        }
        case FCODE_WR_REGISTERS:
        {
            output.push_back(wrRegisters(master, {uint8_t(slave)}, timeout, input));
            break;
        }
        default:
        {
            ENSURE(false, RuntimeError);
            break;
        }
    }
}

} /* JSON */
} /* RTU */
} /* Modbus */
