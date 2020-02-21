/*
Detector Building
UHS Science Olympiad
Team #23
BLUE

FUNCTION
reads temperature in ºC using an analog temperature sensor
outputs voltage and temperature reading
turns on LEDs according to defined temperature ranges

SETUP
+5V -> temperature sensor -> A1
                          -> GND
D2 -> red LED -> 410Ω  -> GND
D3 -> green LED -> 410Ω  -> GND
D4 -> blue LED -> 410Ω  -> GND
*/

//sensor and LED pins
int analog_temp = A1;  // A1, output voltage of temperature sensor
int led_red = 2;      // D2, anode of red LED
int led_green = 3;    // D3, anode of green LED
int led_blue = 4;     // D4, anode of blue LED

//LED temperature ranges in ºC
int min_red = 30;
int max_red = 75;
int min_green = 20;
int max_green = 30;
int min_blue = 0;
int max_blue = 20;

//reference voltage for analog readings
float ref_voltage = 3.3;

//bits of resolution for analog readings
int resolution = 12; //maximum for Due

//precision of serial monitor (decimal places)
int decimals = 4;

//calibrated equation
float m = 98.23263268;
float b = -45.57288033;

//variables used for smoothing voltage readings
const int num_readings = 100; //last n values to be averaged
int read_index = 0;
int pin_value_readings[num_readings];
float pin_value_total = 0;

//mesaurement variables
float pin_value;
float pin_value_smoothed;
float voltage;
float voltage_smoothed;
float temp;
float temp_smoothed;

void setup() {  // runs on upload or press of reset button
  //declare LED pins to be outputs
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);

  //fill smoothing array with zeros
  for (int thisReading = 0; thisReading < num_readings; thisReading++) {
    pin_value_readings[thisReading] = 0;
  }

  //begin serial communication at 9600 bits per second
  Serial.begin(9600);

  //send labels for serial plotter
  Serial.print("Voltage (V)");
  Serial.print("\t");
  Serial.print("Smoothed Voltage (V)");
  Serial.print("\t");
  Serial.print("Temperature (ºC)");
  Serial.print("\t");
  Serial.println("Smoothed Temperature (ºC)");

  //Set resolution of voltage measurements
  analogReadResolution(resolution);
}

void loop() { // runs over and over again
  //read temperature sensor pin value
  pin_value = analogRead(analog_temp);

  //smooth pin_value
  pin_value_total -= pin_value_readings[read_index];
  pin_value_readings[read_index] = pin_value;
  pin_value_total += pin_value_readings[read_index];
  pin_value_smoothed = pin_value_total / num_readings;

  //convert pin value to V
  int scale = pow(2, resolution) - 1;
  voltage = ref_voltage * pin_value / scale;

  // convert smoothed pin value to V
  voltage_smoothed = ref_voltage * pin_value_smoothed / scale;

  //convert voltage to ºC
  temp = m * voltage + b; // calibrated equation

  //convert smoothed voltage to ºC
  temp_smoothed = m * voltage_smoothed + b; // calibrated equation

  //increase index for smoothing array
  read_index ++;
  if (read_index >= num_readings) {read_index = 0;}

  // send temperature and voltage via serial communication
  Serial.print(voltage, decimals);
  Serial.print("\t");
  Serial.print(voltage_smoothed, decimals);
  Serial.print("\t");
  Serial.print(temp, decimals);
  Serial.print("\t");
  Serial.println(temp_smoothed, decimals);

  //turn off all LEDs
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_blue, LOW);

  //turn on LEDs if in their range
  //use <=, ==, or >= as needed
  if ((temp <= max_red) && (temp >= min_red)) {
    digitalWrite(led_red, HIGH);
  }
  if ((temp <= max_green) && (temp >= min_green)) {
    digitalWrite(led_green, HIGH);
  }
  if ((temp <= max_blue) && (temp >= min_blue)) {
    digitalWrite(led_blue, HIGH);
  }

  //wait n milliseconds before next measurement
  delay(100);
}
