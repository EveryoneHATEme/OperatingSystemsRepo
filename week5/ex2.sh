echo "Compiling ex2.c file..."
gcc -pthread ex2.c -o ex2
echo "Compilation done\n"

echo "Executing ex2 file..."
./ex2
echo "Execution finished\n"

echo "Removing ex2 file..."
rm ex2
echo "Done!\n"