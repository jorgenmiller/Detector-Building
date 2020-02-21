# Detector-Building  

Arduino code for Detector Building  

## Pseudocode  

### variables:  
Set LED pins and temp sensor pin  
Create smoothing array and related variables
Set max and min temperatures for each LED  

### setup:  
Setup LEDs  
Set all smoothing array values to 0
Begin Serial  

### loop:  
Read raw pin value  
Convert pin value to voltage
Convert voltage to temperature using determined equation  
Print temperature and voltage to serial  
Turn off LEDs  
Turn on LED if in range for each  
Wait some time  
