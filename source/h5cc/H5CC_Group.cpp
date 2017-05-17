#include "H5CC_Group.h"
#include "H5CC_Exception.h"

namespace H5CC {

Group::Group(hid_t hid, std::string name)
{
  try
  {
    location_ = H5::Group(hid);
    name_ = name;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}


}
