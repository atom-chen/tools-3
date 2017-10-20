// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GroupTypeConfig.proto

#ifndef PROTOBUF_GroupTypeConfig_2eproto__INCLUDED
#define PROTOBUF_GroupTypeConfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GroupTypeConfig_2eproto();
void protobuf_AssignDesc_GroupTypeConfig_2eproto();
void protobuf_ShutdownFile_GroupTypeConfig_2eproto();

class GroupTypeConfig;

// ===================================================================

class GroupTypeConfig : public ::google::protobuf::Message {
 public:
  GroupTypeConfig();
  virtual ~GroupTypeConfig();

  GroupTypeConfig(const GroupTypeConfig& from);

  inline GroupTypeConfig& operator=(const GroupTypeConfig& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GroupTypeConfig& default_instance();

  void Swap(GroupTypeConfig* other);

  // implements Message ----------------------------------------------

  GroupTypeConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GroupTypeConfig& from);
  void MergeFrom(const GroupTypeConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 array = 1;
  inline int array_size() const;
  inline void clear_array();
  static const int kArrayFieldNumber = 1;
  inline ::google::protobuf::int32 array(int index) const;
  inline void set_array(int index, ::google::protobuf::int32 value);
  inline void add_array(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      array() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_array();

  // @@protoc_insertion_point(class_scope:GroupTypeConfig)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > array_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_GroupTypeConfig_2eproto();
  friend void protobuf_AssignDesc_GroupTypeConfig_2eproto();
  friend void protobuf_ShutdownFile_GroupTypeConfig_2eproto();

  void InitAsDefaultInstance();
  static GroupTypeConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// GroupTypeConfig

// repeated int32 array = 1;
inline int GroupTypeConfig::array_size() const {
  return array_.size();
}
inline void GroupTypeConfig::clear_array() {
  array_.Clear();
}
inline ::google::protobuf::int32 GroupTypeConfig::array(int index) const {
  return array_.Get(index);
}
inline void GroupTypeConfig::set_array(int index, ::google::protobuf::int32 value) {
  array_.Set(index, value);
}
inline void GroupTypeConfig::add_array(::google::protobuf::int32 value) {
  array_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GroupTypeConfig::array() const {
  return array_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GroupTypeConfig::mutable_array() {
  return &array_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GroupTypeConfig_2eproto__INCLUDED
