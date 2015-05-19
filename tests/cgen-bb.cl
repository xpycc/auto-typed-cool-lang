class Main {
  i: Int;
  s: String;
  b: Bool;
  io: IO <- new IO;
  o: Object;
  main(): Main {{
	  b <- not b;
	io.out_int(i);
	io.out_string(s);
    io.out_string("\n");
  o.copy();
	self;
  }};
};
