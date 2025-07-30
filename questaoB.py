import random
import time
import matplotlib.pyplot as plt

def generate_array(size):
    return [random.randint(1, 100000) for _ in range(size)]

def linear_search(arr, key):
    for i in range(len(arr)):
        if arr[i] == key:
            return i
    return -1

def linear_search_sentinel(arr, key):
    arr.append(key)
    i = 0
    while True:
        if arr[i] == key:
            break
        i += 1
    arr.pop()
    if i == len(arr):
        return -1
    return i

def binary_search(arr, key):
    low = 0
    high = len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == key:
            return mid
        elif arr[mid] < key:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def fast_binary_search(arr, key, low=0, high=None):
    if high is None:
        high = len(arr) - 1
    if low > high:
        return -1
    mid = (low + high) // 2
    if arr[mid] == key:
        return mid
    elif arr[mid] > key:
        return fast_binary_search(arr, key, low, mid - 1)
    else:
        return fast_binary_search(arr, key, mid + 1, high)

sizes = [1000, 3000, 6000, 9000, 12000, 15000, 18000, 21000, 24000]
key = random.randint(1, 100000)

times_linear = []
times_sentinel = []
times_binary = []
times_fast_binary = []

for size in sizes:
    array = generate_array(size)  
    array[-1] = key

    start = time.perf_counter()
    linear_search(array.copy(), key)
    times_linear.append(time.perf_counter() - start)

    start = time.perf_counter()
    linear_search_sentinel(array.copy(), key)
    times_sentinel.append(time.perf_counter() - start)

    sorted_array = sorted(array)

    start = time.perf_counter()
    binary_search(sorted_array, key)
    times_binary.append(time.perf_counter() - start)

    start = time.perf_counter()
    fast_binary_search(sorted_array, key)
    times_fast_binary.append(time.perf_counter() - start)

plt.figure(figsize=(12, 6))
plt.plot(sizes, times_linear, label='Busca Linear')
plt.plot(sizes, times_sentinel, label='Busca Linear com Sentinela')
plt.plot(sizes, times_binary, label='Busca Binária')
plt.plot(sizes, times_fast_binary, label='Busca Binária Rápida')
plt.xlabel('Tamanho do vetor')
plt.ylabel('Tempo de execução (s)')
plt.title('Comparação entre o tempo de execução das buscas')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()