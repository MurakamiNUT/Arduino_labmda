#include"NexisR_Maxon_Driver.h"



//�s�v���ۂ�
void hogehoge(uint8_t* buf,uint8_t cs,uint16_t index,uint8_t subin,uint32_t obj_data){
  *(uint8_t* )(buf+0)=cs;
  *(uint16_t*)(buf+1)=index;
  *(uint8_t* )(buf+3)=subin;
  *(uint32_t*)(buf+4)=obj_data;
  return;
}

//�R���X�g���N�^
//�A�h���X�̐ݒ�
datapack::datapack(){
  cs    =(uint8_t* )(buf+0);
  index =(uint16_t*)(buf+1);
  subin =(uint8_t* )(buf+3);
  object=(uint32_t*)(buf+4);
}
//�f�[�^�Z�b�g
void datapack::set_data(uint8_t in_cs,uint16_t in_index,uint8_t in_subin,uint32_t in_object){
  *cs    =in_cs;
  *index =in_index;
  *subin =in_subin;
  *object=in_object;
  return ;
}

//�h���C�o������(SPI��CS�s����9�Ԃɐݒ�)
NexisR_Maxon_Driver::NexisR_Maxon_Driver(int eposID):CAN(9){
  id=eposID;
}
//�h���C�o������(SPI��CS�s���������Őݒ�)
NexisR_Maxon_Driver::NexisR_Maxon_Driver(int eposID,int canPin):CAN(canPin){
  id=eposID;
}
//�ʐM�J�n(���x1Mbps�Œ�)
int NexisR_Maxon_Driver::begin(){
  if(CAN_OK == CAN.begin(CAN_1000KBPS)){
    //Serial2.println("CAN BUS Shield init ok!");
    return 0;
  }
  else{
    //Serial2.println("CAN BUS Shield init fail");
    return -1;
  }
}

//�ʐM�J�n(���x�͈����w��)
int NexisR_Maxon_Driver::begin(int canbps){
  if(CAN_OK == CAN.begin(canbps)){
    //Serial2.println("CAN BUS Shield init ok!");
    return 0;
  }
  else{
    //Serial2.println("CAN BUS Shield init fail");
    return -1;
  }
}
//�^�C���A�E�g�m�F
int NexisR_Maxon_Driver::check_timeout(){
  int temp=micros();
  while(CAN_MSGAVAIL!=CAN.checkReceive()){
    time_used=micros()-temp;
    if(time_used>NRMD_TIMEOUT){break;}
  }
  return time_used;
}
//�f�o�b�O�p�ʐM
void NexisR_Maxon_Driver::print_data(unsigned char rt){
  if(rt==RX){
    //Serial2.print("[RX]ID:"); Serial2.print(CAN.getCanId()-NRMD_RX_ID, HEX); 
    //Serial2.print(" LEN:"); Serial2.print(rx.len); 
    //Serial2.print(" DATA:");
    for(unsigned char i = 0; i<rx.len; i++){
      //Serial2.print(rx.buf[i], BIN); Serial2.print(".");
    }
    //Serial2.println();
  }
  else if(rt==TX){
    //Serial2.print("[TX]ID:"); Serial2.print(id, HEX); 
    //Serial2.print(" LEN:"); Serial2.print(tx.len); 
    //Serial2.print(" DATA:");
    for(unsigned char i = 0; i<tx.len; i++){
      //Serial2.print(tx.buf[i], HEX); Serial2.print(".");
    }
    //Serial2.println();
  }
  else{
    //Serial2.println("print error:");
  }
  return;
}
//�f�o�b�O�p�ʐM
void NexisR_Maxon_Driver::print_data(unsigned char rt,unsigned char flame){
  if(flame!=FLAME){/*Serial2.println("flame error:");*/return;}
  if(rt==RX){
    /*Serial2.print("[RX]ID:");Serial2.print(CAN.getCanId()-NRMD_RX_ID, HEX); 
    Serial2.print(" SDO:");Serial2.print(*rx.cs, HEX); 
    Serial2.print(" INDEX:");Serial2.print(*rx.index, HEX); 
    Serial2.print(" SUBIN:");Serial2.print(*rx.subin, HEX); 
    Serial2.print(" OBJECT:");Serial2.print(*rx.object, HEX);
    Serial2.print(" = ");Serial2.print((int)(*rx.object));
    Serial2.println();*/
  }
  else if(rt==TX){
/*
    Serial2.print("[TX]ID:");Serial2.print(id, HEX); 
    Serial2.print(" SDO:");Serial2.print(*tx.cs, HEX); 
    Serial2.print(" INDEX:");Serial2.print(*tx.index, HEX); 
    Serial2.print(" SUBIN:");Serial2.print(*tx.subin, HEX); 
    Serial2.print(" OBJECT:");Serial2.print(*tx.object, HEX);
    Serial2.print(" = ");Serial2.print((int)(*tx.object));
    Serial2.println();
*/  
}
  else{
   // Serial2.println("print error:");
  }
  return;
}
//�R�}���h����M�p�֐�
int NexisR_Maxon_Driver::any_command(uint8_t cs,uint16_t index,uint8_t subin,uint32_t object){
  tx.set_data(cs,index,subin,object);
  rx.set_data(0,0,0,0);
  tx.len=8;

  CAN.sendMsgBuf(NRMD_TX_ID+id, 0,tx.len,tx.buf);
  if(check_timeout()<NRMD_TIMEOUT){
    CAN.readMsgBuf(&rx.len,rx.buf);
  }
  return time_used;
}
//���݂�P�Q�C���擾
int NexisR_Maxon_Driver::get_current_Pgain(){
  any_command(NRMD_READ ,0x60F6,0x01,0x00000000);
  if(time_used>NRMD_TIMEOUT){/*Serial2.print("COMMAND TIMEOUT");*/return CONNECT_ERROR;}
  return (int)(*rx.object);
}
//���d���l�̐ݒ�
int NexisR_Maxon_Driver::set_nominal_current(uint32_t set_param){
 nominal_current=set_param;
}

//���x���䃂�[�h
//
int NexisR_Maxon_Driver::mode_speed(){
  int f=CONNECT_SUCCESS;
  //if(any_command(NRMD_WRITE,0x6060,0x00,0x000000FE)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if (any_command(NRMD_WRITE, 0x3001, 0x01, (uint32_t)nominal_current)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }	//fix by iwamoto for nominal current 8000
  if (any_command(NRMD_WRITE, 0x3001, 0x02, (uint32_t)30000)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }	//fix by iwamoto for nominal current 8000
  if (any_command(NRMD_WRITE, 0x6060, 0x00, (uint32_t)    3)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  if (any_command(NRMD_WRITE, 0x607F, 0x00, (uint32_t)50000)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  if (any_command(NRMD_WRITE, 0x6083, 0x00, (uint32_t)32000)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  if (any_command(NRMD_WRITE, 0x6084, 0x00, (uint32_t)32000)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  if (any_command(NRMD_WRITE, 0x6085, 0x00, (uint32_t)32000)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  if (any_command(NRMD_WRITE, 0x6086, 0x00, (uint32_t)    0)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }			//fix by iwamoto for epos4? 2018
  //if(any_command(NRMD_READ ,0x607F,0x00,      7701)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x60C5,0x00,0xFFFFFFFF)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x00000006)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x0000000F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  return f;
}
int NexisR_Maxon_Driver::mode_position(){
  int f=CONNECT_SUCCESS;
  if(any_command(NRMD_WRITE,0x6060,0x00,0x00000001)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x6065,0x00,      2000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x607D,0x01,0x80000000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x607D,0x02,0x7FFFFFFF)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x607F,0x00,      7701)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x60C5,0x00,0xFFFFFFFF)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x00000006)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x0000000F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  return f;
}
int NexisR_Maxon_Driver::mode_position(int homing){
  int f=CONNECT_SUCCESS;
  if(homing==HOMING){
    if(any_command(NRMD_WRITE,0x6060,0x00,0x00000001)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6081,0x00,      1000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6083,0x00,     10000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6084,0x00,     10000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6085,0x00,     10000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6086,0x00,         0)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    
    if(any_command(NRMD_WRITE,0x6040,0x00,0x00000006)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6040,0x00,0x0000000F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    return f;
  }
  else{return -1;}
}
int NexisR_Maxon_Driver::mode_current(){
  int f=CONNECT_SUCCESS;
//  if(any_command(NRMD_WRITE,0x6060,0x00,0x000000FD)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if (any_command(NRMD_WRITE, 0x6060, 0x00, 0x0000000A)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }//fix by iwamoto for epos4? 2018
  //if(any_command(NRMD_READ ,0x6010,0x01,      5000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x6010,0x04,     10000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  //if(any_command(NRMD_READ ,0x6010,0x05,         5)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x00000006)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if(any_command(NRMD_WRITE,0x6040,0x00,0x0000000F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  return f;
}
int NexisR_Maxon_Driver::set_speed(long speed){
  int f=CONNECT_SUCCESS;
//  if(any_command(NRMD_WRITE,0x206B,0x00,(uint32_t)speed)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if (any_command(NRMD_WRITE, 0x60FF, 0x00, (uint32_t)speed)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }//fix by iwamoto for epos4 2018
  if (any_command(NRMD_WRITE, 0x6040, 0x00, 0x0000000F)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }
  return f;
}
int NexisR_Maxon_Driver::set_position(long position){
  int f=CONNECT_SUCCESS;
//  if(any_command(NRMD_WRITE,0x2062,0x00,(uint32_t)position)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if (any_command(NRMD_WRITE, 0x607A, 0x00, (uint32_t)position)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }//fix by iwamoto for wpos4

  return f;
}
int NexisR_Maxon_Driver::set_position(int homing,long position){
  int f=CONNECT_SUCCESS;
  if(homing==HOMING){
   // if(any_command(NRMD_WRITE,0x607A,0x00,(uint32_t)position)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6040,0x00,0x0000001F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    return f;
  }
  else{return CONNECT_ERROR;}
}
int NexisR_Maxon_Driver::set_current(long current){
  int f=CONNECT_SUCCESS;
  //if(any_command(NRMD_WRITE,0x2030,0x00,(uint32_t)current)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  if (any_command(NRMD_WRITE, 0x6071, 0x00, (uint32_t)current)>NRMD_TIMEOUT) { f = CONNECT_ERROR; }//fix by iwamoto for epos4 2018
  return f;
}
long NexisR_Maxon_Driver::get_speed(){
//  if(any_command(NRMD_READ ,0x2028,0x00,0x00)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  if (any_command(NRMD_READ, 0x606C, 0x00, 0x00)>NRMD_TIMEOUT) { return CONNECT_ERROR; }//fix by iwamoto 2018 for epos4

  return (long)(*rx.object);
}
long NexisR_Maxon_Driver::get_position(){
  if(any_command(NRMD_READ ,0x6064,0x00,0x00)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  return (long)(*rx.object);
}
long NexisR_Maxon_Driver::get_current(){
//  if(any_command(NRMD_READ ,0x6078,0x00,0x00)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  if (any_command(NRMD_READ, 0x6077, 0x00, 0x00)>NRMD_TIMEOUT) { return CONNECT_ERROR; }//fix by iwamoto 2018 for epos4

  return (long)(*rx.object);
}
int NexisR_Maxon_Driver::ClearFault(){
  int f=CONNECT_SUCCESS;
  if(any_command(NRMD_READ ,0x6040,0x00,0x0080)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  return f;
}





int NexisR_Maxon_Driver::get_State_DigIn(){
  if(any_command(NRMD_READ ,0x2071,0x01,0)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  return (int)(*rx.object);
}

int NexisR_Maxon_Driver::get_State_DigIn(uint32_t ref){
  if(any_command(NRMD_READ ,0x2071,0x01,0)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  return (int)((*rx.object)&ref);
}


int NexisR_Maxon_Driver::homing_start(int ccw,int Speed_Search,int Speed_Zero,int Home_Position){
  int f=CONNECT_SUCCESS;
  homing_buf[0]=ccw;
  homing_buf[1]=Speed_Search;
  homing_buf[2]=Speed_Zero;
  homing_buf[3]=Home_Position;

  do{
    if(any_command(NRMD_WRITE,0x6060,0x00, 0x06)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    
    if(any_command(NRMD_WRITE,0x6065,0x00, 2000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x607C,0x00,Home_Position)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x607F,0x00,25000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6085,0x00,10000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6099,0x01,Speed_Search )>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6099,0x02,Speed_Zero   )>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x609A,0x00, 1000)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x2080,0x00,  500)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x2081,0x00,    0)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  
    if(any_command(NRMD_WRITE,0x6098,0x00,ccw  )>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  
    if(any_command(NRMD_WRITE,0x6040,0x00,0x006)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6040,0x00,0x00F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
  
    if(any_command(NRMD_WRITE,0x6040,0x00,0x00F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    if(any_command(NRMD_WRITE,0x6040,0x00,0x01F)>NRMD_TIMEOUT){f=CONNECT_ERROR;}
    delay(1);
    //Serial2.print("homing...");
    if(f==CONNECT_ERROR){return CONNECT_ERROR;}
  }while(homing_judge_n()!=0);
  
  return f;
}

int NexisR_Maxon_Driver::homing_judge_n(){
  if(any_command(NRMD_READ ,0x6041,0x00,00)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  return (int)(*rx.object&(0x1400));

}
int NexisR_Maxon_Driver::homing_judge(){
  int j;
  if(any_command(NRMD_READ ,0x6041,0x00,00)>NRMD_TIMEOUT){return CONNECT_ERROR;}
  j=(int)(*rx.object&(0x1400));
  if(j==0x400){
    //Serial2.print("[judge warning]");
    if(homing_start(homing_buf[0],homing_buf[1],homing_buf[2],homing_buf[3])){return CONNECT_ERROR;}
  }
  return j;
}
