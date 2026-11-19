# Wraps the plain-C submodules under external/ as a single ESP-IDF component.
# Their own CMakeLists target host builds, so we compile the sources directly.
set(EXT "${CMAKE_CURRENT_LIST_DIR}/../../external")

idf_component_register(
    SRCS
        "${EXT}/dartt-protocol/src/dartt.c"
        "${EXT}/dartt-protocol/src/dartt_sync.c"
        "${EXT}/dartt-protocol/src/dartt_crc.c"
        "${EXT}/byte-stuffing/C-COBS/cobs.c"
        "${EXT}/byte-stuffing/bytestream/bytestream.c"
        "${EXT}/dartt_audio/embedded/audio.c"
    INCLUDE_DIRS
        "${EXT}/dartt-protocol/src"
        "${EXT}/byte-stuffing/C-COBS"
        "${EXT}/byte-stuffing/bytestream"
        "${EXT}/dartt_audio/embedded"
)
