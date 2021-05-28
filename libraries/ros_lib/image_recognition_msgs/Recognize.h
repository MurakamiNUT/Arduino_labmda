#ifndef _ROS_SERVICE_Recognize_h
#define _ROS_SERVICE_Recognize_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "image_recognition_msgs/Recognition.h"

namespace image_recognition_msgs
{

static const char RECOGNIZE[] = "image_recognition_msgs/Recognize";

  class RecognizeRequest : public ros::Msg
  {
    public:
      typedef sensor_msgs::Image _image_type;
      _image_type image;

    RecognizeRequest():
      image()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->image.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return RECOGNIZE; };
    const char * getMD5(){ return "b13d2865c5af2a64e6e30ab1b56e1dd5"; };

  };

  class RecognizeResponse : public ros::Msg
  {
    public:
      uint32_t recognitions_length;
      typedef image_recognition_msgs::Recognition _recognitions_type;
      _recognitions_type st_recognitions;
      _recognitions_type * recognitions;

    RecognizeResponse():
      recognitions_length(0), recognitions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->recognitions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->recognitions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->recognitions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->recognitions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->recognitions_length);
      for( uint32_t i = 0; i < recognitions_length; i++){
      offset += this->recognitions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t recognitions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      recognitions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      recognitions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      recognitions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->recognitions_length);
      if(recognitions_lengthT > recognitions_length)
        this->recognitions = (image_recognition_msgs::Recognition*)realloc(this->recognitions, recognitions_lengthT * sizeof(image_recognition_msgs::Recognition));
      recognitions_length = recognitions_lengthT;
      for( uint32_t i = 0; i < recognitions_length; i++){
      offset += this->st_recognitions.deserialize(inbuffer + offset);
        memcpy( &(this->recognitions[i]), &(this->st_recognitions), sizeof(image_recognition_msgs::Recognition));
      }
     return offset;
    }

    const char * getType(){ return RECOGNIZE; };
    const char * getMD5(){ return "0b68c401f85156d0f457b618ff650d93"; };

  };

  class Recognize {
    public:
    typedef RecognizeRequest Request;
    typedef RecognizeResponse Response;
  };

}
#endif
