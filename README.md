# Big Number - Simple Library

## 📄 Overview:
This simple library aims to be able to perform the four basic mathematical operations (addition, subtraction, multiplication, and division) involving numbers with many digits.

## 💡 Operations:
This library presents the implementation of the four basic mathematical operations for integers.
1. Addition with Carrying: Receives a number A and a number B and performs the digit-by-digit addition.
2. Subtraction with Borrowing: Receives a number A and a number B and performs the digit-by-digit subtraction.
3. Multiplication of Partial Products: Receives a number A and a number B and performs the multiplication.
4. Euclidean Division: Receives a number A and a number B and performs the division.

## 🤔 How To Use:
When you run the code, it will request two files. The first file is the input file, and the second file is the output file.

```
Enter the input file: ../test/operation_sum_input/op1.txt
Enter the output file: ../test/operation_sum_output/op1.txt
```

The input file must follow a specific format, which is described below:
1. Digits of Number A.
2. Digits of Number B.
3. Operator (+, -, *, /).

```
2222
22
+
```

After this information is entered, the response will be displayed in the output file.

## 🎯 Numeric Set: Z
This library operates exclusively on integers.

![Numeric Set](img/set.webp)

## 🚀 Importance:
Primitive data types in programming languages have a size limitation that prevents them from operating on very large numbers. This is why there is a need to create mechanisms that allow us to overcome this problem and operate on this type of number.

## 🔐 Digit Limit:
This library uses "long int" to store the number of elements in a number. Therefore, it is possible to perform operations with numbers that have up to 2,147,483,647 digits.

## 🔨 Valgrind:
As can be seen in the image below, Valgrind did not detect any errors in the code (all four operations were tested).

![Valgrind Screen](img/valgrind.webp)
