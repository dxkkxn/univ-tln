def codegen(postfixed_l):
    f = open("a.out", "w")
    f.write("#!/usr/bin/python3\n")
    stack_level = 0
    for element in postfixed_l:
        assert(stack_level >= 0)
        if isinstance(element, bool):
            f.write(f"t{stack_level} = {element}\n")
            stack_level += 1
        elif element == "not":
            f.write(f"t{stack_level-1} = not t{stack_level-1}\n")
        else:
            f.write(f"t{stack_level-2} = t{stack_level-2} {element} t{stack_level-1}\n")
            stack_level -= 1
    f.write("print(t0)")
    f.close()
    print("Compilated successfully")


