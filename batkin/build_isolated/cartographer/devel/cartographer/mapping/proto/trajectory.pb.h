// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cartographer/mapping/proto/trajectory.proto

#ifndef PROTOBUF_cartographer_2fmapping_2fproto_2ftrajectory_2eproto__INCLUDED
#define PROTOBUF_cartographer_2fmapping_2fproto_2ftrajectory_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "cartographer/transform/proto/transform.pb.h"
// @@protoc_insertion_point(includes)
namespace cartographer {
namespace mapping {
namespace proto {
class Trajectory;
class TrajectoryDefaultTypeInternal;
extern TrajectoryDefaultTypeInternal _Trajectory_default_instance_;
class Trajectory_Node;
class Trajectory_NodeDefaultTypeInternal;
extern Trajectory_NodeDefaultTypeInternal _Trajectory_Node_default_instance_;
class Trajectory_Submap;
class Trajectory_SubmapDefaultTypeInternal;
extern Trajectory_SubmapDefaultTypeInternal _Trajectory_Submap_default_instance_;
}  // namespace proto
}  // namespace mapping
}  // namespace cartographer

namespace cartographer {
namespace mapping {
namespace proto {

namespace protobuf_cartographer_2fmapping_2fproto_2ftrajectory_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_cartographer_2fmapping_2fproto_2ftrajectory_2eproto

// ===================================================================

class Trajectory_Node : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:cartographer.mapping.proto.Trajectory.Node) */ {
 public:
  Trajectory_Node();
  virtual ~Trajectory_Node();

  Trajectory_Node(const Trajectory_Node& from);

  inline Trajectory_Node& operator=(const Trajectory_Node& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Trajectory_Node(Trajectory_Node&& from) noexcept
    : Trajectory_Node() {
    *this = ::std::move(from);
  }

  inline Trajectory_Node& operator=(Trajectory_Node&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Trajectory_Node& default_instance();

  static inline const Trajectory_Node* internal_default_instance() {
    return reinterpret_cast<const Trajectory_Node*>(
               &_Trajectory_Node_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Trajectory_Node* other);
  friend void swap(Trajectory_Node& a, Trajectory_Node& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Trajectory_Node* New() const PROTOBUF_FINAL { return New(NULL); }

  Trajectory_Node* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Trajectory_Node& from);
  void MergeFrom(const Trajectory_Node& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Trajectory_Node* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .cartographer.transform.proto.Rigid3d pose = 5;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 5;
  const ::cartographer::transform::proto::Rigid3d& pose() const;
  ::cartographer::transform::proto::Rigid3d* mutable_pose();
  ::cartographer::transform::proto::Rigid3d* release_pose();
  void set_allocated_pose(::cartographer::transform::proto::Rigid3d* pose);

  // int64 timestamp = 1;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  ::google::protobuf::int64 timestamp() const;
  void set_timestamp(::google::protobuf::int64 value);

  // int32 node_index = 7;
  void clear_node_index();
  static const int kNodeIndexFieldNumber = 7;
  ::google::protobuf::int32 node_index() const;
  void set_node_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:cartographer.mapping.proto.Trajectory.Node)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::cartographer::transform::proto::Rigid3d* pose_;
  ::google::protobuf::int64 timestamp_;
  ::google::protobuf::int32 node_index_;
  mutable int _cached_size_;
  friend struct protobuf_cartographer_2fmapping_2fproto_2ftrajectory_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Trajectory_Submap : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:cartographer.mapping.proto.Trajectory.Submap) */ {
 public:
  Trajectory_Submap();
  virtual ~Trajectory_Submap();

  Trajectory_Submap(const Trajectory_Submap& from);

  inline Trajectory_Submap& operator=(const Trajectory_Submap& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Trajectory_Submap(Trajectory_Submap&& from) noexcept
    : Trajectory_Submap() {
    *this = ::std::move(from);
  }

  inline Trajectory_Submap& operator=(Trajectory_Submap&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Trajectory_Submap& default_instance();

  static inline const Trajectory_Submap* internal_default_instance() {
    return reinterpret_cast<const Trajectory_Submap*>(
               &_Trajectory_Submap_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Trajectory_Submap* other);
  friend void swap(Trajectory_Submap& a, Trajectory_Submap& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Trajectory_Submap* New() const PROTOBUF_FINAL { return New(NULL); }

  Trajectory_Submap* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Trajectory_Submap& from);
  void MergeFrom(const Trajectory_Submap& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Trajectory_Submap* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .cartographer.transform.proto.Rigid3d pose = 1;
  bool has_pose() const;
  void clear_pose();
  static const int kPoseFieldNumber = 1;
  const ::cartographer::transform::proto::Rigid3d& pose() const;
  ::cartographer::transform::proto::Rigid3d* mutable_pose();
  ::cartographer::transform::proto::Rigid3d* release_pose();
  void set_allocated_pose(::cartographer::transform::proto::Rigid3d* pose);

  // int32 submap_index = 2;
  void clear_submap_index();
  static const int kSubmapIndexFieldNumber = 2;
  ::google::protobuf::int32 submap_index() const;
  void set_submap_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:cartographer.mapping.proto.Trajectory.Submap)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::cartographer::transform::proto::Rigid3d* pose_;
  ::google::protobuf::int32 submap_index_;
  mutable int _cached_size_;
  friend struct protobuf_cartographer_2fmapping_2fproto_2ftrajectory_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Trajectory : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:cartographer.mapping.proto.Trajectory) */ {
 public:
  Trajectory();
  virtual ~Trajectory();

  Trajectory(const Trajectory& from);

  inline Trajectory& operator=(const Trajectory& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Trajectory(Trajectory&& from) noexcept
    : Trajectory() {
    *this = ::std::move(from);
  }

  inline Trajectory& operator=(Trajectory&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Trajectory& default_instance();

  static inline const Trajectory* internal_default_instance() {
    return reinterpret_cast<const Trajectory*>(
               &_Trajectory_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(Trajectory* other);
  friend void swap(Trajectory& a, Trajectory& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Trajectory* New() const PROTOBUF_FINAL { return New(NULL); }

  Trajectory* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Trajectory& from);
  void MergeFrom(const Trajectory& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Trajectory* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef Trajectory_Node Node;
  typedef Trajectory_Submap Submap;

  // accessors -------------------------------------------------------

  // repeated .cartographer.mapping.proto.Trajectory.Node node = 1;
  int node_size() const;
  void clear_node();
  static const int kNodeFieldNumber = 1;
  const ::cartographer::mapping::proto::Trajectory_Node& node(int index) const;
  ::cartographer::mapping::proto::Trajectory_Node* mutable_node(int index);
  ::cartographer::mapping::proto::Trajectory_Node* add_node();
  ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Node >*
      mutable_node();
  const ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Node >&
      node() const;

  // repeated .cartographer.mapping.proto.Trajectory.Submap submap = 2;
  int submap_size() const;
  void clear_submap();
  static const int kSubmapFieldNumber = 2;
  const ::cartographer::mapping::proto::Trajectory_Submap& submap(int index) const;
  ::cartographer::mapping::proto::Trajectory_Submap* mutable_submap(int index);
  ::cartographer::mapping::proto::Trajectory_Submap* add_submap();
  ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Submap >*
      mutable_submap();
  const ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Submap >&
      submap() const;

  // int32 trajectory_id = 3;
  void clear_trajectory_id();
  static const int kTrajectoryIdFieldNumber = 3;
  ::google::protobuf::int32 trajectory_id() const;
  void set_trajectory_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:cartographer.mapping.proto.Trajectory)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Node > node_;
  ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Submap > submap_;
  ::google::protobuf::int32 trajectory_id_;
  mutable int _cached_size_;
  friend struct protobuf_cartographer_2fmapping_2fproto_2ftrajectory_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Trajectory_Node

// int32 node_index = 7;
inline void Trajectory_Node::clear_node_index() {
  node_index_ = 0;
}
inline ::google::protobuf::int32 Trajectory_Node::node_index() const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.Node.node_index)
  return node_index_;
}
inline void Trajectory_Node::set_node_index(::google::protobuf::int32 value) {
  
  node_index_ = value;
  // @@protoc_insertion_point(field_set:cartographer.mapping.proto.Trajectory.Node.node_index)
}

// int64 timestamp = 1;
inline void Trajectory_Node::clear_timestamp() {
  timestamp_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Trajectory_Node::timestamp() const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.Node.timestamp)
  return timestamp_;
}
inline void Trajectory_Node::set_timestamp(::google::protobuf::int64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:cartographer.mapping.proto.Trajectory.Node.timestamp)
}

// .cartographer.transform.proto.Rigid3d pose = 5;
inline bool Trajectory_Node::has_pose() const {
  return this != internal_default_instance() && pose_ != NULL;
}
inline void Trajectory_Node::clear_pose() {
  if (GetArenaNoVirtual() == NULL && pose_ != NULL) delete pose_;
  pose_ = NULL;
}
inline const ::cartographer::transform::proto::Rigid3d& Trajectory_Node::pose() const {
  const ::cartographer::transform::proto::Rigid3d* p = pose_;
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.Node.pose)
  return p != NULL ? *p : *reinterpret_cast<const ::cartographer::transform::proto::Rigid3d*>(
      &::cartographer::transform::proto::_Rigid3d_default_instance_);
}
inline ::cartographer::transform::proto::Rigid3d* Trajectory_Node::mutable_pose() {
  
  if (pose_ == NULL) {
    pose_ = new ::cartographer::transform::proto::Rigid3d;
  }
  // @@protoc_insertion_point(field_mutable:cartographer.mapping.proto.Trajectory.Node.pose)
  return pose_;
}
inline ::cartographer::transform::proto::Rigid3d* Trajectory_Node::release_pose() {
  // @@protoc_insertion_point(field_release:cartographer.mapping.proto.Trajectory.Node.pose)
  
  ::cartographer::transform::proto::Rigid3d* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void Trajectory_Node::set_allocated_pose(::cartographer::transform::proto::Rigid3d* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:cartographer.mapping.proto.Trajectory.Node.pose)
}

// -------------------------------------------------------------------

// Trajectory_Submap

// int32 submap_index = 2;
inline void Trajectory_Submap::clear_submap_index() {
  submap_index_ = 0;
}
inline ::google::protobuf::int32 Trajectory_Submap::submap_index() const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.Submap.submap_index)
  return submap_index_;
}
inline void Trajectory_Submap::set_submap_index(::google::protobuf::int32 value) {
  
  submap_index_ = value;
  // @@protoc_insertion_point(field_set:cartographer.mapping.proto.Trajectory.Submap.submap_index)
}

// .cartographer.transform.proto.Rigid3d pose = 1;
inline bool Trajectory_Submap::has_pose() const {
  return this != internal_default_instance() && pose_ != NULL;
}
inline void Trajectory_Submap::clear_pose() {
  if (GetArenaNoVirtual() == NULL && pose_ != NULL) delete pose_;
  pose_ = NULL;
}
inline const ::cartographer::transform::proto::Rigid3d& Trajectory_Submap::pose() const {
  const ::cartographer::transform::proto::Rigid3d* p = pose_;
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.Submap.pose)
  return p != NULL ? *p : *reinterpret_cast<const ::cartographer::transform::proto::Rigid3d*>(
      &::cartographer::transform::proto::_Rigid3d_default_instance_);
}
inline ::cartographer::transform::proto::Rigid3d* Trajectory_Submap::mutable_pose() {
  
  if (pose_ == NULL) {
    pose_ = new ::cartographer::transform::proto::Rigid3d;
  }
  // @@protoc_insertion_point(field_mutable:cartographer.mapping.proto.Trajectory.Submap.pose)
  return pose_;
}
inline ::cartographer::transform::proto::Rigid3d* Trajectory_Submap::release_pose() {
  // @@protoc_insertion_point(field_release:cartographer.mapping.proto.Trajectory.Submap.pose)
  
  ::cartographer::transform::proto::Rigid3d* temp = pose_;
  pose_ = NULL;
  return temp;
}
inline void Trajectory_Submap::set_allocated_pose(::cartographer::transform::proto::Rigid3d* pose) {
  delete pose_;
  pose_ = pose;
  if (pose) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:cartographer.mapping.proto.Trajectory.Submap.pose)
}

// -------------------------------------------------------------------

// Trajectory

// int32 trajectory_id = 3;
inline void Trajectory::clear_trajectory_id() {
  trajectory_id_ = 0;
}
inline ::google::protobuf::int32 Trajectory::trajectory_id() const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.trajectory_id)
  return trajectory_id_;
}
inline void Trajectory::set_trajectory_id(::google::protobuf::int32 value) {
  
  trajectory_id_ = value;
  // @@protoc_insertion_point(field_set:cartographer.mapping.proto.Trajectory.trajectory_id)
}

// repeated .cartographer.mapping.proto.Trajectory.Node node = 1;
inline int Trajectory::node_size() const {
  return node_.size();
}
inline void Trajectory::clear_node() {
  node_.Clear();
}
inline const ::cartographer::mapping::proto::Trajectory_Node& Trajectory::node(int index) const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.node)
  return node_.Get(index);
}
inline ::cartographer::mapping::proto::Trajectory_Node* Trajectory::mutable_node(int index) {
  // @@protoc_insertion_point(field_mutable:cartographer.mapping.proto.Trajectory.node)
  return node_.Mutable(index);
}
inline ::cartographer::mapping::proto::Trajectory_Node* Trajectory::add_node() {
  // @@protoc_insertion_point(field_add:cartographer.mapping.proto.Trajectory.node)
  return node_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Node >*
Trajectory::mutable_node() {
  // @@protoc_insertion_point(field_mutable_list:cartographer.mapping.proto.Trajectory.node)
  return &node_;
}
inline const ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Node >&
Trajectory::node() const {
  // @@protoc_insertion_point(field_list:cartographer.mapping.proto.Trajectory.node)
  return node_;
}

// repeated .cartographer.mapping.proto.Trajectory.Submap submap = 2;
inline int Trajectory::submap_size() const {
  return submap_.size();
}
inline void Trajectory::clear_submap() {
  submap_.Clear();
}
inline const ::cartographer::mapping::proto::Trajectory_Submap& Trajectory::submap(int index) const {
  // @@protoc_insertion_point(field_get:cartographer.mapping.proto.Trajectory.submap)
  return submap_.Get(index);
}
inline ::cartographer::mapping::proto::Trajectory_Submap* Trajectory::mutable_submap(int index) {
  // @@protoc_insertion_point(field_mutable:cartographer.mapping.proto.Trajectory.submap)
  return submap_.Mutable(index);
}
inline ::cartographer::mapping::proto::Trajectory_Submap* Trajectory::add_submap() {
  // @@protoc_insertion_point(field_add:cartographer.mapping.proto.Trajectory.submap)
  return submap_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Submap >*
Trajectory::mutable_submap() {
  // @@protoc_insertion_point(field_mutable_list:cartographer.mapping.proto.Trajectory.submap)
  return &submap_;
}
inline const ::google::protobuf::RepeatedPtrField< ::cartographer::mapping::proto::Trajectory_Submap >&
Trajectory::submap() const {
  // @@protoc_insertion_point(field_list:cartographer.mapping.proto.Trajectory.submap)
  return submap_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace proto
}  // namespace mapping
}  // namespace cartographer

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cartographer_2fmapping_2fproto_2ftrajectory_2eproto__INCLUDED
