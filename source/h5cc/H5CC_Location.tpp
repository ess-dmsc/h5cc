#include "H5CC_Exception.h"
#include "H5CC_Types.h"

#define TT template<typename T>
#define TDT template<typename DT>

namespace H5CC {

TT Location<T>::Location()
{}

TT Location<T>::Location(T t, std::string name)
  : location_(t)
  , name_ (name)
{}

TT std::string Location<T>::name() const
{
  return name_;
}

TT std::list<std::string> Location<T>::attributes() const
{
  try
  {
    std::list<std::string> ret;
    for (int i=0; i < location_.getNumAttrs(); ++i)
    {
      H5::Attribute attr = location_.openAttribute(i);
      ret.push_back(attr.getName());
    }
    return ret;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT bool Location<T>::has_attribute(std::string name) const
{
  try
  {
    return location_.attrExists(name);
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT void Location<T>::remove_attribute(std::string name)
{
  try
  {
    location_.removeAttr(name);
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT TDT void Location<T>::write_attribute(std::string name, DT val)
{
  if (has_attribute(name))
    remove_attribute(name);
  try
  {
    H5::Attribute attribute = location_.createAttribute(name, type_of(DT()), H5::DataSpace (H5S_SCALAR));
    attr_write(attribute, val);
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT TDT DT Location<T>::read_attribute(std::string name) const
{
  try
  {
    DT ret;
    H5::Attribute attribute = location_.openAttribute(name);
    attr_read(attribute, ret);
    return ret;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT TDT void Location<T>::attr_write(H5::Attribute& attr, DT val)
{
  attr.write(type_of(val), &val );
}

TT void Location<T>::attr_write(H5::Attribute& attr, std::string val)
{
  attr.write(type_of(val), val );
}

TT TDT void Location<T>::attr_read(const H5::Attribute& attr, DT& val) const
{
  attr.read(type_of(val), &val );
}

TT void Location<T>::attr_read(const H5::Attribute& attr, std::string& val) const
{
  attr.read(type_of(val), val );
}



}

#undef TT
#undef TDT
