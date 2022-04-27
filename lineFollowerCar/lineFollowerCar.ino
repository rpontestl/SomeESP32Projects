//Por Rafael Pontes
//Definição dos pinos de controle do motor
#define M1 13 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta ATV_A ponte H;
#define M2 27 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta ATV_B ponte H;
#define dir1 14 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 26 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_SD 34
#define pin_SC 32
#define pin_SE 35


bool SensorD = 0;
bool SensorC = 0;
bool SensorE = 0;

const int reD = 0;
const int frenteD = 1;
const int reE = 2;
const int frenteE = 3; 

//variável responsável por controlar a velocidade dos motores
int vel_max = 250;

void setup(){
//Setamos os pinos de controle dos motores como saída
ledcAttachPin(M1,reD);
ledcSetup(reD,4000,8);
ledcAttachPin(dir1,frenteD);
ledcSetup(frenteD,4000,8);
ledcAttachPin(M2,reE);
ledcSetup(reE,4000,8);
ledcAttachPin(dir2,frenteE);
ledcSetup(frenteE,4000,8); 


//Setamos os pinos dos sensores como entrada
pinMode(pin_SE, INPUT);
pinMode(pin_SC, INPUT);
pinMode(pin_SD, INPUT);
}

void loop(){
//Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
SensorD = digitalRead(pin_SD);
SensorC = digitalRead(pin_SC);
SensorE = digitalRead(pin_SE);

//Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
if((SensorE == 0) && (SensorC == 1) && (SensorD == 0)){ // Se detectar na extremidade das faixas duas cores brancas
ledcWrite(reD,0);
ledcWrite(frenteD,vel_max);
ledcWrite(reE,0);
ledcWrite(frenteE,vel_max);
}
if((SensorE == 1) && (SensorC == 1)){ // Curva abrupta esquerda
ledcWrite(frenteD,vel_max);
ledcWrite(reD,0);
ledcWrite(frenteE,0);
ledcWrite(reE,150);
delay(50);
}

if((SensorD == 1) && (SensorC == 1)){ // Curva abrupta direita
ledcWrite(frenteD,0);
ledcWrite(reD,150);
ledcWrite(frenteE,vel_max);
ledcWrite(reE,0);
delay(50);
}

if((SensorD == 1) && (SensorC == 0)){ //curva suave direita
ledcWrite(frenteD,0);
ledcWrite(reD,50);
ledcWrite(frenteE,200);
ledcWrite(reE,0);
}

if((SensorE == 1) && (SensorC == 0)){ //curva suave esquerda 
ledcWrite(frenteD,200);
ledcWrite(reD,0);
ledcWrite(frenteE,0);
ledcWrite(reE,50);
}

}
