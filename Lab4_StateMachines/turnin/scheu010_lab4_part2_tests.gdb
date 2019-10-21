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

test "PINA: 0x02, 0x00 => PORTC: 0x06, state: WAIT"
set state = BEGIN
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x06
expect state INIT
checkResult

test "PINA: 0x00 => PORTC: 0x07, state: INIT"
set state = BEGIN
setPINA 0x00
continue 5
expectPORTC 0x07
expect state INIT
checkResult

test "PINA: 0x01, 0x00 => PORTC: 0x08, state: WAIT"
set state = BEGIN
continue 5
setPINA 0x01
continue 5
#setPINA 0x00
continue 5
expectPORTC 0x08
expect state WAIT
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00 => PORTC: 0x09, state: WAIT"
set state = BEGIN
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTC 0x09
expect state INIT
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x02, 0x00 => PORTC: 0x08, state: WAIT"
set state = BEGIN
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x08
expect state INIT
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 => PORTC: 0x09, state: WAIT"
set state = BEGIN
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTC 0x09
expect state INIT
checkResult

test "PINA: 0x02, 0x00 => PORTC: 0x06, state: WAIT"
set state = BEGIN
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x06
expect state INIT
checkResult

test "PINA: 6 times (0x02, 0x00) => PORTC: 0x01, state: WAIT"
set state = BEGIN
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x01
expect state INIT
checkResult
 

test "PINA: 7 times (0x02, 0x00) => PORTC: 0x00, state: WAIT"
set state = BEGIN
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x00
expect state INIT
checkResult

test "PINA: 8 times (0x02, 0x00) => PORTC: 0x00, state: WAIT"
set state = BEGIN
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x00
expect state INIT
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
