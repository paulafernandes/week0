# realpython.com/python-strings/
import sys
import string
# definition of constants
ALPHA = 26
lowA = 97
uppA = 65
# end of definition of constants

def main():
    # www.tutorialspoint.com/python3/python_command_line_arguments.htm
    if len(sys.argv) != 2:
        print("Usage: ./vigenere k")
        sys.exit(1) # exit code 1, wrong number of parameters

    argVal = (sys.argv[1]).lower()

    # stackoverflow.com/questions/19859282/check-if-a-string-contains-a-number
    if hasNumbers(argVal):
        print("Usage: ./vigenere k")
        sys.exit(1) # exit code 1, contains digits


    nChar = ""
    plainText = input("plaintext: ")
    kidx = 0
    for l in plainText:
        if kidx == len(argVal):
            kidx = 0
        if l.isalpha() and l.islower():
            # docs.python.org/3/library/string.html#string.ascii_lowercase
            nChar += chr((ord(l) - lowA + string.ascii_lowercase.index(argVal[kidx])) % ALPHA + lowA)
            kidx += 1
        elif l.isalpha() and l.isupper():
            nChar += chr((ord(l) - uppA + string.ascii_lowercase.index(argVal[kidx])) % ALPHA + uppA)
            kidx += 1
        else: nChar += l

    print("ciphertext: {}".format(nChar))

    return 0

def hasNumbers(inputString):
    return any(char.isdigit() for char in inputString)

if __name__ == "__main__":
    main()