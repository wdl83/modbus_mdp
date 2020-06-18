#include <cstdint>

namespace Modbus {
namespace RTU {

struct CRC
{
    uint16_t value;

    CRC(): value{0xFFFF} {}
    CRC(uint16_t v): value{v} {}
    CRC(uint8_t high, uint8_t low): value((high << 8) | low) {}
};

static_assert(sizeof(uint16_t) == sizeof(CRC), "CRC must not be padded");

CRC calcCRC(const uint8_t *begin, const uint8_t *end);

} /* RTU */
} /* Modbus */
