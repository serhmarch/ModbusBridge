#include <iostream>
#include <csignal>
#include <vector>
#include <thread>

#include <ModbusServerResource.h>
#include <ModbusClientPort.h>
#include <ModbusTcpPort.h>
#include <ModbusRtuPort.h>
#include <ModbusAscPort.h>

#include "modbus/mtcpbridge.h"
#include "modbus/mtcpclient.h"

const char* help_options =
"Usage: mbridge [options]\n"
"\n"
"Options (-c client, -s server):\n"
"  -help (-?) - show this help.\n"
"  -c<param>  - param for client.\n"
"  -s<param>  - param for server.\n"
"\n"
"Params <param> for client (-c) and server (-s):\n"
"  * type (t) <type> - protocol type. Can be TCP, RTU or ASC (default is TCP)\n"
"  * host (h) <host> - remote TCP host name (localhost is default)\n"
"  * port (p) <port> - remote TCP port (502 is default)\n"
"  * tm <timeout>    - timeout for TCP (millisec, default is 3000)\n"
"  * serial (sl)     - serial port name for RTU and ASC\n"
"  * baud (b)        - baud rate (for RTU and ASC)\n"
"  * data (d)        - data bits (5-8, for RTU and ASC)\n"
"  * parity          - parity: E (even), O (odd), N (none) (default is none)\n"
"  * stop (s)        - stop bits: 1, 1.5, 2\n"
"  * tfb <timeout>   - timeout first byte for RTU or ASC (millisec, default is 3000)\n"
"  * tib <timeout>   - timeout inter byte for RTU or ASC (millisec, default is 50)\n"
;

void printTx(const Modbus::Char *source, const uint8_t* buff, uint16_t size)
{
    std::cout << source << " Tx: " << Modbus::bytesToString(buff, size) << std::endl;
}

void printRx(const Modbus::Char *source, const uint8_t* buff, uint16_t size)
{
    std::cout << source << " Rx: " << Modbus::bytesToString(buff, size) << std::endl;
}

void printTxAsc(const Modbus::Char *source, const uint8_t* buff, uint16_t size)
{
    std::cout << source << " Tx: " << Modbus::asciiToString(buff, size) << std::endl;
}

void printRxAsc(const Modbus::Char *source, const uint8_t* buff, uint16_t size)
{
    std::cout << source << " Rx: " << Modbus::asciiToString(buff, size) << std::endl;
}

void printNewConnection(const Modbus::Char *source)
{
    std::cout << "New connection: " << source << std::endl;
}

void printCloseConnection(const Modbus::Char *source)
{
    std::cout << "Close connection: " << source << std::endl;
}

struct Options
{
    Modbus::ProtocolType   type ;
    Modbus::SerialSettings ser  ;
    Modbus::TcpSettings    tcp  ; 
    Modbus::String sSerialPort;

    Options()
    {
        const ModbusTcpPort::Defaults &dTcp = ModbusTcpPort ::Defaults::instance();
        const ModbusSerialPort::Defaults &dSer = ModbusSerialPort::Defaults::instance();

        type                 = Modbus::TCP               ;
        tcp.host             = dTcp.host                 ;
        tcp.port             = dTcp.port                 ;
        tcp.timeout          = dTcp.timeout              ;
      //ser.portName         = dSer.portName             ;
        ser.baudRate         = dSer.baudRate             ;
        ser.dataBits         = dSer.dataBits             ;
        ser.parity           = dSer.parity               ;
        ser.stopBits         = dSer.stopBits             ;
        ser.flowControl      = dSer.flowControl          ;
        ser.timeoutFirstByte = dSer.timeoutFirstByte     ;
        ser.timeoutInterByte = dSer.timeoutInterByte     ;

        Modbus::List<Modbus::String> ports = Modbus::availableSerialPorts();
        if (ports.size() > 0)
            sSerialPort = *ports.begin();
        else
            sSerialPort = dSer.portName;
        ser.portName = sSerialPort.c_str();
    }
};
Options cliOptions;
Options srvOptions;

void parseOptions(int argc, char **argv)
{
    Options *options;
    for (int i = 1; i < argc; i++)
    {
        char *opt = argv[i];
        if (opt[0] != '-')
        {
            printf("Bad option: %s. Option must have '-' (dash) before its name\n", opt);
            puts(help_options);
            exit(1);
        }
        ++opt; // pass '-' (dash)
        if (!strcmp(opt, "help") || !strcmp(opt, "?"))
        {
            puts(help_options);
            exit(0);
        }
        else if (opt[0] == 'c')
        {
            options = &cliOptions;
            ++opt;
        }
        else if (opt[0] == 's')
        {
            options = &srvOptions;
            ++opt;
        }
        else
        {
            printf("Bad option: %s\n", opt);
            puts(help_options);
            exit(1);
        }
        if (!strcmp(opt, "type") || !strcmp(opt, "t"))
        {
            if (++i < argc)
            {
                char *sOptValue = argv[i];
                if (!strcmp(sOptValue, "TCP"))
                {
                    options->type = Modbus::TCP;
                    continue;
                }
                else if (!strcmp(sOptValue, "RTU"))
                {
                    options->type = Modbus::RTU;
                    continue;
                }
                else if (!strcmp(sOptValue, "ASC"))
                {
                    options->type = Modbus::ASC;
                    continue;
                }
            }
            printf("'-type' option must have a value: TCP, RTU or ASC\n");
            exit(1);
        }
        if (!strcmp(opt, "host") || !strcmp(opt, "h"))
        {
            if (++i < argc)
            {
                options->tcp.host = argv[i];
                continue;
            }
            printf("'-host' option must have a value\n");
            exit(1);
        }
        if (!strcmp(opt, "port") || !strcmp(opt, "p"))
        {
            if (++i < argc)
            {
                options->tcp.port = (uint16_t)atoi(argv[i]);
                continue;
            }
            printf("'-port' option must have a value: 0-65535\n");
            exit(1);
        }
        if (!strcmp(opt, "tm"))
        {
            if (++i < argc)
            {
                options->tcp.timeout = (uint32_t)atoi(argv[i]);
                continue;
            }
            printf("'-tm' option must have an integer value\n");
            exit(1);
        }
        if (!strcmp(opt, "serial") || !strcmp(opt, "sl"))
        {
            if (++i < argc)
            {
                options->ser.portName = argv[i];
                continue;
            }
            printf("'-serial' option must have a value: serial port name like 'COM1' (Windows) or /dev/ttyS0 (Unix) \n");
            exit(1);
        }
        if (!strcmp(opt, "baud") || !strcmp(opt, "b"))
        {
            if (++i < argc)
            {
                options->ser.baudRate = (int)atoi(argv[i]);
                continue;
            }
            printf("'-baud' option must have a value: 1200, 2400, 4800, 9600, 19200, 115200 etc\n");
            exit(1);
        }
        if (!strcmp(opt, "data") || !strcmp(opt, "d"))
        {
            if (++i < argc)
            {
                options->ser.dataBits = (int8_t)atoi(argv[i]);
                continue;
            }
            printf("'-data' option must have a value: 5-8\n");
            exit(1);
        }
        if (!strcmp(opt, "parity"))
        {
            if (++i < argc)
            {
                char *sOptValue = argv[i];
                if (!strcmp(sOptValue, "N") || !strcmp(sOptValue, "no"))
                {
                    options->ser.parity = Modbus::NoParity;
                    continue;
                }
                else if (!strcmp(sOptValue, "E") || !strcmp(sOptValue, "even"))
                {
                    options->ser.parity = Modbus::EvenParity;
                    continue;
                }
                else if (!strcmp(sOptValue, "O") || !strcmp(sOptValue, "odd"))
                {
                    options->ser.parity = Modbus::OddParity;
                    continue;
                }
            }
            printf("'-parity' option must have a value: E (even), O (odd), N (none)\n");
            exit(1);
        }
        if (!strcmp(opt, "stop") || !strcmp(opt, "s"))
        {
            if (++i < argc)
            {
                char *sOptValue = argv[i];
                if (!strcmp(sOptValue, "1"))
                {
                    options->ser.stopBits = Modbus::OneStop;
                    continue;
                }
                else if (!strcmp(sOptValue, "1.5"))
                {
                    options->ser.stopBits = Modbus::OneAndHalfStop;
                    continue;
                }
                else if (!strcmp(sOptValue, "2"))
                {
                    options->ser.stopBits = Modbus::TwoStop;
                    continue;
                }
            }
            printf("'-stop' option must have a value: 1, 1.5 or 2\n");
            exit(1);
        }
        if (!strcmp(opt, "tfb"))
        {
            if (++i < argc)
            {
                options->ser.timeoutFirstByte = (uint32_t)atoi(argv[i]);
                continue;
            }
            printf("'-tfb' option (timeout first byte) must have a value: <integer>\n");
            exit(1);
        }
        if (!strcmp(opt, "tib"))
        {
            if (++i < argc)
            {
                options->ser.timeoutInterByte = (uint32_t)atoi(argv[i]);
                continue;
            }
            printf("'-tfb' option (timeout inter byte) must have a value: <integer>\n");
            exit(1);
        }
        printf("Bad option: %s\n", opt);
        puts(help_options);
        exit(1);
    }
}

volatile bool fRun = true;

void signal_handler(int /*signal*/)
{
    fRun = false;
}

int main(int argc, char **argv)
{
    const bool blocking = false;
    ModbusServerPort *srv;
    ModbusClientPort *cli;

    cliOptions.type = Modbus::RTU;

    parseOptions(argc, argv);

    switch (cliOptions.type)
    {
    case Modbus::RTU:
        cli = Modbus::createClientPort(Modbus::RTU, &cliOptions.ser, blocking);
        cli->setObjectName("RTU:Client");
        cli->connect(&ModbusClientPort::signalTx, printTx);
        cli->connect(&ModbusClientPort::signalRx, printRx);
        std::cout << srv->objectName() << ": " << cliOptions.ser.portName << std::endl;
        break;
    case Modbus::ASC:
        cli = Modbus::createClientPort(Modbus::ASC, &cliOptions.ser, blocking);
        cli->setObjectName("ASC:Client");
        cli->connect(&ModbusClientPort::signalTx, printTxAsc);
        cli->connect(&ModbusClientPort::signalRx, printRxAsc);
        std::cout << srv->objectName() << ": " << cliOptions.ser.portName << std::endl;
        break;
    default:
        cli = Modbus::createClientPort(Modbus::TCP, &cliOptions.tcp, blocking);
        cli->setObjectName("TCP:Client");
        cli->connect(&ModbusClientPort::signalTx, printTx);
        cli->connect(&ModbusClientPort::signalRx, printRx);
        std::cout << srv->objectName() << ": " << cliOptions.tcp.host << ":" << cliOptions.tcp.port << std::endl;
        break;
    }

    switch (srvOptions.type)
    {
    case Modbus::RTU:
        srv = Modbus::createServerPort(cli, Modbus::RTU, &srvOptions.ser, blocking);
        srv->setObjectName("RTU:Server");
        srv->connect(&ModbusServerPort::signalTx, printTx);
        srv->connect(&ModbusServerPort::signalRx, printRx);
        std::cout << srv->objectName() << ": " << cliOptions.ser.portName << std::endl;
        break;
    case Modbus::ASC:
        srv = Modbus::createServerPort(cli, Modbus::ASC, &srvOptions.ser, blocking);
        srv->setObjectName("ASC:Server");
        srv->connect(&ModbusServerPort::signalTx, printTxAsc);
        srv->connect(&ModbusServerPort::signalRx, printRxAsc);
        std::cout << srv->objectName() << ": " << cliOptions.ser.portName << std::endl;
        break;
    default:
    {
        mTcpBridge *tcp = new mTcpBridge(cli);
        tcp->setPort(cliOptions.tcp.port);
        tcp->setTimeout(cliOptions.tcp.timeout);
        srv = tcp;
        srv->setObjectName("TCP:Server");
        srv->connect(&ModbusServerPort::signalTx, printTx);
        srv->connect(&ModbusServerPort::signalRx, printRx);
        srv->connect(&ModbusTcpServer::signalNewConnection, printNewConnection);
        srv->connect(&ModbusTcpServer::signalCloseConnection, printCloseConnection);
        std::cout << srv->objectName() << ": " << cliOptions.tcp.port << std::endl;
    }
        break;
    }

    std::signal(SIGINT, signal_handler);
    std::cout << "mbridge starts ..." << std::endl;
    while (fRun)
    {
        srv->process();
        Modbus::msleep(1);
    }
    delete srv;
    delete cli;
    std::cout << "mbridge stopped" << std::endl;
}
