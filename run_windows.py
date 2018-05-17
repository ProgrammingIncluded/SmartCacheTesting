import subprocess

programs = ["memory_bw.exe", "page_fault.exe"]
values = range(0, 21)

for p in programs:
    print(p)
    for val in values:
        res = subprocess.check_output(["powershell.exe", "./" + str(p), "-n " + str(val) + " -r 100000000"], shell=True)
        val = res.decode("utf-8").replace("\\r\\n", "\\n")
        print(val)
