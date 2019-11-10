/*
Detector Building
made by Jørgen Miller in Nov 2019
UHS Science Olympiad

USE
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

int analog_temp = 1;  // A1, output voltage of temperature sensor
int led_red = 2;      // D2, anode of red LED
int led_green = 3;    // D3, anode of green LED
int led_blue = 4;     // D4, anode of blue LED

// LED temperature ranges in ºC
int min_red = 16;
int max_red = 75;
int min_green = 14;
int max_green = 16;
int min_blue = 0;
int max_blue = 14;
  
void setup() {  // runs on upload or press of reset button
  // declare LED pins to be outputs
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);

  // begin serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // labels for serial plotter
  Serial.print("Termperature(ºC)");
  Serial.print("\t");
  Serial.println("Voltage(mV)");
}

void loop() { // runs over and over again
  int pin_value;
  float temp;

  // read voltage from temperature sensor
  pin_value = analogRead(analog_temp);
  temp = (.105 * pin_value); // calibrated equation
  
//  int temp_F;
//  temp_F = (125*pin_value)>>8;
//  temp = (temp_F - 32) * 5/9;

  // send temperature and voltage via serial communication
  Serial.print(temp);
  Serial.print("\t");
  Serial.print(pin_value);
  Serial.println();
  
  //turn off all LEDs
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_blue, LOW);

  //turn on LEDs if in their range
  if ((temp <= max_red) && (temp >= min_red)) {
    digitalWrite(led_red, HIGH);
  }
  if ((temp <= max_green) && (temp >= min_green)) {
    digitalWrite(led_green, HIGH);
  }
  if ((temp <= max_blue) && (temp >= min_blue)) {
    digitalWrite(led_blue, HIGH);
  }

  delay(400); // wait 0.4 seconds
}
