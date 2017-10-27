import serial
import time

import datetime

serial_port = '/dev/ttyUSB0';
baud_rate = 115200;
write_to_file_path = "output.log";

output_file = open(write_to_file_path, "w+");
ser = serial.Serial(serial_port, baud_rate)
while True:
	line = ser.readline();
	line = line.decode("utf-8")
#	print(line);
	timestamp = str(datetime.datetime.now())
	output_file.write(timestamp + ' --- ' + line + '\n');
