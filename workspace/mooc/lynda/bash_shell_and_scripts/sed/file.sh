
unset TheFile
File=${TheFile:-/tmp/data.file}
echo File is $File
echo TheFile is $TheFile

TheFile=/home/adeswand/test.file
File=${TheFile:-/tmp/data.file$}
echo File is $File
echo TheFile is $TheFile
