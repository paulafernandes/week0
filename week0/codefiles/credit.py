def main():
    numCC = get_input("Number: ")
    # slicing strings
    # www.digitalocean.com/community/tutorials/how-to-index-and-slice-strings-in-python-3
    lenCC = len(numCC)
    isValid = ccAlgorythm(numCC, lenCC)
    typeResult = ""
    if isValid:
        typeResult = getCCType(numCC, lenCC)
        print(typeResult)
    else: print("INVALID")

def ccAlgorythm(ccNum, lenCC):
    i, j, total, totalSum, calc, toMult, toSum = 0, 0, 0, 0, 0, 0, 0
    # if len of cc number is even or not, to choose the right order
    if lenCC % 2 == 0:
        toMult = ccNum[::2]
        toSum = ccNum[1:lenCC:2]
    else:
        toSum = ccNum[::2]
        toMult= ccNum[1:lenCC:2]

    # loop through the values and multiply it by 2
    while i < (len(toMult) - 1):
        for num in toMult:
            calc = int(num) * 2
            if calc > 9: calc = calc - 9
            total += calc
            i += 1
    # sums of the remaining digits
    while j < (len(toSum) - 1):
        for sum in toSum:
            totalSum += int(sum)
            j += 1
    if (total + totalSum) % 10 == 0:
        return True
    else: return False

# stackoverflow.com/questions/13628791/how-do-i-check-whether-an-int-is-between-the-two-numbers
def getCCType(ccNum, lenCC):
    firstdigits = ccNum[0:2]
    if   34 <= int(firstdigits) <= 37 and lenCC == 15:
        return "AMEX"
    elif 50 <= int(firstdigits) <= 56 and lenCC == 16:
        return "MASTERCARD"
    elif ccNum[0:1] == "4" and (lenCC == 13 or lenCC == 16):
        return "VISA"
    else:
        return "INVALID"

def get_input(prompt):
    while True:
        userIp = input(prompt)
        if userIp.isdigit():
            break
    return userIp

if __name__ == "__main__":
    main()