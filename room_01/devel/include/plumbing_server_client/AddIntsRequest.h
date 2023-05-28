// Generated by gencpp from file plumbing_server_client/AddIntsRequest.msg
// DO NOT EDIT!


#ifndef PLUMBING_SERVER_CLIENT_MESSAGE_ADDINTSREQUEST_H
#define PLUMBING_SERVER_CLIENT_MESSAGE_ADDINTSREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace plumbing_server_client
{
template <class ContainerAllocator>
struct AddIntsRequest_
{
  typedef AddIntsRequest_<ContainerAllocator> Type;

  AddIntsRequest_()
    : num1(0)
    , num2(0)  {
    }
  AddIntsRequest_(const ContainerAllocator& _alloc)
    : num1(0)
    , num2(0)  {
  (void)_alloc;
    }



   typedef int32_t _num1_type;
  _num1_type num1;

   typedef int32_t _num2_type;
  _num2_type num2;





  typedef boost::shared_ptr< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> const> ConstPtr;

}; // struct AddIntsRequest_

typedef ::plumbing_server_client::AddIntsRequest_<std::allocator<void> > AddIntsRequest;

typedef boost::shared_ptr< ::plumbing_server_client::AddIntsRequest > AddIntsRequestPtr;
typedef boost::shared_ptr< ::plumbing_server_client::AddIntsRequest const> AddIntsRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator1> & lhs, const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator2> & rhs)
{
  return lhs.num1 == rhs.num1 &&
    lhs.num2 == rhs.num2;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator1> & lhs, const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace plumbing_server_client

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c68f3979e1a90aac7d1c75a1096d1e60";
  }

  static const char* value(const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc68f3979e1a90aacULL;
  static const uint64_t static_value2 = 0x7d1c75a1096d1e60ULL;
};

template<class ContainerAllocator>
struct DataType< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "plumbing_server_client/AddIntsRequest";
  }

  static const char* value(const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 num1\n"
"int32 num2   \n"
;
  }

  static const char* value(const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.num1);
      stream.next(m.num2);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct AddIntsRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::plumbing_server_client::AddIntsRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::plumbing_server_client::AddIntsRequest_<ContainerAllocator>& v)
  {
    s << indent << "num1: ";
    Printer<int32_t>::stream(s, indent + "  ", v.num1);
    s << indent << "num2: ";
    Printer<int32_t>::stream(s, indent + "  ", v.num2);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PLUMBING_SERVER_CLIENT_MESSAGE_ADDINTSREQUEST_H
