echo "Compiling ex4.c file..."
gcc -pthread ex4.c -o ex4
echo "Compilation done\n"

echo "Executing ex4 file with n = 10,000,000 and m = 1..."
time ./ex4 10000000 1
echo "Execution finished\n"

echo "Executing ex4 file with n = 10,000,000 and m = 2..."
time ./ex4 10000000 2
echo "Execution finished\n"

echo "Executing ex4 file with n = 10,000,000 and m = 4..."
time ./ex4 10000000 4
echo "Execution finished\n"

echo "Executing ex4 file with n = 10,000,000 and m = 10..."
time ./ex4 10000000 10
echo "Execution finished\n"

echo "Executing ex4 file with n = 10,000,000 and m = 100..."
time ./ex4 10000000 100
echo "Execution finished\n"

echo "Removing ex4 file..."
rm ex4
echo "Done!\n"