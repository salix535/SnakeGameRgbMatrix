import serial
import keyboard

ser = serial.Serial('COM11', 115200)

print("Use arrow keys to control Snake. Press ESC to exit.")

last_command = "RIGHT"

while True:
    if keyboard.is_pressed("up"):
        if last_command != "UP":
            ser.write(b'U')
            last_command = "UP"
    elif keyboard.is_pressed("down"):
        if last_command != "DOWN":
            ser.write(b'D')
            last_command = "DOWN"
    elif keyboard.is_pressed("right"):
        if last_command != "RIGHT":
            ser.write(b'R')
            last_command = "RIGHT"
    elif keyboard.is_pressed("left"):
        if last_command != "LEFT":
            ser.write(b'L')
            last_command = "LEFT"
    elif keyboard.is_pressed("esc"):
        break