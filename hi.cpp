  Words& Words::operator=(const Words &source) {
    string *new_source;
    
    if(this == &source)
      return *this;
    
    if(capacity != source.capacity)
      {
	new_source = new string[source.capacity];
	delete [] data;
	data = new_source;
	capacity = source.capacity;
      }
    
    used = source.used;
    copy(source.data, source.data + used, data);
    return *this;
  }
