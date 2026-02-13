# Process Control and Parallel Execution (COMP.2560)

This repository focuses on **Process Management** within a Linux environment, developed as part of the System Programming curriculum at the **University of Windsor**.

The projects cover the fundamentals of the process life cycle, from creation and execution to termination analysis.

## 🛠️ Technical Highlights

### 1. Process Termination Analysis
* **File:** `process_exit_diagnostics.c`
* Implements robust monitoring of child processes using system macros to differentiate between normal exits and signal-induced terminations (e.g., `SIGABRT`).

### 2. Multi-Process Arithmetic Logic
* **File:** `multiprocess_calculator.c`
* Demonstrates the use of `fork()` and `wait()` to perform independent tasks in child processes, communicating simple status results back to the parent.

### 3. Parallel Command Executor (Mini-Shell)
* **File:** `parallel_command_executor.c`
* A sophisticated tool that parses command-line arguments and uses `execvp()` to run multiple system commands concurrently, simulating the core behavior of a shell.

## 💻 Environment
* **Language:** C (POSIX)
* **University:** University of Windsor
* **Key Concepts:** Process ID (PID) management, Forking, Exec family functions, and Exit status macros.