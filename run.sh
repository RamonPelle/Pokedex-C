TEMP_DIR=./temp

if [ -f "$TEMP_DIR" ] ; then
    rm -r "$TEMP_DIR"
fi
mkdir -p $TEMP_DIR

i=0
for line in $(ls  ./libs/*.c); do 
    gcc -c $line -o $TEMP_DIR/$i.out;
    i=$((i+1))
 done

gcc -c main.c -o $TEMP_DIR/main.out

gcc $(find $TEMP_DIR/*) -o output.out

rm -r $TEMP_DIR
