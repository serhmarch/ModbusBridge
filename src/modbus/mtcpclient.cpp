#include "mtcpclient.h"

#include <ModbusClientPort.h>

mTcpClient::mTcpClient(ModbusClientPort *clientPort) : ModbusObject(),
    m_clientPort(clientPort)
{
    setObjectName(m_clientPort->objectName());
}

Modbus::StatusCode mTcpClient::readCoils(uint8_t unit, uint16_t offset, uint16_t count, void *values)
{
    return m_clientPort->readCoils(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::readDiscreteInputs(uint8_t unit, uint16_t offset, uint16_t count, void *values)
{
    return m_clientPort->readDiscreteInputs(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::readHoldingRegisters(uint8_t unit, uint16_t offset, uint16_t count, uint16_t *values)
{
    return m_clientPort->readHoldingRegisters(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::readInputRegisters(uint8_t unit, uint16_t offset, uint16_t count, uint16_t *values)
{
    return m_clientPort->readInputRegisters(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::writeSingleCoil(uint8_t unit, uint16_t offset, bool value)
{
    return m_clientPort->writeSingleCoil(this, unit, offset, value);
}

Modbus::StatusCode mTcpClient::writeSingleRegister(uint8_t unit, uint16_t offset, uint16_t value)
{
    return m_clientPort->writeSingleRegister(this, unit, offset, value);
}

Modbus::StatusCode mTcpClient::readExceptionStatus(uint8_t unit, uint8_t *status)
{
    return m_clientPort->readExceptionStatus(this, unit, status);
}

Modbus::StatusCode mTcpClient::diagnostics(uint8_t unit, uint16_t subfunc, uint8_t insize, const uint8_t *indata, uint8_t *outsize, uint8_t *outdata)
{
    return m_clientPort->diagnostics(this, unit, subfunc, insize, indata, outsize, outdata);
}

Modbus::StatusCode mTcpClient::getCommEventCounter(uint8_t unit, uint16_t *status, uint16_t *eventCount)
{
    return m_clientPort->getCommEventCounter(this, unit, status, eventCount);
}

Modbus::StatusCode mTcpClient::getCommEventLog(uint8_t unit, uint16_t *status, uint16_t *eventCount, uint16_t *messageCount, uint8_t *eventBuffSize, uint8_t *eventBuff)
{
    return m_clientPort->getCommEventLog(this, unit, status, eventCount, messageCount, eventBuffSize, eventBuff);
}

Modbus::StatusCode mTcpClient::writeMultipleCoils(uint8_t unit, uint16_t offset, uint16_t count, const void *values)
{
    return m_clientPort->writeMultipleCoils(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::writeMultipleRegisters(uint8_t unit, uint16_t offset, uint16_t count, const uint16_t *values)
{
    return m_clientPort->writeMultipleRegisters(this, unit, offset, count, values);
}

Modbus::StatusCode mTcpClient::reportServerID(uint8_t unit, uint8_t *count, uint8_t *data)
{
    return m_clientPort->reportServerID(this, unit, count, data);
}

Modbus::StatusCode mTcpClient::maskWriteRegister(uint8_t unit, uint16_t offset, uint16_t andMask, uint16_t orMask)
{
    return m_clientPort->maskWriteRegister(this, unit, offset, andMask, orMask);
}

Modbus::StatusCode mTcpClient::readWriteMultipleRegisters(uint8_t unit, uint16_t readOffset, uint16_t readCount, uint16_t *readValues, uint16_t writeOffset, uint16_t writeCount, const uint16_t *writeValues)
{
    return m_clientPort->readWriteMultipleRegisters(this, unit, readOffset, readCount, readValues, writeOffset, writeCount, writeValues);
}

Modbus::StatusCode mTcpClient::readFIFOQueue(uint8_t unit, uint16_t fifoadr, uint16_t *count, uint16_t *values)
{
    return m_clientPort->readFIFOQueue(this, unit, fifoadr, count, values);
}
