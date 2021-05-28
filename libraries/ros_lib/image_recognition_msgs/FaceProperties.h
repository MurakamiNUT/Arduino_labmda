#ifndef _ROS_image_recognition_msgs_FaceProperties_h
#define _ROS_image_recognition_msgs_FaceProperties_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace image_recognition_msgs
{

  class FaceProperties : public ros::Msg
  {
    public:
      typedef uint8_t _gender_type;
      _gender_type gender;
      typedef uint8_t _age_type;
      _age_type age;
      enum { MALE = 0 };
      enum { FEMALE = 1 };

    FaceProperties():
      gender(0),
      age(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->gender >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gender);
      *(outbuffer + offset + 0) = (this->age >> (8 * 0)) & 0xFF;
      offset += sizeof(this->age);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->gender =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->gender);
      this->age =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->age);
     return offset;
    }

    const char * getType(){ return "image_recognition_msgs/FaceProperties"; };
    const char * getMD5(){ return "0509e719654f194b1f2f178434bcb902"; };

  };

}
#endif