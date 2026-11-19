# ESP32-cam

This codebase defines 'robot cam' firmware for the XIAO ESP32-S3 Camera+microphone PCB.

## Persistent Configuration

This codebase has a lightweight nonvolatile settings interface which saves key settings to flash. This includes:

- DARTT Serial Address
- WiFi SSID
- WiFi Password
- TCP port (for configuration changes)
- Camera port (UDP)
- Camera port (TCP)
- Audio port (UDP)

The flash memory storage location should be fixed, starting at the last page of memory. On startup, it should load from that fixed location. If it is empty (i.e. all settings are at their flash/erase value), it should be written with the default settings, which are defined with a `default` instance of the nonvolatile settings typedef struct.

All nonvolatile settings should be wrapped in a typedef struct. On startup, after the initial default write, the `fds_load` function will load the contents of the nonvolatile settings into a global struct which is a member variable of the parent global DARTT struct. 



## Dartt

The nonvolatile settings can be modified over DARTT, either over a TCP connection (`TYPE_ADDR_CRC_MESSAGE`) or serial (`TYPE_SERIAL_MESSAGE`).

``` C
typedef struct dartt_map_t
{
	fds_settings_t fds;
	uint32_t action_register;
	uint32_t action_key;	//when this is nonzero and matches the action regsiter value, fire an enumerated action (flash write, etc.)
	//uint32_t camera_buffer[...]	//tbd whether this is feasible
}dartt_map_t;
```

It may be possible to stream camera data over DARTT, by simply dumping the raw camera buffer into 

Claude: Query the user for example DARTT projects that indicate how this wiring should look.

## Serial

Serial (UART) should be on the main (USB C connector) UART port of the ESP32. It should use COBS (from external/byte-stuffing/C-COBS) for multi-byte framing. It should use a DMA handler. An example STM32 DMA handler can be found at https://github.com/Ocanath/stm32-dma-cobs-uart - if possible the ESP32 should match this behvaior

## Networked Camera Stream

The camera data should be accessible to the parent project (mjpeg streamer compatible) https://github.com/Ocanath/stm32-dma-cobs-uart. It is acceptable for the parent project to change its parsing logic in order to be compatible with the ESP32 cam.


## Project Plan

- First, create boilerplate for the ESP32 IDF with all necessary dependencies linked. The main() should have a blinky program running.
- Next, wire serial. Determine whether live expressions are supported or serial step debugging...

