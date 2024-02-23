# Python Code - MAIN
import serial
import pyautogui

ser = serial.Serial('COM10', 9600)

while True:
    line = ser.readline().decode('utf-8').strip()

    if line == 'Start Slideshow':
        pyautogui.press('f5')
    elif line == 'End Slideshow':
        pyautogui.press('esc')
    elif line == 'Next Slide':
        pyautogui.press('right')
    elif line == 'Previous Slide':
        pyautogui.press('left')
