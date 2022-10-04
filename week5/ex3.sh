echo "Compiling ex3.c file..."
gcc -pthread ex3.c -o ex3
echo "Compilation done\n"

echo "Executing ex3 file with n = 10,000,000 and m = 1..."
time ./ex3 10000000 1
echo "Execution finished\n"

echo "Executing ex3 file with n = 10,000,000 and m = 2..."
time ./ex3 10000000 2
echo "Execution finished\n"

echo "Executing ex3 file with n = 10,000,000 and m = 4..."
time ./ex3 10000000 4
echo "Execution finished\n"

echo "Executing ex3 file with n = 10,000,000 and m = 10..."
time ./ex3 10000000 10
echo "Execution finished\n"

echo "Executing ex3 file with n = 10,000,000 and m = 100..."
time ./ex3 10000000 100
echo "Execution finished\n"

echo "Removing ex3 file..."
rm ex3
echo "Done!\n"