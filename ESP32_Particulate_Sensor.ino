///this code is written and tested for ncd.io wireless temperature humidity sensor with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-temperature-humidity-sensor-product-manual/
/// sesnro can be found here https://store.ncd.io/product/industrial-long-range-wireless-temperature-humidity-sensor/

  uint8_t data[67];
  int k = 10;
  int i;

void setup()
{
  Serial1.begin(115200, SERIAL_8N1, 16, 17); // pins 16 rx2, 17 tx2, 19200 bps, 8 bits no parity 1 stop bit​
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Particulate Matter Sensor for Air Quality Monitoring");
}


void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 67; i++)
      {
      data[i] = Serial1.read();
      delay(10);    
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==32)  //////// make sure the sensor type is correct
         {  
  float MassConcentrationPM1_0 = (((data[24])<<24)+((data[25])<<16)+((data[26])<<8)+(data[27]));
  float MassConcentrationPM2_5 = (((data[28])<<24)+((data[29])<<16)+((data[30])<<8)+(data[31]));
  float MassConcentrationPM4_0 = (((data[32])<<24)+((data[33])<<16)+((data[34])<<8)+(data[35]));
  float MassConcentrationPM10_0 = (((data[36])<<24)+((data[37])<<16)+((data[38])<<8)+(data[39]));
  float NumberConcentrationPM0_5 = (((data[40])<<24)+((data[41])<<16)+((data[42])<<8)+(data[43]));
  float NumberConcentrationPM1_0 = (((data[44])<<24)+((data[45])<<16)+((data[46])<<8)+(data[47]));
  float NumberConcentrationPM2_5 = (((data[48])<<24)+((data[49])<<16)+((data[50])<<8)+(data[51]));
  float NumberConcentrationPM4_0 = (((data[52])<<24)+((data[53])<<16)+((data[54])<<8)+(data[55]));
  float NumberConcentrationPM10_0 = (((data[56])<<24)+((data[57])<<16)+((data[58])<<8)+(data[59]));
  float TypicalParticleSize = (((data[60])<<24)+((data[61])<<16)+((data[62])<<8)+(data[63]));    

  
  float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Packet Counter                   ");
  Serial.println(data[20]);  
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
    Serial.print("Error Code  ");
  Serial.println(data[23]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
/*  
 *     float humidity = ((((data[24]) * 256) + data[25]) /100.0);
  //int16_t cTempint = (((uint16_t)(data[26])<<8)| data[27]);
  float cTemp = (((data[26])<<8)| data[27]) /100.0;
  float fTemp = cTemp * 1.8 + 32;
  uint16_t eCO2 = (((data[28])<<8)| data[29]);
  uint16_t TVOC = (((data[30])<<8)| data[31]);
  uint16_t H2 = (((data[32])<<8)| data[33]);
  uint16_t Ethanol = (((data[34])<<8)| data[35]);
 *   Serial.print("Relative Humidity :");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius :");
  Serial.print(cTemp);
  Serial.println(" 'C");
  Serial.print("Temperature in Fahrenheit :");
  Serial.print(fTemp);
  Serial.println(" 'F");
*/  
  Serial.print("MassConcentrationPM1.0 :");
  Serial.print(MassConcentrationPM1_0/100.00);
  Serial.println(" ");
  Serial.print("MassConcentrationPM2.5 :");
  Serial.print(MassConcentrationPM2_5/100.00);
  Serial.println(" ");
  Serial.print("MassConcentrationPM4.0 :");
  Serial.print(MassConcentrationPM4_0/100.00);
  Serial.println(" ");
  Serial.print("MassConcentrationPM10.0 :");
  Serial.print(MassConcentrationPM10_0/100.00);
  Serial.println(" ");
  
  Serial.print("NumberConcentrationPM0.5 :");
  Serial.print(NumberConcentrationPM0_5/100.00);
  Serial.println(" ");
  Serial.print("NumberConcentrationPM1.0 :");
  Serial.print(NumberConcentrationPM1_0/100.00);
  Serial.println(" ");
  Serial.print("NumberConcentrationPM2.5 :");
  Serial.print(NumberConcentrationPM2_5/100.00);
  Serial.println(" ");
  Serial.print("NumberConcentrationPM4.0 :");
  Serial.print(NumberConcentrationPM4_0/100.00);
  Serial.println(" ");
  Serial.print("NumberConcentrationPM10.0 :");
  Serial.print(NumberConcentrationPM10_0/100.00);
  Serial.println(" ");
  Serial.print("TypicalParticleSize :");
  Serial.print(TypicalParticleSize/100.00);
  Serial.println(" ");
  
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 68; i++)
    {
      Serial.print(data[i],HEX);
      Serial.print(",");
      delay(1);
    }
    Serial.println("\n");
}
    }
  }
 
}
