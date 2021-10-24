import gdb

class MyBreakpoint (gdb.Breakpoint):
    def stop (self):
        iter_var  = gdb.parse_and_eval("range_iter")
        begin_var = gdb.parse_and_eval("begin_number")
        end_var  = gdb.parse_and_eval("end_number")
        step_var  = gdb.parse_and_eval("step")
        if iter_var % 5 == 0:
            print('@@@', iter_var, begin_var, end_var, step_var)
        return False

if __name__ == "__main__":
    point = MyBreakpoint('27')
    gdb.execute('run 1 12 > /dev/null')
    gdb.execute('q')
