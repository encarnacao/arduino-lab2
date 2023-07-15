import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def animate(i,x,y,ser):
  ser.write(b'g')                                     # Transmit the char 'g' to receive the Arduino data point
  arduinoData_string = ser.readline().decode('ascii') # Decode receive Arduino data as a formatted string
  x_string, y_string = arduinoData_string.split(',')   # Split the string into x and y components
  #print(i)                                           # 'i' is a incrementing variable based upon frames = x argument

  try:
    x_data = float(x_string)
    y_data = float(y_string)
    if y_data > 400: # Ignora flutuações esquisitas
      y_data = y[-1]
    if x_data > 400:
      x_data = x[-1]
    x.append(x_data)
    y.append(y_data)              # Add to the list holding the fixed number of points to animate

  except:                                             # Pass if data point is bad                               
    pass

  x = x[-50:] 
  y = y[-50:]                          # Fix the list size so that the animation plot 'window' is x number of points
  
  ax.clear()                                          # Clear last data frame
  ax.plot(x,y)                                   # Plot new data frame
  
  ax.set_ylim(bottom=-100, top=100)                     # Set Y axis limit of plot
  ax.set_title("Arduino Data")                        # Set title of figure
  ax.set_ylabel("y (cm)")                              # Set title of y axis
  ax.set_xlabel("x (cm)")                              # Set title of x axis 

x = []
y = []                                           # Create empty list variable for later use
                                                        
fig = plt.figure()                                      # Create Matplotlib plots fig is the 'higher level' plot window
ax = fig.add_subplot(111)                               # Add subplot to main fig window

ser = serial.Serial("COM3", 9600)                       # Establish Serial object with COM port and BAUD rate to match Arduino Port/rate
time.sleep(2)                                           # Time delay for Arduino Serial initialization 

                                                        # Matplotlib Animation Fuction that takes takes care of real time plot.
                                                        # Note that 'fargs' parameter is where we pass in our dataList and Serial object. 
ani = animation.FuncAnimation(fig, animate, frames=100, fargs=(x,y, ser), interval=100) 

plt.show()                                              # Keep Matplotlib plot persistent on screen until it is closed
fig.savefig('plot-trajectory.png')                                 
ser.write(b'f')
ser.close()                                             # Close Serial connection when plot is closed

