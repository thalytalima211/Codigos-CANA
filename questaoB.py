import random
import timeit
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
    while arr[i] != key:
        i += 1
    arr.pop()
    return i if i != len(arr) else -1

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

    time_linear = timeit.timeit(lambda: linear_search(array.copy(), key), number=100)
    times_linear.append(time_linear / 100)

    time_sentinel = timeit.timeit(lambda: linear_search_sentinel(array.copy(), key), number=100)
    times_sentinel.append(time_sentinel / 100)

    sorted_array = sorted(array)

    time_bin = timeit.timeit(lambda: binary_search(sorted_array, key), number=100)
    time_fast = timeit.timeit(lambda: fast_binary_search(sorted_array, key), number=100)

    times_binary.append(time_bin / 100)
    times_fast_binary.append(time_fast / 100)

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

plt.figure(figsize=(12, 6))
plt.plot(sizes, times_linear, label='Busca Linear')
plt.plot(sizes, times_sentinel, label='Busca Linear com Sentinela')
plt.plot(sizes, times_binary, label='Busca Binária')
plt.plot(sizes, times_fast_binary, label='Busca Binária Rápida')
plt.xlabel('Tamanho do vetor')
plt.ylabel('Tempo de execução (s, em escala logarítimica)')
plt.yscale('log')
plt.title('Comparação entre o tempo de execução das buscas em escala logarítimica')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()