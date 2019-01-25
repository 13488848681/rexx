
#import <string>

class Widget {
 public:
  Widget(int number, const std::string& name);
  ~Widget();

  // Public accessors to number data
  float GetFloatValue() const;
  int GetIntValue() const;

  // Public accessors to the string data
  std::string GetStringValue() const;
  void GetCharPtrValue(char* buffer, size_t max_size) const;

 private:
  // Data members
  float number_;
  std::string name_;
};
