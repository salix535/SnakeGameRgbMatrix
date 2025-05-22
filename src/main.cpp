#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <config.h>
#include <types.h>
#include "snake.h"
#include <game_state.h>
#include <input_task.h>
#include <deque>
#include <vector>
#include <random>
#include "random_pixel.h"

#define REFRESH_INTERVAL 50

HUB75_I2S_CFG panel_config(
    PANEL_RES_X,
    PANEL_RES_Y,
    PANEL_CHAIN);

Direction current_direction;

MatrixPanel_I2S_DMA *matrix_panel = nullptr;
Snake snake;
std::unordered_set<Pixel> free_pixels;
Pixel apple;

void draw_apple()
{
  matrix_panel->drawPixelRGB888(apple.x, apple.y, 0, 255, 0);
}

void draw_initial_pixels()
{
  for (Pixel p : snake.get_pixels())
  {
    matrix_panel->drawPixelRGB888(p.x, p.y, 255, 0, 0);
  }
  draw_apple();
}

void draw_pixels()
{
  Pixel head = snake.get_pixels().front();
  matrix_panel->drawPixelRGB888(head.x, head.y, 255, 0, 0);
  Pixel tail = snake.get_pixel_to_remove();
  matrix_panel->drawPixelRGB888(tail.x, tail.y, 0, 0, 0);
  draw_apple();
}

void game_over_sequence() {
    matrix_panel->clearScreen();
    matrix_panel->setCursor(20, 20);
    matrix_panel->println("Game Over!");
    matrix_panel->flush();
    delay(10000);
    reinitialise();
}

void reinitialise()
{
  for (int i = 0; i < PANEL_RES_X; i++)
  {
    for (int j = 0; j < PANEL_RES_Y; j++)
    {
      Pixel p = Pixel(i, j);
      free_pixels.insert(p);
    }
  }
  matrix_panel->clearScreen();
  snake = Snake();
  for(Pixel p: snake.get_pixels()) {
    free_pixels.erase(p);
  }
  current_direction = Direction::Right;
  apple = get_random_free_pixel(free_pixels);
  draw_initial_pixels();
}

void setup()
{
  panel_config.gpio.r1 = R1_PIN;
  panel_config.gpio.g1 = G1_PIN;
  panel_config.gpio.b1 = B1_PIN;
  panel_config.gpio.r2 = R2_PIN;
  panel_config.gpio.g2 = G2_PIN;
  panel_config.gpio.b2 = B2_PIN;
  panel_config.gpio.a = A_PIN;
  panel_config.gpio.b = B_PIN;
  panel_config.gpio.c = C_PIN;
  panel_config.gpio.d = D_PIN;
  panel_config.gpio.e = E_PIN;
  panel_config.gpio.lat = LAT_PIN;
  panel_config.gpio.oe = OE_PIN;
  panel_config.gpio.clk = CLK_PIN;

  panel_config.clkphase = false;
  panel_config.driver = HUB75_I2S_CFG::FM6124;

  // Display Setup
  matrix_panel = new MatrixPanel_I2S_DMA(panel_config);
  matrix_panel->begin();
  matrix_panel->setBrightness8(150);
  matrix_panel->clearScreen();
  matrix_panel->fillScreenRGB888(0, 0, 0);
  reinitialise();

  xTaskCreatePinnedToCore(
      serialInputTask,   // Task function
      "SerialInputTask", // Name
      4096,              // Stack size
      NULL,              // Param
      1,                 // Priority
      NULL,              // Handle
      0                  // Core (0 or 1)
  );
  Serial.begin(115200);
}

void loop()
{
  MoveResult move_result = snake.move_snake(current_direction, apple);
  if (move_result.new_head == Pixel(-1, -1))
  {
    game_over_sequence();
  }
  else
  {
    free_pixels.erase(move_result.new_head);
    free_pixels.insert(snake.get_pixel_to_remove());
    if (move_result.ate_apple) {
      apple = get_random_free_pixel(free_pixels);
    }
    draw_pixels();
  }
  delay(REFRESH_INTERVAL);
}
