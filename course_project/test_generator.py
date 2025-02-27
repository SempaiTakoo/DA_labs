import random


WORDS = [
    "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew",
    "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry",
    "strawberry", "tangerine", "watermelon", "zucchini", "carrot", "potato", "tomato",
    "cucumber", "pepper", "onion", "garlic", "broccoli", "spinach", "lettuce"
]


def generate_random_string(num_words):
    return ' '.join(random.choices(WORDS, k=num_words))


def write_to_file(filename, string1, string2):
    with open(filename, 'w') as file:
        file.write(f"{string1}\n")
        file.write(f"{string2}\n")


def main():
    num_words_1 = 5000
    num_words_2 = 10000

    string1 = generate_random_string(num_words_1)
    string2 = generate_random_string(num_words_2)

    write_to_file("input.txt", string1, string2)


if __name__ == "__main__":
    main()
