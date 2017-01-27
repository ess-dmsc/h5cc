#ifndef H5CC_SPACE_H
#define H5CC_SPACE_H

#include <H5Cpp.h>
#include <vector>

namespace H5CC {

class Space
{
public:
  Space() {}
  Space(const H5::DataSpace& sp);
  Space(std::vector<hsize_t> dimensions,
        std::vector<hsize_t> max_dimensions = {});
  Space(std::initializer_list<hsize_t> dimensions,
        std::initializer_list<hsize_t> max_dimensions = {});

  Space slab_space(std::initializer_list<int> list) const;
  size_t data_size() const;

  bool contains(const Space& other) const;
  bool contains(const std::vector<hsize_t>& index) const;
  bool contains(const Space& other, const std::vector<hsize_t>& index) const;

  bool can_contain(const Space& other) const;
  bool can_contain(const std::vector<hsize_t>& index) const;
  bool can_contain(const Space& other, const std::vector<hsize_t>& index) const;

  void select_slab(const Space& slabspace, std::initializer_list<hsize_t> index);
  void select_element(std::initializer_list<hsize_t> index);

  size_t rank() const;
  hsize_t dim(size_t) const;
  hsize_t max_dim(size_t) const;
  std::vector<hsize_t> dims() const { return dims_; }
  std::vector<hsize_t> max_dims() const { return max_dims_; }
  H5::DataSpace space() const { return space_; }

  std::string debug() const;

private:
  H5::DataSpace space_;
  std::vector<hsize_t> dims_;
  std::vector<hsize_t> max_dims_;

  static std::string dims_to_string(const std::vector<hsize_t>& d);
};

}

#endif
