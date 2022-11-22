cd lofsdisk/
sudo mkdir bin
sudo mkdir lib64
sudo cp /bin/bash ./bin
sudo cp /bin/ls ./bin
sudo cp -v /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libc.so.6 /lib64/ld-linux-x86-64.so.2 ./lib64/
sudo cp -v /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libdl.so.2 /lib64/ld-linux-x86-64.so.2 /lib/x86_64-linux-gnu/libpthread.so.0 ./lib64/
sudo cp -r ./lib64 ./lib
cd ..
chroot ./lofsdisk/ /bin/bash <<END
ls
./ex2.out
END