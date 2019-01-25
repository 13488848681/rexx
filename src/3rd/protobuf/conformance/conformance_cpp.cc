
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#include "conformance.pb.h"
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/type_resolver_util.h>

using conformance::ConformanceRequest;
using conformance::ConformanceResponse;
using conformance::TestAllTypes;
using google::protobuf::Descriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::internal::scoped_ptr;
using google::protobuf::util::BinaryToJsonString;
using google::protobuf::util::JsonToBinaryString;
using google::protobuf::util::NewTypeResolverForDescriptorPool;
using google::protobuf::util::Status;
using google::protobuf::util::TypeResolver;
using std::string;

static const char kTypeUrlPrefix[] = "type.googleapis.com";

static string GetTypeUrl(const Descriptor* message) {
  return string(kTypeUrlPrefix) + "/" + message->full_name();
}

int test_count = 0;
bool verbose = false;
TypeResolver* type_resolver;
string* type_url;


bool CheckedRead(int fd, void *buf, size_t len) {
  size_t ofs = 0;
  while (len > 0) {
    ssize_t bytes_read = read(fd, (char*)buf + ofs, len);

    if (bytes_read == 0) return false;

    if (bytes_read < 0) {
      GOOGLE_LOG(FATAL) << "Error reading from test runner: " <<  strerror(errno);
    }

    len -= bytes_read;
    ofs += bytes_read;
  }

  return true;
}

void CheckedWrite(int fd, const void *buf, size_t len) {
  if (write(fd, buf, len) != len) {
    GOOGLE_LOG(FATAL) << "Error writing to test runner: " << strerror(errno);
  }
}

void DoTest(const ConformanceRequest& request, ConformanceResponse* response) {
  TestAllTypes test_message;

  switch (request.payload_case()) {
    case ConformanceRequest::kProtobufPayload:
      if (!test_message.ParseFromString(request.protobuf_payload())) {
        // Getting parse details would involve something like:
        //   http://stackoverflow.com/questions/22121922/how-can-i-get-more-details-about-errors-generated-during-protobuf-parsing-c
        response->set_parse_error("Parse error (no more details available).");
        return;
      }
      break;

    case ConformanceRequest::kJsonPayload: {
      string proto_binary;
      Status status = JsonToBinaryString(type_resolver, *type_url,
                                         request.json_payload(), &proto_binary);
      if (!status.ok()) {
        response->set_parse_error(string("Parse error: ") +
                                  status.error_message().as_string());
        return;
      }

      if (!test_message.ParseFromString(proto_binary)) {
        response->set_runtime_error(
            "Parsing JSON generates invalid proto output.");
        return;
      }
      break;
    }

    case ConformanceRequest::PAYLOAD_NOT_SET:
      GOOGLE_LOG(FATAL) << "Request didn't have payload.";
      break;
  }

  switch (request.requested_output_format()) {
    case conformance::UNSPECIFIED:
      GOOGLE_LOG(FATAL) << "Unspecified output format";
      break;

    case conformance::PROTOBUF:
      GOOGLE_CHECK(
          test_message.SerializeToString(response->mutable_protobuf_payload()));
      break;

    case conformance::JSON: {
      string proto_binary;
      GOOGLE_CHECK(test_message.SerializeToString(&proto_binary));
      Status status = BinaryToJsonString(type_resolver, *type_url, proto_binary,
                                         response->mutable_json_payload());
      if (!status.ok()) {
        response->set_serialize_error(
            string("Failed to serialize JSON output: ") +
            status.error_message().as_string());
        return;
      }
      break;
    }

    default:
      GOOGLE_LOG(FATAL) << "Unknown output format: "
                        << request.requested_output_format();
  }
}

bool DoTestIo() {
  string serialized_input;
  string serialized_output;
  ConformanceRequest request;
  ConformanceResponse response;
  uint32_t bytes;

  if (!CheckedRead(STDIN_FILENO, &bytes, sizeof(uint32_t))) {
    // EOF.
    return false;
  }

  serialized_input.resize(bytes);

  if (!CheckedRead(STDIN_FILENO, (char*)serialized_input.c_str(), bytes)) {
    GOOGLE_LOG(ERROR) << "Unexpected EOF on stdin. " << strerror(errno);
  }

  if (!request.ParseFromString(serialized_input)) {
    GOOGLE_LOG(FATAL) << "Parse of ConformanceRequest proto failed.";
    return false;
  }

  DoTest(request, &response);

  response.SerializeToString(&serialized_output);

  bytes = serialized_output.size();
  CheckedWrite(STDOUT_FILENO, &bytes, sizeof(uint32_t));
  CheckedWrite(STDOUT_FILENO, serialized_output.c_str(), bytes);

  if (verbose) {
    fprintf(stderr, "conformance-cpp: request=%s, response=%s\n",
            request.ShortDebugString().c_str(),
            response.ShortDebugString().c_str());
  }

  test_count++;

  return true;
}

int main() {
  type_resolver = NewTypeResolverForDescriptorPool(
      kTypeUrlPrefix, DescriptorPool::generated_pool());
  type_url = new string(GetTypeUrl(TestAllTypes::descriptor()));
  while (1) {
    if (!DoTestIo()) {
      fprintf(stderr, "conformance-cpp: received EOF from test runner "
                      "after %d tests, exiting\n", test_count);
      return 0;
    }
  }
}
