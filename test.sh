#!/bin/bash

# Function to prepare a file for sorting check
prepare_for_sort_check() {
    local file=$1
    local last_line=$(tail -n 1 "$file")

    # Check if the last line is ';0' and exclude it if so
    if [ "$last_line" == ";0" ]; then
        head -n -1 "$file" > tmp_file.csv
        echo "tmp_file.csv"
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
g++ main.cpp -o main
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Array of dataset files
datasets=("data/population1.csv" "data/population2.csv" "data/population3.csv" "data/population4.csv")

# Process each dataset
for dataset in "${datasets[@]}"; do
    ./main "$dataset" out/out.csv v

    # Prepare files for sorting check
    file_to_check=$(prepare_for_sort_check out/out_bst.csv)
    if ! ./is_sorted.sh "$file_to_check"; then
        echo "Sorting check failed for out/out_bst.csv in $dataset."
        rm -f tmp_file.csv 2> /dev/null
        exit 1
    fi

    file_to_check=$(prepare_for_sort_check out/out_rbt.csv)
    if ! ./is_sorted.sh "$file_to_check"; then
        echo "Sorting check failed for out/out_rbt.csv in $dataset."
        rm -f tmp_file.csv 2> /dev/null
        exit 1
    fi

    rm -f tmp_file.csv 2> /dev/null

    # Extract the dataset number
    dataset_num=$(echo $dataset | grep -o -E '[0-9]+')

    # Check if log file is identical to the sample
    if ! compare_files "log_pop$dataset_num.txt" "samples/log_pop$dataset_num.txt"; then
        echo "Log file comparison failed for $dataset."
        exit 1
    fi
done

echo "All tests passed successfully."
exit 0
