#include "byte_stream.hh"
#include "debug.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : buffer(2 * capacity), 
                                              writer_pos(0), 
                                              reader_pos(0), 
                                              capacity_( capacity ), 
                                              error_(false){}

// Push data to stream, but only as much as available capacity allows.
void Writer::push(const string& data)
{
  uint64_t n = std::min<uint64_t>(data.size(), available_capacity());
  uint64_t start = writer_pos % buffer.capacity();
  uint64_t left = buffer.capacity() - start;

  if(n <= left){
    std::copy(data.begin(), data.begin() + n, buffer.begin() + start);
  }else{
    std::copy(data.begin(), data.begin() + left, buffer.begin() + writer_pos);
    std::copy(data.begin() + left, data.begin() + n, buffer.begin());
  }
  
  writer_pos += n;
  // debug( "Writer::push({}) not yet implemented", data );
}

// Signal that the stream has reached its ending. Nothing more will be written.
void Writer::close()
{
  debug( "Writer::close() not yet implemented" );
}

// Has the stream been closed?
bool Writer::is_closed() const
{
  debug( "Writer::is_closed() not yet implemented" );
  return {}; // Your code here.
}

// How many bytes can be pushed to the stream right now?
uint64_t Writer::available_capacity() const
{
  debug( "Writer::available_capacity() not yet implemented" );
  return {}; // Your code here.
}

// Total number of bytes cumulatively pushed to the stream
uint64_t Writer::bytes_pushed() const
{
  debug( "Writer::bytes_pushed() not yet implemented" );
  return {}; // Your code here.
}

// Peek at the next bytes in the buffer -- ideally as many as possible.
// It's not required to return a string_view of the *whole* buffer, but
// if the peeked string_view is only one byte at a time, it will probably force
// the caller to do a lot of extra work.
string_view Reader::peek() const
{
  debug( "Reader::peek() not yet implemented" );
  return {}; // Your code here.
}

// Remove `len` bytes from the buffer.
void Reader::pop( uint64_t len )
{
  debug( "Reader::pop({}) not yet implemented", len );
}

// Is the stream finished (closed and fully popped)?
bool Reader::is_finished() const
{
  debug( "Reader::is_finished() not yet implemented" );
  return {}; // Your code here.
}

// Number of bytes currently buffered (pushed and not popped)
uint64_t Reader::bytes_buffered() const
{
  debug( "Reader::bytes_buffered() not yet implemented" );
  return {}; // Your code here.
}

// Total number of bytes cumulatively popped from stream
uint64_t Reader::bytes_popped() const
{
  debug( "Reader::bytes_popped() not yet implemented" );
  return {}; // Your code here.
}
