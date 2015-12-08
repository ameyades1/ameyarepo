class Main inherits IO {

  -- Returns object, root of all classes (like C#). Compulsory method
  main() :Object   
  { 
    self.out_string("Hello World!\n")
    -- self is like 'this' pointer in C++ : The pointer to current object
  };

};
