// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: calc.proto

#include "calc.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace protorpc {
PROTOBUF_CONSTEXPR CalcParam::CalcParam(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.num_)*/int64_t{0}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CalcParamDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CalcParamDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CalcParamDefaultTypeInternal() {}
  union {
    CalcParam _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CalcParamDefaultTypeInternal _CalcParam_default_instance_;
PROTOBUF_CONSTEXPR CalcResult::CalcResult(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.num_)*/int64_t{0}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CalcResultDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CalcResultDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CalcResultDefaultTypeInternal() {}
  union {
    CalcResult _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CalcResultDefaultTypeInternal _CalcResult_default_instance_;
}  // namespace protorpc
static ::_pb::Metadata file_level_metadata_calc_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_calc_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_calc_2eproto = nullptr;

const uint32_t TableStruct_calc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protorpc::CalcParam, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protorpc::CalcParam, _impl_.num_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protorpc::CalcResult, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protorpc::CalcResult, _impl_.num_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::protorpc::CalcParam)},
  { 7, -1, -1, sizeof(::protorpc::CalcResult)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::protorpc::_CalcParam_default_instance_._instance,
  &::protorpc::_CalcResult_default_instance_._instance,
};

const char descriptor_table_protodef_calc_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\ncalc.proto\022\010protorpc\"\030\n\tCalcParam\022\013\n\003n"
  "um\030\001 \001(\003\"\031\n\nCalcResult\022\013\n\003num\030\001 \001(\003b\006pro"
  "to3"
  ;
static ::_pbi::once_flag descriptor_table_calc_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_calc_2eproto = {
    false, false, 83, descriptor_table_protodef_calc_2eproto,
    "calc.proto",
    &descriptor_table_calc_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_calc_2eproto::offsets,
    file_level_metadata_calc_2eproto, file_level_enum_descriptors_calc_2eproto,
    file_level_service_descriptors_calc_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_calc_2eproto_getter() {
  return &descriptor_table_calc_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_calc_2eproto(&descriptor_table_calc_2eproto);
namespace protorpc {

// ===================================================================

class CalcParam::_Internal {
 public:
};

CalcParam::CalcParam(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protorpc.CalcParam)
}
CalcParam::CalcParam(const CalcParam& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CalcParam* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.num_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.num_ = from._impl_.num_;
  // @@protoc_insertion_point(copy_constructor:protorpc.CalcParam)
}

inline void CalcParam::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.num_){int64_t{0}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

CalcParam::~CalcParam() {
  // @@protoc_insertion_point(destructor:protorpc.CalcParam)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CalcParam::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CalcParam::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CalcParam::Clear() {
// @@protoc_insertion_point(message_clear_start:protorpc.CalcParam)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.num_ = int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CalcParam::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 num = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.num_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* CalcParam::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protorpc.CalcParam)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 num = 1;
  if (this->_internal_num() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_num(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protorpc.CalcParam)
  return target;
}

size_t CalcParam::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protorpc.CalcParam)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 num = 1;
  if (this->_internal_num() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_num());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CalcParam::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CalcParam::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CalcParam::GetClassData() const { return &_class_data_; }


void CalcParam::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CalcParam*>(&to_msg);
  auto& from = static_cast<const CalcParam&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protorpc.CalcParam)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_num() != 0) {
    _this->_internal_set_num(from._internal_num());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CalcParam::CopyFrom(const CalcParam& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protorpc.CalcParam)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CalcParam::IsInitialized() const {
  return true;
}

void CalcParam::InternalSwap(CalcParam* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.num_, other->_impl_.num_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CalcParam::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_calc_2eproto_getter, &descriptor_table_calc_2eproto_once,
      file_level_metadata_calc_2eproto[0]);
}

// ===================================================================

class CalcResult::_Internal {
 public:
};

CalcResult::CalcResult(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protorpc.CalcResult)
}
CalcResult::CalcResult(const CalcResult& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CalcResult* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.num_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.num_ = from._impl_.num_;
  // @@protoc_insertion_point(copy_constructor:protorpc.CalcResult)
}

inline void CalcResult::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.num_){int64_t{0}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

CalcResult::~CalcResult() {
  // @@protoc_insertion_point(destructor:protorpc.CalcResult)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CalcResult::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CalcResult::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CalcResult::Clear() {
// @@protoc_insertion_point(message_clear_start:protorpc.CalcResult)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.num_ = int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CalcResult::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 num = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.num_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* CalcResult::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protorpc.CalcResult)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 num = 1;
  if (this->_internal_num() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_num(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protorpc.CalcResult)
  return target;
}

size_t CalcResult::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protorpc.CalcResult)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 num = 1;
  if (this->_internal_num() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_num());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CalcResult::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CalcResult::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CalcResult::GetClassData() const { return &_class_data_; }


void CalcResult::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CalcResult*>(&to_msg);
  auto& from = static_cast<const CalcResult&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protorpc.CalcResult)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_num() != 0) {
    _this->_internal_set_num(from._internal_num());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CalcResult::CopyFrom(const CalcResult& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protorpc.CalcResult)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CalcResult::IsInitialized() const {
  return true;
}

void CalcResult::InternalSwap(CalcResult* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.num_, other->_impl_.num_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CalcResult::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_calc_2eproto_getter, &descriptor_table_calc_2eproto_once,
      file_level_metadata_calc_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protorpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protorpc::CalcParam*
Arena::CreateMaybeMessage< ::protorpc::CalcParam >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protorpc::CalcParam >(arena);
}
template<> PROTOBUF_NOINLINE ::protorpc::CalcResult*
Arena::CreateMaybeMessage< ::protorpc::CalcResult >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protorpc::CalcResult >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
