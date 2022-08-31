#  Creating files with names root.txt, home.txt and separate directories for them
echo "Creating directory \"folder_for_root...\""
date
sleep 3
mkdir folder_for_root

echo "Creating file \"folder_for_root/root.txt\"..."
date
sleep 3
touch folder_for_root/root.txt

echo "Creating directory \"folder_for_home\"..."
date
sleep 3
mkdir folder_for_home

echo "Creating file \"folder_for_home/home.txt\"..."
date
sleep 3
touch folder_for_home/home.txt

#  Filling the files root.txt and home.txt with content 
ls -tr / > folder_for_root/root.txt
ls -tr ~ > folder_for_home/home.txt

#  Printing out the contents of the files and the directories
echo "\nThe content of \"folder_for_root/root.txt\":"
cat folder_for_root/root.txt

echo "\nThe content of \"folder_for_home/home.txt\":"
cat folder_for_home/home.txt

echo "\nThe content of \"folder_for_home\":"
ls folder_for_home

echo "\nThe content of \"folder_for_root\":"
ls folder_for_root