#!/bin/zsh
rm -rf  ./BMPHeader.o ./DigitRec.o ./Filter.o ./IconStatus.o ./SSOCR.o ./Version.o  ./BMPHeader.d ./DigitRec.d ./Filter.d ./IconStatus.d ./SSOCR.d ./Version.d  ssocr
echo ' '
echo 'Invoking: GCC C Compiler'
echo 'Building file: ../BMPHeader.c'

gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"BMPHeader.d" -MT"BMPHeader.o" -o "BMPHeader.o" "../BMPHeader.c"
echo 'Finished building: ../BMPHeader.c'
echo ' '
echo 'Building file: ../DigitRec.c'
gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"DigitRec.d" -MT"DigitRec.o" -o "DigitRec.o" "../DigitRec.c"
echo 'Finished building: ../DigitRec.c'
echo ' '
echo 'Building file: ../Filter.c'
gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Filter.d" -MT"Filter.o" -o "Filter.o" "../Filter.c"
echo 'Finished building: ../Filter.c'
echo ' '
echo 'Building file: ../IconStatus.c'
gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"IconStatus.d" -MT"IconStatus.o" -o "IconStatus.o" "../IconStatus.c"
echo 'Finished building: ../IconStatus.c'
echo ' '
echo 'Building file: ../SSOCR.c'
gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"SSOCR.d" -MT"SSOCR.o" -o "SSOCR.o" "../SSOCR.c"
echo 'Finished building: ../SSOCR.c'
echo ' '
echo 'Building file: ../Version.c'
gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Version.d" -MT"Version.o" -o "Version.o" "../Version.c"
echo 'Finished building: ../Version.c'
echo ' '
echo 'Building target: ssocr'
gcc  -o "ssocr"  ./BMPHeader.o ./DigitRec.o ./Filter.o ./IconStatus.o ./SSOCR.o ./Version.o   -lm
echo 'Finished building target: ssocr'
echo ' '
