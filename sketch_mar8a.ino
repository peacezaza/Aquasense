#define drivo1 4
#define drivo2 17
#define drivo3 16
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 13
#define L298IN1 21
#define L298IN2 22
#define PH_SENSOR_PIN 36


#define STEPS_PER_REV 2048 
int stepDelay = 2;          
int sensorValue = 0;
float voltage = 0.0; 
float phValue = 0.0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(drivo1, OUTPUT);
  pinMode(drivo2, OUTPUT);
  pinMode(drivo3, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(L298IN1, OUTPUT);
  pinMode(L298IN2, OUTPUT);
}
void stepMotor(int step) {
  switch (step % 4) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(drivo1, LOW);
  digitalWrite(drivo2, LOW);
  digitalWrite(drivo3, LOW);

  for (int i = 0; i < STEPS_PER_REV; i++) {
    stepMotor(i);
    delay(stepDelay);
  }
  
  digitalWrite(L298IN1, LOW); 
  digitalWrite(L298IN2, HIGH);  

  // int sensorValue = analogRead(PH_SENSOR_PIN);  // Read the analog value
  // float voltage = sensorValue * (5.0 / 4095.0);  // Convert the value to voltage (assuming 5V input)
  
  // // Assuming the sensor outputs 2.5V at pH 7, and 59mV change per pH unit
  // float phValue = (voltage - 2.5) / 0.059;
  
  // // Output the sensor data
  // Serial.print("Sensor Value: ");
  // Serial.print(sensorValue);
  // Serial.print("\tVoltage: ");
  // Serial.print(voltage, 2);  // Display voltage with 2 decimal places
  // Serial.print("\tPH: ");
  // Serial.println(phValue, 2);  // Display pH value with 2 decimal places

  delay(1000); 
}
