#include <stdint.h>
#include <stddef.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* One header per dependency: proves include paths resolve. */
#include "dartt_crc.h"
#include "cobs.h"
#include "bytestream.h"
#include "audio.h"
#include "camera_stream.h"

static const char *TAG = "robot_cam";

/* Take the address of one symbol per library so the linker must resolve it.
 * volatile keeps the compiler from discarding the references. Nothing is called. */
static void *const volatile s_link_check[] = {
    (void *)dartt_crc16,
    (void *)cobs_stream,
    (void *)bytestream,
    (void *)audio_stream,
    (void *)camera_stream_init,
};

void app_main(void)
{
    const gpio_num_t led = (gpio_num_t)CONFIG_ROBOT_CAM_LED_GPIO;
    gpio_reset_pin(led);
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

    /* Reading the table (not calling anything) keeps the references alive. */
    for (size_t i = 0; i < sizeof(s_link_check) / sizeof(s_link_check[0]); i++) {
        ESP_LOGI(TAG, "linked symbol %u @ %p", (unsigned)i, s_link_check[i]);
    }

    int level = 0;
    while (1) {
        gpio_set_level(led, level); /* user LED is active low */
        level = !level;
        vTaskDelay(pdMS_TO_TICKS(CONFIG_ROBOT_CAM_BLINK_MS));
    }
}
