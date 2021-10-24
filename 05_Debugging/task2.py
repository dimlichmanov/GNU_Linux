import gdb

class MyBreakpoint (gdb.Breakpoint):
    ordered_iter = 0
    def stop (self):
        iter_var  = gdb.parse_and_eval("range_iter")
        begin_var = gdb.parse_and_eval("begin_number")
        end_var  = gdb.parse_and_eval("end_number")
        step_var  = gdb.parse_and_eval("step")
        self.ordered_iter+=1
        if 27 < self.ordered_iter and 36 > self.ordered_iter :
            print('@@@', iter_var, begin_var, end_var, step_var)
        return False

if __name__ == "__main__":
    point = MyBreakpoint('27')
    gdb.execute('set pagination off')
    gdb.execute('run -100 100 3 > /dev/null')
    gdb.execute('q')
