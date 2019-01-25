
#import <Foundation/Foundation.h>

#import "Conformance.pbobjc.h"

static void Die(NSString *format, ...) __dead2;

static BOOL verbose = NO;
static int32_t testCount = 0;

static void Die(NSString *format, ...) {
  va_list args;
  va_start(args, format);
  NSString *msg = [[NSString alloc] initWithFormat:format arguments:args];
  NSLog(@"%@", msg);
  va_end(args);
  [msg release];
  exit(66);
}

static NSData *CheckedReadDataOfLength(NSFileHandle *handle, NSUInteger numBytes) {
  NSData *data = [handle readDataOfLength:numBytes];
  NSUInteger dataLen = data.length;
  if (dataLen == 0) {
    return nil;  // EOF.
  }
  if (dataLen != numBytes) {
    Die(@"Failed to read the request length (%d), only got: %@",
        numBytes, data);
  }
  return data;
}

static ConformanceResponse *DoTest(ConformanceRequest *request) {
  ConformanceResponse *response = [ConformanceResponse message];
  TestAllTypes *testMessage = nil;

  switch (request.payloadOneOfCase) {
    case ConformanceRequest_Payload_OneOfCase_GPBUnsetOneOfCase:
      Die(@"Request didn't have a payload: %@", request);
      break;

    case ConformanceRequest_Payload_OneOfCase_ProtobufPayload: {
      NSError *error = nil;
      testMessage = [TestAllTypes parseFromData:request.protobufPayload
                                          error:&error];
      if (!testMessage) {
        response.parseError =
            [NSString stringWithFormat:@"Parse error: %@", error];
      }
      break;
    }

    case ConformanceRequest_Payload_OneOfCase_JsonPayload:
      response.skipped = @"ObjC doesn't support parsing JSON";
      break;
  }

  if (testMessage) {
    switch (request.requestedOutputFormat) {
      case WireFormat_GPBUnrecognizedEnumeratorValue:
      case WireFormat_Unspecified:
        Die(@"Unrecognized/unspecified output format: %@", request);
        break;

      case WireFormat_Protobuf:
        response.protobufPayload = testMessage.data;
        if (!response.protobufPayload) {
          response.serializeError =
            [NSString stringWithFormat:@"Failed to make data from: %@", testMessage];
        }
        break;

      case WireFormat_Json:
        response.skipped = @"ObjC doesn't support generating JSON";
        break;
    }
  }

  return response;
}

static uint32_t UInt32FromLittleEndianData(NSData *data) {
  if (data.length != sizeof(uint32_t)) {
    Die(@"Data not the right size for uint32_t: %@", data);
  }
  uint32_t value;
  memcpy(&value, data.bytes, sizeof(uint32_t));
  return CFSwapInt32LittleToHost(value);
}

static NSData *UInt32ToLittleEndianData(uint32_t num) {
  uint32_t value = CFSwapInt32HostToLittle(num);
  return [NSData dataWithBytes:&value length:sizeof(uint32_t)];
}

static BOOL DoTestIo(NSFileHandle *input, NSFileHandle *output) {
  // See conformance_test_runner.cc for the wire format.
  NSData *data = CheckedReadDataOfLength(input, sizeof(uint32_t));
  if (!data) {
    // EOF.
    return NO;
  }
  uint32_t numBytes = UInt32FromLittleEndianData(data);
  data = CheckedReadDataOfLength(input, numBytes);
  if (!data) {
    Die(@"Failed to read request");
  }

  NSError *error = nil;
  ConformanceRequest *request = [ConformanceRequest parseFromData:data
                                                            error:&error];
  if (!request) {
    Die(@"Failed to parse the message data: %@", error);
  }

  ConformanceResponse *response = DoTest(request);
  if (!response) {
    Die(@"Failed to make a reply from %@", request);
  }

  data = response.data;
  [output writeData:UInt32ToLittleEndianData((int32_t)data.length)];
  [output writeData:data];

  if (verbose) {
    NSLog(@"Request: %@", request);
    NSLog(@"Response: %@", response);
  }

  ++testCount;
  return YES;
}

int main(int argc, const char *argv[]) {
  @autoreleasepool {
    NSFileHandle *input = [[NSFileHandle fileHandleWithStandardInput] retain];
    NSFileHandle *output = [[NSFileHandle fileHandleWithStandardOutput] retain];

    BOOL notDone = YES;
    while (notDone) {
      @autoreleasepool {
        notDone = DoTestIo(input, output);
      }
    }

    NSLog(@"Received EOF from test runner after %d tests, exiting.", testCount);
  }
  return 0;
}
