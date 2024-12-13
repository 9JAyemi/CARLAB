import cv2
from picamera2 import Picamera2
from ultralytics import YOLO
from gpiozero import LED
#from gpiozero import PWMLED
import RPi.GPIO as GPIO
import time

# Initialize the camera
picam2 = Picamera2()
picam2.preview_configuration.main.size = (1280, 1280)
picam2.preview_configuration.main.format = "RGB888"
picam2.preview_configuration.align()
picam2.configure("preview")
picam2.start()

# initialise output pin
output = LED(14)
output2 = LED(15)

#GPIO.setmode(GPIO.BCM)
#GPIO.setup(18, GPIO.OUT)`
#output3 = GPIO.PWM(18, 200)
output3 = LED(18)

outputAR1 = LED(27)
outputAR2 = LED(22)
outputAR3 = LED(23)

#output.start(0)

# Load our YOLOv8 model
model = YOLO("yolov8s-world.pt")

# Define custom classes
model.set_classes(["flag with green fabric", "flag with red fabric", "flag with yellow fabric"])

# List of class IDs we want to detect
objects_to_detect = [0, 1, 2]  # You can modify this list

while True:
    # Capture a frame from the camera
    frame = picam2.capture_array()

    # Run object detection on the frame
    results = model(frame, imgsz = 160)

    # Get the classes of detected objects
    detected_objects = results[0].boxes.cls.tolist()

   
   
   
    # Control the Pin based on detection
    if 0 in detected_objects:
        output.on()  # Turn on Pin
        outputAR1.on()
        print("GPIO14 (Green Flag) turned on!")
        # time.sleep(5)
    else:
        output.off()
        outputAR1.off()
       
    if 1 in detected_objects:
        output2.on()  # Turn on Pin
        outputAR2.on()
        print("GPIO15 (Red Flag) turned on!")
        # time.sleep(5)
    else:
        output2.off()
        outputAR2.off()
    if 2 in detected_objects:
        output3.on()
        outputAR3.on()
        print("GPIO18 (Yellow Flag) turned on!")
        # time.sleep(5)
    else:
        output3.off()
        outputAR3.off()
   
       
           
    # Display the frame with detection results
    annotated_frame = results[0].plot()
    cv2.imshow("Object Detection", annotated_frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) == ord("q"):
        break

# Clean up
cv2.destroyAllWindows()
