from collections import OrderedDict
import csv
import re
import sys

structs = OrderedDict()

class Entry:
    def __init__(self, bits, name, comment, bit_start, last_bit):
        self.bits = bits
        self.name = name
        self.comment = comment
        self.bit_start = bit_start
        self.last_bit = last_bit

class SubleafEntry:
    def __init__(self, start, stop):
        if int(start) > 31:
            self.start = 31
        else:
            self.start = start
        if int(stop) > 31:
            self.stop = 31
        else:
            self.stop = stop
        self.dict = OrderedDict()

TABSIZE = "    "

def get_mask(len):
    res = ""
    for _ in range(int(len)):
        res = res + "1"
    return hex(int(res, 2))

def get_cast(len):
    len = int(len)
    if len <= 8:
        return "(uint8_t)"
    elif len <= 16:
        return "(uint16_t)"
    elif len <= 32:
        return "(uint32_t)"


def get_leaf(inp):
    inp = inp.strip(' ')
    return inp

def get_subleaf(inp):
    inp = inp.strip(' ')
    if re.match(r'\d+\:\d+', inp):
        inp = inp.split(":")
    else:
        inp = [inp, inp]
    return inp

def get_reg(inp):
    inp = inp.strip(' ')
    return inp

def get_bits(inp):
    inp = inp.strip(' ')
    if re.match(r'\d+\:\d+', inp):
        inp = inp.split(":")
        inp = [(int(inp[0]) - int(inp[1])) + 1, inp[1]]
    else:
        inp = [1, inp]
    return (inp[1], str(inp[0]))

def get_name(inp):
    inp = inp.strip(' ')
    if re.match(r'^\d', inp):
        inp = "f" + inp
    return inp

def get_comment(inp):
    inp = inp.strip(' ')
    inp = inp.replace("*/","* / ")
    return inp

with open(sys.argv[2], mode="w") as out_file:
    with open(sys.argv[1], newline='') as in_file:
        in_reader = csv.reader(in_file, delimiter=',')
        last_bit = 0
        for row in in_reader:
            leaf = get_leaf(row[0])
            subleaf_ret = get_subleaf(row[1])
            subleaf = subleaf_ret[1]
            reg = get_reg(row[2])
            bits_ret = get_bits(row[3])
            bits = bits_ret[1]
            if not leaf in structs:
                last_bit = 0
                structs[leaf] = OrderedDict()
            if not subleaf in structs[leaf]:
                last_bit = 0
                structs[leaf][subleaf] = SubleafEntry(subleaf_ret[1], subleaf_ret[0])
            if not reg in structs[leaf][subleaf].dict:
                last_bit = 0
                structs[leaf][subleaf].dict[reg] = list()
            structs[leaf][subleaf].dict[reg].append(Entry(bits, get_name(row[4]), get_comment(row[5]), bits_ret[0], int(last_bit)))
            last_bit = int(bits_ret[0])+int(bits)
    out_file.write("#ifndef LEAFS_H\n")
    out_file.write("#define LEAFS_H\n")
    out_file.write("\n")
    out_file.write("#include <stdint.h>\n")
    out_file.write("\n")
    for leaf in structs:
        for subleaf in structs[leaf]:
            out_file.write("typedef struct\n{\n")
            for reg in structs[leaf][subleaf].dict:
                unused_counter = 0
                out_file.write(TABSIZE+"/*   "+reg+"   */\n")
                for elem in structs[leaf][subleaf].dict[reg]:
                    if not int(elem.bit_start) == int(elem.last_bit):
                        out_file.write(TABSIZE+"uint32_t unused_"+reg+"_"+str(unused_counter)+": "+str(int(elem.bit_start)-int(elem.last_bit))+"; /* unused */\n")    
                        unused_counter = unused_counter + 1
                    out_file.write(TABSIZE+"uint32_t "+elem.name+": "+elem.bits+"; /* "+elem.comment+" */\n")
                out_file.write(TABSIZE+"\n")
            out_file.write("} clib_cpuid_leaf_"+leaf+"_subleaf_"+subleaf+"_t;\n")
            out_file.write("\n")
    out_file.write("#endif /* LEAFS_H */\n")                

with open(sys.argv[3], mode="w") as out_src_file:
    out_src_file.write("#include \"clib_cpuid.h\"\n")
    out_src_file.write("#include \"clib_error.h\"\n")
    out_src_file.write("#include <inttypes.h>\n")
    out_src_file.write("#include <stddef.h>\n")
    out_src_file.write("\n")
    out_src_file.write("#if defined(__GNUC__) && !defined(__clang__)\n")
    out_src_file.write("#pragma GCC diagnostic push\n")
    out_src_file.write("#pragma GCC diagnostic ignored \"-Wconversion\"\n")
    out_src_file.write("#endif\n")
    out_src_file.write("\n")
    for leaf in structs:
        for subleaf in structs[leaf]:
            out_src_file.write("clib_cpuid_leaf_"+leaf+"_subleaf_"+subleaf+"_t leaf_"+leaf+"_subleaf_"+subleaf+" = { 0 };\n")
    out_src_file.write("\n")

    out_src_file.write("void *clib_cpuid_get (uint32_t leaf, uint32_t subleaf)\n")
    out_src_file.write("{\n")
    out_src_file.write(TABSIZE+"uint32_t eax = 0;\n")
    out_src_file.write(TABSIZE+"uint32_t ebx = 0;\n")
    out_src_file.write(TABSIZE+"uint32_t ecx = 0;\n")
    out_src_file.write(TABSIZE+"uint32_t edx = 0;\n")
    out_src_file.write("\n")
    out_src_file.write(TABSIZE+"clib_cpuid_raw(leaf, subleaf, &eax, &ebx, &ecx, &edx);\n")
    out_src_file.write(TABSIZE+"switch(leaf)\n")
    out_src_file.write(TABSIZE+"{\n")
    for leaf in structs:
        out_src_file.write(TABSIZE+"case "+leaf+":\n")
        first = True
        for subleaf in structs[leaf]:
            elem = structs[leaf][subleaf]
            if not first:
                out_src_file.write(TABSIZE+TABSIZE+"else ")
            else:
                out_src_file.write(TABSIZE+TABSIZE)
            first = False

            if not elem.start == elem.stop:
                lower = 2**(int(elem.start) + 1) - 1
                upper = 2**(int(elem.stop) + 1) - 1
                out_src_file.write("if((UINT32_C("+str(lower)+") <= subleaf) &&  (subleaf <= UINT32_C("+str(upper)+")))\n")
            else:
                out_src_file.write("if(subleaf == "+subleaf+")\n")

            out_src_file.write(TABSIZE+TABSIZE+"{\n")
            name = "leaf_"+leaf+"_subleaf_"+subleaf
            for reg in elem.dict:
                out_src_file.write(TABSIZE+TABSIZE+TABSIZE+"/*   "+reg+"   */\n")
                for bit in elem.dict[reg]:
                    out_src_file.write(TABSIZE+TABSIZE+TABSIZE+name+"."+bit.name+" = "+get_cast(bit.bits)+"(")
                    if not int(bit.bit_start) == 0:
                        out_src_file.write("("+reg+" >> UINT32_C("+bit.bit_start+"))")
                    else:
                        out_src_file.write(reg)
                    if not int(bit.bits) == 32:
                        out_src_file.write(" & UINT32_C("+get_mask(bit.bits)+"));\n")
                    else:
                        out_src_file.write(");\n")
            out_src_file.write(TABSIZE+TABSIZE+TABSIZE+"return &"+name+";\n")
            out_src_file.write(TABSIZE+TABSIZE+"}\n")
        out_src_file.write(TABSIZE+TABSIZE+"else\n")
        out_src_file.write(TABSIZE+TABSIZE+"{\n")
        out_src_file.write(TABSIZE+TABSIZE+TABSIZE+"clib_errno = CLIB_ERRNO_CPUID_INVALID_SUBLEAF;\n")
        out_src_file.write(TABSIZE+TABSIZE+TABSIZE+"return NULL;\n")
        out_src_file.write(TABSIZE+TABSIZE+"}\n")
        out_src_file.write(TABSIZE+TABSIZE+"break;\n")
    out_src_file.write(TABSIZE+"default:\n")
    out_src_file.write(TABSIZE+TABSIZE+"clib_errno = CLIB_ERRNO_CPUID_INVALID_SUBLEAF;\n")
    out_src_file.write(TABSIZE+TABSIZE+"return NULL;\n")
    out_src_file.write(TABSIZE+TABSIZE+"break;\n")
    out_src_file.write(TABSIZE+"}\n")
    out_src_file.write("}\n")
    out_src_file.write("\n")
    out_src_file.write("#if defined(__GNUC__) && !defined(__clang__)\n")
    out_src_file.write("#pragma GCC diagnostic pop\n")
    out_src_file.write("#endif\n")
