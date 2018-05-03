#include <AFMotor.h>
 
AF_DCMotor motor_um(1); //Seleciona o motor 1
AF_DCMotor motor_dois(2); //Seleciona o motor 4
AF_DCMotor motor_tres(3); //Seleciona o motor 1
AF_DCMotor motor_quatro(4); //Seleciona o motor 4

#define PIN_SE A4
#define PIN_SD A5

int SENSOR_E, SENSOR_D;
 
//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 200, rotate = 75;
//limiar do sensor
int threshold = 5;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;

int limite_se = 75, limite_sd = 80; 

//Rotina de calibracao do sensor
void calibrate(){
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   delay(100);
   SENSOR_E = analogRead(PIN_SE);
   SENSOR_D = analogRead(PIN_SD);
   
   leftOffset = leftOffset + SENSOR_E;
   //centre = centre + SENSOR_D;
   rightOffset = rightOffset + SENSOR_D;
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 //centre = centre / 10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 //leftOffset = centre - leftOffset;
 //rightOffset = centre - rightOffset;
}
 
void setup(){
  //calibrate();
  Serial.begin(9600);
  Serial.println("Fora Temer");
}

void lerSensores(){
  SENSOR_E = analogRead(PIN_SE) + leftOffset;
  SENSOR_D = analogRead(PIN_SD) + rightOffset;
  Serial.print("SE: "); Serial.println(SENSOR_E);
  Serial.print("SD: "); Serial.println(SENSOR_D);
}

//Essa função faz o robô virar a esquerda(vai para Cuba)
void vireEsquerda(){
  Serial.println("ESQUERDA");
  left = startSpeed;
  right = startSpeed - rotate;
  setVelocidadeMotores();
}

//Vira o robô para a direita(Bolsonaro 2018)
void vireDireita(){
  Serial.println("DIREITA");
  left = startSpeed - rotate;
  right = startSpeed;
  setVelocidadeMotores();
}

void vireEsquerdaParado(){
  left = 0;
  right = startSpeed + rotate;
  setVelocidadeMotores();
}

void vireDireitaParado(){
  left = startSpeed + rotate;
  right = 0;
  setVelocidadeMotores();
}

void seguirFrente(){
  Serial.println("FRENTE");
  left = startSpeed;
  right = startSpeed;
  setVelocidadeMotores();
}

void setVelocidadeMotores(){
  motor_um.setSpeed(left);
  motor_um.run(FORWARD);
  motor_quatro.setSpeed(left);
  motor_quatro.run(FORWARD);
  motor_dois.setSpeed(right);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(right);
  motor_tres.run(FORWARD);      
}

void loop()
{
  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
  lerSensores();
  
  if(SENSOR_E <= limite_se){
    vireEsquerda();
  }
  else if(SENSOR_D <= limite_sd){ 
    vireDireita();
  }
  else{
    seguirFrente();
  }  
}

