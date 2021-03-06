// Generated by gencpp from file modules/target_reqRequest.msg
// DO NOT EDIT!


#ifndef MODULES_MESSAGE_TARGET_REQREQUEST_H
#define MODULES_MESSAGE_TARGET_REQREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose.h>

namespace modules
{
template <class ContainerAllocator>
struct target_reqRequest_
{
  typedef target_reqRequest_<ContainerAllocator> Type;

  target_reqRequest_()
    : request()  {
    }
  target_reqRequest_(const ContainerAllocator& _alloc)
    : request(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _request_type;
  _request_type request;




  typedef boost::shared_ptr< ::modules::target_reqRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::modules::target_reqRequest_<ContainerAllocator> const> ConstPtr;

}; // struct target_reqRequest_

typedef ::modules::target_reqRequest_<std::allocator<void> > target_reqRequest;

typedef boost::shared_ptr< ::modules::target_reqRequest > target_reqRequestPtr;
typedef boost::shared_ptr< ::modules::target_reqRequest const> target_reqRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::modules::target_reqRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::modules::target_reqRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace modules

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/indigo/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::modules::target_reqRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::modules::target_reqRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::modules::target_reqRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::modules::target_reqRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::modules::target_reqRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::modules::target_reqRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::modules::target_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4fabcdf1d38a4bd4d2e9f5a8ffe3985b";
  }

  static const char* value(const ::modules::target_reqRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4fabcdf1d38a4bd4ULL;
  static const uint64_t static_value2 = 0xd2e9f5a8ffe3985bULL;
};

template<class ContainerAllocator>
struct DataType< ::modules::target_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "modules/target_reqRequest";
  }

  static const char* value(const ::modules::target_reqRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::modules::target_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Pose request\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::modules::target_reqRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::modules::target_reqRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.request);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct target_reqRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::modules::target_reqRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::modules::target_reqRequest_<ContainerAllocator>& v)
  {
    s << indent << "request: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.request);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MODULES_MESSAGE_TARGET_REQREQUEST_H
