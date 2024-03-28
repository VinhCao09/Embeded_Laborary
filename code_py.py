import Adafruit_DHT
import RPi.GPIO as GPIO
import serial
import time


ser = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=1.0)
time.sleep(3)
ser.reset_input_buffer()
print("Serial OK")
sensor = Adafruit_DHT.DHT11
gas=0
gpio = 17
GPIO.setmode(GPIO.BCM)
buzzer_pin = 14
gas_sensor_pin = 18
GPIO.setup(buzzer_pin, GPIO.OUT)
GPIO.setup(gas_sensor_pin, GPIO.IN)

try:
    while True:
        if GPIO.input(gas_sensor_pin) == GPIO.LOW: 
            print("Gas detected!")
            gas = 1
            GPIO.output(buzzer_pin, GPIO.HIGH)
            time.sleep(1) 
            GPIO.output(buzzer_pin, GPIO.LOW)
            nhietdo='t'+str(temperature)
            doam='h'+str(humidity)
            khigas='g1'
            ser.write(nhietdo.encode('utf-8'))
            ser.write(doam.encode('utf-8'))
            ser.write(khigas.encode('utf-8'))
        else:
            print("No gas detected")
            gas = 0
            time.sleep(0.1) 
        humidity, temperature = Adafruit_DHT.read_retry(sensor, gpio)
        if humidity is not None and temperature is not None:
            print ('Temp: {0:0.1f}*C  Humidity: {1:0.1f} %'.format(temperature, humidity))
        #   time.sleep(0.5)
            #ser.write("Hello! from 12412\n".encode('utf-8'))
        #else:
        #    print("Loi xay ra!")
        print("Da gui du lieu cho ESP8266")
        nhietdo='t'+str(temperature)
        doam='h'+str(humidity)
        khigas='g'+str(gas)
        ser.write(nhietdo.encode('utf-8'))
        ser.write(doam.encode('utf-8'))
        ser.write(khigas.encode('utf-8'))
        
except KeyboardInterrupt:
    GPIO.cleanup()


