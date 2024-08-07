// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: base.proto

#include "base.pb.h"

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
PROTOBUF_CONSTEXPR Error::Error(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.message_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.code_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ErrorDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ErrorDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ErrorDefaultTypeInternal() {}
  union {
    Error _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ErrorDefaultTypeInternal _Error_default_instance_;
PROTOBUF_CONSTEXPR Request::Request(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.params_)*/{}
  , /*decltype(_impl_.method_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.id_)*/uint64_t{0u}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct RequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RequestDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RequestDefaultTypeInternal() {}
  union {
    Request _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RequestDefaultTypeInternal _Request_default_instance_;
PROTOBUF_CONSTEXPR Response::Response(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.result_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.error_)*/nullptr
  , /*decltype(_impl_.id_)*/uint64_t{0u}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ResponseDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ResponseDefaultTypeInternal() {}
  union {
    Response _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ResponseDefaultTypeInternal _Response_default_instance_;
}  // namespace protorpc
static ::_pb::Metadata file_level_metadata_base_2eproto[3];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_base_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_base_2eproto = nullptr;

const uint32_t TableStruct_base_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protorpc::Error, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protorpc::Error, _impl_.code_),
  PROTOBUF_FIELD_OFFSET(::protorpc::Error, _impl_.message_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protorpc::Request, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protorpc::Request, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::protorpc::Request, _impl_.method_),
  PROTOBUF_FIELD_OFFSET(::protorpc::Request, _impl_.params_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protorpc::Response, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::protorpc::Response, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::protorpc::Response, _impl_.result_),
  PROTOBUF_FIELD_OFFSET(::protorpc::Response, _impl_.error_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::protorpc::Error)},
  { 8, -1, -1, sizeof(::protorpc::Request)},
  { 17, -1, -1, sizeof(::protorpc::Response)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::protorpc::_Error_default_instance_._instance,
  &::protorpc::_Request_default_instance_._instance,
  &::protorpc::_Response_default_instance_._instance,
};

const char descriptor_table_protodef_base_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nbase.proto\022\010protorpc\"&\n\005Error\022\014\n\004code\030"
  "\001 \001(\005\022\017\n\007message\030\002 \001(\t\"5\n\007Request\022\n\n\002id\030"
  "\001 \001(\004\022\016\n\006method\030\002 \001(\t\022\016\n\006params\030\003 \003(\014\"F\n"
  "\010Response\022\n\n\002id\030\001 \001(\004\022\016\n\006result\030\002 \001(\014\022\036\n"
  "\005error\030\003 \001(\0132\017.protorpc.Errorb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_base_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_base_2eproto = {
    false, false, 197, descriptor_table_protodef_base_2eproto,
    "base.proto",
    &descriptor_table_base_2eproto_once, nullptr, 0, 3,
    schemas, file_default_instances, TableStruct_base_2eproto::offsets,
    file_level_metadata_base_2eproto, file_level_enum_descriptors_base_2eproto,
    file_level_service_descriptors_base_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_base_2eproto_getter() {
  return &descriptor_table_base_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_base_2eproto(&descriptor_table_base_2eproto);
namespace protorpc {

// ===================================================================

class Error::_Internal {
 public:
};

Error::Error(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protorpc.Error)
}
Error::Error(const Error& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Error* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.message_){}
    , decltype(_impl_.code_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.message_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.message_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_message().empty()) {
    _this->_impl_.message_.Set(from._internal_message(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.code_ = from._impl_.code_;
  // @@protoc_insertion_point(copy_constructor:protorpc.Error)
}

inline void Error::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.message_){}
    , decltype(_impl_.code_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.message_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.message_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Error::~Error() {
  // @@protoc_insertion_point(destructor:protorpc.Error)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Error::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.message_.Destroy();
}

void Error::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Error::Clear() {
// @@protoc_insertion_point(message_clear_start:protorpc.Error)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.message_.ClearToEmpty();
  _impl_.code_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Error::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.code_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string message = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_message();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "protorpc.Error.message"));
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

uint8_t* Error::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protorpc.Error)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 code = 1;
  if (this->_internal_code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_code(), target);
  }

  // string message = 2;
  if (!this->_internal_message().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "protorpc.Error.message");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_message(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protorpc.Error)
  return target;
}

size_t Error::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protorpc.Error)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 2;
  if (!this->_internal_message().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  // int32 code = 1;
  if (this->_internal_code() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_code());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Error::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Error::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Error::GetClassData() const { return &_class_data_; }


void Error::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Error*>(&to_msg);
  auto& from = static_cast<const Error&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protorpc.Error)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_message().empty()) {
    _this->_internal_set_message(from._internal_message());
  }
  if (from._internal_code() != 0) {
    _this->_internal_set_code(from._internal_code());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Error::CopyFrom(const Error& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protorpc.Error)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Error::IsInitialized() const {
  return true;
}

void Error::InternalSwap(Error* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.message_, lhs_arena,
      &other->_impl_.message_, rhs_arena
  );
  swap(_impl_.code_, other->_impl_.code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Error::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_base_2eproto_getter, &descriptor_table_base_2eproto_once,
      file_level_metadata_base_2eproto[0]);
}

// ===================================================================

class Request::_Internal {
 public:
};

Request::Request(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protorpc.Request)
}
Request::Request(const Request& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Request* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.params_){from._impl_.params_}
    , decltype(_impl_.method_){}
    , decltype(_impl_.id_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.method_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.method_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_method().empty()) {
    _this->_impl_.method_.Set(from._internal_method(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.id_ = from._impl_.id_;
  // @@protoc_insertion_point(copy_constructor:protorpc.Request)
}

inline void Request::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.params_){arena}
    , decltype(_impl_.method_){}
    , decltype(_impl_.id_){uint64_t{0u}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.method_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.method_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Request::~Request() {
  // @@protoc_insertion_point(destructor:protorpc.Request)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Request::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.params_.~RepeatedPtrField();
  _impl_.method_.Destroy();
}

void Request::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Request::Clear() {
// @@protoc_insertion_point(message_clear_start:protorpc.Request)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.params_.Clear();
  _impl_.method_.ClearToEmpty();
  _impl_.id_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Request::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string method = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_method();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "protorpc.Request.method"));
        } else
          goto handle_unusual;
        continue;
      // repeated bytes params = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_params();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<26>(ptr));
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

uint8_t* Request::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protorpc.Request)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // string method = 2;
  if (!this->_internal_method().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_method().data(), static_cast<int>(this->_internal_method().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "protorpc.Request.method");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_method(), target);
  }

  // repeated bytes params = 3;
  for (int i = 0, n = this->_internal_params_size(); i < n; i++) {
    const auto& s = this->_internal_params(i);
    target = stream->WriteBytes(3, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protorpc.Request)
  return target;
}

size_t Request::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protorpc.Request)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated bytes params = 3;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.params_.size());
  for (int i = 0, n = _impl_.params_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
      _impl_.params_.Get(i));
  }

  // string method = 2;
  if (!this->_internal_method().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_method());
  }

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Request::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Request::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Request::GetClassData() const { return &_class_data_; }


void Request::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Request*>(&to_msg);
  auto& from = static_cast<const Request&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protorpc.Request)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.params_.MergeFrom(from._impl_.params_);
  if (!from._internal_method().empty()) {
    _this->_internal_set_method(from._internal_method());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Request::CopyFrom(const Request& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protorpc.Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Request::IsInitialized() const {
  return true;
}

void Request::InternalSwap(Request* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.params_.InternalSwap(&other->_impl_.params_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.method_, lhs_arena,
      &other->_impl_.method_, rhs_arena
  );
  swap(_impl_.id_, other->_impl_.id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Request::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_base_2eproto_getter, &descriptor_table_base_2eproto_once,
      file_level_metadata_base_2eproto[1]);
}

// ===================================================================

class Response::_Internal {
 public:
  static const ::protorpc::Error& error(const Response* msg);
};

const ::protorpc::Error&
Response::_Internal::error(const Response* msg) {
  return *msg->_impl_.error_;
}
Response::Response(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protorpc.Response)
}
Response::Response(const Response& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Response* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.result_){}
    , decltype(_impl_.error_){nullptr}
    , decltype(_impl_.id_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.result_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.result_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_result().empty()) {
    _this->_impl_.result_.Set(from._internal_result(), 
      _this->GetArenaForAllocation());
  }
  if (from._internal_has_error()) {
    _this->_impl_.error_ = new ::protorpc::Error(*from._impl_.error_);
  }
  _this->_impl_.id_ = from._impl_.id_;
  // @@protoc_insertion_point(copy_constructor:protorpc.Response)
}

inline void Response::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.result_){}
    , decltype(_impl_.error_){nullptr}
    , decltype(_impl_.id_){uint64_t{0u}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.result_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.result_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Response::~Response() {
  // @@protoc_insertion_point(destructor:protorpc.Response)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Response::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.result_.Destroy();
  if (this != internal_default_instance()) delete _impl_.error_;
}

void Response::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Response::Clear() {
// @@protoc_insertion_point(message_clear_start:protorpc.Response)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.result_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && _impl_.error_ != nullptr) {
    delete _impl_.error_;
  }
  _impl_.error_ = nullptr;
  _impl_.id_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Response::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes result = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_result();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .protorpc.Error error = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_error(), ptr);
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

uint8_t* Response::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protorpc.Response)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // bytes result = 2;
  if (!this->_internal_result().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_result(), target);
  }

  // .protorpc.Error error = 3;
  if (this->_internal_has_error()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(3, _Internal::error(this),
        _Internal::error(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protorpc.Response)
  return target;
}

size_t Response::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protorpc.Response)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes result = 2;
  if (!this->_internal_result().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_result());
  }

  // .protorpc.Error error = 3;
  if (this->_internal_has_error()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.error_);
  }

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Response::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Response::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Response::GetClassData() const { return &_class_data_; }


void Response::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Response*>(&to_msg);
  auto& from = static_cast<const Response&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protorpc.Response)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_result().empty()) {
    _this->_internal_set_result(from._internal_result());
  }
  if (from._internal_has_error()) {
    _this->_internal_mutable_error()->::protorpc::Error::MergeFrom(
        from._internal_error());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Response::CopyFrom(const Response& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protorpc.Response)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Response::IsInitialized() const {
  return true;
}

void Response::InternalSwap(Response* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.result_, lhs_arena,
      &other->_impl_.result_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Response, _impl_.id_)
      + sizeof(Response::_impl_.id_)
      - PROTOBUF_FIELD_OFFSET(Response, _impl_.error_)>(
          reinterpret_cast<char*>(&_impl_.error_),
          reinterpret_cast<char*>(&other->_impl_.error_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Response::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_base_2eproto_getter, &descriptor_table_base_2eproto_once,
      file_level_metadata_base_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protorpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protorpc::Error*
Arena::CreateMaybeMessage< ::protorpc::Error >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protorpc::Error >(arena);
}
template<> PROTOBUF_NOINLINE ::protorpc::Request*
Arena::CreateMaybeMessage< ::protorpc::Request >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protorpc::Request >(arena);
}
template<> PROTOBUF_NOINLINE ::protorpc::Response*
Arena::CreateMaybeMessage< ::protorpc::Response >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protorpc::Response >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
