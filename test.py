import serial
import csv
import time
import os

# Open the serial port (replace 'COM4' with your port, or '/dev/ttyUSB0' for Linux)
ser = serial.Serial('COM4', 115200, timeout=1)

# Give some time for the Arduino to initialize
time.sleep(2)

# Check if the CSV file exists to determine if it is empty
file_exists = os.path.isfile('output_data.csv')

# Open the CSV file in append mode ('a')
with open('output_data.csv', mode='a', newline='') as file:
    writer = csv.writer(file)

    # Write the header row only once if the file is empty
    if not file_exists or os.stat('output_data.csv').st_size == 0:
        writer.writerow(["Voltage (V)", "Current (A)", "Power (W)", "Energy (kWh)"])

    while True:
        try:
            # Read a line from the serial port and decode, ignoring errors
            line = ser.readline().decode('utf-8', errors='ignore').strip()

            # Skip empty lines
            if not line:
                continue

            # Split the line into CSV fields (assuming comma-separated values)
            data = line.split(',')

            # Write the data to the CSV file
            writer.writerow(data)

            # Print to the console for debugging
            print(data)

            # Ensure the file is immediately written and saved (flush the buffer)
            file.flush()

        except KeyboardInterrupt:
            # Exit the loop if user presses Ctrl+C
            print("Stopping data collection.")
            break
        except Exception as e:
            # Print any other error
            print(f"Error: {e}")

# Close the serial port
ser.close()