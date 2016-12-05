#ifndef TEST_VARIANT_H
#define TEST_VARIANT_H

#include "H5CC_Variant.h"
#include "H5CC_Types.h"
#include "H5EnumType.h"
#include <boost/lexical_cast.hpp>
#include <map>

namespace H5CC {

template <typename T>
class Atomic : public VariantType
{
public:
  Atomic() {}
  Atomic(T t) : data_(t) {}

  H5::DataType h5_type() const override { return type_of(T()); }

  std::string type_name() const override
  {
    return "atomic-" + boost::lexical_cast<std::string>(sizeof(data_) * 8);
  }

  void write(H5::Attribute& attr) const override
  {
    auto data = data_;
    attr.write(this->h5_type(), &data);
  }

  void read(const H5::Attribute& attr) override
  {
    attr.read(this->h5_type(), &data_);
  }

  std::string to_string() const override
  {
    return boost::lexical_cast<std::string>(data_);
  }

protected:
  T data_;
};

class Enum : public VariantType
{
public:
  Enum() {}
  Enum(int32_t t, std::map<int32_t, std::string> options) : val_(t), options_(options) {}
  Enum(std::initializer_list<std::string> options)
  {
    int32_t t {0};
    for (auto o : options)
    {
      options_[t] = o;
      ++t;
    }
  }

  H5::DataType h5_type() const override
  {
    H5::EnumType t(H5::PredType::NATIVE_INT32);
    for (auto i : options_)
    {
      auto v = i.first;
      t.insert(i.second, &v);
    }
    return t;
  }

  std::string type_name() const override
  {
    return "enum";
  }

  void write(H5::Attribute& attr) const override
  {
    auto val = val_;
    attr.write(this->h5_type(), &val);
  }

  void read(const H5::Attribute& attr) override
  {
    auto dtype = attr.getEnumType();
    options_.clear();
    for (int i=0; i < dtype.getNmembers(); ++i)
    {
      int32_t t;
      dtype.getMemberValue(i, &t);
      std::string name = dtype.nameOf(&t, 10);
      options_[t] = name;
    }

    attr.read(this->h5_type(), &val_);
  }

  std::string to_string() const override
  {
    std::string ret = boost::lexical_cast<std::string>(val_);
    if (options_.count(val_))
      ret += "=" + options_.at(val_);

    std::string opts;
    for (auto o : options_)
      opts += o.second + " ";
    if (!opts.empty())
      ret += "[" + opts + "]";

    return ret;
  }

protected:
  int32_t val_;
  std::map<int32_t, std::string> options_;
};


class String : public VariantType
{
public:
  H5::DataType h5_type() const override { return type_of(std::string()); }

  std::string type_name() const override { return "string"; }

  void write(H5::Attribute& attr) const override
  {
    auto data = data_;
    attr.write(this->h5_type(), data);
  }

  void read(const H5::Attribute& attr) override
  {
    attr.read(this->h5_type(), data_);
  }

  std::string to_string() const override
  {
    return data_;
  }

protected:
  std::string data_;
};




}

#endif
