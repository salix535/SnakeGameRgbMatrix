#include <Arduino.h>
#include <game_state.h>
#include "input_task.h"

void serialInputTask(void *param)
{
    String input = "";
    bool esc_seq = false;

    while (true)
    {
        if (Serial.available())
        {
            char c = Serial.read();

            Direction new_direction = current_direction;

            if (c == 'U')
                new_direction = Direction::Up;
            else if (c == 'D')
                new_direction = Direction::Down;
            else if (c == 'R')
                new_direction = Direction::Right;
            else if (c == 'L')
                new_direction = Direction::Left;

            if (new_direction != get_opposite(current_direction))
            {
                current_direction = new_direction;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
