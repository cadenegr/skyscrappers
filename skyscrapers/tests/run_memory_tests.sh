#!/bin/bash

# Skyscrapers Memory Test Suite
# Tests for memory leaks and memory safety using valgrind

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
MEMORY_RESULTS_DIR="$TESTS_DIR/memory_results"
EXECUTABLE="$PROJECT_DIR/skyscrapers"

# Create results directory
mkdir -p "$MEMORY_RESULTS_DIR"

echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║      SKYSCRAPERS MEMORY TEST SUITE       ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

# Check if valgrind is available
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: valgrind is not installed${NC}"
    echo -e "${YELLOW}Please install valgrind: sudo apt-get install valgrind${NC}"
    exit 1
fi

# Check if executable exists
if [[ ! -f "$EXECUTABLE" ]]; then
    echo -e "${RED}Error: Executable not found at $EXECUTABLE${NC}"
    echo -e "${YELLOW}Please run 'make' to build the project first.${NC}"
    exit 1
fi

echo -e "${CYAN}Testing executable: $EXECUTABLE${NC}"
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
    fi
    ((TOTAL_TESTS++))
}

# Function to run valgrind test
run_valgrind_test() {
    local test_name=$1
    local input_data=$2
    local output_file="$MEMORY_RESULTS_DIR/$test_name.valgrind"
    
    # Run valgrind with comprehensive checks
    timeout 30s valgrind \
        --tool=memcheck \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --error-exitcode=42 \
        --log-file="$output_file" \
        "$EXECUTABLE" "$input_data" > /dev/null 2>&1
    
    local exit_code=$?
    
    # Check for memory errors
    if [[ $exit_code -eq 0 ]] || [[ $exit_code -eq 1 ]]; then
        # Program ran, check valgrind results
        if grep -q "ERROR SUMMARY: 0 errors" "$output_file"; then
            if grep -q "no leaks are possible\|All heap blocks were freed" "$output_file"; then
                print_status "PASS" "$test_name (memory)"
            else
                print_status "FAIL" "$test_name (memory)" "Memory leaks detected"
            fi
        else
            local error_count=$(grep "ERROR SUMMARY:" "$output_file" | grep -o "[0-9]\+" | head -1)
            if [[ -n "$error_count" && "$error_count" -gt 0 ]]; then
                print_status "FAIL" "$test_name (memory)" "Found $error_count memory errors"
            else
                print_status "PASS" "$test_name (memory)"
            fi
        fi
    elif [[ $exit_code -eq 42 ]]; then
        print_status "FAIL" "$test_name (memory)" "Valgrind detected memory errors (exit 42)"
    elif [[ $exit_code -eq 124 ]]; then
        print_status "FAIL" "$test_name (memory)" "Valgrind timed out"
    else
        # For invalid inputs, program exit with error is normal, check valgrind results
        if grep -q "ERROR SUMMARY: 0 errors" "$output_file"; then
            print_status "PASS" "$test_name (memory)"
        else
            print_status "FAIL" "$test_name (memory)" "Memory errors on exit code $exit_code"
        fi
    fi
}

# Test 1: Memory tests on valid inputs
echo -e "${PURPLE}═══ MEMORY TESTS - VALID INPUTS ═══${NC}"

if [[ -d "$VALID_DIR" ]]; then
    for input_file in "$VALID_DIR"/*.input; do
        if [[ -f "$input_file" ]]; then
            test_name=$(basename "$input_file" .input)
            input_data=$(cat "$input_file")
            run_valgrind_test "$test_name" "$input_data"
        fi
    done
else
    echo -e "${YELLOW}No valid test directory found${NC}"
fi

echo ""

# Test 2: Memory tests on invalid inputs
echo -e "${PURPLE}═══ MEMORY TESTS - INVALID INPUTS ═══${NC}"

if [[ -d "$INVALID_DIR" ]]; then
    for input_file in "$INVALID_DIR"/*.input; do
        if [[ -f "$input_file" ]]; then
            test_name=$(basename "$input_file" .input)
            input_data=$(cat "$input_file")
            run_valgrind_test "$test_name" "$input_data"
        fi
    done
else
    echo -e "${YELLOW}No invalid test directory found${NC}"
fi

echo ""

# Test 3: Stress test with multiple runs
echo -e "${PURPLE}═══ MEMORY STRESS TESTS ═══${NC}"

# Run the same test multiple times to catch intermittent issues
stress_input="4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
for i in {1..5}; do
    run_valgrind_test "stress_test_$i" "$stress_input"
done

echo ""

# Summary
echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║            MEMORY TEST SUMMARY           ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo -e "Total Tests:  ${CYAN}$TOTAL_TESTS${NC}"
echo -e "Passed:       ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed:       ${RED}$FAILED_TESTS${NC}"

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL MEMORY TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}No memory leaks or errors detected${NC}"
    exit 0
else
    echo -e "${RED}❌ $FAILED_TESTS memory tests failed${NC}"
    echo -e "${YELLOW}Check $MEMORY_RESULTS_DIR for detailed valgrind output${NC}"
    exit 1
fi