# Skyscrapers Test Suite Documentation

## Overview

This comprehensive test suite validates the correctness, memory safety, and performance of the skyscrapers 4x4 puzzle solver. The test suite consists of three main components:

1. **Functional Tests** - Verify algorithm correctness and input validation
2. **Memory Tests** - Check for memory leaks and memory safety using valgrind
3. **Performance Tests** - Benchmark algorithm execution time and efficiency

## Directory Structure

```
tests/
├── valid/                  # Valid input test cases
├── invalid/                # Invalid input test cases  
├── expected/               # Expected outputs for valid tests
├── results/                # Test execution results
├── memory_results/         # Valgrind memory test results
├── benchmark_results/      # Performance benchmark data
├── run_tests.sh           # Functional test runner
├── run_memory_tests.sh    # Memory test runner
├── run_benchmarks.sh      # Performance test runner
├── run_all_tests.sh       # Master test runner
└── README.md              # This documentation
```

## Test Categories

### Valid Input Tests
- **test_valid_01**: Basic valid case with clear constraints
- **test_valid_02**: All 1s - minimal constraints
- **test_valid_03**: All 4s - maximum constraints  
- **test_valid_04**: All 2s - medium constraints
- **test_valid_05**: Mixed constraints pattern
- **test_valid_06**: Alternating pattern
- **test_valid_07**: Corner constraints only

### Invalid Input Tests
- **test_invalid_01**: Complex impossible puzzle
- **test_invalid_02**: Out of range value (5)
- **test_invalid_03**: Out of range value (0)
- **test_invalid_04**: Too few arguments
- **test_invalid_05**: Too many arguments
- **test_invalid_06**: Non-numeric input
- **test_invalid_07**: Extra whitespace
- **test_invalid_08**: Empty input

## Running Tests

### Quick Start
```bash
# Run all test suites
./tests/run_all_tests.sh

# Run only functional tests
./tests/run_all_tests.sh --functional-only

# Run specific test suite
./tests/run_tests.sh           # Functional tests
./tests/run_memory_tests.sh    # Memory tests  
./tests/run_benchmarks.sh      # Performance tests
```

### Command Line Options
```bash
./tests/run_all_tests.sh [OPTIONS]

Options:
  --functional-only    Run only functional tests
  --memory-only        Run only memory tests
  --performance-only   Run only performance tests
  --quick             Skip time-intensive performance tests
  --help              Show help message
```

## Test Output

### Functional Tests
- ✅ **PASS**: Test completed successfully
- ❌ **FAIL**: Test failed with details
- ⊝ **SKIP**: Test skipped (missing expected output)

### Memory Tests  
- Tests for memory leaks using valgrind
- Validates no buffer overflows or invalid memory access
- Checks proper cleanup of allocated memory

### Performance Tests
- Measures execution time in milliseconds
- Reports min/max/average timing across multiple runs
- Provides performance assessment

## Expected Results

### Valid Inputs
All valid inputs should:
- Execute successfully without crashes
- Produce correct 4x4 grid solutions
- Have no memory leaks
- Complete within reasonable time (< 100ms typical)

### Invalid Inputs
All invalid inputs should:
- Reject input with appropriate error message
- Exit gracefully without crashes
- Have no memory leaks
- Fail fast (< 10ms typical)

## Adding New Tests

### Adding Valid Test Cases
1. Create input file in `tests/valid/test_valid_XX.input`
2. Run the solver to generate expected output:
   ```bash
   ./skyscrapers "$(cat tests/valid/test_valid_XX.input)" > tests/expected/test_valid_XX.out
   ```
3. Run test suite to validate

### Adding Invalid Test Cases
1. Create input file in `tests/invalid/test_invalid_XX.input`
2. Ensure the input should produce an error
3. Run test suite to validate proper error handling

### Real-World Test Cases from puzzle-skyscrapers.com
For additional test validation, you can use puzzles from **[puzzle-skyscrapers.com](https://www.puzzle-skyscrapers.com/)**:

1. Visit the website and select any 4x4 skyscrapers puzzle
2. Copy the edge constraint numbers (16 numbers total)
3. Create a new test file with the constraints as space-separated values
4. Test with: `./skyscrapers "constraints_from_website"`

This allows you to validate the solver against an extensive library of real skyscrapers puzzles with varying difficulty levels, demonstrating the robustness and accuracy of the unique constraint satisfaction algorithm.

## Troubleshooting

### Common Issues

**Memory test failures on invalid inputs:**
- Check if valgrind is properly installed
- Verify error handling doesn't access uninitialized memory

**Performance tests timeout:**
- Increase timeout values in benchmark script
- Check for infinite loops in algorithm

**Functional test failures:**
- Compare expected vs actual output in `tests/results/`
- Check for whitespace formatting differences

### Debug Mode
For detailed debugging, run individual components:
```bash
# Debug specific test
./skyscrapers "test_input" 2>&1 | tee debug.log

# Memory debug specific test  
valgrind --leak-check=full ./skyscrapers "test_input"

# Timing specific test
time ./skyscrapers "test_input"
```

## Continuous Integration

The test suite is designed for easy integration with CI/CD pipelines:

```bash
# CI-friendly command (returns proper exit codes)
./tests/run_all_tests.sh --quick

# Exit code 0: All tests passed
# Exit code 1: One or more tests failed
```

## Performance Baselines

### Expected Performance (typical desktop):
- Simple puzzles (all 1s): < 10ms
- Complex puzzles: < 100ms
- Invalid input rejection: < 5ms

### Memory Usage:
- Typical allocation: < 1KB
- No memory leaks
- Clean program termination

## Algorithm Validation

The test suite validates:
- **Correctness**: All generated solutions satisfy skyscrapers rules
- **Completeness**: Algorithm finds solutions when they exist
- **Robustness**: Proper handling of edge cases and invalid inputs
- **Efficiency**: Reasonable execution time for all test cases
- **Safety**: No memory errors or undefined behavior