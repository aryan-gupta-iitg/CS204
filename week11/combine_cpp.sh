#!/bin/bash

# Function to check if an include is a standard library include
is_standard_include() {
    local include_name="$1"
    
    # List of common standard C++ headers
    standard_headers=(
        "iostream" "vector" "string" "algorithm" "map" "set" "unordered_map" 
        "unordered_set" "queue" "stack" "deque" "list" "array" "bitset"
        "utility" "functional" "memory" "iterator" "numeric" "cmath" "cstdlib"
        "cstdio" "cstring" "cctype" "climits" "cfloat" "cassert" "ctime"
        "chrono" "random" "regex" "thread" "mutex" "atomic" "condition_variable"
        "future" "fstream" "sstream" "iomanip" "locale" "codecvt" "typeinfo"
        "exception" "stdexcept" "new" "limits" "valarray" "complex" "ratio"
        "tuple" "type_traits" "initializer_list" "system_error" "scoped_allocator"
        "streambuf" "ios" "iosfwd" "ostream" "istream" "strstream" "spanstream"
        "syncstream" "forward_list" "unordered_map" "unordered_set" "shared_mutex"
        "execution" "filesystem" "any" "optional" "variant" "string_view"
        "charconv" "format" "bit" "compare" "concepts" "coroutine" "ranges"
        "span" "version" "source_location" "stop_token" "semaphore" "latch"
        "barrier" "numbers" "expected" "stacktrace" "stdfloat" "mdspan"
        "print" "generator" "hazard_pointer" "rcu" "flat_map" "flat_set"
    )
    
    # Check if the include is in the standard headers list
    for std_header in "${standard_headers[@]}"; do
        if [[ "$include_name" == "$std_header" ]]; then
            return 0  # It's a standard header
        fi
    done
    
    # Check for C-style headers (starting with 'c' and containing standard names)
    if [[ "$include_name" =~ ^c[a-z]+ ]]; then
        return 0  # Likely a C standard header
    fi
    
    return 1  # Not a standard header
}

# Function to recursively process includes
process_file() {
    local file_path="$1"
    local processed_files="$2"
    local output_file="$3"
    local base_dir="$4"
    
    # Check if file exists
    if [[ ! -f "$file_path" ]]; then
        echo "Warning: File $file_path not found" >&2
        return 1
    fi
    
    # Get absolute path to avoid processing the same file multiple times
    local abs_path=$(realpath "$file_path" 2>/dev/null || echo "$file_path")
    
    # Check if this file has already been processed
    if [[ "$processed_files" == *"$abs_path"* ]]; then
        return 0
    fi
    
    # Add this file to processed list
    processed_files="$processed_files $abs_path"
    
    echo "// === Content from: $file_path ===" >> "$output_file"
    
    # Process each line of the file
    while IFS= read -r line; do
        # Check if line is an include directive
        if [[ "$line" =~ ^[[:space:]]*#include[[:space:]]*[\"\<]([^\"]+)[\"\>] ]]; then
            include_file="${BASH_REMATCH[1]}"
            
            # Extract just the filename without path for standard library check
            include_name=$(basename "$include_file")
            
            # Check if it's a standard include
            if is_standard_include "$include_name"; then
                # Keep standard includes
                echo "$line" >> "$output_file"
            else
                # It's a non-standard include, try to find and process it
                found_file=""
                
                # Try different paths to find the include file
                if [[ "$line" =~ ^[[:space:]]*#include[[:space:]]*\"([^\"]+)\" ]]; then
                    # Local include with quotes - look relative to current file
                    local current_dir=$(dirname "$file_path")
                    candidate="$current_dir/$include_file"
                    if [[ -f "$candidate" ]]; then
                        found_file="$candidate"
                    fi
                fi
                
                # If not found, try relative to base directory
                if [[ -z "$found_file" ]]; then
                    candidate="$base_dir/$include_file"
                    if [[ -f "$candidate" ]]; then
                        found_file="$candidate"
                    fi
                fi
                
                # If not found, try current directory
                if [[ -z "$found_file" ]]; then
                    candidate="./$include_file"
                    if [[ -f "$candidate" ]]; then
                        found_file="$candidate"
                    fi
                fi
                
                if [[ -n "$found_file" ]]; then
                    echo "// Including non-standard header: $include_file" >> "$output_file"
                    process_file "$found_file" "$processed_files" "$output_file" "$base_dir"
                else
                    echo "// Warning: Could not find include file: $include_file" >> "$output_file"
                    echo "$line" >> "$output_file"
                fi
            fi
        else
            # Regular line, just copy it
            echo "$line" >> "$output_file"
        fi
    done < "$file_path"
    
    echo "" >> "$output_file"
}

# Main script
if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <cpp_file>"
    echo "Example: $0 main.cpp"
    exit 1
fi

input_file="$1"

# Check if input file exists
if [[ ! -f "$input_file" ]]; then
    echo "Error: File '$input_file' not found"
    exit 1
fi

# Extract filename without extension
filename=$(basename "$input_file")
name_without_ext="${filename%.*}"

# Create output filename
output_file="${name_without_ext}_combined.cpp"

# Get base directory (directory containing the input file)
base_dir=$(dirname "$input_file")

# Initialize output file
echo "// Combined C++ file generated from: $input_file" > "$output_file"
echo "// Generated on: $(date)" >> "$output_file"
echo "" >> "$output_file"

# Process the main file
echo "Processing $input_file..."
process_file "$input_file" "" "$output_file" "$base_dir"

echo "Combined file created: $output_file"
echo "Done!"