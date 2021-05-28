#ifndef _ROS_image_recognition_msgs_CategoricalDistribution_h
#define _ROS_image_recognition_msgs_CategoricalDistribution_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "image_recognition_msgs/CategoryProbability.h"

namespace image_recognition_msgs
{

  class CategoricalDistribution : public ros::Msg
  {
    public:
      uint32_t probabilities_length;
      typedef image_recognition_msgs::CategoryProbability _probabilities_type;
      _probabilities_type st_probabilities;
      _probabilities_type * probabilities;
      typedef float _unknown_probability_type;
      _unknown_probability_type unknown_probability;

    CategoricalDistribution():
      probabilities_length(0), probabilities(NULL),
      unknown_probability(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->probabilities_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->probabilities_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->probabilities_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->probabilities_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->probabilities_length);
      for( uint32_t i = 0; i < probabilities_length; i++){
      offset += this->probabilities[i].serialize(outbuffer + offset);
      }
      union {
        float real;
        uint32_t base;
      } u_unknown_probability;
      u_unknown_probability.real = this->unknown_probability;
      *(outbuffer + offset + 0) = (u_unknown_probability.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_unknown_probability.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_unknown_probability.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_unknown_probability.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->unknown_probability);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t probabilities_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      probabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      probabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      probabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->probabilities_length);
      if(probabilities_lengthT > probabilities_length)
        this->probabilities = (image_recognition_msgs::CategoryProbability*)realloc(this->probabilities, probabilities_lengthT * sizeof(image_recognition_msgs::CategoryProbability));
      probabilities_length = probabilities_lengthT;
      for( uint32_t i = 0; i < probabilities_length; i++){
      offset += this->st_probabilities.deserialize(inbuffer + offset);
        memcpy( &(this->probabilities[i]), &(this->st_probabilities), sizeof(image_recognition_msgs::CategoryProbability));
      }
      union {
        float real;
        uint32_t base;
      } u_unknown_probability;
      u_unknown_probability.base = 0;
      u_unknown_probability.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_unknown_probability.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_unknown_probability.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_unknown_probability.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->unknown_probability = u_unknown_probability.real;
      offset += sizeof(this->unknown_probability);
     return offset;
    }

    const char * getType(){ return "image_recognition_msgs/CategoricalDistribution"; };
    const char * getMD5(){ return "33d3c52e53151a3b74f712a5f80b67be"; };

  };

}
#endif