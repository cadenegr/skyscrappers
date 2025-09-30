#!/bin/bash

# Skyscrapers Performance Benchmark Suite
# Tests algorithm performance and timing

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
TESTS_DIR="$SCRIPT_DIR"
VALID_DIR="$TESTS_DIR/valid"
BENCHMARK_RESULTS_DIR="$TESTS_DIR/benchmark_results"
EXECUTABLE="$PROJECT_DIR/skyscrapers"

# Create results directory
mkdir -p "$BENCHMARK_RESULTS_DIR"

echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║    SKYSCRAPERS PERFORMANCE BENCHMARKS    ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

# Check if executable exists
if [[ ! -f "$EXECUTABLE" ]]; then
    echo -e "${RED}Error: Executable not found at $EXECUTABLE${NC}"
    echo -e "${YELLOW}Please run 'make' to build the project first.${NC}"
    exit 1
fi

echo -e "${CYAN}Benchmarking executable: $EXECUTABLE${NC}"
echo ""

# Function to run timing test
run_timing_test() {
    local test_name=$1
    local input_data=$2
    local iterations=${3:-10}
    
    echo -e "${PURPLE}Testing: $test_name${NC}"
    
    local total_time=0
    local successful_runs=0
    local min_time=999999
    local max_time=0
    
    for ((i=1; i<=iterations; i++)); do
        # Use 'time' command to measure execution time
        local start_time=$(date +%s%N)
        if timeout 30s "$EXECUTABLE" "$input_data" > /dev/null 2>&1; then
            local end_time=$(date +%s%N)
            local execution_time=$((($end_time - $start_time) / 1000000))  # Convert to milliseconds
            
            total_time=$((total_time + execution_time))
            successful_runs=$((successful_runs + 1))
            
            if (( execution_time < min_time )); then
                min_time=$execution_time
            fi
            if (( execution_time > max_time )); then
                max_time=$execution_time
            fi
            
            echo -e "  Run $i: ${execution_time}ms"
        else
            echo -e "  Run $i: ${RED}FAILED${NC}"
        fi
    done
    
    if [[ $successful_runs -gt 0 ]]; then
        local avg_time=$((total_time / successful_runs))
        echo -e "  ${GREEN}Results for $test_name:${NC}"
        echo -e "    Successful runs: $successful_runs/$iterations"
        echo -e "    Average time:    ${CYAN}${avg_time}ms${NC}"
        echo -e "    Min time:        ${GREEN}${min_time}ms${NC}"
        echo -e "    Max time:        ${YELLOW}${max_time}ms${NC}"
        
        # Save results to file
        echo "$test_name,$successful_runs,$iterations,$avg_time,$min_time,$max_time" >> "$BENCHMARK_RESULTS_DIR/benchmark_results.csv"
    else
        echo -e "  ${RED}All runs failed for $test_name${NC}"
    fi
    
    echo ""
}

# Initialize CSV file
echo "test_name,successful_runs,total_runs,avg_time_ms,min_time_ms,max_time_ms" > "$BENCHMARK_RESULTS_DIR/benchmark_results.csv"

# Test 1: Performance on valid inputs
echo -e "${PURPLE}═══ PERFORMANCE TESTS - VALID INPUTS ═══${NC}"

if [[ -d "$VALID_DIR" ]]; then
    for input_file in "$VALID_DIR"/*.input; do
        if [[ -f "$input_file" ]]; then
            test_name=$(basename "$input_file" .input)
            input_data=$(cat "$input_file")
            run_timing_test "$test_name" "$input_data" 5
        fi
    done
else
    echo -e "${YELLOW}No valid test directory found${NC}"
fi

# Test 2: Stress test with complex case
echo -e "${PURPLE}═══ STRESS TESTS ═══${NC}"
complex_input="4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
run_timing_test "stress_complex" "$complex_input" 20

# Test 3: Quick benchmarks
echo -e "${PURPLE}═══ QUICK BENCHMARKS ═══${NC}"
simple_input="1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
run_timing_test "quick_simple" "$simple_input" 10

# Summary from CSV
echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║           PERFORMANCE SUMMARY            ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"

if [[ -f "$BENCHMARK_RESULTS_DIR/benchmark_results.csv" ]]; then
    echo -e "${CYAN}Benchmark results saved to: $BENCHMARK_RESULTS_DIR/benchmark_results.csv${NC}"
    echo ""
    echo -e "${YELLOW}Performance Summary:${NC}"
    
    # Calculate overall statistics
    total_tests=$(tail -n +2 "$BENCHMARK_RESULTS_DIR/benchmark_results.csv" | wc -l)
    avg_of_averages=$(tail -n +2 "$BENCHMARK_RESULTS_DIR/benchmark_results.csv" | cut -d',' -f4 | awk '{sum+=$1} END {print sum/NR}')
    min_of_mins=$(tail -n +2 "$BENCHMARK_RESULTS_DIR/benchmark_results.csv" | cut -d',' -f5 | sort -n | head -1)
    max_of_maxs=$(tail -n +2 "$BENCHMARK_RESULTS_DIR/benchmark_results.csv" | cut -d',' -f6 | sort -n | tail -1)
    
    echo -e "Total tests run:     ${CYAN}$total_tests${NC}"
    echo -e "Overall avg time:    ${CYAN}${avg_of_averages}ms${NC}"
    echo -e "Fastest execution:   ${GREEN}${min_of_mins}ms${NC}"
    echo -e "Slowest execution:   ${YELLOW}${max_of_maxs}ms${NC}"
    
    # Performance assessment
    if (( $(echo "$avg_of_averages < 100" | bc -l) )); then
        echo -e "${GREEN}🚀 Excellent performance! (< 100ms average)${NC}"
    elif (( $(echo "$avg_of_averages < 500" | bc -l) )); then
        echo -e "${YELLOW}⚡ Good performance (< 500ms average)${NC}"
    else
        echo -e "${RED}⚠️  Performance could be improved (> 500ms average)${NC}"
    fi
fi

echo -e "${GREEN}✅ Performance benchmarking complete!${NC}"