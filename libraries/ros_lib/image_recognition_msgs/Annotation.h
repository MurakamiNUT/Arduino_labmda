#ifndef _ROS_image_recognition_msgs_Annotation_h
#define _ROS_image_recognition_msgs_Annotation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/RegionOfInterest.h"

namespace image_recognition_msgs
{

  class Annotation : public ros::Msg
  {
    public:
      typedef const char* _label_type;
      _label_type label;
      typedef sensor_msgs::RegionOfInterest _roi_type;
      _roi_type roi;

    Annotation():
      label(""),
      roi()
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
      offset += this->roi.serialize(outbuffer + offset);
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
      offset += this->roi.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "image_recognition_msgs/Annotation"; };
    const char * getMD5(){ return "58cf75ea3b312a76df6febf6296b89fb"; };

  };

}
#endif