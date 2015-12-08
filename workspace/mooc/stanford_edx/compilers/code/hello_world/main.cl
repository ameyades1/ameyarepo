class Main {

  i : IO <- new IO;
  
  -- Returns object type IO. Compulsory method
  main() :IO   
  { 
    i.out_string("Hello World!\n")
  };

};
