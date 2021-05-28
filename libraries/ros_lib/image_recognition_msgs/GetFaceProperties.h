#ifndef _ROS_SERVICE_GetFaceProperties_h
#define _ROS_SERVICE_GetFaceProperties_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "image_recognition_msgs/FaceProperties.h"

namespace image_recognition_msgs
{

static const char GETFACEPROPERTIES[] = "image_recognition_msgs/GetFaceProperties";

  class GetFacePropertiesRequest : public ros::Msg
  {
    public:
      uint32_t face_image_array_length;
      typedef sensor_msgs::Image _face_image_array_type;
      _face_image_array_type st_face_image_array;
      _face_image_array_type * face_image_array;

    GetFacePropertiesRequest():
      face_image_array_length(0), face_image_array(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->face_image_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->face_image_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->face_image_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->face_image_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->face_image_array_length);
      for( uint32_t i = 0; i < face_image_array_length; i++){
      offset += this->face_image_array[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t face_image_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      face_image_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      face_image_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      face_image_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->face_image_array_length);
      if(face_image_array_lengthT > face_image_array_length)
        this->face_image_array = (sensor_msgs::Image*)realloc(this->face_image_array, face_image_array_lengthT * sizeof(sensor_msgs::Image));
      face_image_array_length = face_image_array_lengthT;
      for( uint32_t i = 0; i < face_image_array_length; i++){
      offset += this->st_face_image_array.deserialize(inbuffer + offset);
        memcpy( &(this->face_image_array[i]), &(this->st_face_image_array), sizeof(sensor_msgs::Image));
      }
     return offset;
    }

    const char * getType(){ return GETFACEPROPERTIES; };
    const char * getMD5(){ return "e3bad4931a01d73662add4a92636467c"; };

  };

  class GetFacePropertiesResponse : public ros::Msg
  {
    public:
      uint32_t properties_array_length;
      typedef image_recognition_msgs::FaceProperties _properties_array_type;
      _properties_array_type st_properties_array;
      _properties_array_type * properties_array;

    GetFacePropertiesResponse():
      properties_array_length(0), properties_array(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->properties_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->properties_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->properties_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->properties_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->properties_array_length);
      for( uint32_t i = 0; i < properties_array_length; i++){
      offset += this->properties_array[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t properties_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      properties_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      properties_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      properties_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->properties_array_length);
      if(properties_array_lengthT > properties_array_length)
        this->properties_array = (image_recognition_msgs::FaceProperties*)realloc(this->properties_array, properties_array_lengthT * sizeof(image_recognition_msgs::FaceProperties));
      properties_array_length = properties_array_lengthT;
      for( uint32_t i = 0; i < properties_array_length; i++){
      offset += this->st_properties_array.deserialize(inbuffer + offset);
        memcpy( &(this->properties_array[i]), &(this->st_properties_array), sizeof(image_recognition_msgs::FaceProperties));
      }
     return offset;
    }

    const char * getType(){ return GETFACEPROPERTIES; };
    const char * getMD5(){ return "0520558de71d14fd1e03c6bfdd5c8935"; };

  };

  class GetFaceProperties {
    public:
    typedef GetFacePropertiesRequest Request;
    typedef GetFacePropertiesResponse Response;
  };

}
#endif
