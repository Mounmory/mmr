// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mutlti.proto

#include "mutlti.pb.h"

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

namespace com {
namespace example {
PROTOBUF_CONSTEXPR Message1::Message1(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.data_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct Message1DefaultTypeInternal {
  PROTOBUF_CONSTEXPR Message1DefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~Message1DefaultTypeInternal() {}
  union {
    Message1 _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 Message1DefaultTypeInternal _Message1_default_instance_;
PROTOBUF_CONSTEXPR Message2::Message2(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.id_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct Message2DefaultTypeInternal {
  PROTOBUF_CONSTEXPR Message2DefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~Message2DefaultTypeInternal() {}
  union {
    Message2 _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 Message2DefaultTypeInternal _Message2_default_instance_;
}  // namespace example
}  // namespace com
static ::_pb::Metadata file_level_metadata_mutlti_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_mutlti_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_mutlti_2eproto = nullptr;

const uint32_t TableStruct_mutlti_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::com::example::Message1, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::com::example::Message1, _impl_.data_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::com::example::Message2, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::com::example::Message2, _impl_.id_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::com::example::Message1)},
  { 7, -1, -1, sizeof(::com::example::Message2)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::com::example::_Message1_default_instance_._instance,
  &::com::example::_Message2_default_instance_._instance,
};

const char descriptor_table_protodef_mutlti_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014mutlti.proto\022\013com.example\"\030\n\010Message1\022"
  "\014\n\004data\030\001 \001(\t\"\026\n\010Message2\022\n\n\002id\030\001 \001(\005b\006p"
  "roto3"
  ;
static ::_pbi::once_flag descriptor_table_mutlti_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_mutlti_2eproto = {
    false, false, 85, descriptor_table_protodef_mutlti_2eproto,
    "mutlti.proto",
    &descriptor_table_mutlti_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_mutlti_2eproto::offsets,
    file_level_metadata_mutlti_2eproto, file_level_enum_descriptors_mutlti_2eproto,
    file_level_service_descriptors_mutlti_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_mutlti_2eproto_getter() {
  return &descriptor_table_mutlti_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_mutlti_2eproto(&descriptor_table_mutlti_2eproto);
namespace com {
namespace example {

// ===================================================================

class Message1::_Internal {
 public:
};

Message1::Message1(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:com.example.Message1)
}
Message1::Message1(const Message1& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Message1* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.data_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data().empty()) {
    _this->_impl_.data_.Set(from._internal_data(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:com.example.Message1)
}

inline void Message1::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.data_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Message1::~Message1() {
  // @@protoc_insertion_point(destructor:com.example.Message1)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Message1::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.data_.Destroy();
}

void Message1::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Message1::Clear() {
// @@protoc_insertion_point(message_clear_start:com.example.Message1)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.data_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Message1::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_data();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.example.Message1.data"));
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

uint8_t* Message1::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.example.Message1)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.example.Message1.data");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.example.Message1)
  return target;
}

size_t Message1::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:com.example.Message1)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string data = 1;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Message1::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Message1::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Message1::GetClassData() const { return &_class_data_; }


void Message1::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Message1*>(&to_msg);
  auto& from = static_cast<const Message1&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:com.example.Message1)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _this->_internal_set_data(from._internal_data());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Message1::CopyFrom(const Message1& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:com.example.Message1)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Message1::IsInitialized() const {
  return true;
}

void Message1::InternalSwap(Message1* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data_, lhs_arena,
      &other->_impl_.data_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata Message1::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mutlti_2eproto_getter, &descriptor_table_mutlti_2eproto_once,
      file_level_metadata_mutlti_2eproto[0]);
}

// ===================================================================

class Message2::_Internal {
 public:
};

Message2::Message2(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:com.example.Message2)
}
Message2::Message2(const Message2& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Message2* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.id_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.id_ = from._impl_.id_;
  // @@protoc_insertion_point(copy_constructor:com.example.Message2)
}

inline void Message2::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.id_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

Message2::~Message2() {
  // @@protoc_insertion_point(destructor:com.example.Message2)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Message2::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Message2::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Message2::Clear() {
// @@protoc_insertion_point(message_clear_start:com.example.Message2)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.id_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Message2::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
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

uint8_t* Message2::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.example.Message2)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.example.Message2)
  return target;
}

size_t Message2::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:com.example.Message2)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Message2::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Message2::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Message2::GetClassData() const { return &_class_data_; }


void Message2::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Message2*>(&to_msg);
  auto& from = static_cast<const Message2&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:com.example.Message2)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Message2::CopyFrom(const Message2& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:com.example.Message2)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Message2::IsInitialized() const {
  return true;
}

void Message2::InternalSwap(Message2* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.id_, other->_impl_.id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Message2::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_mutlti_2eproto_getter, &descriptor_table_mutlti_2eproto_once,
      file_level_metadata_mutlti_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace example
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::com::example::Message1*
Arena::CreateMaybeMessage< ::com::example::Message1 >(Arena* arena) {
  return Arena::CreateMessageInternal< ::com::example::Message1 >(arena);
}
template<> PROTOBUF_NOINLINE ::com::example::Message2*
Arena::CreateMaybeMessage< ::com::example::Message2 >(Arena* arena) {
  return Arena::CreateMessageInternal< ::com::example::Message2 >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
