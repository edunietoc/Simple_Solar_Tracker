#include <Servo.h>

#define PanelVPin 2 
#define BatVPin 3
//80 / 175
int pos=127;
int output[2];
Servo servo;

void getSensorData(){ //Recibe la informacion de la fotoresistencia
  for(int i=0; i<2; i++){
      output[i]= analogRead(i);
  }
  //Serial.println(output[0]);
}

void moveServo(){ //funcion para mover servo
  int cal=20;
  int LSensor= output[0];
  int RSensor= output[1];
  Serial.println("SensorL: "+String(LSensor));  // Fotores izquierda
  Serial.println("SensorR: "+String(RSensor));  // Fotores derecha
  int diff= abs(LSensor-RSensor);
  if(diff<cal){
    servo.write(pos);
  }
  
  else{
    
    if(LSensor<RSensor){
      pos++;
      if(pos>175){ //limite superior de movimiento
      pos=175;
      }
      servo.write(pos);  
    }
    
    if(LSensor>RSensor){
      pos--;
      if(pos<80){ //limite inferior de movimiento
      pos=80;
      }
      servo.write(pos);  
    }
  
  
  }
 
}




float PanelVoltage(){ //Leer voltaje de panel
  const int R1 = 10000;
  const int R2 = 4700;
  float PVoltage;
  PVoltage = analogRead(PanelVPin)*0.004887;
  PVoltage=(PVoltage*(R1+R2))/R2;
  return PVoltage;
  //Serial.println(analogRead(PanelVPin));
}

float BatteryVoltage(){ //Leer el voltaje de bateria 
  const int R1 = 10000;
  const int R2 = 4700;
  float BVoltage;
  BVoltage = analogRead(BatVPin)*0.004887;
  BVoltage=(BVoltage*(R1+R2))/R2;
  return BVoltage;
}


void setup() {
  Serial.begin(9600);
  servo.attach(9);
  servo.write(127);  
}

void loop() {
  
  float BatVolt;
  float PanVolt;
  PanVolt= PanelVoltage();
  BatVolt = BatteryVoltage();
  getSensorData(); 
  moveServo();
  Serial.println("");
  Serial.println("Battery: "+String(BatVolt)); //Interfaz Voltaje de bateria
  Serial.println("Panel: "+String(PanVolt));   // Voltaje de panel
  Serial.println("Posicion de Servo en °: "+String(pos));
  Serial.println("");
  delay(300);
  
}
