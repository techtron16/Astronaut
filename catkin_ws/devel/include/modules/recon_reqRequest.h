// Generated by gencpp from file modules/recon_reqRequest.msg
// DO NOT EDIT!


#ifndef MODULES_MESSAGE_RECON_REQREQUEST_H
#define MODULES_MESSAGE_RECON_REQREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/String.h>

namespace modules
{
template <class ContainerAllocator>
struct recon_reqRequest_
{
  typedef recon_reqRequest_<ContainerAllocator> Type;

  recon_reqRequest_()
    : tags()  {
    }
  recon_reqRequest_(const ContainerAllocator& _alloc)
    : tags(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::std_msgs::String_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::String_<ContainerAllocator> >::other >  _tags_type;
  _tags_type tags;




  typedef boost::shared_ptr< ::modules::recon_reqRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::modules::recon_reqRequest_<ContainerAllocator> const> ConstPtr;

}; // struct recon_reqRequest_

typedef ::modules::recon_reqRequest_<std::allocator<void> > recon_reqRequest;

typedef boost::shared_ptr< ::modules::recon_reqRequest > recon_reqRequestPtr;
typedef boost::shared_ptr< ::modules::recon_reqRequest const> recon_reqRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::modules::recon_reqRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::modules::recon_reqRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace modules

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/indigo/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::modules::recon_reqRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::modules::recon_reqRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::modules::recon_reqRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::modules::recon_reqRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::modules::recon_reqRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::modules::recon_reqRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::modules::recon_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "27808c1c07c092312933fbb1f7b440b4";
  }

  static const char* value(const ::modules::recon_reqRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x27808c1c07c09231ULL;
  static const uint64_t static_value2 = 0x2933fbb1f7b440b4ULL;
};

template<class ContainerAllocator>
struct DataType< ::modules::recon_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "modules/recon_reqRequest";
  }

  static const char* value(const ::modules::recon_reqRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::modules::recon_reqRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/String[] tags\n\
\n\
================================================================================\n\
MSG: std_msgs/String\n\
string data\n\
";
  }

  static const char* value(const ::modules::recon_reqRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::modules::recon_reqRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.tags);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct recon_reqRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::modules::recon_reqRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::modules::recon_reqRequest_<ContainerAllocator>& v)
  {
    s << indent << "tags[]" << std::endl;
    for (size_t i = 0; i < v.tags.size(); ++i)
    {
      s << indent << "  tags[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "    ", v.tags[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // MODULES_MESSAGE_RECON_REQREQUEST_H
