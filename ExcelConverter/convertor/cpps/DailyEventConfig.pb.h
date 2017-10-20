// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DailyEventConfig.proto

#ifndef PROTOBUF_DailyEventConfig_2eproto__INCLUDED
#define PROTOBUF_DailyEventConfig_2eproto__INCLUDED

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
#include "GroupTypeConfig.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_DailyEventConfig_2eproto();
void protobuf_AssignDesc_DailyEventConfig_2eproto();
void protobuf_ShutdownFile_DailyEventConfig_2eproto();

class DailyEventConfig;

// ===================================================================

class DailyEventConfig : public ::google::protobuf::Message {
 public:
  DailyEventConfig();
  virtual ~DailyEventConfig();

  DailyEventConfig(const DailyEventConfig& from);

  inline DailyEventConfig& operator=(const DailyEventConfig& from) {
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
  static const DailyEventConfig& default_instance();

  void Swap(DailyEventConfig* other);

  // implements Message ----------------------------------------------

  DailyEventConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DailyEventConfig& from);
  void MergeFrom(const DailyEventConfig& from);
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

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // required int32 open_time = 2;
  inline bool has_open_time() const;
  inline void clear_open_time();
  static const int kOpenTimeFieldNumber = 2;
  inline ::google::protobuf::int32 open_time() const;
  inline void set_open_time(::google::protobuf::int32 value);

  // required int32 close_time = 3;
  inline bool has_close_time() const;
  inline void clear_close_time();
  static const int kCloseTimeFieldNumber = 3;
  inline ::google::protobuf::int32 close_time() const;
  inline void set_close_time(::google::protobuf::int32 value);

  // required int32 activity_id = 4;
  inline bool has_activity_id() const;
  inline void clear_activity_id();
  static const int kActivityIdFieldNumber = 4;
  inline ::google::protobuf::int32 activity_id() const;
  inline void set_activity_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:DailyEventConfig)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_open_time();
  inline void clear_has_open_time();
  inline void set_has_close_time();
  inline void clear_has_close_time();
  inline void set_has_activity_id();
  inline void clear_has_activity_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 open_time_;
  ::google::protobuf::int32 close_time_;
  ::google::protobuf::int32 activity_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_DailyEventConfig_2eproto();
  friend void protobuf_AssignDesc_DailyEventConfig_2eproto();
  friend void protobuf_ShutdownFile_DailyEventConfig_2eproto();

  void InitAsDefaultInstance();
  static DailyEventConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// DailyEventConfig

// required int32 id = 1;
inline bool DailyEventConfig::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DailyEventConfig::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DailyEventConfig::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DailyEventConfig::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 DailyEventConfig::id() const {
  return id_;
}
inline void DailyEventConfig::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required int32 open_time = 2;
inline bool DailyEventConfig::has_open_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DailyEventConfig::set_has_open_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DailyEventConfig::clear_has_open_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DailyEventConfig::clear_open_time() {
  open_time_ = 0;
  clear_has_open_time();
}
inline ::google::protobuf::int32 DailyEventConfig::open_time() const {
  return open_time_;
}
inline void DailyEventConfig::set_open_time(::google::protobuf::int32 value) {
  set_has_open_time();
  open_time_ = value;
}

// required int32 close_time = 3;
inline bool DailyEventConfig::has_close_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DailyEventConfig::set_has_close_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DailyEventConfig::clear_has_close_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DailyEventConfig::clear_close_time() {
  close_time_ = 0;
  clear_has_close_time();
}
inline ::google::protobuf::int32 DailyEventConfig::close_time() const {
  return close_time_;
}
inline void DailyEventConfig::set_close_time(::google::protobuf::int32 value) {
  set_has_close_time();
  close_time_ = value;
}

// required int32 activity_id = 4;
inline bool DailyEventConfig::has_activity_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DailyEventConfig::set_has_activity_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DailyEventConfig::clear_has_activity_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DailyEventConfig::clear_activity_id() {
  activity_id_ = 0;
  clear_has_activity_id();
}
inline ::google::protobuf::int32 DailyEventConfig::activity_id() const {
  return activity_id_;
}
inline void DailyEventConfig::set_activity_id(::google::protobuf::int32 value) {
  set_has_activity_id();
  activity_id_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DailyEventConfig_2eproto__INCLUDED
