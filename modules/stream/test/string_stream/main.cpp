#include <stream/string_stream.hpp>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "../my_assert.hpp"

using namespace Aversive::Stream;
using namespace Aversive::Container;

static constexpr buffer_t SIZE = 2048;
static constexpr u64 BUFFER_SIZE = 1024;
static char buffer[BUFFER_SIZE] = { '\0' };
static constexpr s64 VALUE = 15;

static const char* const str1 = "Hello";
static const char* const str2 = "How are you?";


template<typename Signed, typename Unsigned>
void integerTester(FormattedStringStream<SIZE>& stream) {
  constexpr int BIT = sizeof(Signed)*8;
  
  //stream.setMode(Stream::FORMATTED);
  
  stream << "   " << (Unsigned) VALUE << " ";
  Unsigned a;
  stream >> a;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream formatted u%d read and write", BIT);
  myAssert(a == (Unsigned) VALUE, buffer);
  
  stream << "   " << (Signed) VALUE << " ";
  Signed b;
  stream >> b;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream formatted s%d read and write", BIT);
  myAssert(b == (Signed) VALUE, buffer);
  
  stream.getChar();
  
  //stream.setMode(Stream::BINARY);
  
  stream << (Unsigned) VALUE;
  stream >> a;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream binary u%d read and write", BIT);
  myAssert(a == (Unsigned) VALUE, buffer);
  
  stream << (Signed) VALUE;
  stream >> b;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream binary s%d read and write", BIT);
  myAssert(b == (Signed) VALUE, buffer);
}

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  FormattedStringStream<SIZE> stream;

  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");
  stream.putChar('a');

  myAssert(stream.writable() == SIZE - 1, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 1, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  char a = stream.getChar();
  myAssert(a == 'a',  "Line " S__LINE__ ": StringStream get and set value");
  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  integerTester<s8,  u8> (stream);
  integerTester<s16, u16>(stream);
  integerTester<s32, u32>(stream);
  integerTester<s64, u64>(stream);
  
  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  //stream.setMode(Stream::FORMATTED);
  stream.setSeparatorMode(stream.WORD);
  //stream.setUserBufferSize(255);
  stream << "   " << str1 << "   " << str2 << "\n";
  
  stream >> buffer;
  myAssert(strcmp(str1, buffer) == 0, "Line " S__LINE__ ": StringStream fomatted word read and write");

  stream.setSeparatorMode(stream.LINE);
  stream >> buffer;
  myAssert(strcmp(str2, buffer) == 0, "Line " S__LINE__ ": StringStream formatted line read and write");

  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");
  
  std::cout << "OK" << std::endl;
  return 0;
}
