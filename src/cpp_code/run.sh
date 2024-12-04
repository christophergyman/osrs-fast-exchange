current_dir=$(pwd)
g++ -std=c++20 main.cpp -o main -I"${current_dir}/vendor/json/single_include"

./main
rm main

