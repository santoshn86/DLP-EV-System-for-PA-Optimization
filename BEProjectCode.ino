#include <PZEM004Tv30.h>
PZEM004Tv30 pzem1(14, 12); // GPIO14(D5) to Tx PZEM004; GPIO12(D6) to Rx PZEM004
float VOLTAGE, CURRENT, POWER, energy1, Freq, pf1, va1, VAR1;

void setup() 
{
  Serial.begin(115200);
  //Serial.println("Voltage (V),Current (A),Power (W),Frequency (Hz),Cosine Phi (PF),Energy (kWh),Apparent Power (VA),Reactive Power (VAR)");
}

void loop() 
{
  VOLTAGE = pzem1.voltage();
  VOLTAGE = zeroIfNan(VOLTAGE);
  CURRENT = pzem1.current();
  CURRENT = zeroIfNan(CURRENT);
  POWER = pzem1.power();
  POWER = zeroIfNan(POWER);
  energy1 = pzem1.energy() / 1000; // kWh
  energy1 = zeroIfNan(energy1);
  Freq = pzem1.frequency();
  Freq = zeroIfNan(Freq);
  pf1 = pzem1.pf();
  pf1 = zeroIfNan(pf1);

  if (pf1 == 0) 
    va1 = 0;
  else 
    va1 = POWER / pf1;

  if (pf1 == 0) 
    VAR1 = 0;
  else
    VAR1 = POWER / pf1 * sqrt(1 - sq(pf1));

  // Delay before next reading
  delay(1000);

  // Output data in CSV format to the serial port
  Serial.printf("%.2f,%.2f,%.2f,%.2f\n", 
                VOLTAGE, CURRENT, POWER, energy1);
}

float zeroIfNan(float v) 
{
  if (isnan(v)) 
    v = 0;
  return v;
}