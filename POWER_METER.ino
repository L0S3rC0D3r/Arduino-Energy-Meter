#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3, 2);
int backLight = 9;
long behold_my_power = 0;
float sample1, sample2, voltage, val, actualval, amps, totamps, avgamps, amphr, watt, energy;
void setup()
{
  Serial.begin(9600);
  pinMode(backLight, OUTPUT); //set pin 9 as output
  analogWrite(backLight, 150); //controls the backlight intensity 0-254
  lcd.begin(16,2); // columns, rows. size of display
  lcd.clear(); // clear the screen
}
void loop()
{
  // taking 150 samples from voltage divider with a interval of 2sec and then average the samples data collected 
  for(int i=0;i<150;i++)
  {
    sample1=sample1+analogRead(A2); //read the voltage from the divider circuit
    delay (2);
  }
  
  sample1=sample1/150;
  voltage=4.669*2*sample1/1000;
  
  // taking 150 samples from sensors with a interval of 2sec and then average the samples data collected
  for(int i=0;i<150;i++)
  {
    sample2+=analogRead(A3); //read the current from sensor !!
    delay(2);
  }
  sample2=sample2/150;
  val =(4.883*sample2)/1024.0;
  actualval =val-2.5; // offset voltage is 2.5v
  amps =actualval*10;

  // TIME //
  long milisec = millis(); // calculate time in milliseconds
  long time=milisec/1000; // convert milliseconds to seconds
  Serial.print("sample1: ");Serial.print(sample1);
  Serial.print(", sample2: ");Serial.print(sample2);
  Serial.print(", voltage: ");Serial.print(voltage);
  Serial.print(", val: ");Serial.print(val);
  Serial.print(", actualval: ");Serial.print(actualval);
  Serial.print(", amps: ");Serial.print(amps);
  Serial.print(", milisec: ");Serial.print(milisec);
  Serial.print(", time: ");Serial.println(time);

  delay(200);
  // CALCULATIONS //
  totamps=totamps+amps; // calculate total amps
  behold_my_power+=1;
  avgamps=totamps/behold_my_power; // average amps (sum of all current/seconds?)
  amphr=(avgamps)/3600; // amp-hour (1 hour/3600 sec)
  watt =voltage*amps; // power=voltage*current
  energy=(watt*time)/3600; //Watt-sec is again convert to Watt-Hr by dividing 1hr(3600sec)
  // energy=(watt*time)/(1000*3600); for reading in kWh

  // LCD //
  lcd.setCursor(16,1); // set the cursor outside the display count
  lcd.print(" "); // print empty character
  delay(600);
  //////////////////////////////////////////print power and energy to a LCD////////////////////////////////////////////////
  lcd.setCursor(1,0); // set the cursor at 1st col and 1st row
  lcd.print(watt);
  lcd.print("W ");
  lcd.print(voltage);
  lcd.print("V");
  lcd.setCursor(1,1); // set the cursor at 1st col and 2nd row
  lcd.print(energy);
  lcd.print("WH ");
  lcd.print(amps);
  lcd.print("A");
} 
