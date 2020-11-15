/* 아두이노 */
float getVPP();
const int sensorIn1 = A0;
const int sensorIn2 = A1;
int mVperAmp = 100; // use 185 for 5A Module and 100 for 20A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup(){ 
 Serial.begin(9600);

}

void loop(){ 


while(Serial.available()){
char data = (char) Serial.read(); 

if(data == 'A') {
 Voltage = getVPP(sensorIn1);
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp; 
 Serial.println(AmpsRMS);
  delay(500);}
  

else if (data == 'B') {
 Voltage = getVPP(sensorIn2);
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.println(AmpsRMS);
  delay(500);}
  }}





float getVPP(const int sensorIn)
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn) - 300;
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
