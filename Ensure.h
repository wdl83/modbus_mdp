#pragma once

#include "mdp/Ensure.h"

#include <modbus/modbus.h>

struct ReportModbusErrNo : public std::runtime_error
{
    ReportModbusErrNo(const std::string &msg):
        std::runtime_error{std::string{::modbus_strerror(errno)} + " at " + msg}
    {}
};

using ModbusRuntimeError = Exception<ReportModbusErrNo>;
