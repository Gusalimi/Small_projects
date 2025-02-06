import random
import os


def guess(given, to_guess, note) -> None:
    while True:
        try:
            user_guess = input(given[note] + "> ")
        except EOFError:
            print("Bye !")
            exit(0)
        user_guess = user_guess.lower()

        if (user_guess == 'q' or user_guess == 'quit'):
            print("Bye !")
            exit(0)

        if (user_guess == "ré"):
            user_guess = "re"
        if (user_guess == to_guess[note]):
            os.system("clear")
            print("Correct !")
            break
        else:
            os.system("clear")
            print("Wrong, try again")


def main() -> None:
    notes_en = ["c", "d", "e", "f", "g", "a", "b"]
    notes_fr = ["do", "re", "mi", "fa", "sol", "la", "si"]

    os.system("clear")
    while True:
        direction = random.randint(0, 1)
        note = random.randint(0, 6)

        if (direction == 0):
            given = notes_en
            to_guess = notes_fr
        else:
            given = notes_fr
            to_guess = notes_en

        guess(given, to_guess, note)


if __name__ == "__main__":
    main()
