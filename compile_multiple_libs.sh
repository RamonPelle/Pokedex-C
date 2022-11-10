TEMP_DIR=./temp # Temporary dir to copy builds
LIBS_DIR=./libs # Dir where the .c files are
OUTPUT_FILENAME=output.out

# Handle old temp dir if exists
if [ -f "$TEMP_DIR" ] ; then
    rm -r "$TEMP_DIR"
fi
mkdir -p $TEMP_DIR

# Build every c file
i=0
for line in $(ls  $LIBS_DIR/*.c); do 
    gcc -c $line -o $TEMP_DIR/$i.out;
    i=$((i+1))
 done

# Finally build main and final file
gcc -c main.c -o $TEMP_DIR/main.out
gcc $(find $TEMP_DIR/*) -o $OUTPUT_FILENAME
 
# Remove temp dir
rm -r $TEMP_DIR