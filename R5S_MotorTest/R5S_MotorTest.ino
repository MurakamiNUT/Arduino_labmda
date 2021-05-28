#include <MsTimer2.h>
#include <NexisR_Maxon_Driver.h>

#define SPEED_TEST 1500

//Debug Flag
#define UNIT_TEST 0
#define LOG_FLG 1

//MaxonMotor Indices
#define FLIP_FRONT_RIGHT 0
#define FLIP_FRONT_LEFT 1
#define FLIP_REAR_RIGHT 2
#define FLIP_REAR_LEFT 3
#define CRAWLER_RIGHT 4
#define CRAWLER_LEFT 5

#define MOTOR_NUM 6

//MaxonMotor EPOS_ID Define
/*
#define FLIP_FRONT_RIGHT_ID 2//RR
#define FLIP_FRONT_LEFT_ID 3//RL
#define FLIP_REAR_RIGHT_ID 4//CR
#define FLIP_REAR_LEFT_ID 5//CL
#define CRAWLER_RIGHT_ID 6//FR/FL
#define CRAWLER_LEFT_ID 7//FL/FR
*/
#define FLIP_FRONT_RIGHT_ID 6//R
#define FLIP_FRONT_LEFT_ID 7//R
#define FLIP_REAR_RIGHT_ID 2//R
#define FLIP_REAR_LEFT_ID 3//R
#define CRAWLER_RIGHT_ID 4//FR/FL
#define CRAWLER_LEFT_ID 5//FL/FR

#define SERIAL_BAUDRATE 9600
#define MAXON_CAN_BPS CAN_1000KBPS

//Reference Update Cycle[ms]
#define REF_UPDATE_TIME 50

//Instance and Variables Declaration
NexisR_Maxon_Driver maxon_motor[MOTOR_NUM] = {
          NexisR_Maxon_Driver(FLIP_FRONT_RIGHT_ID),
          NexisR_Maxon_Driver(FLIP_FRONT_LEFT_ID),
          NexisR_Maxon_Driver(FLIP_REAR_RIGHT_ID),
          NexisR_Maxon_Driver(FLIP_REAR_LEFT_ID),
          NexisR_Maxon_Driver(CRAWLER_RIGHT_ID),
          NexisR_Maxon_Driver(CRAWLER_LEFT_ID)
};

int motor_speed[MOTOR_NUM] = {0};

bool state=false;

//Function Prototype
void SerialLog(void);
void SerialErrorLog(char* err_msg);
void SpeedRefUpdate(void);

void setup() {
  // put your setup code here, to run once:
  //Start Serial Communication
  Serial.begin(9600);
  Serial.print("Initializing...\n");

  //MotorDriver Activate
  for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_nominal_current(8000);
#if UNIT_TEST
  //Without CANOpen Communication
#else
  //CANOpen Communication Activate
  bool err_flg=false;
  for(int idx=0; idx<MOTOR_NUM; idx ++){
    maxon_motor[idx].begin(MAXON_CAN_BPS);
    if(maxon_motor[idx].mode_speed()==CONNECT_ERROR){
      Serial.print("CONNECT ERROR:ID");
      Serial.println(idx);
      err_flg=true;
    }
  }
  if(err_flg){
    SerialErrorLog("CONNECT ERROR");
    while(1)delay(1000);
  }
#endif

  Serial.print("Startup.\n");
  
  MsTimer2::set(REF_UPDATE_TIME, SpeedRefUpdate);
  MsTimer2::start();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  SerialLog();
  delay(100);
}

void SerialLog(void){
#if LOG_FLG
  if(state)Serial.print("ON\n");
  else Serial.print("OFF\n");
#endif
}

void SerialErrorLog(char* err_msg){
#if LOG_FLG
  Serial.print("\n----------\nFatal Error Occurred.\nError Name:");
  Serial.println(err_msg);
#endif
}

void SpeedRefUpdate(void){
  if(Serial.available()){
    char cmd = Serial.read();
    if(cmd!='Z')state=true;
    else state=false;
#if UNIT_TEST
    //Serial.println(cmd);
#else
    switch(cmd){
      case 'A':
        motor_speed[CRAWLER_RIGHT]=-SPEED_TEST;
        motor_speed[CRAWLER_LEFT]=SPEED_TEST;
        break;
      case 'B':
        motor_speed[CRAWLER_RIGHT]=SPEED_TEST;
        motor_speed[CRAWLER_LEFT]=-SPEED_TEST;
        break;
      case 'C':
        motor_speed[CRAWLER_RIGHT]=SPEED_TEST;
        motor_speed[CRAWLER_LEFT]=SPEED_TEST;
        break;
      case 'D':
        motor_speed[CRAWLER_RIGHT]=-SPEED_TEST;
        motor_speed[CRAWLER_LEFT]=-SPEED_TEST;
        break;
      case 'E':
        motor_speed[FLIP_FRONT_RIGHT]=-SPEED_TEST;
        break;
      case 'F':
        motor_speed[FLIP_FRONT_RIGHT]=SPEED_TEST;
        break;
      case 'G':
        motor_speed[FLIP_FRONT_LEFT]=-SPEED_TEST;
        break;
      case 'H':
        motor_speed[FLIP_FRONT_LEFT]=SPEED_TEST;
        break;
      case 'I':
        motor_speed[FLIP_REAR_RIGHT]=-SPEED_TEST;
        break;
      case 'J':
        motor_speed[FLIP_REAR_RIGHT]=SPEED_TEST;
        break;
      case 'K':
        motor_speed[FLIP_REAR_LEFT]=-SPEED_TEST;
        break;
      case 'L':
        motor_speed[FLIP_REAR_LEFT]=SPEED_TEST;
        break;
      default:
      case 'Z':
        for(int idx=0; idx<MOTOR_NUM; idx ++)motor_speed[idx] = 0;
        break;
    }
    for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_speed(motor_speed[idx]);
#endif
  }
}
