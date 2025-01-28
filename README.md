# ModbusBridge

## Overview

ModbusBridge (`mbridge`) is a free, open-source Modbus bridge application written in C++. 
It provides convertion between different type of Modbus protocol: `TCP`, `RTU`, `ASC`.

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
$ mbridge -h
Bad option: h
Usage: mbridge [options]

Options (-c client, -s server):
  -help (-?) - show this help.
  -c<param>  - param for client.
  -s<param>  - param for server.

Params <param> for client (-c) and server (-s):
  * type (t) <type> - protocol type. Can be TCP, RTU or ASC (default is TCP)
  * host (h) <host> - remote TCP host name (localhost is default)
  * port (p) <port> - remote TCP port (502 is default)
  * tm <timeout>    - timeout for TCP (millisec, default is 3000)
  * serial (sl)     - serial port name for RTU and ASC
  * baud (b)        - baud rate (for RTU and ASC)
  * data (d)        - data bits (5-8, for RTU and ASC)
  * parity          - parity: E (even), O (odd), N (none) (default is none)
  * stop (s)        - stop bits: 1, 1.5, 2
  * tfb <timeout>   - timeout first byte for RTU or ASC (millisec, default is 3000)
  * tib <timeout>   - timeout inter byte for RTU or ASC (millisec, default is 5)
```

## Build using CMake

1.  Build Tools

    Previously you need to install c++ compiler kit, git and cmake itself (qt tools if needed).
    Then set PATH env variable to find compliler, cmake, git etc.

2.  Create project directory, move to it and clone repository:
    ```console
    $ cd ~
    $ mkdir src
    $ cd src
    $ git clone https://github.com/serhmarch/ModbusBridge.git
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
