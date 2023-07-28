import gdb

n_measures = 10



breakpoint = ['main.c:35', 'main.c:37', 'main.c:39']
defines = ['BUBBLE', 'TREE','BUBBLE_W']

measure = list()

def evalDef():
    for i in range(0, len(defines)):
        print(defines[i])
        out = gdb.execute('info macro ' + defines[i],to_string=True)
        print(str(out))
        if("Defined at" in str(out)):
            return breakpoint[i]
        


def main():
    gdb.execute('set confirm off') #disable quit confirmation
    gdb.execute('set pagination off')  # disable GDB pagination
    gdb.execute('target remote localhost:3333')
    breakp = evalDef()
    gdb.execute(f'break {breakp}')
    
    
    for i in range(0, n_measures):
        gdb.execute('c')
        cycles_value = int(gdb.parse_and_eval('cycles'))
        gdb.execute('print cycles')
        measure.append(cycles_value)
    
        

if __name__ == '__main__':
    main()
    print('Measure: ', measure)
    gdb.execute('quit')
    