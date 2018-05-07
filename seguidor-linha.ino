#include <AFMotor.h>
 
AF_DCMotor motor_um(1); //Seleciona o motor 1
AF_DCMotor motor_dois(2); //Seleciona o motor 2
AF_DCMotor motor_tres(3); //Seleciona o motor 3
AF_DCMotor motor_quatro(4); //Seleciona o motor 4

#define PIN_SE A4
#define PIN_SD A5

int SENSOR_E, SENSOR_D;

//velocidade inicial e deslocamento de rotacao
int startSpeed = 50, rotate = 40;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;
//condição para seguir em frente
boolean andar = true;
//velocidades individuais de cada motor para andar em linha reta
int motor1=50, motor2=50, motor3=70, motor4=70;
//resistêcia maxima para cada sensor
int limite_se = 130, limite_sd = 100; 

//retorna true caso a resistência do sensor esquerdo seja menor
//que a resistência maxima
boolean isBlackLeft(){
  lerSensores();
  return SENSOR_E <= limite_se;  
} 

//retorna true caso a resistência do sensor direito seja menor
//que a resistência maxima
boolean isBlackRight(){
  lerSensores();
  return SENSOR_D <= limite_sd;
}
  
void setup(){
  Serial.begin(9600);
}

void lerSensores(){
  SENSOR_E = analogRead(PIN_SE);
  SENSOR_D = analogRead(PIN_SD);
}

//virar para a esquerda parando as rodas da esquerda
void vireEsquerdaParado(){
  left = 0;
  right = startSpeed + rotate;
  setVelocidadeMotores();
}

//virar para a direita parando as rodas das direita
void vireDireitaParado(){
  left = startSpeed + rotate;
  right = 0;
  setVelocidadeMotores();
}

//segue em frente
void seguirFrente(){
  left = startSpeed;
  right = startSpeed;
  setVelocidadeAndar();
}

//velocidade dos motores quando estão rodando
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

//velocidade dos motores quando segue em linha reta
void setVelocidadeAndar(){
  motor_um.setSpeed(motor1);
  motor_um.run(FORWARD);
  motor_quatro.setSpeed(motor4);
  motor_quatro.run(FORWARD);
  motor_dois.setSpeed(motor2);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(motor3);
  motor_tres.run(FORWARD);      
}

//zera a velocidade dos motores
void setVelocidadeStop(){
  andar = false;
  motor_um.setSpeed(0);
  motor_um.run(BACKWARD);
  motor_quatro.setSpeed(0);
  motor_quatro.run(BACKWARD);
  motor_dois.setSpeed(0);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(0);
  motor_tres.run(FORWARD);     
}

void loop(){
  //utiliza a mesma velocidade em ambos os motores para iniciar
  left = startSpeed;
  right = startSpeed;
  lerSensores();
  //caso os dois sensores estejam em cima da linha preta
  if(isBlackRight() && isBlackLeft()){
    seguirFrente();
  }
  //caso o sensor direito esteja em cima da linha preta
  else if(isBlackRight()){
    setVelocidadeStop();
   //enquanto o sensor esquerdo não encontrar a linha preta
    while(!isBlackLeft()){
      vireEsquerdaParado();
      }
    andar=true;
  }
  //caso o sensor esquerdo esteja em cima da linha preta  
  else if(isBlackLeft()){
    setVelocidadeStop();
    //enquanto o sensor esquerdo não encontrar a linha preta
    while(!isBlackRight()){ 
      vireDireitaParado();
      }
    andar=true;
  }
  else if(andar){
    seguirFrente();
  }  
}
