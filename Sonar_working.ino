#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;


const int num_runs = 10;
const int pwPin1 = 4;
long output[num_runs];
long sensor1, cm;

void setup () {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  pinMode(pwPin1, INPUT);
}

void sort(long a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) { 
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

void read_sensor(){
  int i = 0;

  for(i=0;i<num_runs;i++){
      sensor1 = pulseIn(pwPin1, HIGH);
      output[i] = sensor1/58;
  }
  sort(output,num_runs);
  cm = output[num_runs/2];

}



void loop () {
  read_sensor();
  SerialBT.print(cm);
  SerialBT.print(":");
  //SerialBT.println();

  printall();
  delay(50);
}

void printall(){
  Serial.print("S1");
  Serial.print(" = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}
