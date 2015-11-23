#!c:/Perl/bin

open (MYFILE, "E:/Tanvi/SSOCR_Testing_App/List.txt") || die "List.txt file doesnot exist \n $!";
while (<MYFILE>)
{
        chomp;
 #       print "$_\n";
        $frame=$_;
 #       print "$frame\n";

         system ("E:/Tanvi/SSOCR_Testing_App/ssocr E:/Tanvi/SSOCR_Testing_App/Input_files/$frame E:/Tanvi/SSOCR_Testing_App/Output_files/op_$frame.txt");

         open(OP_FILE,"E:/Tanvi/SSOCR_Testing_App/Output_files/op_$frame.txt") || die "op_$frame.txt file doesnot exist \n $!";
         {
                $op_num=<OP_FILE>;
#                print "Print: $op_num\n";
         }
         close (OP_FILE);
         
         open(EXP_OP_FILE,"E:/Tanvi/SSOCR_Testing_App/Expected_Output_files/exp_op_$frame.txt") || die "exp_op_$frame.txt file doesnot exist \n $!";
         {
                $exp_op_num=<EXP_OP_FILE>;
 #               print "Print:: $exp_op_num\n";
         }
         close (EXP_OP_FILE);

         if($op_num eq $exp_op_num)
         {
                print ("$op_num match with the expected $exp_op_num: Pass\n");
         }
         else
         {
                print ("$op_num doesnot match with the expected $exp_op_num: Fail\n");
         }
}
close (MYFILE);



#system ("E:/Tanvi/SSOCR_Testing_App/ssocr E:/Tanvi/SSOCR_Testing_App/perfint4.bmp E:/Tanvi/SSOCR_Testing_App/perfint4_op.txt");Û

# SSOCR_Testing_App
