
#! C:/Perl/bin

$SSOCR_PATH="c:/Tanvi/SSOCR_Testing_App";
$Result_PATH="c:\\Tanvi\\SSOCR_Testing_App\\Results.txt";

system ("del $Result_PATH");

open (MYFILE, "$SSOCR_PATH/List.txt") || die "List.txt file doesnot exist \n $!";
while (<MYFILE>)
{
        chomp;
        $frame=$_;
 #       print "$frame\n";

         system ("$SSOCR_PATH/ssocr $SSOCR_PATH/Input_files/$frame $SSOCR_PATH/Output_files/op_$frame.txt");

         open(OP_FILE,"$SSOCR_PATH/Output_files/op_$frame.txt") || die "op_$frame.txt file doesnot exist \n $!";
         {
                $op_num=<OP_FILE>;
#                print "Print: $op_num\n";
         }
         close (OP_FILE);
         
         open(EXP_OP_FILE,"$SSOCR_PATH/Expected_Output_files/exp_op_$frame.txt") || die "exp_op_$frame.txt file doesnot exist \n $!";
         {
                $exp_op_num=<EXP_OP_FILE>;
 #               print "Print:: $exp_op_num\n";
         }
         close (EXP_OP_FILE);

       # system ("del $SSOCR_PATH/Results.txt");
#system ("cd $SSOCR_PATH/Results.txt");      
       # system ("del C:/Tanvi/SSOCR_Testing_App/Results.txt");

         open(RESULT_FILE,"+>>", "$SSOCR_PATH/Results.txt") || die "exp_op_$frame.txt file doesnot exist \n $!";


         if($op_num eq $exp_op_num)
         {
                print (RESULT_FILE "For $frame frame $op_num match with the expected $exp_op_num: Pass\n");
         }
         else
         {
                print (RESULT_FILE "For $frame frame $op_num doesnot match with the expected $exp_op_num: Fail\n");
         }
         close (RESULT_FILE);
}

close (MYFILE);



#system ("E:/Tanvi/SSOCR_Testing_App/ssocr E:/Tanvi/SSOCR_Testing_App/perfint4.bmp E:/Tanvi/SSOCR_Testing_App/perfint4_op.txt");Û

# SSOCR_Testing_App
