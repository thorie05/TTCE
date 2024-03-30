import ttce

def main():
    board = ttce.Chessboard("4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1")
    status = board.get_status()

    for i, f in enumerate(status[0]):
        if f != " ":
            print(f, end="")
        else:
            print(".", end="")
        if (i + 1) % 8 == 0:
            print()

    for i in range(1, len(status)):
        print(status[i])

if __name__ == "__main__":
    main()
