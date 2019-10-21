# Test file for Lab3_BitManipulation


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below



test "PINA: 0x00 => PORTC: 0"
setPINA 0x00
continue 5
expectPORTC 0
checkResult

test "PINA: 0x1 => PORTC: 60"
setPINA 0x01
continue 5
expectPORTC 0x60
checkResult

test "PINA: 0x4 => PORTC: 70"
setPINA 0x04
continue 5
expectPORTC 0x70
checkResult

test "PINA: 0x06 => PORTC: 38"
setPINA 0x06
continue 5
expectPORTC 0x38
checkResult

test "PINA: 0x09 => PORTC: 3C"
setPINA 0x09
continue 5
expectPORTC 0x3C
checkResult

test "PINA: 0x0A => PORTC: 3E"
setPINA 0x0A
continue 5
expectPORTC 0x3E
checkResult

test "PINA: 0x0F => PORTC: 3F"
setPINA 0x0F
continue 5
expectPORTC 0x3F
checkResult

test "PINA: 0x3F => PORTC: BF"
setPINA 0x3F
continue 5
expectPORTC 0xBF
checkResult

test "PINA: 0x1F => PORTC: 3F"
setPINA 0x1F
continue 5
expectPORTC 0x3F
checkResult

test "PINA: 0x5F => PORTC: 3F"
setPINA 0x5F
continue 5
expectPORTC 0x3F
checkResult

test "PINA: 0x7F => PORTC: 3F"
setPINA 0x7F
continue 5
expectPORTC 0x3F
checkResult




# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
