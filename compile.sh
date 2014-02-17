
rm -rf ./dev
clear
g++ -o dev dev.cpp -lpthread -lrt -lmysqlclient -DUITOX_TRACE_ENABLE
./dev

