#ifndef _ROS_beginner_tutorials_Motor_h
#define _ROS_beginner_tutorials_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace beginner_tutorials
{

  class Motor : public ros::Msg
  {
    public:
      int32_t motor_speed[6];

    Motor():
      motor_speed()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_motor_speedi;
      u_motor_speedi.real = this->motor_speed[i];
      *(outbuffer + offset + 0) = (u_motor_speedi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_speedi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_speedi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_speedi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_speed[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_motor_speedi;
      u_motor_speedi.base = 0;
      u_motor_speedi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_speedi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_speedi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_speedi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_speed[i] = u_motor_speedi.real;
      offset += sizeof(this->motor_speed[i]);
      }
     return offset;
    }

    const char * getType(){ return "beginner_tutorials/Motor"; };
    const char * getMD5(){ return "c2c8fc50808318a33c399242582c9409"; };

  };

}
#endif