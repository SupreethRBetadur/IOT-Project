#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



 

LiquidCrystal_I2C lcd(0x3F, 16, 2);
Adafruit_MPU6050 mpu;

int x_accelrest,y_accelrest,z_accelrest;
int led=2;

void setup(void) {
  Serial.begin(115200);
   
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
 
  Serial.println("");

  
  pinMode(led,OUTPUT);
  
  

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  x_accelrest = a.acceleration.x;
  y_accelrest = a.acceleration.y;
  z_accelrest = a.acceleration.z;
  
  Wire.begin();
  lcd.init();
  lcd.backlight();
  delay(100);
}
  

void loop() {
  /* Get new sensor events with the readings */
 

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  int x_accelread = a.acceleration.x - x_accelrest;
  int y_accelread = a.acceleration.y - y_accelrest;
  int z_accelread = a.acceleration.z - z_accelrest;

  if (x_accelread==0 && y_accelread==0 && z_accelread==0){
    lcd.setCursor(3,0);
    lcd.print("Waiting for ");
    lcd.setCursor(4,1);
    lcd.print("Response");
    Serial.println("Waiting for response.");
    digitalWrite(led,LOW);
  }

  else if(x_accelread>=4 && y_accelread>=0 && z_accelread<=0){
   
    lcd.setCursor(2,0);
    lcd.print("I want food");
    Serial.println("I want food");
    digitalWrite(led,HIGH);
  }

  else if(x_accelread<=-4 && y_accelread>=0 && z_accelread<=-4){
    
    lcd.setCursor(1,0);
    lcd.print("I want medicine");
    Serial.println("I want medicine");
    digitalWrite(led,HIGH);
  }

  else if(x_accelread>=0 && y_accelread>=4 && z_accelread<=0){
   
    lcd.setCursor(4,0);
    lcd.print("Emergency");
    Serial.println("Emergency");
    digitalWrite(led,HIGH);
  }

  else if(x_accelread>=0 && y_accelread<=-4 && z_accelread<=-4){
    
    lcd.setCursor(2,0);
    lcd.print("I want to use");
    lcd.setCursor(5,1);
    lcd.print("toilet");
    Serial.println("I want to use toilet.");
    digitalWrite(led,HIGH);
  }
  
 /*Serial.print("X-acceleration: ");
  Serial.print(x_accelread);
  Serial.print("  Y-acceleration: ");
  Serial.print(y_accelread);
  Serial.print(" Z-acceleration: ");
  Serial.println(z_accelread);*/

  
  delay(500);
  lcd.clear();
  
}

https://wokwi.com/projects/398143210419112961