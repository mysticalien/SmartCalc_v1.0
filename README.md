# SmartCalc v1.0

Welcome to **SmartCalc v1.0**! This advanced calculator application not only handles basic arithmetic operations but also evaluates complex mathematical expressions, supports variable substitution, and plots function graphs. Additionally, it features a credit and deposit calculator for financial planning. 

## Features

### Arithmetic Operations
- **Basic Operations**: Addition, Subtraction, Multiplication, Division, Modulus, Power, Unary Plus, and Unary Minus.
- **Mathematical Functions**: Sine, Cosine, Tangent, Arcsine, Arccosine, Arctangent, Square Root, Natural Logarithm, and Common Logarithm.

### Expression Evaluation
- **Infix Notation**: Enter arithmetic expressions in the conventional format.
- **Polish Notation**: Use prefix notation for an alternative way to input expressions.
- **Reverse Polish Notation**: Employ postfix notation, popular in stack-based calculations.

### Variable Support
- Substitute variable `x` with numerical values in expressions.

### Graph Plotting
- **Function Graphing**: Plot graphs of functions with respect to `x`, complete with coordinate axes, scale markers, and adaptive grids.
- **Domain and Codomain**: Specify display limits within a range of -1,000,000 to 1,000,000.
- **Precision**: Ensure accuracy up to at least 7 decimal places.

### Financial Calculators
- **Credit Calculator**: Compute monthly payments, overpayments, and total payments based on the loan amount, term, interest rate, and type (annuity or differentiated).
- **Deposit Calculator**: Calculate accrued interest, tax amounts, and final deposit value considering deposit amount, term, interest rate, tax rate, payment periodicity, interest capitalization, and transaction lists (replenishments and withdrawals).

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/mysticalien/SmartCalc_v1.0.git
   cd SmartCalc_v1.0
   ```

2. **Build the Project**:
   ```bash
   cd src
   make
   ```

3. **Run the Program**:
   ```bash
   make install
   ```
   
4. **Test the Program**:
   ```bash
   make test
   ./calc_test
   make gcov_report
   ```

## Makefile Targets

- `all`: Compile the program.
- `install`: Install the program to a specified directory.
- `uninstall`: Remove the installed program.
- `clean`: Clean up compiled files.
- `dvi`: Generate documentation.
- `dist`: Create a distributable archive.
- `test`: Run unit tests.
- `gcov_report`: Generate a code coverage report.

## Interface



## Unit Testing

I use the Check library for comprehensive unit testing to ensure the correctness of the expression evaluation modules.

## GUI

Graphical user interface is built using the Qt library, providing a user-friendly and interactive experience for both Linux and Mac users.

## Usage

- **Arithmetic Calculations**: Enter expressions and press `=` to evaluate.
- **Variable Substitution**: Input expressions with `x` and assign values to `x`.
- **Graph Plotting**: Input a function in terms of `x` and visualize its graph.
- **Credit Calculator**: Input loan details and compute payments.
- **Deposit Calculator**: Enter deposit details and calculate profitability.

---

Happy Calculating! If you have any questions or suggestions, please feel free to reach out.
