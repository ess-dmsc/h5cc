#include <H5Cpp.h>

namespace H5CC {

void exceptions_off()
{
  H5::Exception::dontPrint();
}

}
