#include "H5CC_Space.h"
#include "H5CC_Exception.h"
#include <sstream>

#include <iostream>

namespace H5CC {

Space::Space(const H5::DataSpace& sp)
{
  std::vector<hsize_t> dims;
  std::vector<hsize_t> max_dims;
  try
  {
    int rank = sp.getSimpleExtentNdims();
    if (rank > 0)
    {
      dims.resize(rank, 0);
      max_dims.resize(rank, 0);
      sp.getSimpleExtentDims(dims.data(), max_dims.data());
    }
  }
  catch (...)
  {
    Exception::rethrow();
  }
  space_ = sp;
  dims_ = dims;
  max_dims_ = max_dims;
}

Space::Space (std::initializer_list<hsize_t> dimensions,
              std::initializer_list<hsize_t> max_dimensions)
  : Space(std::vector<hsize_t>(dimensions.begin(), dimensions.end()),
          std::vector<hsize_t>(max_dimensions.begin(), max_dimensions.end()))
{}

Space::Space (std::vector<hsize_t> dimensions,
              std::vector<hsize_t> max_dimensions)
{
  try
  {
    if (max_dimensions.size() && (max_dimensions.size() == dimensions.size()))
      space_ = H5::DataSpace(dimensions.size(), dimensions.data(), max_dimensions.data());
    else
    {
      space_ = H5::DataSpace(dimensions.size(), dimensions.data());
      max_dimensions = dimensions;
    }
    dims_ = dimensions;
    max_dims_ = max_dimensions;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

size_t Space::rank() const
{
  return dims_.size();
}

hsize_t Space::dim(size_t d) const
{
  if (d < dims_.size())
    return dims_.at(d);
  else
    return 0;
}

hsize_t Space::max_dim(size_t d) const
{
  if (d < max_dims_.size())
    return max_dims_.at(d);
  else
    return 0;
}

Space Space::slab_space(std::initializer_list<int> list) const
{
  Space ret;
  if (list.size() <= dims_.size())
  {
    auto newdims = dims_;
    int i=0;
    for (auto &d : list)
    {
      if ((d >= 0) && (d < int(dims_[i])))
        newdims[i] = d;
      i++;
    }

    try
    {
      ret.space_ = H5::DataSpace(newdims.size(), newdims.data());
    }
    catch (...)
    {
      Exception::rethrow();
    }

    ret.dims_ = newdims;
  }
  return ret;
}

size_t Space::data_size() const
{
  if (!rank())
    return 0;
  size_t ret = 1;
  for (auto &d : dims_)
    ret *= d;
  return ret;
}

bool Space::contains(const Space& other) const
{
  if (other.dims_.empty() || (dims_.size() != other.dims_.size()))
    return false;
  for (size_t i=0; i < dims_.size(); ++i)
    if ((other.dims_.at(i) < 1) || (other.dims_.at(i) > dims_.at(i)))
      return false;
  return true;
}

bool Space::contains(const std::vector<hsize_t>& index) const
{
  if (index.empty() || (dims_.size() != index.size()))
    return false;
  for (size_t i=0; i < dims_.size(); ++i)
    if (index.at(i) >= dims_.at(i))
      return false;
  return true;
}

bool Space::contains(const Space& other, const std::vector<hsize_t>& index) const
{
  if (!contains(index))
    return false;
  if (!contains(other))
    return false;
  for (size_t i=0; i < dims_.size(); ++i)
    if ((other.dims_.at(i) + index.at(i)) > dims_.at(i))
      return false;
  return true;
}

bool Space::can_contain(const Space& other) const
{
  if (other.dims_.empty() || (max_dims_.size() != other.dims_.size()))
    return false;
  for (size_t i=0; i < max_dims_.size(); ++i)
    if ((other.dims_.at(i) < 1) || (other.dims_.at(i) > max_dims_.at(i)))
      return false;
  return true;
}

bool Space::can_contain(const std::vector<hsize_t>& index) const
{
  if (index.empty() || (max_dims_.size() != index.size()))
    return false;
  for (size_t i=0; i < max_dims_.size(); ++i)
    if (index.at(i) >= max_dims_.at(i))
      return false;
  return true;
}

bool Space::can_contain(const Space& other, const std::vector<hsize_t>& index) const
{
  if (!can_contain(index))
    return false;
  if (!can_contain(other))
    return false;
  for (size_t i=0; i < max_dims_.size(); ++i)
    if ((other.dims_.at(i) + index.at(i)) > max_dims_.at(i))
      return false;
  return true;
}

void Space::select_slab(const Space& slabspace, std::initializer_list<hsize_t> index)
{
  std::vector<hsize_t> choice(index.begin(), index.end());
  if (!contains(slabspace, choice))
    throw std::out_of_range("slab selection out of data space range");
  try
  {
    space_.selectHyperslab(H5S_SELECT_SET, slabspace.dims_.data(), choice.data());
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

void Space::select_element(std::initializer_list<hsize_t> index)
{
  std::vector<hsize_t> choice(index.begin(), index.end());
  if (!contains(choice))
    throw std::out_of_range("element selection out of data space range");
  try
  {
    space_.selectElements(H5S_SELECT_SET, 1, choice.data());
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

std::string Space::debug() const
{
  std::stringstream ss;
  ss << dims_to_string(dims_);
  if (!max_dims_.empty() && (max_dims_ != dims_))
  {
    ss << " max(" << dims_to_string(max_dims_) << ")";
  }
  if (!space_.isSimple())
    ss << " nonsimple";
  return ss.str();
}

std::string Space::dims_to_string(const std::vector<hsize_t>& d)
{
  if (d.empty())
    return "nullsize";
  std::stringstream ss;
  if (d.at(0) == H5S_UNLIMITED)
    ss << "U";
  else
    ss << d.at(0);
  for (size_t i=1; i < d.size(); ++i)
    if (d.at(i) == H5S_UNLIMITED)
      ss << "xU";
    else
      ss << "x" << d.at(i);
  return ss.str();
}


}
