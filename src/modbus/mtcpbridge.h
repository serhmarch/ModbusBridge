#ifndef MTCPBRIDGE_H
#define MTCPBRIDGE_H

#include <ModbusTcpServer.h>

class ModbusClientPort;

class mTcpBridge : public ModbusTcpServer
{
public:
    mTcpBridge(ModbusClientPort *clientPort);
    ~mTcpBridge();
    
public:
    ModbusServerPort *createTcpPort(ModbusTcpSocket *socket) override;
    void deleteTcpPort(ModbusServerPort *port) override;

private:
    ModbusClientPort *m_clientPort;
};

#endif // MTCPBRIDGE_H