# Questão A - Responsável: Thalyta Lima Rodrigues

import matplotlib.pyplot as plt
import random
import time
import math

def generateArray(size):
    i = 0
    array = []
    while i < size:
        array.append(random.randint(1, size))
        i += 1
    return array

def bubbleSort(array):
    i = 0
    while i < len(array):
        j = 0
        while j < len(array) - 1:
            if array[j] > array[j + 1]:
                temp = array[j]
                array[j] = array[j + 1]
                array[j + 1] = temp
            j += 1
        i += 1

def insertionSort(array):
    for i in range(1, len(array)):
        x = array[i]
        j = i - 1

        while(j >= 0 and array[j] > x):
            array[j + 1] = array[j]
            j -= 1
        
        array[j + 1] = x

def selectionSort(array):
    for i in range(len(array) - 1):
        min = i
        for j in range(i + 1, len(array)):
            if(array[j] < array[min]):
                min = j
        aux = array[i]
        array[i] = array[min]
        array[min] = aux
    
def mergeSort(array, left, right):
    if(left < right):
        mid = math.floor((left + right) / 2)
        mergeSort(array, left, mid)
        mergeSort(array, mid + 1, right)

        tam = right - left + 1
        fim1, fim2 = False, False
        p1, p2 = left, mid + 1
        temp = []
        for i in range(tam):
            if(not fim1 and not fim2):
                if(array[p1] < array[p2]):
                    temp.append(array[p1])
                    p1 += 1
                else:
                    temp.append(array[p2])
                    p2 += 1

                if(p1 > mid):
                    fim1 = True
                if(p2 > right):
                    fim2 = True
            else:
                if(not fim1):
                    temp.append(array[p1])
                    p1 += 1
                else:
                    temp.append(array[p2])
                    p2 += 1
                    
        j, k = 0, left
        while(j < tam):
            array[k] = temp[j]
            j += 1
            k += 1

def quickSort(array, left, right):
    if(right > left):
        i = left
        for j in range(left + 1, right + 1):
            if(array[j] < array[left]):
                i += 1
                array[i], array[j] = array[j], array[i] 
        array[left], array[i] = array[i], array[left]

        quickSort(array, left, i - 1)
        quickSort(array, i + 1, right)

def countingSort(array):
    k = max(array)
    B = [0 for w in range(len(array))]
    C = [0 for w in range(k + 1)]

    for i in range(len(array)):
        C[array[i] - 1] += 1
    for i in range(1, k):
        C[i] += C[i - 1]
    for i in range(len(array) - 1, -1, -1):
        B[C[array[i] - 1] - 1] = array[i]
        C[array[i] - 1] -= 1
    for i in range(len(array)):
        array[i] = B[i]

def radixSort(array):
    max_num_dig = len(str(max(abs(x) for x in array)))
    aux = [0] * len(array)
    
    for w in range(max_num_dig):
        position = [0] * 10
        count = [0] * 10
        for i in range(len(array)):
            d = (array[i] // (10 ** w)) % 10
            count[d] += 1
        for j in range(1, 10):
            position[j] = position[j - 1] + count[j - 1]
        for i in range(len(array)):
            d = (array[i] // (10 ** w)) % 10
            aux[position[d]] = array[i]
            position[d] += 1
        for i in range(len(array)):
            array[i] = aux[i]

def bucketSort(array):
    b = [[] for _ in range(len(array))]
    for i in range(len(array)):
        array[i] /= len(array)
    for i in range(len(array)):
        bi = int(len(array) * array[i]) - 1
        b[bi].append(array[i])
    index = 0
    for v in b:
        insertionSort(v)
        for n in v:
            array[index] = n * len(array)
            index += 1

def shellSort(array):
    n = len(array)
    h = n // 2
    count = 0
    while h > 0:
        for i in range(h, n):
            c = array[i]
            j = i
            while j >= h and c < array[j - h]:
                array[j] = array[j - h]
                j -= h
                array[j] = c
                count += 1
        h =  int(h / 2.2)

def heapSort(array):
    n = len(array)
    i = n // 2
    while True:
        if i > 0:
            i -= 1
            t = array[i]
        else:
            n -= 1
            if n <= 0:
                return
            t = array[n]
            array[n] = array[0]
        pai = i
        filho = i * 2 + 1
        while filho < n:
            if (filho + 1 < n) and (array[filho + 1] > array[filho]):
                filho += 1
            if array[filho] > t:
                array[pai] = array[filho]
                pai = filho
                filho = pai * 2 + 1
            else:
                break
        array[pai] = t

sizes = [1000, 3000, 6000, 9000, 12000, 15000, 18000, 21000, 24000]
sorting_algorithms = {
    "Bubble Sort": bubbleSort,
    "Insertion Sort": insertionSort,
    "Selection Sort": selectionSort,
    "Merge Sort": mergeSort,
    "Quick Sort": quickSort,
    "Counting Sort": countingSort,
    "Radix Sort": radixSort,
    "Bucket Sort": bucketSort,
    "Shell Sort": shellSort,
    "Heap Sort": heapSort
}
times = {name: [] for name in sorting_algorithms}

for size in sizes:
    print('Tamanho {} executando...'.format(size))
    array = generateArray(size)

    for name, sort_func in sorting_algorithms.items():
        test_array = list(array)
        start = time.perf_counter()     
        sort_func(test_array, 0, size - 1) if name in ['Merge Sort', 'Quick Sort'] else sort_func(test_array)
        end = time.perf_counter()       
        elapsed_time = end - start 

        times[name].append(elapsed_time)

fig, ax = plt.subplots(figsize=(10, 6))
for name in sorting_algorithms:
    ax.plot(sizes, times[name], label=name)
ax.set_title("Comparação de Algoritmos de Ordenação")
ax.set_xlabel("Tamanho do Vetor")
ax.set_ylabel("Tempo (segundos)")
ax.legend()
plt.grid()
plt.show()

grupo_lento = ["Bubble Sort", "Insertion Sort", "Selection Sort"]
fig, ax = plt.subplots(figsize=(8, 5))
for name in grupo_lento:
    ax.plot(sizes, times[name], label=name)
ax.set_title("Comparação — Algoritmos Lentos")
ax.set_xlabel("Tamanho do Vetor")
ax.set_ylabel("Tempo (segundos)")
ax.legend()
ax.grid()
plt.show()

grupo_linear = ["Counting Sort", "Radix Sort", "Bucket Sort"]
fig, ax = plt.subplots(figsize=(8, 5))
for name in grupo_linear:
    ax.plot(sizes, times[name], label=name)
ax.set_title("Comparação — Algoritmos de Tempo Linear")
ax.set_xlabel("Tamanho do Vetor")
ax.set_ylabel("Tempo (segundos)")
ax.legend()
ax.grid()
plt.show()

grupo_eficiente = ["Quick Sort", "Merge Sort", "Heap Sort", "Shell Sort"]
fig, ax = plt.subplots(figsize=(8, 5))
for name in grupo_eficiente:
    ax.plot(sizes, times[name], label=name)
ax.set_title("Comparação — Algoritmos Eficientes")
ax.set_xlabel("Tamanho do Vetor")
ax.set_ylabel("Tempo (segundos)")
ax.legend()
ax.grid()
plt.show()