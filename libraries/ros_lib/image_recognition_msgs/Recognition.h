#ifndef _ROS_image_recognition_msgs_Recognition_h
#define _ROS_image_recognition_msgs_Recognition_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "image_recognition_msgs/CategoricalDistribution.h"
#include "sensor_msgs/RegionOfInterest.h"

namespace image_recognition_msgs
{

  class Recognition : public ros::Msg
  {
    public:
      typedef image_recognition_msgs::CategoricalDistribution _categorical_distribution_type;
      _categorical_distribution_type categorical_distribution;
      typedef sensor_msgs::RegionOfInterest _roi_type;
      _roi_type roi;

    Recognition():
      categorical_distribution(),
      roi()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->categorical_distribution.serialize(outbuffer + offset);
      offset += this->roi.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->categorical_distribution.deserialize(inbuffer + offset);
      offset += this->roi.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "image_recognition_msgs/Recognition"; };
    const char * getMD5(){ return "4b43115e31295aecb76e808f68d9d2b7"; };

  };

}
#endif