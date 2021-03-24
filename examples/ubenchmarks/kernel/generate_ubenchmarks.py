#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 23 10:16:39 2021

@author: mchow
"""
import random
import argparse
import os

registers = ["t0", "t1", "t2", "a0", "a1", "a2","a3", "a4", "a5", "a3",
             "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9","s10",
             "s11","t3", "t4", "t5", "t6"]

ISA_table = {
	#Instruction "	: Instruction type
	"add"       : "R",
    "addi"      : "I",
    "and"       : "R",
    "andi"      : "I",
    "auipc"     : "U",
    "beq_nt"    : "B_NT",
    "beq_t"     : "B_T",
    "div"       : "R",
    "jal"       : "J",
    "li"        : "U",
    "mul"       : "R",
    "mv"        : "M",
    "or"        : "R",
    "ori"       : "I",
    "sll"       : "R",
    "slt"       : "R",
    "sltu"      : "R",
    "sra"       : "R",
    "srl"       : "R",
    "sub"       : "R",
    "xor"       : "R",
    "xori"      : "I",
}

    
# Main function for code generation, given instr name and type
def generate_code(nb_instr, instr, template_code, instr_type):

    	
    compute_code = ""
    regIndex = 0
    numReg = len(registers)
    template_code = template_code.replace("KERNAL_NAME", instr)
    instr = instr.split("_")[0]

    
    register_code = ""
    line = '\t\t\t\t\t"li %s, 0x%s;"\n'
    for reg in registers:
        current_reg = random.randrange(16**8)
        register_code += (line % (reg, ('%08x' % current_reg)))
        
        
    template_code = template_code.replace("REGISTERS", register_code)
        

    line = '\t\t\t\t\t"m%d: %s %s, %s, %s;"\n'
    halfway = False
    for i in range(nb_instr):
        rd = registers[regIndex]
        rs1 = registers[(regIndex + 1) % numReg]
        rs2 = ""
        if instr_type == "R":
            rs2 = registers[(regIndex + 2) % numReg]
        elif instr_type == "I":
            rs2 = '0x'+('%03x' % random.randrange(16**3))
        elif instr_type == "U":
            rs1 = ""
            rs2 = '0x'+('%05x' % random.randrange(16**5))
        elif instr_type == "B_NT":
            rs2 = "ms"
        elif instr_type == "B_T":
            rs1 = rd
            if i == 50:
                rs2 = "ms"
                halfway = True
            elif halfway:
                rs2 = "m%d" % (nb_instr - i)
            else:
                rs2 = "m%d" % (nb_instr - i-1)
        elif instr_type == "J":
            rd = ""
            rs1 = ""
            if i == 50:
                rs2 = "ms"
                halfway = True
            elif halfway:
                rs2 = "m%d" % (nb_instr - i)
            else:
                rs2 = "m%d" % (nb_instr - i-1)
        elif instr_type == "M":
            rs2 = rs1
            rs1 = ""
            
            
        regIndex = (regIndex + 1) % numReg
        compute_code += (line % (i, instr, rd,rs1,rs2)).replace(" ,","")
    #endfor

	# Put the generated instruction into the template code

    template_code = template_code.replace("CODE", compute_code)

    return template_code
#enddef


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-NI", help="number of instructions to be generated (default=1)", dest="nb_instr", action='store', default=100, type=int)
    args = parser.parse_args()
	
    # Read the template code
    f = open("template.tmp",'r')
    template_code  = f.read()
    f.close()

    # For every instructions in the ISA, generate the benchmark
    for instr in ISA_table:
        # Generate the code 
        code = generate_code(args.nb_instr, instr, template_code, ISA_table[instr])
        # Write to file
        if not os.path.exists(instr):
            os.makedirs(instr)

        f = open(instr+"/kernel.cpp",'w')
        f.write(code)
        f.close()
        
if __name__ == "__main__":
	main()