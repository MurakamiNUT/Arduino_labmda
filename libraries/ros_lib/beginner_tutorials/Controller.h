#ifndef _ROS_beginner_tutorials_Controller_h
#define _ROS_beginner_tutorials_Controller_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace beginner_tutorials
{

  class Controller : public ros::Msg
  {
    public:
      typedef float _LS_Left_Right_type;
      _LS_Left_Right_type LS_Left_Right;
      typedef float _LS_Up_Down_type;
      _LS_Up_Down_type LS_Up_Down;
      typedef float _RS_Left_Right_type;
      _RS_Left_Right_type RS_Left_Right;
      typedef float _RS_Up_Down_type;
      _RS_Up_Down_type RS_Up_Down;
      typedef float _Left_Right_type;
      _Left_Right_type Left_Right;
      typedef float _Up_Down_type;
      _Up_Down_type Up_Down;
      typedef bool _Triangle_type;
      _Triangle_type Triangle;
      typedef bool _Circle_type;
      _Circle_type Circle;
      typedef bool _Square_type;
      _Square_type Square;
      typedef bool _Cross_type;
      _Cross_type Cross;
      typedef bool _R1_type;
      _R1_type R1;
      typedef bool _R2_type;
      _R2_type R2;
      typedef bool _L1_type;
      _L1_type L1;
      typedef bool _L2_type;
      _L2_type L2;
      typedef bool _Select_type;
      _Select_type Select;
      typedef bool _Start_type;
      _Start_type Start;
      typedef bool _L3_type;
      _L3_type L3;
      typedef bool _R3_type;
      _R3_type R3;

    Controller():
      LS_Left_Right(0),
      LS_Up_Down(0),
      RS_Left_Right(0),
      RS_Up_Down(0),
      Left_Right(0),
      Up_Down(0),
      Triangle(0),
      Circle(0),
      Square(0),
      Cross(0),
      R1(0),
      R2(0),
      L1(0),
      L2(0),
      Select(0),
      Start(0),
      L3(0),
      R3(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_LS_Left_Right;
      u_LS_Left_Right.real = this->LS_Left_Right;
      *(outbuffer + offset + 0) = (u_LS_Left_Right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_LS_Left_Right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_LS_Left_Right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_LS_Left_Right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->LS_Left_Right);
      union {
        float real;
        uint32_t base;
      } u_LS_Up_Down;
      u_LS_Up_Down.real = this->LS_Up_Down;
      *(outbuffer + offset + 0) = (u_LS_Up_Down.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_LS_Up_Down.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_LS_Up_Down.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_LS_Up_Down.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->LS_Up_Down);
      union {
        float real;
        uint32_t base;
      } u_RS_Left_Right;
      u_RS_Left_Right.real = this->RS_Left_Right;
      *(outbuffer + offset + 0) = (u_RS_Left_Right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_RS_Left_Right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_RS_Left_Right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_RS_Left_Right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RS_Left_Right);
      union {
        float real;
        uint32_t base;
      } u_RS_Up_Down;
      u_RS_Up_Down.real = this->RS_Up_Down;
      *(outbuffer + offset + 0) = (u_RS_Up_Down.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_RS_Up_Down.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_RS_Up_Down.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_RS_Up_Down.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RS_Up_Down);
      union {
        float real;
        uint32_t base;
      } u_Left_Right;
      u_Left_Right.real = this->Left_Right;
      *(outbuffer + offset + 0) = (u_Left_Right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Left_Right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Left_Right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Left_Right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Left_Right);
      union {
        float real;
        uint32_t base;
      } u_Up_Down;
      u_Up_Down.real = this->Up_Down;
      *(outbuffer + offset + 0) = (u_Up_Down.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Up_Down.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Up_Down.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Up_Down.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Up_Down);
      union {
        bool real;
        uint8_t base;
      } u_Triangle;
      u_Triangle.real = this->Triangle;
      *(outbuffer + offset + 0) = (u_Triangle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Triangle);
      union {
        bool real;
        uint8_t base;
      } u_Circle;
      u_Circle.real = this->Circle;
      *(outbuffer + offset + 0) = (u_Circle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Circle);
      union {
        bool real;
        uint8_t base;
      } u_Square;
      u_Square.real = this->Square;
      *(outbuffer + offset + 0) = (u_Square.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Square);
      union {
        bool real;
        uint8_t base;
      } u_Cross;
      u_Cross.real = this->Cross;
      *(outbuffer + offset + 0) = (u_Cross.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Cross);
      union {
        bool real;
        uint8_t base;
      } u_R1;
      u_R1.real = this->R1;
      *(outbuffer + offset + 0) = (u_R1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R1);
      union {
        bool real;
        uint8_t base;
      } u_R2;
      u_R2.real = this->R2;
      *(outbuffer + offset + 0) = (u_R2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R2);
      union {
        bool real;
        uint8_t base;
      } u_L1;
      u_L1.real = this->L1;
      *(outbuffer + offset + 0) = (u_L1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L1);
      union {
        bool real;
        uint8_t base;
      } u_L2;
      u_L2.real = this->L2;
      *(outbuffer + offset + 0) = (u_L2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L2);
      union {
        bool real;
        uint8_t base;
      } u_Select;
      u_Select.real = this->Select;
      *(outbuffer + offset + 0) = (u_Select.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Select);
      union {
        bool real;
        uint8_t base;
      } u_Start;
      u_Start.real = this->Start;
      *(outbuffer + offset + 0) = (u_Start.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Start);
      union {
        bool real;
        uint8_t base;
      } u_L3;
      u_L3.real = this->L3;
      *(outbuffer + offset + 0) = (u_L3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L3);
      union {
        bool real;
        uint8_t base;
      } u_R3;
      u_R3.real = this->R3;
      *(outbuffer + offset + 0) = (u_R3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R3);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_LS_Left_Right;
      u_LS_Left_Right.base = 0;
      u_LS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_LS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_LS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_LS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->LS_Left_Right = u_LS_Left_Right.real;
      offset += sizeof(this->LS_Left_Right);
      union {
        float real;
        uint32_t base;
      } u_LS_Up_Down;
      u_LS_Up_Down.base = 0;
      u_LS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_LS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_LS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_LS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->LS_Up_Down = u_LS_Up_Down.real;
      offset += sizeof(this->LS_Up_Down);
      union {
        float real;
        uint32_t base;
      } u_RS_Left_Right;
      u_RS_Left_Right.base = 0;
      u_RS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_RS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_RS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_RS_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->RS_Left_Right = u_RS_Left_Right.real;
      offset += sizeof(this->RS_Left_Right);
      union {
        float real;
        uint32_t base;
      } u_RS_Up_Down;
      u_RS_Up_Down.base = 0;
      u_RS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_RS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_RS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_RS_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->RS_Up_Down = u_RS_Up_Down.real;
      offset += sizeof(this->RS_Up_Down);
      union {
        float real;
        uint32_t base;
      } u_Left_Right;
      u_Left_Right.base = 0;
      u_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Left_Right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Left_Right = u_Left_Right.real;
      offset += sizeof(this->Left_Right);
      union {
        float real;
        uint32_t base;
      } u_Up_Down;
      u_Up_Down.base = 0;
      u_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Up_Down.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Up_Down = u_Up_Down.real;
      offset += sizeof(this->Up_Down);
      union {
        bool real;
        uint8_t base;
      } u_Triangle;
      u_Triangle.base = 0;
      u_Triangle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Triangle = u_Triangle.real;
      offset += sizeof(this->Triangle);
      union {
        bool real;
        uint8_t base;
      } u_Circle;
      u_Circle.base = 0;
      u_Circle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Circle = u_Circle.real;
      offset += sizeof(this->Circle);
      union {
        bool real;
        uint8_t base;
      } u_Square;
      u_Square.base = 0;
      u_Square.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Square = u_Square.real;
      offset += sizeof(this->Square);
      union {
        bool real;
        uint8_t base;
      } u_Cross;
      u_Cross.base = 0;
      u_Cross.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Cross = u_Cross.real;
      offset += sizeof(this->Cross);
      union {
        bool real;
        uint8_t base;
      } u_R1;
      u_R1.base = 0;
      u_R1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R1 = u_R1.real;
      offset += sizeof(this->R1);
      union {
        bool real;
        uint8_t base;
      } u_R2;
      u_R2.base = 0;
      u_R2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R2 = u_R2.real;
      offset += sizeof(this->R2);
      union {
        bool real;
        uint8_t base;
      } u_L1;
      u_L1.base = 0;
      u_L1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L1 = u_L1.real;
      offset += sizeof(this->L1);
      union {
        bool real;
        uint8_t base;
      } u_L2;
      u_L2.base = 0;
      u_L2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L2 = u_L2.real;
      offset += sizeof(this->L2);
      union {
        bool real;
        uint8_t base;
      } u_Select;
      u_Select.base = 0;
      u_Select.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Select = u_Select.real;
      offset += sizeof(this->Select);
      union {
        bool real;
        uint8_t base;
      } u_Start;
      u_Start.base = 0;
      u_Start.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Start = u_Start.real;
      offset += sizeof(this->Start);
      union {
        bool real;
        uint8_t base;
      } u_L3;
      u_L3.base = 0;
      u_L3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L3 = u_L3.real;
      offset += sizeof(this->L3);
      union {
        bool real;
        uint8_t base;
      } u_R3;
      u_R3.base = 0;
      u_R3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R3 = u_R3.real;
      offset += sizeof(this->R3);
     return offset;
    }

    const char * getType(){ return "beginner_tutorials/Controller"; };
    const char * getMD5(){ return "4ae600ba7dabc458e439f4fb69cb52eb"; };

  };

}
#endif