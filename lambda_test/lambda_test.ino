#include <ros.h>
#include <NexisR_Maxon_Driver.h>
#include <beginner_tutorials/Motor.h>
#include <MsTimer2.h>

ros::NodeHandle nh;


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

#define MAXON_CAN_BPS CAN_1000KBPS

bool emergency = false;
int em_count = 0;

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
//void SerialLog(void);
//void SerialErrorLog(char* err_msg);


struct FLIP{
    bool Front_Right;
    bool Front_Left;
    bool Rear_Right;
    bool Rear_Left;
};
struct FLIP flip;
void messageCb( const beginner_tutorials::Motor& msg) {
  em_count = 0;
  emergency = false;
  if(!emergency){
    for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_speed(msg.motor_speed[idx]);
  }
}

void flash(){
  em_count++;
  if(em_count >= 5) emergency = true;
  if(emergency){
   // for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_speed(0);
  }
}

void setup(){
  pinMode(13,OUTPUT);
  Serial.begin(57600);
  //Serial.begin(115200);
  nh.initNode();
  ros::Subscriber<beginner_tutorials::Motor> sub("Motor_Con", &messageCb );
  nh.subscribe(sub);
  //int Nominal_Corrent[MOTOR_NUM] = {1490,1490,1490,1490,7610,7610};
  for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_nominal_current(15000);
  //RAMせつやくのため
  /*
  maxon_motor[0].set_nominal_current(1490);
  maxon_motor[1].set_nominal_current(1490);
  maxon_motor[2].set_nominal_current(1490);
  maxon_motor[3].set_nominal_current(1490);
  maxon_motor[4].set_nominal_current(7610);//7610
  maxon_motor[5].set_nominal_current(7610);
  */
#if 0
  //CANOpen Communication Activate
  bool err_flg=false;
  for(int idx=0; idx<MOTOR_NUM; idx ++){
    maxon_motor[idx].begin(MAXON_CAN_BPS);
    delay(100);
    if(maxon_motor[idx].mode_speed()==CONNECT_ERROR){
      //Serial.print("CONNECT ERROR:ID");
      //Serial.println(idx);
      err_flg=true;
    }
  }
  if(err_flg){
   // SerialErrorLog("CONNECT ERROR");
    while(1)delay(1000);
  }
#else
  //まだうまくいってない
  int count = 0;
  int finish_count = 0;//CONNECT_SUCCESS返しても通信うまく行ってない時があるため
  bool err_flg=true;
  bool fin_flg[MOTOR_NUM]={0,0,0,0,0,0};
  while(err_flg){
    for(int idx=0; idx<MOTOR_NUM; idx ++){
     // if(!(fin_flg[idx])){
        maxon_motor[idx].begin(MAXON_CAN_BPS);
        delay(100);
        if(maxon_motor[idx].mode_speed()==CONNECT_SUCCESS)  fin_flg[idx] = true;
        delay(100);
        err_flg = true;
      //} 
      count = 0;
      for(int i = 0; i < MOTOR_NUM; i++)if(fin_flg[i])count ++;
      if(count >= MOTOR_NUM){
        finish_count++;
        for(int i = 0; i < MOTOR_NUM; i++) fin_flg[idx] = 0;
      }
      if(finish_count >= 3)err_flg = false;
    count = 0;
    }
    delay(500);
  }
#endif

  MsTimer2::set(200, flash); 
  MsTimer2::start();
}
void loop(){
    nh.spinOnce(); 
}
