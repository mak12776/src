
import random
import os
import string
import math

chars = string.ascii_letters + string.digits + '_'

def lcm(a, b):
    return a * b // math.gcd(a, b)

def generate(
        chars = None, length = 30,
        include_lettrers = True,
        include_digits = True,
        extra = None):
    rand = random.SystemRandom()
    if chars is None:
        chars = ''
        if include_lettrers:
            chars += string.ascii_letters
        if include_digits:
            chars += string.digits
        if extra is not None:
            chars += extra
    return ''.join(rand.choice(chars) for i in range(length))

assert len(generate()) == 30
assert len(generate(length = 20)) == 20


if __name__ == '__main__':
    print(generate(extra='_'))
