// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MineCardCountConfig.proto

#ifndef PROTOBUF_MineCardCountConfig_2eproto__INCLUDED
#define PROTOBUF_MineCardCountConfig_2eproto__INCLUDED

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
void  protobuf_AddDesc_MineCardCountConfig_2eproto();
void protobuf_AssignDesc_MineCardCountConfig_2eproto();
void protobuf_ShutdownFile_MineCardCountConfig_2eproto();

class MineCardCountConfig;

// ===================================================================

class MineCardCountConfig : public ::google::protobuf::Message {
 public:
  MineCardCountConfig();
  virtual ~MineCardCountConfig();

  MineCardCountConfig(const MineCardCountConfig& from);

  inline MineCardCountConfig& operator=(const MineCardCountConfig& from) {
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
  static const MineCardCountConfig& default_instance();

  void Swap(MineCardCountConfig* other);

  // implements Message ----------------------------------------------

  MineCardCountConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MineCardCountConfig& from);
  void MergeFrom(const MineCardCountConfig& from);
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

  // required int32 max_card_count = 2;
  inline bool has_max_card_count() const;
  inline void clear_max_card_count();
  static const int kMaxCardCountFieldNumber = 2;
  inline ::google::protobuf::int32 max_card_count() const;
  inline void set_max_card_count(::google::protobuf::int32 value);

  // required int32 max_mine_count = 3;
  inline bool has_max_mine_count() const;
  inline void clear_max_mine_count();
  static const int kMaxMineCountFieldNumber = 3;
  inline ::google::protobuf::int32 max_mine_count() const;
  inline void set_max_mine_count(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MineCardCountConfig)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_max_card_count();
  inline void clear_has_max_card_count();
  inline void set_has_max_mine_count();
  inline void clear_has_max_mine_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 max_card_count_;
  ::google::protobuf::int32 max_mine_count_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_MineCardCountConfig_2eproto();
  friend void protobuf_AssignDesc_MineCardCountConfig_2eproto();
  friend void protobuf_ShutdownFile_MineCardCountConfig_2eproto();

  void InitAsDefaultInstance();
  static MineCardCountConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// MineCardCountConfig

// required int32 id = 1;
inline bool MineCardCountConfig::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MineCardCountConfig::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MineCardCountConfig::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MineCardCountConfig::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 MineCardCountConfig::id() const {
  return id_;
}
inline void MineCardCountConfig::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required int32 max_card_count = 2;
inline bool MineCardCountConfig::has_max_card_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MineCardCountConfig::set_has_max_card_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MineCardCountConfig::clear_has_max_card_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MineCardCountConfig::clear_max_card_count() {
  max_card_count_ = 0;
  clear_has_max_card_count();
}
inline ::google::protobuf::int32 MineCardCountConfig::max_card_count() const {
  return max_card_count_;
}
inline void MineCardCountConfig::set_max_card_count(::google::protobuf::int32 value) {
  set_has_max_card_count();
  max_card_count_ = value;
}

// required int32 max_mine_count = 3;
inline bool MineCardCountConfig::has_max_mine_count() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MineCardCountConfig::set_has_max_mine_count() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MineCardCountConfig::clear_has_max_mine_count() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MineCardCountConfig::clear_max_mine_count() {
  max_mine_count_ = 0;
  clear_has_max_mine_count();
}
inline ::google::protobuf::int32 MineCardCountConfig::max_mine_count() const {
  return max_mine_count_;
}
inline void MineCardCountConfig::set_max_mine_count(::google::protobuf::int32 value) {
  set_has_max_mine_count();
  max_mine_count_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MineCardCountConfig_2eproto__INCLUDED
