echo "Compiling publisher.c and subscriber.c files..."
gcc publisher.c -o publisher
gcc subscriber.c -o subscriber
echo "Compilation done\n"

echo "Running publsiher..."
gnome-terminal -- bash -c "./publisher $1; exec bash"

echo "Running subscribers..."
for i in `seq 0 $1`
do
    if [ "$i" -eq "$1" ]; then
        break
    fi
    gnome-terminal -- bash -c "./subscriber $i; exec bash"
done

echo "Removing publisher and subscriber files..."
rm publisher
rm subscriber
echo "Done!\n"