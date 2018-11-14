# realpython.com/python-strings/
# docs.python.org/3.1/library/string.html

#quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
cents = 0
def main():
    valUser = get_input("Change owed: ")
    cents = round(valUser * 100)
    #Calculate quarters and remainer change
    quarter = cents//25
    cents = cents % 25
    #Calculate dimes and remaining change
    dimes = cents//10
    cents = cents % 10
    #Calculate Nickels and remaining change
    nickels = cents//5
    cents = cents % 5
    #Number of pennies is the remaining change
    totalCoins = quarter + dimes + nickels + cents
    print(str(totalCoins))

# stackoverflow.com/questions/35808484/how-to-check-if-a-string-represents-a-float-number
def get_input(prompt):
    while True:
        userIp = input(prompt)
        try:
            if not userIp == '' and  float(userIp) and float(userIp) > 0:
                break
        except ValueError:
          continue

    return float(userIp+'\n')

if __name__ == "__main__":
    main()
