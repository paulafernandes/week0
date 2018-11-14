def lines(a, b):
    """Return lines in both a and b"""

    ###### RESOURCES ######
    # docs.python.org/2/library/stdtypes.html#str.splitlines
    # stackoverflow.com/questions/1388818/how-can-i-compare-two-lists-in-python-and-return-matches
    # stackoverflow.com/questions/6828722/python-set-to-list

    # uses the function splitlines to extract all the lines to a list
    listA = a.splitlines()
    listB = b.splitlines()

    # compares both lists and returns what is common
    finalList = list(set(listA) & set(listB))

    return finalList


def sentences(a, b):
    """Return sentences in both a and b"""
    from nltk.tokenize import sent_tokenize

    # uses the sent_tokenize function to extract the legal words
    tokenA = sent_tokenize(a)
    tokenB = sent_tokenize(b)

    # compares both lists and returns what is common
    finalList = list(set(tokenA) & set(tokenB))

    return finalList


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    ###### RESOURCES ######
    # www.digitalocean.com/community/tutorials/how-to-index-and-slice-strings-in-python-3
    # https://www.python-course.eu/recursive_functions.php

    listA, listB = [], []

    # checks if the length of the string is not smaller than the n param
    if not len(a) < n:
        listA = CalcSubstrings(a, n, listA)
    if not len(b) < n:
        listB = CalcSubstrings(b, n, listB)

    # compares both lists and returns what is common
    finalList = list(set(listA) & set(listB))

    return finalList


# recursive function that has params the string to be splited, the length of substring and the list to contain the substrings
def CalcSubstrings(fileStr, n, subList):
    if len(fileStr) < n:
        return fileStr
    else:
        subList.append(fileStr[0:n])
        CalcSubstrings(fileStr[1:], n, subList)
        return subList