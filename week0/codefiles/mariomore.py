# realpython.com/python-strings/
# docs.python.org/3.1/library/string.html
# www.digitalocean.com/community/tutorials/how-to-use-string-formatters-in-python-3

def main():
    toPrint = ""
    i = get_input("Height: ")
    rAlign = "{:>"+str(i)+"s}"
    for y in range(i):
        toPrint = toPrint + "#"
        print(rAlign.format(toPrint) + "  " + toPrint)

def get_input(prompt):
    while True:
        userIp = input(prompt)
        if not userIp == '' and userIp.isdigit() and int(userIp) >= 0 and int(userIp) < 24:
            break
    return int(userIp)

if __name__ == "__main__":
    main()