#include "H5CC_File.h"
#include "ExceptionUtil.h"
#include <cassert>
#include <iostream>

int main(int argc, char* argv[])
{
  H5CC::File file("f1.h5");

  std::vector<uint16_t> d {1,2,3,4,5,6,7,8,9};
//  file.open("f1.h5"); //Broken!
  auto dataset = file.create_dataset<uint16_t>("dset", {3,3});
  std::cout << dataset.debug() << "\n";

  dataset.write(d);

  auto d2 = dataset.read<uint16_t>();

  assert(d.size() == d2.size());
  bool same = true;
  for (size_t i=0; i < d.size(); ++i)
  {
//    std::cout << i << " = " << d.at(i) << " " << d2.at(i) << "\n";
    same = same && (d.at(i) == d2.at(i));
  }
  assert(same);

  dataset.write_attribute("a1", int(3));
  assert(dataset.has_attribute("a1"));
  assert(!dataset.has_attribute("a2"));
  int a1 = dataset.read_attribute<int>("a1");
  assert(a1 == 3);

//  for (auto a : dataset.attributes())
//    cout << a << " = " << dataset.read_attribute(a).to_string() << endl;
  try
  {
    dataset.read_attribute<int>("a2");
  }
  catch (...)
  {
    printException();
  }

  dataset.remove_attribute("a1");
  assert(!dataset.has_attribute("a1"));


  dataset.write_attribute("a4", std::string("hello"));
  dataset.write_attribute("a5", uint32_t(77));

  dataset.write_attribute("a6", bool(true));
  auto a6 = dataset.read_attribute<bool>("a6");
  assert(a6 == true);

  dataset.write_attribute("a7", bool(false));
  auto a7 = dataset.read_attribute<bool>("a7");
  assert(a7 == false);

  auto str4 = dataset.read_attribute<std::string>("a4");
  assert(str4 == "hello");

  file.create_group("g1");
  assert(file.has_group("g1"));
  assert(!file.has_group("g2"));
  auto g1 = file.open_group("g1");
  assert(g1.name() == "g1");

  try
  {
    file.open_group("g2");
  }
  catch (...)
  {
    printException();
  }

  auto g2 = file.require_group("g2");
  assert(file.has_group("g2"));
  assert(g2.name() == "g2");

  file.remove("g1");
  assert(!file.has_group("g1"));

  assert(!g2.has_dataset("dset2"));
  auto dataset2 = g2.require_dataset<double>("dset2", {3,3});
  assert(g2.has_dataset("dset2"));
  assert(dataset2.name() == "dset2");

  g2.remove("dset2");
  assert(!g2.has_dataset("dset2"));

  return 0;
}
