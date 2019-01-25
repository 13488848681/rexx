
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_STREAM_PARSER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_STREAM_PARSER_H__

#include <stack>
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/stringpiece.h>
#include <google/protobuf/stubs/status.h>

namespace google {
namespace util {
class Status;
}  // namespace util

namespace protobuf {
namespace util {
namespace converter {

class ObjectWriter;

class LIBPROTOBUF_EXPORT JsonStreamParser {
 public:
  // Creates a JsonStreamParser that will write to the given ObjectWriter.
  explicit JsonStreamParser(ObjectWriter* ow);
  virtual ~JsonStreamParser();

  // Parses a UTF-8 encoded JSON string from a StringPiece.
  util::Status Parse(StringPiece json);


  // Finish parsing the JSON string.
  util::Status FinishParse();


 private:
  enum TokenType {
    BEGIN_STRING,     // " or '
    BEGIN_NUMBER,     // - or digit
    BEGIN_TRUE,       // true
    BEGIN_FALSE,      // false
    BEGIN_NULL,       // null
    BEGIN_OBJECT,     // {
    END_OBJECT,       // }
    BEGIN_ARRAY,      // [
    END_ARRAY,        // ]
    ENTRY_SEPARATOR,  // :
    VALUE_SEPARATOR,  // ,
    BEGIN_KEY,        // letter, _, $ or digit.  Must begin with non-digit
    UNKNOWN           // Unknown token or we ran out of the stream.
  };

  enum ParseType {
    VALUE,        // Expects a {, [, true, false, null, string or number
    OBJ_MID,      // Expects a ',' or }
    ENTRY,        // Expects a key or }
    ENTRY_MID,    // Expects a :
    ARRAY_VALUE,  // Expects a value or ]
    ARRAY_MID     // Expects a ',' or ]
  };

  // Holds the result of parsing a number
  struct NumberResult {
    enum Type { DOUBLE, INT, UINT };
    Type type;
    union {
      double double_val;
      int64 int_val;
      uint64 uint_val;
    };
  };

  // Parses a single chunk of JSON, returning an error if the JSON was invalid.
  util::Status ParseChunk(StringPiece json);

  // Runs the parser based on stack_ and p_, until the stack is empty or p_ runs
  // out of data. If we unexpectedly run out of p_ we push the latest back onto
  // the stack and return.
  util::Status RunParser();

  // Parses a value from p_ and writes it to ow_.
  // A value may be an object, array, true, false, null, string or number.
  util::Status ParseValue(TokenType type);

  // Parses a string and writes it out to the ow_.
  util::Status ParseString();

  // Parses a string, storing the result in parsed_.
  util::Status ParseStringHelper();

  // This function parses unicode escape sequences in strings. It returns an
  // error when there's a parsing error, either the size is not the expected
  // size or a character is not a hex digit.  When it returns str will contain
  // what has been successfully parsed so far.
  util::Status ParseUnicodeEscape();

  // Expects p_ to point to a JSON number, writes the number to the writer using
  // the appropriate Render method based on the type of number.
  util::Status ParseNumber();

  // Parse a number into a NumberResult, reporting an error if no number could
  // be parsed. This method will try to parse into a uint64, int64, or double
  // based on whether the number was positive or negative or had a decimal
  // component.
  util::Status ParseNumberHelper(NumberResult* result);

  // Handles a { during parsing of a value.
  util::Status HandleBeginObject();

  // Parses from the ENTRY state.
  util::Status ParseEntry(TokenType type);

  // Parses from the ENTRY_MID state.
  util::Status ParseEntryMid(TokenType type);

  // Parses from the OBJ_MID state.
  util::Status ParseObjectMid(TokenType type);

  // Handles a [ during parsing of a value.
  util::Status HandleBeginArray();

  // Parses from the ARRAY_VALUE state.
  util::Status ParseArrayValue(TokenType type);

  // Parses from the ARRAY_MID state.
  util::Status ParseArrayMid(TokenType type);

  // Expects p_ to point to an unquoted literal
  util::Status ParseTrue();
  util::Status ParseFalse();
  util::Status ParseNull();

  // Report a failure as a util::Status.
  util::Status ReportFailure(StringPiece message);

  // Report a failure due to an UNKNOWN token type. We check if we hit the
  // end of the stream and if we're finishing or not to detect what type of
  // status to return in this case.
  util::Status ReportUnknown(StringPiece message);

  // Advance p_ past all whitespace or until the end of the string.
  void SkipWhitespace();

  // Advance p_ one UTF-8 character
  void Advance();

  // Expects p_ to point to the beginning of a key.
  util::Status ParseKey();

  // Return the type of the next token at p_.
  TokenType GetNextTokenType();

  // The object writer to write parse events to.
  ObjectWriter* ow_;

  // The stack of parsing we still need to do. When the stack runs empty we will
  // have parsed a single value from the root (e.g. an object or list).
  std::stack<ParseType> stack_;

  // Contains any leftover text from a previous chunk that we weren't able to
  // fully parse, for example the start of a key or number.
  string leftover_;

  // The current chunk of JSON being parsed. Primarily used for providing
  // context during error reporting.
  StringPiece json_;

  // A pointer within the current JSON being parsed, used to track location.
  StringPiece p_;

  // Stores the last key read, as we separate parsing of keys and values.
  StringPiece key_;

  // Storage for key_ if we need to keep ownership, for example between chunks
  // or if the key was unescaped from a JSON string.
  string key_storage_;

  // True during the FinishParse() call, so we know that any errors are fatal.
  // For example an unterminated string will normally result in cancelling and
  // trying during the next chunk, but during FinishParse() it is an error.
  bool finishing_;

  // String we parsed during a call to ParseStringHelper().
  StringPiece parsed_;

  // Storage for the string we parsed. This may be empty if the string was able
  // to be parsed directly from the input.
  string parsed_storage_;

  // The character that opened the string, either ' or ".
  // A value of 0 indicates that string parsing is not in process.
  char string_open_;

  // Storage for the chunk that are being parsed in ParseChunk().
  string chunk_storage_;

  // Whether to allow non UTF-8 encoded input and replace invalid code points.
  bool coerce_to_utf8_;

  GOOGLE_DISALLOW_IMPLICIT_CONSTRUCTORS(JsonStreamParser);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_JSON_STREAM_PARSER_H__
