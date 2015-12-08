class Main {

  i : IO <- new IO;
  
  -- Returns object, root of all classes (like C#). Compulsory method
  main() :Object   
  { 
    i.out_string("Hello World!\n")
  };

};
