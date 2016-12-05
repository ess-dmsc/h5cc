//#include <boost/algorithm/string.hpp>
#include "H5CC_Variant.h"
#include <iostream>

namespace H5CC {

VariantPtr _VariantFactory_::create(H5::DataType type)
{
  for (auto t : types_)
    if (t.h5_type == type)
      return VariantPtr(t.constructor());

  return VariantPtr();
}

VariantPtr _VariantFactory_::create(std::string name)
{
  for (auto t : types_)
    if (t.name == name)
      return VariantPtr(t.constructor());

  return VariantPtr();
}

void _VariantFactory_::register_type(std::string name, H5::DataType type,
                                std::function<VariantType*(void)> typeConstructor)
{
  FactoryEntry entry;
  entry.constructor = typeConstructor;
  entry.name = name;
  entry.h5_type = type;
  types_.push_back(entry);
}

const std::vector<std::string> _VariantFactory_::types() {
  std::vector<std::string> all_types;
  for (auto &q : types_)
    all_types.push_back(q.name);
  return all_types;
}

}



