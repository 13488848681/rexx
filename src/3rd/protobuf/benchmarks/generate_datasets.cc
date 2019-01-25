
#include <fstream>
#include <iostream>
#include "benchmarks.pb.h"

using benchmarks::BenchmarkDataset;
using google::protobuf::Descriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::Message;
using google::protobuf::MessageFactory;

std::set<std::string> names;

const char *file_prefix = "dataset.";
const char *file_suffix = ".pb";

void WriteFileWithPayloads(const std::string& name,
                           const std::string& message_name,
                           const std::vector<std::string>& payload) {
  if (!names.insert(name).second) {
    std::cerr << "Duplicate test name: " << name << "\n";
    abort();
  }

  // First verify that this message name exists in our set of benchmark messages
  // and that these payloads are valid for the given message.
  const Descriptor* d =
      DescriptorPool::generated_pool()->FindMessageTypeByName(message_name);

  if (!d) {
    std::cerr << "For dataset " << name << ", no such message: "
              << message_name << "\n";
    abort();
  }

  Message* m = MessageFactory::generated_factory()->GetPrototype(d)->New();

  for (size_t i = 0; i < payload.size(); i++) {
    if (!m->ParseFromString(payload[i])) {
      std::cerr << "For dataset " << name << ", payload[" << i << "] fails "
                << "to parse\n";
      abort();
    }
  }

  BenchmarkDataset dataset;
  dataset.set_name(name);
  dataset.set_message_name(message_name);
  for (size_t i = 0; i < payload.size(); i++) {
    dataset.add_payload()->assign(payload[i]);
  }

  std::ofstream writer;
  std::string fname = file_prefix + name + file_suffix;
  writer.open(fname.c_str());
  dataset.SerializeToOstream(&writer);
  writer.close();

  std::cerr << "Wrote dataset: " << fname << "\n";
}

void WriteFile(const std::string& name, const std::string& message_name,
               const std::string& payload) {
  std::vector<std::string> payloads;
  payloads.push_back(payload);
  WriteFileWithPayloads(name, message_name, payloads);
}

std::string ReadFile(const std::string& name) {
  std::ifstream file(name.c_str());
  GOOGLE_CHECK(file.is_open()) << "Couldn't find file '" << name <<
                                  "', please make sure you are running "
                                  "this command from the benchmarks/ "
                                  "directory.\n";
  return std::string((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
}

int main() {
  WriteFile("google_message1_proto3", "benchmarks.proto3.GoogleMessage1",
            ReadFile("google_message1.dat"));
  WriteFile("google_message1_proto2", "benchmarks.proto2.GoogleMessage1",
            ReadFile("google_message1.dat"));

  // Not in proto3 because it has a group, which is not supported.
  WriteFile("google_message2", "benchmarks.proto2.GoogleMessage2",
            ReadFile("google_message2.dat"));
}
