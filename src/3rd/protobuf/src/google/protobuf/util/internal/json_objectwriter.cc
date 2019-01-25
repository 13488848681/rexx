
#include <google/protobuf/util/internal/json_objectwriter.h>

#include <math.h>

#include <google/protobuf/stubs/casts.h>
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/util/internal/utility.h>
#include <google/protobuf/util/internal/json_escaping.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/stubs/mathlimits.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

using strings::ArrayByteSource;
;

JsonObjectWriter::~JsonObjectWriter() {
  if (!element_->is_root()) {
    GOOGLE_LOG(WARNING) << "JsonObjectWriter was not fully closed.";
  }
}

JsonObjectWriter* JsonObjectWriter::StartObject(StringPiece name) {
  WritePrefix(name);
  WriteChar('{');
  Push();
  return this;
}

JsonObjectWriter* JsonObjectWriter::EndObject() {
  Pop();
  WriteChar('}');
  if (element()->is_root()) NewLine();
  return this;
}

JsonObjectWriter* JsonObjectWriter::StartList(StringPiece name) {
  WritePrefix(name);
  WriteChar('[');
  Push();
  return this;
}

JsonObjectWriter* JsonObjectWriter::EndList() {
  Pop();
  WriteChar(']');
  if (element()->is_root()) NewLine();
  return this;
}

JsonObjectWriter* JsonObjectWriter::RenderBool(StringPiece name, bool value) {
  return RenderSimple(name, value ? "true" : "false");
}

JsonObjectWriter* JsonObjectWriter::RenderInt32(StringPiece name, int32 value) {
  return RenderSimple(name, SimpleItoa(value));
}

JsonObjectWriter* JsonObjectWriter::RenderUint32(StringPiece name,
                                                 uint32 value) {
  return RenderSimple(name, SimpleItoa(value));
}

JsonObjectWriter* JsonObjectWriter::RenderInt64(StringPiece name, int64 value) {
  WritePrefix(name);
  WriteChar('"');
  stream_->WriteString(SimpleItoa(value));
  WriteChar('"');
  return this;
}

JsonObjectWriter* JsonObjectWriter::RenderUint64(StringPiece name,
                                                 uint64 value) {
  WritePrefix(name);
  WriteChar('"');
  stream_->WriteString(SimpleItoa(value));
  WriteChar('"');
  return this;
}

JsonObjectWriter* JsonObjectWriter::RenderDouble(StringPiece name,
                                                 double value) {
  if (MathLimits<double>::IsFinite(value)) {
    return RenderSimple(name, SimpleDtoa(value));
  }

  // Render quoted with NaN/Infinity-aware DoubleAsString.
  return RenderString(name, DoubleAsString(value));
}

JsonObjectWriter* JsonObjectWriter::RenderFloat(StringPiece name, float value) {
  if (MathLimits<float>::IsFinite(value)) {
    return RenderSimple(name, SimpleFtoa(value));
  }

  // Render quoted with NaN/Infinity-aware FloatAsString.
  return RenderString(name, FloatAsString(value));
}

JsonObjectWriter* JsonObjectWriter::RenderString(StringPiece name,
                                                 StringPiece value) {
  WritePrefix(name);
  WriteChar('"');
  ArrayByteSource source(value);
  JsonEscaping::Escape(&source, &sink_);
  WriteChar('"');
  return this;
}

JsonObjectWriter* JsonObjectWriter::RenderBytes(StringPiece name,
                                                StringPiece value) {
  WritePrefix(name);
  string base64;

  if (use_websafe_base64_for_bytes_)
    WebSafeBase64Escape(value.ToString(), &base64);
  else
    Base64Escape(value, &base64);

  WriteChar('"');
  // TODO(wpoon): Consider a ByteSink solution that writes the base64 bytes
  //              directly to the stream, rather than first putting them
  //              into a string and then writing them to the stream.
  stream_->WriteRaw(base64.data(), base64.size());
  WriteChar('"');
  return this;
}

JsonObjectWriter* JsonObjectWriter::RenderNull(StringPiece name) {
  return RenderSimple(name, "null");
}

void JsonObjectWriter::WritePrefix(StringPiece name) {
  bool not_first = !element()->is_first();
  if (not_first) WriteChar(',');
  if (not_first || !element()->is_root()) NewLine();
  if (!name.empty()) {
    WriteChar('"');
    ArrayByteSource source(name);
    JsonEscaping::Escape(&source, &sink_);
    stream_->WriteString("\":");
    if (!indent_string_.empty()) WriteChar(' ');
  }
}

}  // namespace converter
}  // namespace util
}  // namespace protobuf
}  // namespace google
