# ModbusBridge

## Overview

ModbusBridge (`mbridge`) is a simple cross-platform (Windows, Linux) Modbus converter application
that provides interconvertion between different types of Modbus protocol: `TCP`, `RTU`, `ASC`.

It can be used, for instance, in Raspberry Pi computer to act as Modbus converter.

It's free and open source software based on `ModbusLib` project:

https://github.com/serhmarch/ModbusLib

Application implements such Modbus functions as:
* `1`  (`0x01`) - `READ_COILS`
* `2`  (`0x02`) - `READ_DISCRETE_INPUTS`
* `3`  (`0x03`) - `READ_HOLDING_REGISTERS`
* `4`  (`0x04`) - `READ_INPUT_REGISTERS`
* `5`  (`0x05`) - `WRITE_SINGLE_COIL`
* `6`  (`0x06`) - `WRITE_SINGLE_REGISTER`
* `7`  (`0x07`) - `READ_EXCEPTION_STATUS`
* `8`  (`0x08`) - `DIAGNOSTICS`
* `11` (`0x0B`) - `GET_COMM_EVENT_COUNTER`
* `12` (`0x0C`) - `GET_COMM_EVENT_LOG`
* `15` (`0x0F`) - `WRITE_MULTIPLE_COILS`
* `16` (`0x10`) - `WRITE_MULTIPLE_REGISTERS`
* `17` (`0x11`) - `REPORT_SERVER_ID`
* `22` (`0x16`) - `MASK_WRITE_REGISTER`
* `23` (`0x17`) - `READ_WRITE_MULTIPLE_REGISTERS`
* `24` (`0x18`) - `READ_FIFO_QUEUE`

## Using mbridge

To show list of available parameters print:
```console
$ mbridge -help
Usage: mbridge -ctype <type> [-coptions] -stype <type> [-soptions]

Options (-c client, -s server):
  -help (-?) - show this help.
  -c<param>  - param for client.
  -s<param>  - param for server.

Params <param> for client (-c) and server (-s):
  * type (t) <type> - protocol type. Can be TCP, RTU or ASC (mandatory)
  * host (h) <host> - remote TCP host name (localhost is default)
  * port (p) <port> - remote TCP port (502 is default)
  * tm <timeout>    - timeout for TCP (millisec, default is 3000)
  * serial (sl)     - serial port name for RTU and ASC
  * baud (b)        - baud rate (for RTU and ASC) (default is 9600)
  * data (d)        - data bits (5-8, for RTU and ASC, default is 8)
  * parity          - parity: E (even), O (odd), N (none) (default is none)
  * stop (s)        - stop bits: 1, 1.5, 2 (default is 1)
  * tfb <timeout>   - timeout first byte for RTU or ASC (millisec, default is 3000)
  * tib <timeout>   - timeout inter byte for RTU or ASC (millisec, default is 50)

Examples:
  mbridge -stype TCP -ctype RTU -cserial COM6
  mbridge -stype RTU -sserial /dev/ttyUSB0 -sbaud 19200 -ctype TCP -chost some.plc
```

Next example makes Modbus bridge with RTU client part and TCP server part works on TCP port 502:
```console
> mbridge -stype TCP -ctype RTU -cserial COM6
RTU:Client parameters:
----------------------
port   = COM6
baud   = 9600
data   = 8
parity = No
stop   = 1
flow   = No
tfb    = 1000
tib    = 50

TCP:Server parameters:
----------------------
port    = 502
timeout = 3000

mbridge starts ...
New connection: DESKTOP-TNLLA10:7512
DESKTOP-TNLLA10:7512 Rx: 00 01 00 00 00 06 01 04 00 00 00 04
RTU:Client Tx: 01 04 00 00 00 04 F1 C9
RTU:Client Rx: 01 04 08 00 00 00 00 00 00 00 00 24 0D
DESKTOP-TNLLA10:7512 Tx: 00 01 00 00 00 0B 01 04 08 00 00 00 00 00 00 00 00
...
DESKTOP-TNLLA10:7512 Rx: 00 05 00 00 00 06 01 04 00 00 00 04
RTU:Client Tx: 01 04 00 00 00 04 F1 C9
RTU:Client Rx: 01 04 08 00 00 00 00 00 00 00 00 24 0D
DESKTOP-TNLLA10:7512 Tx: 00 05 00 00 00 0B 01 04 08 00 00 00 00 00 00 00 00
Close connection: DESKTOP-TNLLA10:7512
mbridge stopped
```

## Build using CMake

1.  Build Tools

    Previously you need to install c++ compiler kit, git and cmake itself.
    Then set PATH env variable to find compliler, cmake, git etc.

2.  Create project directory, move to it and clone repository:
    ```console
    $ cd ~
    $ mkdir src
    $ cd src
    $ git clone --recursive https://github.com/serhmarch/ModbusBridge.git
    ```

3.  Create and/or move to directory for build output, e.g. `~/bin/ModbusBridge`:
    ```console
    $ cd ~
    $ mkdir -p bin/ModbusBridge
    $ cd bin/ModbusBridge
    ```

4.  Run cmake to generate project (make) files.
    ```console
    $ cmake -S ~/src/ModbusBridge -B .
    ```

5.  Make binaries (+ debug|release config):
    ```console
    $ cmake --build .
    $ cmake --build . --config Debug
    $ cmake --build . --config Release
    ```    
    
6.  Resulting bin files is located in `./bin` directory.
