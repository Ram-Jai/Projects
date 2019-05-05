#include <Wire.h>
#include <EmonLib.h>             // Include Emon Library
EnergyMonitor emon[3];             // Create an instance
int i;

void setup()
{  
  Serial.begin(115200);
  for (i=0;i<=2;i++){
  emon[i].voltage(1, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon[i].current(2, 111.1);       // Current: input pin, calibration.
  }
}

void loop()
{
  for (i=0;i<=2;i++){
    emon[i].calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
    float P_i      =    3 * emon[i].realPower;            //extract Real Power into variable
    float S_i      =    3 * emon[i].apparentPower;        //extract Apparent Power into variable
    float Q_i      =    sqrt(sq(S_i)-sq(P_i));            //extract Reactive Power into variable
    float pf_i     =    emon[i].powerFactor;              //extract Power Factor into Variable
    float Vrms_i   =    1.732 * emon[i].Vrms;            //extract Vrms into Variable
    float Irms_i   =    1.732 * emon[i].Irms;            //extract Irms into Variable
  }
  Serial.println("Values for line-to-neutral");
  for (i=0;i<=2;i++){
    Serial.print("Apparent Power:   ");
    Serial.println(S_i);
    Serial.print("Active Power:   ");
    Serial.println(P_i);
    Serial.print("Reactive Power:   ");
    Serial.println(Q_i);
    Serial.print("Voltage per phase:   ");
    Serial.println(Vrms_i);
    Serial.print("Current per phase:   ");
    Serial.println(Irms_i);
    Serial.print("Power Factor per phase:   ");
    Serial.println(pf_i);
  }
  Serial.println("***********************************");
  Serial.println("Values for line-to-line");
    Serial.print("Apparent Power:   ");
    Serial.println(1.732*(S_0 + S_1 + S_2)/3);
    Serial.print("Active Power:   ");
    Serial.println(1.732*(P_0 + P_1 + P_2)/3);
    Serial.print("Reactive Power:   ");
    Serial.println(1.732*(Q_0 + Q_1 + Q_2)/3);
    Serial.print("Voltage per line:   ");
    Serial.println(V_0*1.732);
    Serial.print("Current per line:   ");
    Serial.println(I_0);
    Serial.print("power factor per line:   ");
    Serial.println((pf_0 + pf_1 + pf_2)/3);
}
