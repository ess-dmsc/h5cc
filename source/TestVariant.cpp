#include "TestVariant.h"

namespace H5CC {

static VariantRegistrar<Atomic<int8_t>> registrar_int8;
static VariantRegistrar<Atomic<int16_t>> registrar_int16;
static VariantRegistrar<Atomic<int32_t>> registrar_int32;
static VariantRegistrar<Atomic<int64_t>> registrar_int64;

static VariantRegistrar<Atomic<uint8_t>> registrar_uint8;
static VariantRegistrar<Atomic<uint16_t>> registrar_uint16;
static VariantRegistrar<Atomic<uint32_t>> registrar_uint32;
static VariantRegistrar<Atomic<uint64_t>> registrar_uint64;

static VariantRegistrar<Atomic<float>> registrar_float;
static VariantRegistrar<Atomic<double>> registrar_double;
static VariantRegistrar<Atomic<long double>> registrar_long_double;

static VariantRegistrar<String> registrar_string;

//static Enum eee({"False", "True"});
//VariantFactory::getInstance().register_type(eee.type_name(), eee.h5_type(),
//                                            []() { return new Enum();});



}



