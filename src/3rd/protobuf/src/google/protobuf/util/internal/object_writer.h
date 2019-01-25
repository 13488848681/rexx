
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_WRITER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_WRITER_H__

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/stringpiece.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

class DataPiece;

// An ObjectWriter is an interface for writing a stream of events
// representing objects and collections. Implementation of this
// interface can be used to write an object stream to an in-memory
// structure, protobufs, JSON, XML, or any other output format
// desired. The ObjectSource interface is typically used as the
// source of an object stream.
//
// See JsonObjectWriter for a sample implementation of ObjectWriter
// and its use.
//
// Derived classes could be thread-unsafe.
//
// TODO(xinb): seems like a prime candidate to apply the RAII paradigm
// and get rid the need to call EndXXX().
class LIBPROTOBUF_EXPORT ObjectWriter {
 public:
  virtual ~ObjectWriter() {}

  // Starts an object. If the name is empty, the object will not be named.
  virtual ObjectWriter* StartObject(StringPiece name) = 0;

  // Ends an object.
  virtual ObjectWriter* EndObject() = 0;

  // Starts a list. If the name is empty, the list will not be named.
  virtual ObjectWriter* StartList(StringPiece name) = 0;

  // Ends a list.
  virtual ObjectWriter* EndList() = 0;

  // Renders a boolean value.
  virtual ObjectWriter* RenderBool(StringPiece name, bool value) = 0;

  // Renders an 32-bit integer value.
  virtual ObjectWriter* RenderInt32(StringPiece name, int32 value) = 0;

  // Renders an 32-bit unsigned integer value.
  virtual ObjectWriter* RenderUint32(StringPiece name, uint32 value) = 0;

  // Renders a 64-bit integer value.
  virtual ObjectWriter* RenderInt64(StringPiece name, int64 value) = 0;

  // Renders an 64-bit unsigned integer value.
  virtual ObjectWriter* RenderUint64(StringPiece name, uint64 value) = 0;

  // Renders a double value.
  virtual ObjectWriter* RenderDouble(StringPiece name, double value) = 0;

  // Renders a float value.
  virtual ObjectWriter* RenderFloat(StringPiece name, float value) = 0;

  // Renders a StringPiece value. This is for rendering strings.
  virtual ObjectWriter* RenderString(StringPiece name, StringPiece value) = 0;

  // Renders a bytes value.
  virtual ObjectWriter* RenderBytes(StringPiece name, StringPiece value) = 0;

  // Renders a Null value.
  virtual ObjectWriter* RenderNull(StringPiece name) = 0;


  // Renders a DataPiece object to a ObjectWriter.
  static void RenderDataPieceTo(const DataPiece& data, StringPiece name,
                                ObjectWriter* ow);

  // Indicates whether this ObjectWriter has completed writing the root message,
  // usually this means writing of one complete object. Subclasses must override
  // this behavior appropriately.
  virtual bool done() { return false; }

  void set_use_strict_base64_decoding(bool value) {
    use_strict_base64_decoding_ = value;
  }

  bool use_strict_base64_decoding() const {
    return use_strict_base64_decoding_;
  }

 protected:
  ObjectWriter() : use_strict_base64_decoding_(true) {}

 private:
  // If set to true, we use the stricter version of base64 decoding for byte
  // fields by making sure decoded version encodes back to the original string.
  bool use_strict_base64_decoding_;

  // Do not add any data members to this class.
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ObjectWriter);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_WRITER_H__
