import math
import matplotlib.pyplot as plt

eps = 1e-10


class Point(object) :
    class Struct(object) :
        def __init__(self, x, y) :
            self.x = x
            self.y = y

    def make_struct(self, x, y) :
        return self.Struct(x, y)


def dcmp(x) :
    if math.fabs(x) < eps :
        return 0
    else :
        return (-1 if x < 0 else 1)


POINT = Point()
test = POINT.make_struct(1, 2)

print(test.y)
