'''Devshree Mistry            Main Python Sorter Script Triggerer FINAL
'''

# importing the needed modules 
import serial #used for communication 
import subprocess #used to run another python file
import time

serial_connection = serial.Serial('COM3', 115200 , timeout = 1) #opens the connection
serial_connection.flush() #clears the data within the connection to ensure there is nothing there to stop operation
 
while True:
    if serial_connection.in_waiting > 0: #checks if something is in the connection 
        transmission = serial_connection.readline().decode('utf-8').strip() #translates the bytes into string
        if transmission == 'detected':
            print('Object found at sorting platform, commencing sorting process...')
            serial_connection.close()
            subprocess.run(["python", "C:\\Users\\mistr\\EcoBin.py"]) #takes signal to start the sorting process
            time.sleep(2)
            serial_connection.open()
            serial_connection.flush()
