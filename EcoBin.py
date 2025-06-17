'''Devshree Mistry 					Prediction Code                
'''

# importing the needed modules 
from keras.models import load_model #used to integrate the model from teachable machine
import cv2  #cam
import numpy as np #helps with resizing
import serial #method of communication with arduino
import time #helps give the program a steady pace to execute at


# disables scientific notation for clarity
+np.set_printoptions(suppress=True)

# the path below is the path to the classification model 
model = load_model("C:\\Users\\mistr\\Downloads\\converted_keras (5)\\keras_model.h5", compile=False)

# the path below is the path to the model labels 
class_names = open("C:\\Users\\mistr\\Downloads\\converted_keras (5)\\labels.txt", "r").readlines()



camera = cv2.VideoCapture(1,cv2.CAP_DSHOW) #opens camera
print('opened') #shows that the camera has been opened
time.sleep(2) #time.sleep to ensure program does not move too hastily and face corrupt occassions


ret, image = camera.read() #ret shows whether aframe is available or not, whilst image is the image vector array/frame

if image is None:
    print('error!')
    #continue

# resizes the raw image into (224-height,224-width) pixels
image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)

# shows the image in a window
cv2.imshow("Webcam Image", image)

# makes the image a numpy array and reshape it to the models input shape 
image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)

# normalizes the image array
image = (image / 127.5) - 1 

# predicts
prediction = model.predict(image)
index = np.argmax(prediction)
class_name = class_names[index]
confidence_score = prediction[0][index]

# prints prediction and confidence score 
print("Class:", class_name[2:], end="")
print("Confidence Score:", str(np.round(confidence_score * 100))[:-2], "%")
print('The class name is',class_name)

arduino_port = 'COM3'
baud_rate = 115200   #speed

# opens a serial connection
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

time.sleep(3)
print('reached the point of successsful connection')

#the following utilizes serial communication in order to give the arduino the proper signal to direct the trash
if 'non' in class_name:
    print('shakira')
    ser.write(b'2')  # Send '1' as a byte
else:
    ser.write(b'0')
    time.sleep(2)



ser.close()


camera.release()
cv2.destroyAllWindows()



