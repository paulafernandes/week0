# realpython.com/python-strings/
import sys

def main():
    # www.tutorialspoint.com/python3/python_command_line_arguments.htm
    if len(sys.argv) != 2:
        print("Usage: ./caesar k")
        sys.exit(1) # exit code 1, wrong number of parameters

    argVal = int(sys.argv[1])
    nChar = ""
    plainText = input("plaintext: ")
    # definition of constants
    ALPHA = 26
    lowA = 97
    uppA = 65
    # end of definition of constants

    # medium.com/@uniqtech/handling-ascii-character-in-python-58993859c38e
    #loops through the input plaintext
    for l in plainText:
        # checks if it is alphabetic and lowercase to use the proper ascii code
        if l.isalpha() and l.islower():
            charN = ord(l) - lowA
            nChar += chr((charN + argVal) % ALPHA + lowA)
        # checks if it is alphabetic and uppercase to use the proper ascii code
        elif l.isalpha() and l.isupper:
            charN = ord(l) - uppA
            nChar += chr((charN + argVal) % ALPHA + uppA)
        # ignores all other chars
        else: nChar += l

    print("ciphertext: {}".format(nChar))

    return 0

if __name__ == "__main__":
    main()