# ZMark

ZMark is a branch predictor simulator that models predictor accuracies on arbitrary traces. It supports Lua-based predictors and outputs accuracy statistics at intervals of 1,000 branches

## Features

- **Load trace files** via the command line using `-t trace_file`.  
  Trace files must be formatted as `{PC} {t/n}`, for example: `2362e4 t`

- **Output accuracy** every 1,000 branches to a CSV file using `-o output.csv`

- **Use custom Lua predictors** via `-p predictor.lua`
  A Lua file must be provided for the simulator to work

- **Lightweight and extensible** — the core simulator is concise (~325 lines) while supporting arbitrary Lua predictors

## Usage

After compilation, run the simulator as follows:

```bash
./simulator -t trace_file -o output.csv -p predictor.lua
```

## Lua Predictor File Format

The Lua File **Must** define the following functions:
- `reset()`
    Initializes the predictor, returns `0` for success
- `predict(PC)`
    Returns `0` if the branch is not taken, `1` if taken
- `update(PC, branchResult, prediction)`
    Updates predictor state. Return `0` for success

**All 3 Functions** Are required!

## Build Instructions

- Requires `C++23` or greater
- Requires `Lua 5.4-5.4.8` to be installed

To compile the simulator, navigate to the root directory and run: 
```make```

## Notes

- The simulator outputs accuracy statistics every 1,000 branches to the CSV file specified with the `-o` argument
- Traces and Lua predictors can be swapped easily without recompiling
- Designed for easy experimentation with different branch predictors