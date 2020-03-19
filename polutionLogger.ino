#include <SPI.h>  
#include <MySensor.h>  
#include <Wire.h> 
#include <MutichannelGasSensor.h>

/**************************Deklarasi Parameter Gas**********************************/
#define         GAS_CL2                      (0)
#define         GAS_O3                       (1)  
#define         GAS_CO2                      (2)
#define         GAS_CO                       (3) 
#define         GAS_NH4                      (4)
#define         GAS_CH3                      (6)
#define         GAS_CH3_2CO                  (7)
#define         GAS_H2                       (8)
#define         GAS_C2H5OH                   (9) //Alcohol, Ethanol
#define         GAS_C4H10                   (10)
#define         GAS_LPG                     (11)
#define         GAS_Smoke                   (12)
#define         GAS_CO_sec                  (13)  
#define         GAS_LPG_sec                 (14)
#define         GAS_CH4                     (15)
#define         GAS_NO2                     (16)  
#define         GAS_SO2                     (17) 
#define         GAS_C7H8                    (18) //Toluene
#define         GAS_H2S                     (19) //Hydrogen Sulfide
#define         GAS_NH3                     (20) //Ammonia
#define         GAS_C6H6                    (21) //Benzene
#define         GAS_C3H8                    (22) //Propane 
#define         GAS_NHEX                    (23) //n-hexa
#define         GAS_HCHO                    (24) //HCHO / CH2O Formaldehyde

/*****************************Variabel Globals*************************************/
unsigned long SLEEP_TIME = 600; // Sleep time between reads (in seconds)

//VARIABLES
int val = 0;          // variable to store the value coming from the sensor


float calcVoltage = 0;
boolean metric = true; 

//test
float a=0;
boolean pcReceived = false;

#define CHILD_ID_NH3 0
#define CHILD_ID_CO 1
#define CHILD_ID_NO2 2
#define CHILD_ID_C3H8 3
#define CHILD_ID_C4H10 4
#define CHILD_ID_CH4 5
#define CHILD_ID_H2 6
#define CHILD_ID_C2H5OH 7

MySensor polutionLog;  // Arduino  initialization
MyMessage msg_nh3(CHILD_ID_NH3, V_UNIT_PREFIX);
MyMessage msg_co(CHILD_ID_CO, V_UNIT_PREFIX);
MyMessage msg_no2(CHILD_ID_NO2, V_UNIT_PREFIX);
MyMessage msg_c3h8(CHILD_ID_C3H8, V_UNIT_PREFIX);
MyMessage msg_c4h10(CHILD_ID_C4H10, V_UNIT_PREFIX);
MyMessage msg_ch4(CHILD_ID_CH4, V_UNIT_PREFIX);
MyMessage msg_h2(CHILD_ID_H2, V_UNIT_PREFIX);
MyMessage msg_c2h5oh(CHILD_ID_C2H5OH, V_UNIT_PREFIX);

int val_nh3=0;
int val_co=0;
int val_no2=0;
int val_c3h8=0;
int val_c4h10=0;
int val_ch4=0;
int val_h2=0;
int val_c2h5oh=0;

void setup()  
{ 
  polutionLog.begin();
  
  
  // Kirim informasi versi sketsa ke gateway dan Controller
  polutionLog.sendSketchInfo("AIQ Multi Sensors MiCS", "1.0");

  // Daftarkan semua sensor ke gateway (sensor akan dibuat sebagai perangkat tambahan)
  polutionLog.present(CHILD_ID_NH3, S_AIR_QUALITY);  
  polutionLog.send(msg_nh3.set("ppm"));
  polutionLog.present(CHILD_ID_CO, S_AIR_QUALITY);  
  polutionLog.send(msg_co.set("ppm"));
  polutionLog.present(CHILD_ID_NO2, S_AIR_QUALITY);  
  polutionLog.send(msg_no2.set("ppm"));
  polutionLog.present(CHILD_ID_C3H8, S_AIR_QUALITY);  
  polutionLog.send(msg_c3h8.set("ppm"));
  polutionLog.present(CHILD_ID_C4H10, S_AIR_QUALITY);  
  polutionLog.send(msg_c4h10.set("ppm"));
  polutionLog.present(CHILD_ID_CH4, S_AIR_QUALITY);  
  polutionLog.send(msg_ch4.set("ppm"));
  polutionLog.present(CHILD_ID_H2, S_AIR_QUALITY);  
  polutionLog.send(msg_h2.set("ppm"));
  polutionLog.present(CHILD_ID_C2H5OH, S_AIR_QUALITY);  
  polutionLog.send(msg_c2h5oh.set("ppm"));
  mutichannelGasSensor.begin(0x04);//the default I2C address of the slave is 0x04
  mutichannelGasSensor.powerOn();
  
}


void loop()      
{     
  float x;
    x = mutichannelGasSensor.measure_NH3();
    
    if((x>=0)&&(x!=val_nh3)) {
        Serial.print("NH3: ");
        Serial.print(x);
        val_nh3=x;
        polutionLog.send(msg_nh3.set(x,3));        
    }        

    x = mutichannelGasSensor.measure_CO(); 
    
    if((x>=0)&&(x!=val_co)) {
      Serial.print("CO: ");
      Serial.print(x);
        val_co=x;
        polutionLog.send(msg_co.set(x,3));        
    }
        
    x = mutichannelGasSensor.measure_NO2();
    
    if((x>=0)&&(x!=val_no2)) {
      Serial.print("NO2: ");
      Serial.print(x);
        val_no2=x;
        polutionLog.send(msg_no2.set(x,3));
    }  
   
  // Matikan radio. Perhatikan bahwa radio akan diaktifkan kembali
  // pada panggilan write () berikutnya.
  polutionLog.sleep(SLEEP_TIME*4); // tidur untuk: sleepTime
}
