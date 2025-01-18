#include "mtcpbridge.h"

#include "mtcpclient.h"

mTcpBridge::mTcpBridge(ModbusClientPort *clientPort) : ModbusTcpServer(static_cast<ModbusInterface*>(nullptr)),
    m_clientPort(clientPort)
{
}

mTcpBridge::~mTcpBridge()
{
    clearConnections();
}

ModbusServerPort *mTcpBridge::createTcpPort(ModbusTcpSocket *socket)
{
    ModbusServerPort *p = ModbusTcpServer::createTcpPort(socket);
    mTcpClient *c = new mTcpClient(m_clientPort);
    p->setDevice(c);
    return p;
}

void mTcpBridge::deleteTcpPort(ModbusServerPort *port)
{
    mTcpClient *c = static_cast<mTcpClient*>(port->device());
    delete c;
    ModbusTcpServer::deleteTcpPort(port);
}
