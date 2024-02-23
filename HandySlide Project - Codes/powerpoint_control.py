# Python Code - MAIN
import os
import sys
import time
import serial.tools.list_ports
import serial
import pyautogui

ports = serial.tools.list_ports.comports(include_links=False)
for port in ports :
    print('Find port '+ port.device)

ser = serial.Serial(port.device)
if ser.isOpen():
    ser.close()

ser = serial.Serial(port.device, 9600, timeout=1)
ser.flushInput()
ser.flushOutput()
print('Connect ' + ser.name)

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
