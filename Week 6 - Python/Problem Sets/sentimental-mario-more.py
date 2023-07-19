# TODO
def main():
    height = get_height()
    for i in range(height): #rows
        #columns for initial spaces
        for j in range(height - i - 1):
            print(' ', end = '')

        #columns for left bricks
        for j in range(i + 1):
            print('#', end = '')

        #mandatory 2 spaces in between 2 walls
        print('  ', end = '')

        #columns for right bricks
        for j in range(i + 1):
            print('#', end = '')

        print()

def get_height():
    height = 0
    while (height < 1 or height > 8):
        try:
            height = int(input('Height: '))
        except ValueError:
            continue
    else:
        return height


main()