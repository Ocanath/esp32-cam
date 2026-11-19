# Flashing cheat sheet (XIAO ESP32-S3 Sense)

## One-time setup

```bash
sudo usermod -aG dialout $USER   # serial permission; log out/in afterwards
```

## Every terminal session

```bash
source ~/.espressif/tools/activate_idf_v6.1.sh   # puts idf.py on PATH
cd esp32-cam
```

## Commands

| Task | Command |
|------|---------|
| Build only | `idf.py build` |
| Flash + open log | `idf.py -p /dev/ttyACM0 flash monitor` |
| Flash only | `idf.py -p /dev/ttyACM0 flash` |
| Log only | `idf.py -p /dev/ttyACM0 monitor` (exit: `Ctrl+]`) |
| Settings menu | `idf.py menuconfig` |
| Wipe build | `idf.py fullclean` |
| Change target | `idf.py set-target esp32s3` |

First build needs network (downloads `espressif/esp32-camera` into `managed_components/`).

## Find the port

```bash
ls /dev/ttyACM*
```

Native USB: the port vanishes and reappears on every reset, and the name can change (`ttyACM0` -> `ttyACM1`).

## Won't connect? Force bootloader mode

1. Hold **B** (boot).
2. Tap **R** (reset), or replug USB while holding B.
3. Release B, re-run the flash command.
4. Press **R** once afterwards to start the program.

## Troubleshooting

- `idf.py: command not found` -> forgot the `source ...activate_idf_v6.1.sh` step.
- `Permission denied` on the port -> dialout group (see above), or `sudo chmod a+rw /dev/ttyACM0`.
- No `/dev/ttyACM*` at all -> charge-only USB cable, or board needs bootloader mode.
- `camera init failed` (later, once camera is enabled) -> PSRAM not enabled; check `sdkconfig.defaults` was applied (delete `sdkconfig`, re-run `set-target`).
- Config changes ignored -> `sdkconfig` overrides `sdkconfig.defaults`; delete `sdkconfig` and rebuild.

## Expected result (blinky)

User LED blinks ~1 Hz; monitor prints `linked symbol N @ 0x...` lines. Blink GPIO/period: `menuconfig` -> Robot Cam.
