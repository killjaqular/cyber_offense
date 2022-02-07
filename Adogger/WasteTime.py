from random import randint
from sys import stdout

class WasteTime:
    def run():
        while True:
            stdout.write(f'Adogger is isCompromised.\n')
            # Make a random int list
            temp = randint(0, 1000000)
            someList = list()
            for x in range(0, temp):
                someList.append(randint(0, 1000000))

            # Sort the list, least to greatest
            someList = sorted(someList)
