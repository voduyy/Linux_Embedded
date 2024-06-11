#command ls -lh $1

if [ $# -ne 1 ] 
then 
    echo "This script require one arguments"
    exit 1
fi

lines=$(ls -lh $1 | wc -l)

echo "You have $(( $lines - 1 )) objects in the $1 directory"