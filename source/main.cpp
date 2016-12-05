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


  dataset.write_attribute("f1", float(1.42));
  H5CC::VariantPtr f1 = dataset.read_variant("f1");
  std::cout << "f1 = " << f1->debug() << "\n";

  dataset.write_attribute("f2", double(1.42));
  H5CC::VariantPtr f2 = dataset.read_variant("f2");
  std::cout << "f2 = " << f2->debug() << "\n";

  dataset.write_attribute("f3", (long double)(1.42));
  H5CC::VariantPtr f3 = dataset.read_variant("f3");
  std::cout << "f3 = " << f3->debug() << "\n";



  dataset.write_attribute("a3", int64_t(-666));
  H5CC::VariantPtr v3 = dataset.read_variant("a3");
  std::cout << "v3 = " << v3->debug() << "\n";

  dataset.write_attribute("a3a", int32_t(-666));
  H5CC::VariantPtr v3a = dataset.read_variant("a3a");
  std::cout << "v3a = " << v3a->debug() << "\n";

  dataset.write_attribute("a3b", int16_t(-666));
  H5CC::VariantPtr v3b = dataset.read_variant("a3b");
  std::cout << "v3b = " << v3b->debug() << "\n";

  dataset.write_attribute("a3c", int8_t(-6));
  H5CC::VariantPtr v3c = dataset.read_variant("a3c");
  std::cout << "v3c = " << v3c->debug() << "\n";



  dataset.write_attribute("b3", uint64_t(666));
  H5CC::VariantPtr b3 = dataset.read_variant("b3");
  std::cout << "b3 = " << b3->debug() << "\n";

  dataset.write_attribute("b3a", uint32_t(666));
  H5CC::VariantPtr b3a = dataset.read_variant("b3a");
  std::cout << "b3a = " << b3a->debug() << "\n";

  dataset.write_attribute("b3b", uint16_t(666));
  H5CC::VariantPtr b3b = dataset.read_variant("b3b");
  std::cout << "b3b = " << b3b->debug() << "\n";

  dataset.write_attribute("b3c", uint8_t(6));
  H5CC::VariantPtr b3c = dataset.read_variant("b3c");
  std::cout << "b3c = " << b3c->debug() << "\n";


  dataset.write_attribute("a4", std::string("hello"));
  dataset.write_attribute("a5", uint32_t(77));

  dataset.write_attribute("a6", bool(true));
  auto a6 = dataset.read_attribute<bool>("a6");
  assert(a6 == true);

  H5CC::VariantPtr aa6 = dataset.read_variant("a6");
  std::cout << "aa6 = " << aa6->debug() << "\n";

  dataset.write_attribute("a7", bool(false));
  auto a7 = dataset.read_attribute<bool>("a7");
  assert(a7 == false);

  H5CC::VariantPtr aa7 = dataset.read_variant("a7");
  std::cout << "aa7 = " << aa7->debug() << "\n";

  auto str4 = dataset.read_attribute<std::string>("a4");
  assert(str4 == "hello");

  H5CC::VariantPtr strv = dataset.read_variant("a4");
  std::cout << "strv = " << strv->debug() << "\n";

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
