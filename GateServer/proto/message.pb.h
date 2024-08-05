// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_message_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_message_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_message_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_2eproto;
namespace message {
class GetVerifyReq;
class GetVerifyReqDefaultTypeInternal;
extern GetVerifyReqDefaultTypeInternal _GetVerifyReq_default_instance_;
class GetVerifyRsp;
class GetVerifyRspDefaultTypeInternal;
extern GetVerifyRspDefaultTypeInternal _GetVerifyRsp_default_instance_;
}  // namespace message
PROTOBUF_NAMESPACE_OPEN
template<> ::message::GetVerifyReq* Arena::CreateMaybeMessage<::message::GetVerifyReq>(Arena*);
template<> ::message::GetVerifyRsp* Arena::CreateMaybeMessage<::message::GetVerifyRsp>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace message {

enum ErrorCode : int {
  Succeed = 0,
  Error = 1,
  ErrorCode_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ErrorCode_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ErrorCode_IsValid(int value);
constexpr ErrorCode ErrorCode_MIN = Succeed;
constexpr ErrorCode ErrorCode_MAX = Error;
constexpr int ErrorCode_ARRAYSIZE = ErrorCode_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ErrorCode_descriptor();
template<typename T>
inline const std::string& ErrorCode_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ErrorCode>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ErrorCode_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ErrorCode_descriptor(), enum_t_value);
}
inline bool ErrorCode_Parse(
    const std::string& name, ErrorCode* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ErrorCode>(
    ErrorCode_descriptor(), name, value);
}
// ===================================================================

class GetVerifyReq :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.GetVerifyReq) */ {
 public:
  GetVerifyReq();
  virtual ~GetVerifyReq();

  GetVerifyReq(const GetVerifyReq& from);
  GetVerifyReq(GetVerifyReq&& from) noexcept
    : GetVerifyReq() {
    *this = ::std::move(from);
  }

  inline GetVerifyReq& operator=(const GetVerifyReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVerifyReq& operator=(GetVerifyReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const GetVerifyReq& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetVerifyReq* internal_default_instance() {
    return reinterpret_cast<const GetVerifyReq*>(
               &_GetVerifyReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(GetVerifyReq& a, GetVerifyReq& b) {
    a.Swap(&b);
  }
  inline void Swap(GetVerifyReq* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline GetVerifyReq* New() const final {
    return CreateMaybeMessage<GetVerifyReq>(nullptr);
  }

  GetVerifyReq* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<GetVerifyReq>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const GetVerifyReq& from);
  void MergeFrom(const GetVerifyReq& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetVerifyReq* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.GetVerifyReq";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_2eproto);
    return ::descriptor_table_message_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEmailFieldNumber = 1,
  };
  // string email = 1;
  void clear_email();
  const std::string& email() const;
  void set_email(const std::string& value);
  void set_email(std::string&& value);
  void set_email(const char* value);
  void set_email(const char* value, size_t size);
  std::string* mutable_email();
  std::string* release_email();
  void set_allocated_email(std::string* email);
  private:
  const std::string& _internal_email() const;
  void _internal_set_email(const std::string& value);
  std::string* _internal_mutable_email();
  public:

  // @@protoc_insertion_point(class_scope:message.GetVerifyReq)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr email_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// -------------------------------------------------------------------

class GetVerifyRsp :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.GetVerifyRsp) */ {
 public:
  GetVerifyRsp();
  virtual ~GetVerifyRsp();

  GetVerifyRsp(const GetVerifyRsp& from);
  GetVerifyRsp(GetVerifyRsp&& from) noexcept
    : GetVerifyRsp() {
    *this = ::std::move(from);
  }

  inline GetVerifyRsp& operator=(const GetVerifyRsp& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVerifyRsp& operator=(GetVerifyRsp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const GetVerifyRsp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetVerifyRsp* internal_default_instance() {
    return reinterpret_cast<const GetVerifyRsp*>(
               &_GetVerifyRsp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(GetVerifyRsp& a, GetVerifyRsp& b) {
    a.Swap(&b);
  }
  inline void Swap(GetVerifyRsp* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline GetVerifyRsp* New() const final {
    return CreateMaybeMessage<GetVerifyRsp>(nullptr);
  }

  GetVerifyRsp* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<GetVerifyRsp>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const GetVerifyRsp& from);
  void MergeFrom(const GetVerifyRsp& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetVerifyRsp* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.GetVerifyRsp";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_2eproto);
    return ::descriptor_table_message_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEmailFieldNumber = 2,
    kCodeFieldNumber = 3,
    kErrorCodeFieldNumber = 1,
  };
  // string email = 2;
  void clear_email();
  const std::string& email() const;
  void set_email(const std::string& value);
  void set_email(std::string&& value);
  void set_email(const char* value);
  void set_email(const char* value, size_t size);
  std::string* mutable_email();
  std::string* release_email();
  void set_allocated_email(std::string* email);
  private:
  const std::string& _internal_email() const;
  void _internal_set_email(const std::string& value);
  std::string* _internal_mutable_email();
  public:

  // string code = 3;
  void clear_code();
  const std::string& code() const;
  void set_code(const std::string& value);
  void set_code(std::string&& value);
  void set_code(const char* value);
  void set_code(const char* value, size_t size);
  std::string* mutable_code();
  std::string* release_code();
  void set_allocated_code(std::string* code);
  private:
  const std::string& _internal_code() const;
  void _internal_set_code(const std::string& value);
  std::string* _internal_mutable_code();
  public:

  // .message.ErrorCode error_code = 1;
  void clear_error_code();
  ::message::ErrorCode error_code() const;
  void set_error_code(::message::ErrorCode value);
  private:
  ::message::ErrorCode _internal_error_code() const;
  void _internal_set_error_code(::message::ErrorCode value);
  public:

  // @@protoc_insertion_point(class_scope:message.GetVerifyRsp)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr email_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr code_;
  int error_code_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GetVerifyReq

// string email = 1;
inline void GetVerifyReq::clear_email() {
  email_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& GetVerifyReq::email() const {
  // @@protoc_insertion_point(field_get:message.GetVerifyReq.email)
  return _internal_email();
}
inline void GetVerifyReq::set_email(const std::string& value) {
  _internal_set_email(value);
  // @@protoc_insertion_point(field_set:message.GetVerifyReq.email)
}
inline std::string* GetVerifyReq::mutable_email() {
  // @@protoc_insertion_point(field_mutable:message.GetVerifyReq.email)
  return _internal_mutable_email();
}
inline const std::string& GetVerifyReq::_internal_email() const {
  return email_.GetNoArena();
}
inline void GetVerifyReq::_internal_set_email(const std::string& value) {
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void GetVerifyReq::set_email(std::string&& value) {
  
  email_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.GetVerifyReq.email)
}
inline void GetVerifyReq::set_email(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.GetVerifyReq.email)
}
inline void GetVerifyReq::set_email(const char* value, size_t size) {
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.GetVerifyReq.email)
}
inline std::string* GetVerifyReq::_internal_mutable_email() {
  
  return email_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* GetVerifyReq::release_email() {
  // @@protoc_insertion_point(field_release:message.GetVerifyReq.email)
  
  return email_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void GetVerifyReq::set_allocated_email(std::string* email) {
  if (email != nullptr) {
    
  } else {
    
  }
  email_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), email);
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyReq.email)
}

// -------------------------------------------------------------------

// GetVerifyRsp

// .message.ErrorCode error_code = 1;
inline void GetVerifyRsp::clear_error_code() {
  error_code_ = 0;
}
inline ::message::ErrorCode GetVerifyRsp::_internal_error_code() const {
  return static_cast< ::message::ErrorCode >(error_code_);
}
inline ::message::ErrorCode GetVerifyRsp::error_code() const {
  // @@protoc_insertion_point(field_get:message.GetVerifyRsp.error_code)
  return _internal_error_code();
}
inline void GetVerifyRsp::_internal_set_error_code(::message::ErrorCode value) {
  
  error_code_ = value;
}
inline void GetVerifyRsp::set_error_code(::message::ErrorCode value) {
  _internal_set_error_code(value);
  // @@protoc_insertion_point(field_set:message.GetVerifyRsp.error_code)
}

// string email = 2;
inline void GetVerifyRsp::clear_email() {
  email_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& GetVerifyRsp::email() const {
  // @@protoc_insertion_point(field_get:message.GetVerifyRsp.email)
  return _internal_email();
}
inline void GetVerifyRsp::set_email(const std::string& value) {
  _internal_set_email(value);
  // @@protoc_insertion_point(field_set:message.GetVerifyRsp.email)
}
inline std::string* GetVerifyRsp::mutable_email() {
  // @@protoc_insertion_point(field_mutable:message.GetVerifyRsp.email)
  return _internal_mutable_email();
}
inline const std::string& GetVerifyRsp::_internal_email() const {
  return email_.GetNoArena();
}
inline void GetVerifyRsp::_internal_set_email(const std::string& value) {
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void GetVerifyRsp::set_email(std::string&& value) {
  
  email_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.GetVerifyRsp.email)
}
inline void GetVerifyRsp::set_email(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.GetVerifyRsp.email)
}
inline void GetVerifyRsp::set_email(const char* value, size_t size) {
  
  email_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.GetVerifyRsp.email)
}
inline std::string* GetVerifyRsp::_internal_mutable_email() {
  
  return email_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* GetVerifyRsp::release_email() {
  // @@protoc_insertion_point(field_release:message.GetVerifyRsp.email)
  
  return email_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void GetVerifyRsp::set_allocated_email(std::string* email) {
  if (email != nullptr) {
    
  } else {
    
  }
  email_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), email);
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyRsp.email)
}

// string code = 3;
inline void GetVerifyRsp::clear_code() {
  code_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& GetVerifyRsp::code() const {
  // @@protoc_insertion_point(field_get:message.GetVerifyRsp.code)
  return _internal_code();
}
inline void GetVerifyRsp::set_code(const std::string& value) {
  _internal_set_code(value);
  // @@protoc_insertion_point(field_set:message.GetVerifyRsp.code)
}
inline std::string* GetVerifyRsp::mutable_code() {
  // @@protoc_insertion_point(field_mutable:message.GetVerifyRsp.code)
  return _internal_mutable_code();
}
inline const std::string& GetVerifyRsp::_internal_code() const {
  return code_.GetNoArena();
}
inline void GetVerifyRsp::_internal_set_code(const std::string& value) {
  
  code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void GetVerifyRsp::set_code(std::string&& value) {
  
  code_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.GetVerifyRsp.code)
}
inline void GetVerifyRsp::set_code(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.GetVerifyRsp.code)
}
inline void GetVerifyRsp::set_code(const char* value, size_t size) {
  
  code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.GetVerifyRsp.code)
}
inline std::string* GetVerifyRsp::_internal_mutable_code() {
  
  return code_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* GetVerifyRsp::release_code() {
  // @@protoc_insertion_point(field_release:message.GetVerifyRsp.code)
  
  return code_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void GetVerifyRsp::set_allocated_code(std::string* code) {
  if (code != nullptr) {
    
  } else {
    
  }
  code_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), code);
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyRsp.code)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::message::ErrorCode> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::ErrorCode>() {
  return ::message::ErrorCode_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_message_2eproto
