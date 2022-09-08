echo "Compiling ex6.c file..."
gcc ex6.c -o ex6
echo "Compilation done\n"

echo "Executing ex6 file..."
echo "right triangle:"
./ex6 rightTriangle 10

echo "triangle:"

./ex6 triangle 15

echo "rectangle:"

./ex6 rectangle 5
echo "Execution finished\n"

echo "Removing ex6 file..."
rm ex6
echo "Done!\n"