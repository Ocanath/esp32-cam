idf_component_register(
    SRCS "main.c"
    PRIV_REQUIRES
        vendor_libs
        xiao-esp32-camera-stream
        esp_driver_gpio
        esp_timer
)
