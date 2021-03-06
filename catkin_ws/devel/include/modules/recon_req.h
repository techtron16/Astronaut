// Generated by gencpp from file modules/recon_req.msg
// DO NOT EDIT!


#ifndef MODULES_MESSAGE_RECON_REQ_H
#define MODULES_MESSAGE_RECON_REQ_H

#include <ros/service_traits.h>


#include <modules/recon_reqRequest.h>
#include <modules/recon_reqResponse.h>


namespace modules
{

struct recon_req
{

typedef recon_reqRequest Request;
typedef recon_reqResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct recon_req
} // namespace modules


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::modules::recon_req > {
  static const char* value()
  {
    return "504293a32ca80b6b20fe52b4cc8a6439";
  }

  static const char* value(const ::modules::recon_req&) { return value(); }
};

template<>
struct DataType< ::modules::recon_req > {
  static const char* value()
  {
    return "modules/recon_req";
  }

  static const char* value(const ::modules::recon_req&) { return value(); }
};


// service_traits::MD5Sum< ::modules::recon_reqRequest> should match 
// service_traits::MD5Sum< ::modules::recon_req > 
template<>
struct MD5Sum< ::modules::recon_reqRequest>
{
  static const char* value()
  {
    return MD5Sum< ::modules::recon_req >::value();
  }
  static const char* value(const ::modules::recon_reqRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::modules::recon_reqRequest> should match 
// service_traits::DataType< ::modules::recon_req > 
template<>
struct DataType< ::modules::recon_reqRequest>
{
  static const char* value()
  {
    return DataType< ::modules::recon_req >::value();
  }
  static const char* value(const ::modules::recon_reqRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::modules::recon_reqResponse> should match 
// service_traits::MD5Sum< ::modules::recon_req > 
template<>
struct MD5Sum< ::modules::recon_reqResponse>
{
  static const char* value()
  {
    return MD5Sum< ::modules::recon_req >::value();
  }
  static const char* value(const ::modules::recon_reqResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::modules::recon_reqResponse> should match 
// service_traits::DataType< ::modules::recon_req > 
template<>
struct DataType< ::modules::recon_reqResponse>
{
  static const char* value()
  {
    return DataType< ::modules::recon_req >::value();
  }
  static const char* value(const ::modules::recon_reqResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MODULES_MESSAGE_RECON_REQ_H
