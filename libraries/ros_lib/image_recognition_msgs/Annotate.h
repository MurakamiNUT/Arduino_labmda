#ifndef _ROS_SERVICE_Annotate_h
#define _ROS_SERVICE_Annotate_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "image_recognition_msgs/Annotation.h"

namespace image_recognition_msgs
{

static const char ANNOTATE[] = "image_recognition_msgs/Annotate";

  class AnnotateRequest : public ros::Msg
  {
    public:
      typedef sensor_msgs::Image _image_type;
      _image_type image;
      uint32_t annotations_length;
      typedef image_recognition_msgs::Annotation _annotations_type;
      _annotations_type st_annotations;
      _annotations_type * annotations;

    AnnotateRequest():
      image(),
      annotations_length(0), annotations(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->image.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->annotations_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->annotations_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->annotations_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->annotations_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->annotations_length);
      for( uint32_t i = 0; i < annotations_length; i++){
      offset += this->annotations[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->image.deserialize(inbuffer + offset);
      uint32_t annotations_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->annotations_length);
      if(annotations_lengthT > annotations_length)
        this->annotations = (image_recognition_msgs::Annotation*)realloc(this->annotations, annotations_lengthT * sizeof(image_recognition_msgs::Annotation));
      annotations_length = annotations_lengthT;
      for( uint32_t i = 0; i < annotations_length; i++){
      offset += this->st_annotations.deserialize(inbuffer + offset);
        memcpy( &(this->annotations[i]), &(this->st_annotations), sizeof(image_recognition_msgs::Annotation));
      }
     return offset;
    }

    const char * getType(){ return ANNOTATE; };
    const char * getMD5(){ return "8cc91912a5e6a23decc502ffc5dae050"; };

  };

  class AnnotateResponse : public ros::Msg
  {
    public:

    AnnotateResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return ANNOTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class Annotate {
    public:
    typedef AnnotateRequest Request;
    typedef AnnotateResponse Response;
  };

}
#endif
