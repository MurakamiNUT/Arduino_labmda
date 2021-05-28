#ifndef NEXISR_MAXON_DRIVER
#define NEXISR_MAXON_DRIVER

#include <SPI.h>
#include "mcp_can.h"
#define NRMD_TIMEOUT 2000
#define NRMD_TIMEOUT_RETURN 0
#define NRMD_TX_ID 0x600
#define NRMD_RX_ID 0x580
#define NRMD_READ 0x40
#define NRMD_WRITE 0x22

#define FLAME 1

#define RX 0
#define TX 1

#define CW 17
#define CCW 18
#define HOMING 0
#define HOMING_END 0x1400
#define CONNECT_ERROR -1
#define CONNECT_SUCCESS 0

#define IN_GP_A             (1<<15)
#define IN_GP_B             (1<<14)
#define IN_GP_C             (1<<13)
#define IN_GP_D             (1<<12)
#define IN_GP_E             (1<<11)
#define IN_GP_F             (1<<10)
#define IN_GP_G             (1<< 9)
#define IN_GP_H             (1<< 8)
#define IN_GP_I             (1<< 7)
#define IN_GP_J             (1<< 6)
#define IN_Quick_Stop       (1<< 5)
#define IN_Device_Enable    (1<< 4)
#define IN_Position_Market  (1<< 3)
#define IN_Home_Switch      (1<< 2)
#define IN_Positive_Limit   (1<< 1)
#define IN_Negative_Limit   (1<< 0)

/*
#define CAN_5KBPS    1
#define CAN_10KBPS   2
#define CAN_20KBPS   3
#define CAN_25KBPS   4 
#define CAN_31K25BPS 5
#define CAN_33KBPS   6
#define CAN_40KBPS   7
#define CAN_50KBPS   8
#define CAN_80KBPS   9
#define CAN_83K3BPS  10
#define CAN_95KBPS   11
#define CAN_100KBPS  12
#define CAN_125KBPS  13
#define CAN_200KBPS  14
#define CAN_250KBPS  15
#define CAN_500KBPS  16
#define CAN_666KBPS  17
#define CAN_1000KBPS 18
 */

/*

Index		|	Variable accessed
-----------------------------------
0000h		|	Reserved
0001h-009Fh	|	Data types (not supported on EPOS4)
00A0h-0FFFh	|	Reserved
1000h-1FFFh	|	Communication Profile Area (CiA 301)
2000h-5FFFh	|	Manufacturer-specific Profile Area (maxon motor
6000h-9FFFh	|	Standardized Device Area (CiA 402)
A000h-FFFFh	|	Reserved

*/

//datapack�N���X
class datapack{
  public:
    datapack();			//�R���X�g���N�^
    void set_data(uint8_t in_cs,uint16_t in_index,uint8_t in_subin,uint32_t in_object);
						//
    uint8_t buf[8];		//���M�f�[�^�o�b�t�@
    unsigned char len;	//�f�[�^��
	//�ȉ��̃����o��CAN�ő��M����8byte�f�[�^�ɂȂ�
    uint8_t*  cs;		//�R�}���h�w��q
    uint16_t* index;	//�I�u�W�F�N�g�����w��C���f�b�N�X
    uint8_t*  subin;	//�I�u�W�F�N�g�����̉��ʍ\�����w�肷��C���f�b�N�X(�z��C���f�b�N�X�ɋ߂�?)
    uint32_t* object;	//�I�u�W�F�N�g�̃f�[�^
};

//NexisR_Maxon_Driver�N���X
class NexisR_Maxon_Driver{
  private:
    MCP_CAN CAN;			//mcp_can.h
    unsigned id;			//CAN ID
    datapack rx,tx;			//���M�E��M�f�[�^
    int time_used;			//?
    int check_timeout();	//?
    int homing_judge_n();	//?
    int homing_buf[9];		//?
    uint32_t nominal_current;//add by iwamoto 
							//EPOS�̒��d��
  public:
    NexisR_Maxon_Driver(int eposID);			//?
    NexisR_Maxon_Driver(int eposID,int canPin);	//?
    int begin();								//?
    int begin(int canbps);						//?
    void print_data(unsigned char rt);			//?
    void print_data(unsigned char rt,unsigned char flame);
												//?
    int any_command(uint8_t cs,uint16_t index,uint8_t subin,uint32_t object);
												//?
    int get_current_Pgain();					//P�Q�C���擾

    int set_nominal_current(uint32_t set_param);//���d���ݒ�

    int mode_speed();							//���x���䃂�[�h
    int mode_position();						//�ʒu���䃂�[�h
    int mode_position(int homing);				//�ʒu���䃂�[�h�H
    int mode_current();							//�d��(�g���N)���䃂�[�h

    int set_speed(long speed);					//���x�w�ߒl�ݒ�
    int set_position(long position);			//�ʒu�w�ߒl�ݒ�
    int set_position(int homing,long position);	//�ʒu�w�ߒl�ݒ�H
    int set_current(long current);				//�d��(�g���N)�w�ߒl�ݒ�

    long get_speed();							//���ݑ��x�擾
    long get_position();						//���݈ʒu�擾
    long get_current();							//���ݓd���擾

    int homing_start(int ccw,int Speed_Search,int Speed_Zero,int Home_Position);
												//?
    int homing_judge();							//?
    
    int ClearFault();							//?

    int get_State_DigIn();						//?
    int get_State_DigIn(uint32_t ref);			//?
};
  
#endif
