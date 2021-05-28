#include <ros.h>
#include <beginner_tutorials/Controller.h>
#include <NexisR_Maxon_Driver.h>

ros::NodeHandle nh;

bool CLAWLER_MODE = true;
#define SPEED_TEST 16000//5710//1500
#define SPEED_TEST_F 7200
#define RISE_TIME 0.5//最大速度までの到達時間
#define UPDATE_TIME 100//ms Timerの更新周期

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

#define MAXON_CAN_BPS CAN_1000KBPS


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
void messageCb( const beginner_tutorials::Controller& controller_) {
    
//現在値
float Right_C_Vel;
float Left_C_Vel;
//目標値
float Right_C_Vel_T;
float Left_C_Vel_T;
#if UNIT_TEST
    //Serial.println(cmd);
#else
  if(controller_.L3 == true) CLAWLER_MODE = true;
  if(controller_.R3 == true) CLAWLER_MODE = false;
  if(CLAWLER_MODE){
    //クローラー動作記述部
      float radian = atan2(controller_.LS_Up_Down, -controller_.LS_Left_Right);
      float value = sqrt((controller_.LS_Up_Down*controller_.LS_Up_Down) + (-controller_.LS_Left_Right*(-controller_.LS_Left_Right)) );
      float deg; 
      //不感帯
      if((fabs(controller_.LS_Up_Down) > 0.01) || (fabs(controller_.LS_Left_Right) > 0.01)){
        Right_C_Vel_T = sin(radian - (3.141592/4)) * SPEED_TEST * value * 1.4142;
        Left_C_Vel_T  = sin(radian + (3.141592/4)) * SPEED_TEST * value * 1.4142;
      }
      else{
        Right_C_Vel_T = 0;
        Left_C_Vel_T = 0;
      }
      //過剰値のカット
      if(SPEED_TEST < fabs(Right_C_Vel_T)){
        if(Right_C_Vel_T > 0)Right_C_Vel_T = SPEED_TEST;
        else Right_C_Vel_T = -SPEED_TEST;
      }  
      if(SPEED_TEST < fabs(Left_C_Vel_T)){
        if(Left_C_Vel_T > 0) Left_C_Vel_T = SPEED_TEST;
        else Left_C_Vel_T = -SPEED_TEST;
      }
      deg = radian * 180/3.141592;
      if(deg < 0)deg = 180 + (180 + deg);
      //高速低速モード対応
      int Vel_mode = 1;
      if(controller_.Circle)Vel_mode = 2;
      if(controller_.Square)Vel_mode = 0;
      if(Vel_mode == 0){
        Right_C_Vel_T *= 0.5;
        Left_C_Vel_T *= 0.5;
      }
      else if(Vel_mode == 1){
        Right_C_Vel_T *= 0.75;
        Left_C_Vel_T *= 0.75;
      }
      else{}
      //三角加速
      if(fabs(Right_C_Vel_T) < fabs(Right_C_Vel)) Right_C_Vel = Right_C_Vel_T;
      else if (fabs(Right_C_Vel_T) > fabs(Right_C_Vel)){
        if(Right_C_Vel_T >= 0) Right_C_Vel += SPEED_TEST / (RISE_TIME/(UPDATE_TIME/1000.0));
        else                   Right_C_Vel -= SPEED_TEST / (RISE_TIME/(UPDATE_TIME/1000.0));
        if(fabs(Right_C_Vel_T) < fabs(Right_C_Vel)) Right_C_Vel = Right_C_Vel_T;
      }
      else{}
      
      if(fabs(Left_C_Vel_T) < fabs(Left_C_Vel)) Left_C_Vel = Left_C_Vel_T;
      else if (fabs(Left_C_Vel_T) > fabs(Left_C_Vel)){
        if(Left_C_Vel_T >= 0)  Left_C_Vel += SPEED_TEST / (RISE_TIME/(UPDATE_TIME/1000.0));
        else                   Left_C_Vel -= SPEED_TEST / (RISE_TIME/(UPDATE_TIME/1000.0));
        if(fabs(Left_C_Vel_T) < fabs(Left_C_Vel))   Left_C_Vel = Left_C_Vel_T;
      }
      else{}
      ////////////////////////////////////////////////////////////////////////
      motor_speed[CRAWLER_LEFT] = (int)(Left_C_Vel_T);
      motor_speed[CRAWLER_RIGHT]= (int)(-Right_C_Vel_T);
      //-----------------------------------------------------------------------
      //動作フリッパー選択
      if(controller_.R1 == true)flip.Front_Right = true;
      else{
        flip.Front_Right = false;
        motor_speed[FLIP_FRONT_RIGHT]=0;
      }
      if(controller_.L1 == true)flip.Front_Left = true;
      else{
        flip.Front_Left = false;
        motor_speed[FLIP_FRONT_LEFT]=0;
      }
      if(controller_.R2 == true)flip.Rear_Right = true;
      else{
        flip.Rear_Right = false;
        motor_speed[FLIP_REAR_RIGHT]=0;
      }
      if(controller_.L2 == true)flip.Rear_Left = true;
      else{
        flip.Rear_Left = false;
        motor_speed[FLIP_REAR_LEFT]=0;
      }
    
      if(controller_.Cross){//フリッパーを上げる
        if(flip.Front_Right == true){
          motor_speed[FLIP_FRONT_RIGHT]+= SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_FRONT_RIGHT]) > SPEED_TEST_F)  motor_speed[FLIP_FRONT_RIGHT] = SPEED_TEST_F;
        }
        if(flip.Front_Left  == true){
          motor_speed[FLIP_FRONT_LEFT] += SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_FRONT_LEFT])  > SPEED_TEST_F)  motor_speed[FLIP_FRONT_LEFT]  = SPEED_TEST_F;
        }
        if(flip.Rear_Right  == true){
          motor_speed[FLIP_REAR_RIGHT] += SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_REAR_RIGHT])  > SPEED_TEST_F)  motor_speed[FLIP_REAR_RIGHT]  = SPEED_TEST_F;
        }
        if(flip.Rear_Left   == true){
          motor_speed[FLIP_REAR_LEFT]  += SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_REAR_LEFT])   > SPEED_TEST_F)  motor_speed[FLIP_REAR_LEFT]   = SPEED_TEST_F;
        }
      }
      
      else if(controller_.Triangle){//下げる
        if(flip.Front_Right == true){
          motor_speed[FLIP_FRONT_RIGHT]-= SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_FRONT_RIGHT]) > SPEED_TEST_F)  motor_speed[FLIP_FRONT_RIGHT] = -SPEED_TEST_F;
        }
        if(flip.Front_Left  == true){
          motor_speed[FLIP_FRONT_LEFT] -= SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_FRONT_LEFT])  > SPEED_TEST_F)  motor_speed[FLIP_FRONT_LEFT]  = -SPEED_TEST_F;
        }
        if(flip.Rear_Right  == true){
          motor_speed[FLIP_REAR_RIGHT] -= SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_REAR_RIGHT])  > SPEED_TEST_F)  motor_speed[FLIP_REAR_RIGHT]  = -SPEED_TEST_F;
        }
        if(flip.Rear_Left   == true){
          motor_speed[FLIP_REAR_LEFT]  -= SPEED_TEST_F / (RISE_TIME/(UPDATE_TIME/1000.0));
          if(fabs(motor_speed[FLIP_REAR_LEFT])   > SPEED_TEST_F)  motor_speed[FLIP_REAR_LEFT]   = -SPEED_TEST_F;
        }
      }
      else{
        motor_speed[FLIP_FRONT_RIGHT]  = 0;
        motor_speed[FLIP_FRONT_LEFT]   = 0;
        motor_speed[FLIP_REAR_RIGHT]   = 0;
        motor_speed[FLIP_REAR_LEFT]    = 0;
      }
  }
  else{
    motor_speed[CRAWLER_RIGHT]     = 0;
    motor_speed[CRAWLER_LEFT]      = 0;
    motor_speed[FLIP_FRONT_RIGHT]  = 0;
    motor_speed[FLIP_FRONT_LEFT]   = 0;
    motor_speed[FLIP_REAR_RIGHT]   = 0;
    motor_speed[FLIP_REAR_LEFT]    = 0;
  }
    for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_speed(motor_speed[idx]);
#endif
}

ros::Subscriber<beginner_tutorials::Controller> sub("Arduino", &messageCb );

void setup(){
  pinMode(13,OUTPUT);
  Serial.begin(57600);
  //Serial.begin(115200);
  //nh.getHardware()->setBaud(57600);
  //nh.getHardware()->init();
  nh.initNode();
  nh.subscribe(sub);
  //int Nominal_Corrent[MOTOR_NUM] = {1490,1490,1490,1490,7610,7610};
  for(int idx=0; idx<MOTOR_NUM; idx ++)maxon_motor[idx].set_nominal_current(8000);
  //RAMせつやくのため
  /*
  maxon_motor[0].set_nominal_current(1490);
  maxon_motor[1].set_nominal_current(1490);
  maxon_motor[2].set_nominal_current(1490);
  maxon_motor[3].set_nominal_current(1490);
  maxon_motor[4].set_nominal_current(7610);
  maxon_motor[5].set_nominal_current(7610);
  */
#if 1
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
  
  bool err_flg=true;
  bool fin_flg[MOTOR_NUM]={0,0,0,0,0,0};
  while(err_flg){
    for(int idx=0; idx<MOTOR_NUM; idx ++){
      if(!(fin_flg[idx])){
        maxon_motor[idx].begin(MAXON_CAN_BPS);
        delay(500);
        if(maxon_motor[idx].mode_speed()==CONNECT_SUCCESS)  fin_flg[idx] = true;
        err_flg = true;
      } 
      int count = 0;
      for(int i = 0; i < MOTOR_NUM; i++)  count += fin_flg[i];
      if(count > MOTOR_NUM);// err_flg = false;
      else count = 0;
    }
    delay(500);
  }
#endif

 // Serial.print("Startup.\n");
  

}
//ros::rate loop_rate();
void loop(){
   // msg_debug.data = 1;
    nh.spinOnce();
    //nh.loginfo("s");
  
}
