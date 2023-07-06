#Plot test
import matplotlib.pyplot as plt
import serial

ser = serial.Serial("COM3", 9600) 
ser.write(b'g') 

x = [1,2,3,4,5]
y = [1,4,9,16,25]

plt.plot(x,y)
plt.show()
