# !/bin/bash
SCRIPT_DIR=$(dirname "$(realpath "$BASH_SOURCE")")

if [ -d "$SCRIPT_DIR/build/pics" ]; then
    rm -r "$SCRIPT_DIR/build/pics"
    echo "Folder pics is deleted..."
fi
mkdir $SCRIPT_DIR/build/pics
echo "Created new folder pics..."
for item in $SCRIPT_DIR/build/*.dot; do
    echo "$item"
    dot -Tpng $item -o $SCRIPT_DIR/build/pics/$(basename $item .dot).png
done
echo "Created graphs in format .png..."
