#include <cassert>
#include "byte_stream.hh"
#include "debug.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : buffer(2 * capacity), 
                                              writer_pos(0), 
                                              reader_pos(0), 
                                              capacity_( capacity ),
                                              wn(0),
                                              rn(0), 
                                              error_(false),
                                              writer_finished(false){assert(capacity > 0);}

// Push data to stream, but only as much as available capacity allows.
void Writer::push(const string& data)
{
  uint64_t n = std::min<uint64_t>(data.size(), available_capacity());
  if(n == 0) return;
  uint64_t start = writer_pos % buffer.capacity();
  uint64_t left = buffer.capacity() - start;

  if(n <= left){
    std::copy(data.begin(), data.begin() + n, buffer.begin() + start);
  }else{
    std::copy(data.begin(), data.begin() + left, buffer.begin() + start);
    std::copy(data.begin() + left, data.begin() + n, buffer.begin());
  }
  
  wn += n;
  writer_pos += n;

  check();
}

// Signal that the stream has reached its ending. Nothing more will be written.
void Writer::close()
{
  writer_finished = true;
  check();
}

// Has the stream been closed?
bool Writer::is_closed() const
{
  return writer_finished;
}

// How many bytes can be pushed to the stream right now?
uint64_t Writer::available_capacity() const
{
  return capacity_ - (writer_pos - reader_pos);
}

// Total number of bytes cumulatively pushed to the stream
uint64_t Writer::bytes_pushed() const
{
  return wn;
}

// Peek at the next bytes in the buffer -- ideally as many as possible.
// It's not required to return a string_view of the *whole* buffer, but
// if the peeked string_view is only one byte at a time, it will probably force
// the caller to do a lot of extra work.
string_view Reader::peek() const
{
  uint64_t len = writer_pos - reader_pos;

  if(len == 0) return {};

  uint64_t start = reader_pos % buffer.capacity();
  uint64_t left = buffer.capacity() - start;
  uint64_t n = std::min<uint64_t>(len , left);
  string_view result(&buffer[start], n);
  
  return result; // Your code here.
}

// Remove `len` bytes from the buffer.
void Reader::pop( uint64_t len )
{
  uint64_t n = std::min<uint64_t>(len, bytes_buffered());

  rn += n;
  reader_pos += n;

  check();
}

// Is the stream finished (closed and fully popped)?
bool Reader::is_finished() const
{
  return writer_finished && (bytes_buffered() == 0); // Your code here.
}

// Number of bytes currently buffered (pushed and not popped)
uint64_t Reader::bytes_buffered() const
{
  return writer_pos - reader_pos; // Your code here.
}

// Total number of bytes cumulatively popped from stream
uint64_t Reader::bytes_popped() const
{
  return rn; // Your code here.
}

void ByteStream::check(){
  assert(writer_pos >= reader_pos);
  assert(writer_pos - reader_pos <= capacity_);
}
