#include "H5CC_File.h"
#include "ExceptionUtil.h"
#include <cassert>
#include <iostream>

#include <gtest/gtest.h>

TEST(FileTests, OpenFileTest) {
  H5CC::File file("f1.h5");
  ASSERT_TRUE(file.is_open());
}

class GroupTests : public ::testing::Test
{
public:
  static void SetUpTestCase()
  {
    file.open("f2.h5", H5CC::Access::rw_require);
  }

  static void TearDownTestCase()
  {
    file.close();
  }

  virtual void SetUp()
  {
    file.clear();
  }

  virtual void TearDown()
  {}

  static H5CC::File file;
};

H5CC::File GroupTests::file = H5CC::File();

TEST_F(GroupTests, CreateNewGroup)
{
  GroupTests::file.create_group("group");
  ASSERT_TRUE(GroupTests::file.has_group("group"));
}

TEST_F(GroupTests, HasNonexistentGroup)
{
  ASSERT_FALSE(GroupTests::file.has_group("mythical_group"));
}

//TEST(FileTests, AddHandlerTest) {
//  ASSERT_THROW()
//}


class DatasetTests : public ::testing::Test
{
public:
  static void SetUpTestCase()
  {
    file.open("f3.h5", H5CC::Access::rw_require);
  }

  static void TearDownTestCase()
  {
    file.close();
  }

  virtual void SetUp()
  {
    file.clear();
  }

  virtual void TearDown()
  {}

  static H5CC::File file;
};

H5CC::File DatasetTests::file = H5CC::File();

TEST_F(DatasetTests, CreateSimpleDataset)
{
  DatasetTests::file.create_dataset<uint16_t>("data", {3,3});
  ASSERT_TRUE(DatasetTests::file.has_dataset("data"));
}

TEST_F(DatasetTests, CreateChunckedDataset)
{
  DatasetTests::file.create_dataset<uint16_t>("data", {3,3}, {3,1});
  ASSERT_TRUE(DatasetTests::file.has_dataset("data"));
  ASSERT_TRUE(DatasetTests::file.open_dataset("data").is_chunked());
}

TEST_F(DatasetTests, CreateExendableDataset)
{
  ASSERT_ANY_THROW(DatasetTests::file.create_dataset<uint16_t>("data", {3,H5S_UNLIMITED}));
}

TEST_F(DatasetTests, CreateExendableChunckedDataset)
{
  DatasetTests::file.create_dataset<uint16_t>("data", {3,H5S_UNLIMITED}, {3,1});
  ASSERT_TRUE(DatasetTests::file.has_dataset("data"));
  ASSERT_TRUE(DatasetTests::file.open_dataset("data").is_chunked());
//  std::cout << "before: " << DatasetTests::file.open_dataset("data").debug() << "\n";
  std::vector<uint16_t> data {1, 2, 3};
  DatasetTests::file.open_dataset("data").write(data, {3,1}, {0,7});
  ASSERT_TRUE(DatasetTests::file.open_dataset("data").shape().data_size() == 24);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*

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

  H5CC::Enum<int32_t> e1;
  e1.set_option(0, "zero");
  e1.set_option(1, "one");
  e1.set_option(42, "forty-two");
  e1.set_value(42);
  std::cout << "e1 = " << e1.to_string() << "\n";

  dataset.write_enum("enum1", e1);

  H5CC::Enum<int32_t> e2 = dataset.read_enum<int32_t>("enum1");
  std::cout << "e2 = " << e1.to_string() << "\n";
  assert(e1 == e2);

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

*/
