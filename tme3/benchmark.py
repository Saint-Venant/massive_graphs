import subprocess
import time
import sys

t0 = time.time()

if len(sys.argv) == 1 or sys.argv[1] not in ["scalability", "scores"]:
    print("usage:")
    print("python3 benchmark.py scalability")
    print("python3 benchmark.py scores")

if sys.argv[1] == "scalability":
    for file in ["email-Eu-core", "com-amazon.ungraph", "com-lj.ungraph", "com-orkut.ungraph"]:
        print("processing file {}.txt".format(file))

        print("Label propagation")    
        subprocess.call(["./cmake-build-debug/tp3", "color-lp", "../data/{}.txt".format(file), "tmp.txt"])
        t1 = time.time()
        print(t1 - t0)
        t0 = t1

        if file == "email-Eu-core" or file == "com-amazon.ungraph":
            print("Louvain algorithm")
            subprocess.check_output(["./louvain/louvain", "../data/{}.txt".format(file), "tmp.txt"])
            t1 = time.time()
            print(t1 - t0)
            t0 = t1

elif sys.argv[1] == "scores":
    for file in ["400_0p1_0p0005", "400_0p1_0p005", "400_0p05_0p005", "400_0p03_0p005", "LFR1", "LFR2", "LFR3", "LFR4"]:
        print("processing file {}.txt".format(file))
       
        print("Label propagation")    
        subprocess.call(["./cmake-build-debug/tp3", "color-lp", "generated_graphs/{}.txt".format(file), "tmp.txt"])
        subprocess.call(["./cmake-build-debug/tp3", "score", "generated_graphs/{}.txt".format(file), "tmp.txt"])
        t1 = time.time()
        print(t1 - t0)
        t0 = t1

        print("Louvain algorithm")
        subprocess.check_output(["./louvain/louvain", "generated_graphs/{}.txt".format(file), "tmp.txt"])
        subprocess.call(["./cmake-build-debug/tp3", "score", "generated_graphs/{}.txt".format(file), "tmp.txt"])
        t1 = time.time()
        print(t1 - t0)
        t0 = t1
        print()
