import time
start = time.time()
for i in range(10):
    time.sleep(1)
    
stop = time.time()
print(stop-start)