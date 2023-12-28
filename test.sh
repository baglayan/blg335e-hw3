#!/bin/bash

# Function to prepare a file for sorting check
prepare_for_sort_check() {
    local file=$1
    local last_line=$(tail -n 1 "$file")

    # Check if the last line is ';0' and exclude it if so
    if [ "$last_line" == ";0" ]; then
        head -n -1 "$file" > /home/ubuntu/hostVolume/hw3/tmp_file.csv
        echo "/home/ubuntu/hostVolume/hw3/tmp_file.csv"
    else
        echo "$file"
    fi
}

# Function to compare two files
compare_files() {
    local file1=$1
    local file2=$2
    # Use diff to compare the files. If they are the same, diff will produce no output and the exit status will be 0.
    if diff -q "$file1" "$file2" > /dev/null; then
        return 0
    else
        echo "Files $file1 and $file2 differ."
        return 1
    fi
}


# Compile the program
/usr/bin/g++ /home/ubuntu/hostVolume/hw3/main.cpp -o /home/ubuntu/hostVolume/hw3/main
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Array of dataset files
datasets=("/home/ubuntu/hostVolume/hw3/data/population1.csv" "/home/ubuntu/hostVolume/hw3/data/population2.csv" "/home/ubuntu/hostVolume/hw3/data/population3.csv" "/home/ubuntu/hostVolume/hw3/data/population4.csv")

# Process each dataset
for dataset in "${datasets[@]}"; do
    /home/ubuntu/hostVolume/hw3//main "$dataset" /home/ubuntu/hostVolume/hw3/out/out.csv v

    # Prepare files for sorting check
    file_to_check=$(prepare_for_sort_check /home/ubuntu/hostVolume/hw3/out/out_bst.csv)
    if ! /home/ubuntu/hostVolume/hw3/is_sorted.sh "$file_to_check"; then
        echo "Sorting check failed for out/out_bst.csv in $dataset."
        rm -f /home/ubuntu/hostVolume/hw3/tmp_file.csv 2> /dev/null
        exit 1
    fi

    file_to_check=$(prepare_for_sort_check /home/ubuntu/hostVolume/hw3/out/out_rbt.csv)
    if ! /home/ubuntu/hostVolume/hw3/is_sorted.sh "$file_to_check"; then
        echo "Sorting check failed for out/out_rbt.csv in $dataset."
        rm -f /home/ubuntu/hostVolume/hw3/tmp_file.csv 2> /dev/null
        exit 1
    fi

    rm -f /home/ubuntu/hostVolume/hw3/tmp_file.csv 2> /dev/null

    # Extract the dataset number
    dataset_num=$(echo $dataset | grep -o -E '[0-9]+' | tail -n 1)

    find . | grep -v ".git" | sed -e "s/[^-][^\/]*\//  |/g" -e "s/|\([^ ]\)/|-\1/" 

    # Check if log file is identical to the sample
    if ! compare_files "/home/ubuntu/hostVolume/hw3/log_pop$dataset_num.txt" "/home/ubuntu/hostVolume/hw3/samples/log_pop$dataset_num.txt"; then
        echo "Log file comparison failed for $dataset."
        exit 1
    fi
done

echo "All tests passed successfully."
exit 0
