#ifndef _ROS_image_recognition_msgs_CategoryProbability_h
#define _ROS_image_recognition_msgs_CategoryProbability_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace image_recognition_msgs
{

  class CategoryProbability : public ros::Msg
  {
    public:
      typedef const char* _label_type;
      _label_type label;
      typedef float _probability_type;
      _probability_type probability;

    CategoryProbability():
      label(""),
      probability(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_label = strlen(this->label);
      varToArr(outbuffer + offset, length_label);
      offset += 4;
      memcpy(outbuffer + offset, this->label, length_label);
      offset += length_label;
      union {
        float real;
        uint32_t base;
      } u_probability;
      u_probability.real = this->probability;
      *(outbuffer + offset + 0) = (u_probability.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_probability.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_probability.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_probability.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->probability);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_label;
      arrToVar(length_label, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_label; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_label-1]=0;
      this->label = (char *)(inbuffer + offset-1);
      offset += length_label;
      union {
        float real;
        uint32_t base;
      } u_probability;
      u_probability.base = 0;
      u_probability.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_probability.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_probability.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_probability.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->probability = u_probability.real;
      offset += sizeof(this->probability);
     return offset;
    }

    const char * getType(){ return "image_recognition_msgs/CategoryProbability"; };
    const char * getMD5(){ return "eb7ef1e65c230d37e0b3ceae14668372"; };

  };

}
#endif