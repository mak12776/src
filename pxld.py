
import collections
import numpy as np
import imageio

class Point:
    __slots__ = 'x', 'y'
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def copy(self):
        return Point(self.x, self.y)

def Color(*args):
    return bytearray(args)

RGB_RED =       b'\xFF\x00\x00'
RGB_BLUE =      b'\x00\x00\xFF'
RGB_GREEN =     b'\x00\xFF\x00'

RGB_BLACK =     b'\x00\x00\x00'
RGB_SILVER =    b'\xC0\xC0\xC0'
RGB_GRAY =      b'\x80\x80\x80'
RGB_WHITE =     b'\xFF\xFF\xFF'


def get_color_width(mode):
    if mode == 'RGBA':
        return 4
    elif mode == 'RGB':
        return 3
    elif mode == 'LA':
        return 2
    elif mode == 'L':
        return 1
    else:
        raise ValueError('unknown mode: {}'.format(mode))

class Image:
    __slots__ = 'buffer', 'mode', 'size', 'color_width', 'x_width', 'y_width'
    def __init__(self, mode, size, fill = None):
        self.color_width = get_color_width(mode)
        self.size = size.copy()
        self.x_width = size.x * self.color_width
        self.y_width = size.y * self.x_width

        self.buffer = np.zeros((size.y, size.x, self.color_width), np.uint8)
        self.mode = mode

    def fill(self, color):
        for y in range(0, self.size.y):
            for x in range(0, self.size.x):
                for c in range(0, self.color_width):
                    self.buffer[y][x][c] = color[c]

    def map(self, func):
        for y in range(0, self.size.y):
            for x in range(0, self.size.x):
                func(x, y, self.buffer[y][x])

    def save(self, name):
        imageio.imwrite(name, self.buffer)

class Animation:
    __slots__ = 'image', 'start', 'end'
    def __init__(self, mode, size, fill = None):
        self.image = Image(mode, size, fill)

    def render(self, file, format, **kwargs):
        if isinstance(file, str):
            file = open(file, 'wb')
            close_file = True
        else:
            close_file = False
        try:
            images = list()
            self.start()
            images.append(np.copy(self.image.buffer))
            while self.step():
                images.append(np.copy(self.image.buffer))
            imageio.mimwrite(file, images, format=format, **kwargs)
        finally:
            if close_file:
                file.close()
