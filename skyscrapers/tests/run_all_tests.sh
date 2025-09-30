#!/bin/bash

# Master Test Runner for Skyscrapers Project
# Runs all test suites: functional, memory, and performance tests

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
EXECUTABLE="$PROJECT_DIR/skyscrapers"

echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║       SKYSCRAPERS MASTER TEST SUITE      ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo ""

# Function to print section header
print_header() {
    echo -e "${PURPLE}$1${NC}"
    echo -e "${PURPLE}$(printf '═%.0s' $(seq 1 ${#1}))${NC}"
}

# Function to run a test suite
run_test_suite() {
    local suite_name=$1
    local script_path=$2
    local description=$3
    
    print_header "$suite_name"
    echo -e "${CYAN}$description${NC}"
    echo ""
    
    if [[ -f "$script_path" ]]; then
        if bash "$script_path"; then
            echo -e "${GREEN}✅ $suite_name completed successfully${NC}"
            return 0
        else
            echo -e "${RED}❌ $suite_name failed${NC}"
            return 1
        fi
    else
        echo -e "${RED}❌ Test script not found: $script_path${NC}"
        return 1
    fi
}

# Check if executable exists
if [[ ! -f "$EXECUTABLE" ]]; then
    echo -e "${RED}Error: Executable not found at $EXECUTABLE${NC}"
    echo -e "${YELLOW}Building project...${NC}"
    cd "$PROJECT_DIR"
    if make; then
        echo -e "${GREEN}✅ Build successful${NC}"
    else
        echo -e "${RED}❌ Build failed${NC}"
        exit 1
    fi
    echo ""
fi

# Test suite tracking
total_suites=0
passed_suites=0
failed_suites=0

# Parse command line arguments
run_functional=true
run_memory=true
run_performance=true
quick_mode=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --functional-only)
            run_memory=false
            run_performance=false
            shift
            ;;
        --memory-only)
            run_functional=false
            run_performance=false
            shift
            ;;
        --performance-only)
            run_functional=false
            run_memory=false
            shift
            ;;
        --quick)
            quick_mode=true
            shift
            ;;
        --help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  --functional-only    Run only functional tests"
            echo "  --memory-only        Run only memory tests"
            echo "  --performance-only   Run only performance tests"
            echo "  --quick             Skip time-intensive performance tests"
            echo "  --help              Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Use --help for available options"
            exit 1
            ;;
    esac
done

echo -e "${CYAN}Test Configuration:${NC}"
echo -e "  Functional tests: $([ "$run_functional" = true ] && echo "${GREEN}enabled${NC}" || echo "${YELLOW}disabled${NC}")"
echo -e "  Memory tests:     $([ "$run_memory" = true ] && echo "${GREEN}enabled${NC}" || echo "${YELLOW}disabled${NC}")"
echo -e "  Performance tests: $([ "$run_performance" = true ] && echo "${GREEN}enabled${NC}" || echo "${YELLOW}disabled${NC}")"
echo -e "  Quick mode:       $([ "$quick_mode" = true ] && echo "${GREEN}enabled${NC}" || echo "${YELLOW}disabled${NC}")"
echo ""

# Run Functional Tests
if [[ "$run_functional" = true ]]; then
    if run_test_suite "FUNCTIONAL TESTS" "$SCRIPT_DIR/run_tests.sh" "Testing algorithm correctness and input validation"; then
        ((passed_suites++))
    else
        ((failed_suites++))
    fi
    ((total_suites++))
    echo ""
fi

# Run Memory Tests
if [[ "$run_memory" = true ]]; then
    if command -v valgrind &> /dev/null; then
        if run_test_suite "MEMORY TESTS" "$SCRIPT_DIR/run_memory_tests.sh" "Testing for memory leaks and memory safety"; then
            ((passed_suites++))
        else
            ((failed_suites++))
        fi
        ((total_suites++))
        echo ""
    else
        echo -e "${YELLOW}⚠️  Skipping memory tests - valgrind not available${NC}"
        echo ""
    fi
fi

# Run Performance Tests
if [[ "$run_performance" = true ]] && [[ "$quick_mode" = false ]]; then
    if run_test_suite "PERFORMANCE TESTS" "$SCRIPT_DIR/run_benchmarks.sh" "Measuring algorithm performance and timing"; then
        ((passed_suites++))
    else
        ((failed_suites++))
    fi
    ((total_suites++))
    echo ""
fi

# Final Summary
echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║              FINAL SUMMARY               ║${NC}"
echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
echo -e "Total Test Suites: ${CYAN}$total_suites${NC}"
echo -e "Passed Suites:     ${GREEN}$passed_suites${NC}"
echo -e "Failed Suites:     ${RED}$failed_suites${NC}"
echo ""

if [[ $failed_suites -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TEST SUITES PASSED! 🎉${NC}"
    echo -e "${GREEN}Your skyscrapers solver is working perfectly!${NC}"
    exit 0
else
    echo -e "${RED}❌ $failed_suites test suite(s) failed${NC}"
    echo -e "${YELLOW}Please check the individual test outputs for details${NC}"
    exit 1
fi