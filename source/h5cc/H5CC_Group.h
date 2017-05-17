#pragma once

#include "H5CC_DataSet.h"

namespace H5CC {

template<typename T>
class Groupoid : public Location<T>
{
public:
  Groupoid() : Location<T>() {}
  Groupoid(T t, std::string name) : Location<T>(t, name) {}

  bool empty() const;
  std::list<std::string> members() const;
  std::list<std::string> members(H5O_type_t t) const;
  bool has_member(std::string name) const;
  bool has_member(std::string name, H5O_type_t t) const;
  void remove(std::string name);
  void clear();

  bool has_dataset(std::string name) const { return has_member(name, H5O_TYPE_DATASET); }
  std::list<std::string> datasets() const { return members(H5O_TYPE_DATASET); }
  DataSet open_dataset(std::string name) const;
  template <typename DT> DataSet create_dataset(const std::string& name,
                         const std::vector<hsize_t>& dimensions,
                         const std::vector<hsize_t>& chunk_dimensions = {});
  template <typename DT> DataSet require_dataset(const std::string& name,
                         const std::vector<hsize_t>& dims,
                         const std::vector<hsize_t>& chunkdims = {});

  bool has_group(std::string name) const { return has_member(name, H5O_TYPE_GROUP); }
  std::list<std::string> groups() const { return members(H5O_TYPE_GROUP); }
  Groupoid<H5::Group> open_group(std::string name) const;
  Groupoid<H5::Group> create_group(std::string name);
  Groupoid<H5::Group> require_group(std::string name);
};

class Group : public Groupoid<H5::Group>
{
public:
  Group();
  Group(H5::Group g, std::string name);
  //This his hacky. Can we get name of group from hid?
  Group(hid_t hid, std::string name = "_from_hid");
};

}

#include "H5CC_Group.tpp"

