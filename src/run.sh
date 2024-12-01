# get current working directory
current_directory=$(pwd)

#compile
gcc main.c -o main -lcurl -L"${current_directory}/lib/cjson/1.7.18/lib" -I"${current_directory}/lib/cjson/1.7.18/include" -lcjson
./main
rm ./main
