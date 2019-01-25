
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_OBJECTWRITER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_OBJECTWRITER_H__

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/util/internal/structured_objectwriter.h>
#include <google/protobuf/stubs/bytestream.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

// An ObjectWriter implementation that outputs JSON. This ObjectWriter
// supports writing a compact form or a pretty printed form.
//
// Sample usage:
//   string output;
//   StringOutputStream* str_stream = new StringOutputStream(&output);
//   CodedOutputStream* out_stream = new CodedOutputStream(str_stream);
//   JsonObjectWriter* ow = new JsonObjectWriter("  ", out_stream);
//   ow->StartObject("")
//       ->RenderString("name", "value")
//       ->RenderString("emptystring", string())
//       ->StartObject("nested")
//         ->RenderInt64("light", 299792458);
//         ->RenderDouble("pi", 3.141592653589793);
//       ->EndObject()
//       ->StartList("empty")
//       ->EndList()
//     ->EndObject();
//
// And then the output string would become:
// {
//   "name": "value",
//   "emptystring": "",
//   "nested": {
//     "light": "299792458",
//     "pi": 3.141592653589793
//   },
//   "empty": []
// }
//
// JsonObjectWriter does not validate if calls actually result in valid JSON.
// For example, passing an empty name when one would be required won't result
// in an error, just an invalid output.
//
// Note that all int64 and uint64 are rendered as strings instead of numbers.
// This is because JavaScript parses numbers as 64-bit float thus int64 and
// uint64 would lose precision if rendered as numbers.
//
// JsonObjectWriter is thread-unsafe.
class LIBPROTOBUF_EXPORT JsonObjectWriter : public StructuredObjectWriter {
 public:
  JsonObjectWriter(StringPiece indent_string,
                   google::protobuf::io::CodedOutputStream* out)
      : element_(new Element(NULL)),
        stream_(out),
        sink_(out),
        indent_string_(indent_string.ToString()),
        use_websafe_base64_for_bytes_(false) {}
  virtual ~JsonObjectWriter();

  // ObjectWriter methods.
  virtual JsonObjectWriter* StartObject(StringPiece name);
  virtual JsonObjectWriter* EndObject();
  virtual JsonObjectWriter* StartList(StringPiece name);
  virtual JsonObjectWriter* EndList();
  virtual JsonObjectWriter* RenderBool(StringPiece name, bool value);
  virtual JsonObjectWriter* RenderInt32(StringPiece name, int32 value);
  virtual JsonObjectWriter* RenderUint32(StringPiece name, uint32 value);
  virtual JsonObjectWriter* RenderInt64(StringPiece name, int64 value);
  virtual JsonObjectWriter* RenderUint64(StringPiece name, uint64 value);
  virtual JsonObjectWriter* RenderDouble(StringPiece name, double value);
  virtual JsonObjectWriter* RenderFloat(StringPiece name, float value);
  virtual JsonObjectWriter* RenderString(StringPiece name, StringPiece value);
  virtual JsonObjectWriter* RenderBytes(StringPiece name, StringPiece value);
  virtual JsonObjectWriter* RenderNull(StringPiece name);

  void set_use_websafe_base64_for_bytes(bool value) {
    use_websafe_base64_for_bytes_ = value;
  }

 protected:
  class LIBPROTOBUF_EXPORT Element : public BaseElement {
   public:
    explicit Element(Element* parent) : BaseElement(parent), is_first_(true) {}

    // Called before each field of the Element is to be processed.
    // Returns true if this is the first call (processing the first field).
    bool is_first() {
      if (is_first_) {
        is_first_ = false;
        return true;
      }
      return false;
    }

   private:
    bool is_first_;

    GOOGLE_DISALLOW_IMPLICIT_CONSTRUCTORS(Element);
  };

  virtual Element* element() { return element_.get(); }

 private:
  class LIBPROTOBUF_EXPORT ByteSinkWrapper : public strings::ByteSink {
   public:
    explicit ByteSinkWrapper(google::protobuf::io::CodedOutputStream* stream)
        : stream_(stream) {}
    virtual ~ByteSinkWrapper() {}

    // ByteSink methods.
    virtual void Append(const char* bytes, size_t n) {
      stream_->WriteRaw(bytes, n);
    }

   private:
    google::protobuf::io::CodedOutputStream* stream_;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ByteSinkWrapper);
  };

  // Renders a simple value as a string. By default all non-string Render
  // methods convert their argument to a string and call this method. This
  // method can then be used to render the simple value without escaping it.
  JsonObjectWriter* RenderSimple(StringPiece name, const string& value) {
    WritePrefix(name);
    stream_->WriteString(value);
    return this;
  }

  // Pushes a new element to the stack.
  void Push() { element_.reset(new Element(element_.release())); }

  // Pops an element off of the stack and deletes the popped element.
  void Pop() {
    bool needs_newline = !element_->is_first();
    element_.reset(element_->pop<Element>());
    if (needs_newline) NewLine();
  }

  // If pretty printing is enabled, this will write a newline to the output,
  // followed by optional indentation. Otherwise this method is a noop.
  void NewLine() {
    if (!indent_string_.empty()) {
      WriteChar('\n');
      for (int i = 0; i < element()->level(); i++) {
        stream_->WriteString(indent_string_);
      }
    }
  }

  // Writes a prefix. This will write out any pretty printing and
  // commas that are required, followed by the name and a ':' if
  // the name is not null.
  void WritePrefix(StringPiece name);

  // Writes an individual character to the output.
  void WriteChar(const char c) { stream_->WriteRaw(&c, sizeof(c)); }

  google::protobuf::scoped_ptr<Element> element_;
  google::protobuf::io::CodedOutputStream* stream_;
  ByteSinkWrapper sink_;
  const string indent_string_;

  // Whether to use regular or websafe base64 encoding for byte fields. Defaults
  // to regular base64 encoding.
  bool use_websafe_base64_for_bytes_;

  GOOGLE_DISALLOW_IMPLICIT_CONSTRUCTORS(JsonObjectWriter);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_OBJECTWRITER_H__
