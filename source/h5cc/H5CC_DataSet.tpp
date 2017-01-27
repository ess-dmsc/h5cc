#include "H5CC_Types.h"
#include "H5CC_Exception.h"

namespace H5CC {

#define TT template<typename T>

TT void DataSet::write(const T& data, std::initializer_list<hsize_t> index)
{
  try
  {
    auto space = shape_;
    space.select_element(index);
    Shape dspace({1});
    Location<H5::DataSet>::location_.write(&data, pred_type_of(T()),
                                           dspace.dataspace(), space.dataspace());
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT void DataSet::write(const std::vector<T>& data, Shape slab,
                       std::initializer_list<hsize_t> index)
{
  try
  {
    auto space = shape_;
    if (space.contains(slab, index))
      space.select_slab(slab, index);
    else if (space.can_contain(slab, index))
    {
      std::vector<hsize_t> start(index.begin(), index.end());
      std::vector<hsize_t> newsize;
      for (size_t i=0; i < shape_.rank(); ++i)
        newsize.push_back(std::max(shape_.dim(i), slab.dim(i) + start.at(i)));
      Location<H5::DataSet>::location_.extend(newsize.data());
    }
    else
      throw std::out_of_range("slab selection out of data space range");
    Location<H5::DataSet>::location_.write(data.data(), pred_type_of(T()),
                                           slab.dataspace(), space.dataspace());
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT void DataSet::write(const std::vector<T>& data,
                       std::initializer_list<int> slab_size,
                       std::initializer_list<hsize_t> index)
{
  write(data, shape_.slab_shape(slab_size), index);
}

TT void DataSet::write(const std::vector<T>& data)
{
  if (data.size() != shape_.data_size())
    throw std::out_of_range("Data size does not match H5::DataSpace size");
  try
  {
    Location<H5::DataSet>::location_.write(data.data(), pred_type_of(T()), shape_.dataspace());
  }
  catch (...)
  {
    Exception::rethrow();
  }
}


TT T DataSet::read(std::initializer_list<hsize_t> index) const
{
  try
  {
    T data;
    auto space = shape_;
    space.select_element(index);
    Shape dspace({1});
    Location<H5::DataSet>::location_.read(&data, pred_type_of(T()),
                                          dspace.dataspace(), space.dataspace());
    return data;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT std::vector<T> DataSet::read(Shape slab, std::initializer_list<hsize_t> index) const
{
  try
  {
    auto space = shape_;
    space.select_slab(slab, index);
    std::vector<T> data(slab.data_size());
    Location<H5::DataSet>::location_.read(data.data(), pred_type_of(T()),
                                          slab.dataspace(), space.dataspace());
    return data;
  }
  catch (...)
  {
    Exception::rethrow();
  }
}

TT std::vector<T> DataSet::read(std::initializer_list<int> slab_size,
                                std::initializer_list<hsize_t> index) const
{
  return read<T>(shape_.slab_shape(slab_size), index);
}

TT std::vector<T> DataSet::read() const
{
  std::vector<T> data;
  try
  {
    data.resize(shape_.data_size());
    Location<H5::DataSet>::location_.read(data.data(), pred_type_of(T()),
                                          shape_.dataspace());
  }
  catch (...)
  {
    Exception::rethrow();
  }
  return data;
}

#undef TT

}
