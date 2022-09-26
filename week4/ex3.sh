echo "Compiling ex3.c file..."
gcc ex3.c -o ex3
echo "Compilation done\n"

echo "Executing ex3 file with argument 3 as a background process..."
./ex3 3 &

echo "Executing pstree..."
pstree

echo "Sleeping for 3 seconds..."
sleep 3

echo "Executing pstree once more..."
pstree


echo "Executing ex3 file with argument 5 as a background process..."
./ex3 5 &

echo "Executing pstree..."
pstree

echo "Sleeping for 5 seconds..."
sleep 5

echo "Executing pstree once more..."
pstree


echo "Removing ex3 file..."
rm ex3
echo "Done!\n"