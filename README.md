# CS 442 John Cornwell

This compiler can:

**Process Integer Expressions**
- Integer literals and variables.
- Variables must be declared before they are used.
- Assign values to variables.
- Do arithmetic operators (+, -, *, /, %, -(unary minus), and ^).
- Use relational operators (<, <=, ==, >=, >, and !).
- Use boolean operators (!, &&, and ||).
- All operators except ^ use the precedence and associativity rules of C. 

**Use Integer I/O**
- Read a comma-delimited list of variables.
- Print a comma-delimited list of expressions.
- Print a newline.
- Print a number of spaces equal to an input expression.

**Use Control Structures**
- If statements including optional else. !!Can also use as many else ifs as needed!!
- While loops
- For loops: Same formatting as C syntax. Ex: for(i = 0; i < 4; i = i + 1){Body}
- Use the C definition of true (non-zero) and false (zero).

**Use Arrays**
- Single dimension arrays whose size is determined at compile time.
- Uses C syntax for declaration and use.
- Subscripts can be either constants or variable expressions.

**Use Functions**
- Void and int functions.
- Value parameters.
- Use local variables.
- Use recursion.

**Use Booleans**
  - Boolean literals and variables.
  - Boolean assignment.
  - Print the words true and false, and read booleans (non-zero for true and 0 for false).
  - Variables must be declared before use.
  - Boolean functions and parameters.


## Usage

Use the provided makefile to build the compiler.

This compiler must be provided an input file, a listing file, and an optional output file. If an output file is not provided, the output will be printed to stdout. The resulting output will be an executable MIPS program. The listing file is simply a file that can be used to print the read program.

Run the compiler with the following command

```bash
./compiler <input file> <listing file> [output file]
```
on a UNIX system or 

```bash
compiler <input file> <listing file> [output file]
```
on Windows.

# Author
John Cornwell
