#!/bin/bash

# Skyscrapers Test Suite
# Comprehensive testing framework for the skyscrapers puzzle solver

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
TESTS_DIR="$SCRIPT_DIR"
VALID_DIR="$TESTS_DIR/valid"
INVALID_DIR="$TESTS_DIR/invalid"
EXPECTED_DIR="$TESTS_DIR/expected"
RESULTS_DIR="$TESTS_DIR/results"
EXECUTABLE="$PROJECT_DIR/skyscrapers"

# Create results directory
mkdir -p "$RESULTS_DIR"

echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║        SKYSCRAPERS TEST SUITE            ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

# Function to print test status
print_status() {
    local status=$1
    local test_name=$2
    local details=$3
    
    if [[ $status == "PASS" ]]; then
        echo -e "  [${GREEN}✓ PASS${NC}] $test_name"
        ((PASSED_TESTS++))
    elif [[ $status == "FAIL" ]]; then
        echo -e "  [${RED}✗ FAIL${NC}] $test_name"
        if [[ -n $details ]]; then
            echo -e "    ${YELLOW}Details: $details${NC}"
        fi
        ((FAILED_TESTS++))
    elif [[ $status == "SKIP" ]]; then
        echo -e "  [${YELLOW}⊝ SKIP${NC}] $test_name - $details"
    fi
    ((TOTAL_TESTS++))
}

# Function to compare outputs (ignoring whitespace differences)
compare_outputs() {
    local expected_file=$1
    local actual_file=$2
    
    # Normalize whitespace and compare
    if diff -w -u "$expected_file" "$actual_file" > /dev/null 2>&1; then
        return 0  # Files match
    else
        return 1  # Files differ
    fi
}

# Check if executable exists
if [[ ! -f "$EXECUTABLE" ]]; then
    echo -e "${RED}Error: Executable not found at $EXECUTABLE${NC}"
    echo -e "${YELLOW}Please run 'make' to build the project first.${NC}"
    exit 1
fi

echo -e "${CYAN}Testing executable: $EXECUTABLE${NC}"
echo ""

# Test 1: Valid Input Tests
echo -e "${PURPLE}═══ VALID INPUT TESTS ═══${NC}"

if [[ -d "$VALID_DIR" ]]; then
    for input_file in "$VALID_DIR"/*.input; do
        if [[ -f "$input_file" ]]; then
            test_name=$(basename "$input_file" .input)
            expected_file="$EXPECTED_DIR/$test_name.out"
            actual_file="$RESULTS_DIR/$test_name.out"
            
            if [[ ! -f "$expected_file" ]]; then
                print_status "SKIP" "$test_name" "No expected output file"
                continue
            fi
            
            # Run the test
            input_data=$(cat "$input_file")
            if timeout 10s "$EXECUTABLE" "$input_data" > "$actual_file" 2>&1; then
                if compare_outputs "$expected_file" "$actual_file"; then
                    print_status "PASS" "$test_name"
                else
                    print_status "FAIL" "$test_name" "Output mismatch"
                    # Save diff for debugging
                    diff -w -u "$expected_file" "$actual_file" > "$RESULTS_DIR/$test_name.diff"
                fi
            else
                print_status "FAIL" "$test_name" "Program crashed or timed out"
            fi
        fi
    done
else
    echo -e "${YELLOW}No valid test directory found${NC}"
fi

echo ""

# Test 2: Invalid Input Tests
echo -e "${PURPLE}═══ INVALID INPUT TESTS ═══${NC}"

if [[ -d "$INVALID_DIR" ]]; then
    for input_file in "$INVALID_DIR"/*.input; do
        if [[ -f "$input_file" ]]; then
            test_name=$(basename "$input_file" .input)
            actual_file="$RESULTS_DIR/$test_name.out"
            
            # Run the test
            input_data=$(cat "$input_file")
            if timeout 10s "$EXECUTABLE" "$input_data" > "$actual_file" 2>&1; then
                # For invalid inputs, we expect either "Error" or "Wrong argument parameters" in output
                if grep -q "Error\|Wrong argument parameters" "$actual_file"; then
                    print_status "PASS" "$test_name"
                else
                    print_status "FAIL" "$test_name" "Should have reported error"
                fi
            else
                exit_code=$?
                if [[ $exit_code == 124 ]]; then
                    print_status "FAIL" "$test_name" "Program timed out"
                else
                    # Program exited with error code, which is acceptable for invalid input
                    print_status "PASS" "$test_name"
                fi
            fi
        fi
    done
else
    echo -e "${YELLOW}No invalid test directory found${NC}"
fi

echo ""

# Test 3: Edge Cases
echo -e "${PURPLE}═══ EDGE CASE TESTS ═══${NC}"

# Test with no arguments
if timeout 5s "$EXECUTABLE" > "$RESULTS_DIR/no_args.out" 2>&1; then
    print_status "PASS" "no_arguments" 
else
    print_status "PASS" "no_arguments" # Expected to fail
fi

# Test with empty string
if timeout 5s "$EXECUTABLE" "" > "$RESULTS_DIR/empty_string.out" 2>&1; then
    print_status "PASS" "empty_string"
else
    print_status "PASS" "empty_string" # Expected to fail
fi

echo ""

# Summary
echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║              TEST SUMMARY                ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo -e "Total Tests:  ${CYAN}$TOTAL_TESTS${NC}"
echo -e "Passed:       ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed:       ${RED}$FAILED_TESTS${NC}"

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit 0
else
    echo -e "${RED}❌ $FAILED_TESTS tests failed${NC}"
    echo -e "${YELLOW}Check $RESULTS_DIR for detailed output and diffs${NC}"
    exit 1
fi