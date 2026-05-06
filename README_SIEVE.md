# 🚀 LRU Cache vs SIEVE Cache (C++ Implementation)

## 📌 Project Overview

This project demonstrates the implementation of two cache eviction strategies:

* **LRU (Least Recently Used) Cache**
* **SIEVE Cache (Modern Alternative)**

The goal is to understand:

* How caching works
* Limitations of LRU
* How SIEVE improves performance

---

## 🧠 What is Cache?

A **cache** is a small, fast storage that stores frequently accessed data to reduce access time.

* **Cache Hit** → Data found in cache
* **Cache Miss** → Data not found → needs insertion
* **Eviction** → Removing data when cache is full

---

## ⚙️ LRU Cache Algorithm

### 🔹 Working

* If key exists → move it to front (most recently used)
* If key does not exist:

  * If cache is full → remove least recently used (tail)
  * Insert new key at front

### 🔹 Pseudocode

```
GET(key):
  if key exists:
     move to front
     return value
  return -1

PUT(key, value):
  if key exists:
     update and move to front
  else:
     if cache is full:
        remove tail (LRU)
     insert at front
```

### 🔹 Time & Space Complexity

* Time: O(1)
* Space: O(n)

---

## ⚠️ Limitations of LRU Cache

* ❌ Requires **frequent reordering** of elements
* ❌ Uses **HashMap + Doubly Linked List** (complex)
* ❌ High overhead in multi-threaded systems
* ❌ Poor performance in sequential access patterns
* ❌ More pointer manipulation → slower in practice

---

## 🚀 Introduction to SIEVE Cache

SIEVE is a modern cache eviction algorithm designed to:

* Reduce overhead of LRU
* Improve performance
* Simplify implementation

### 🔹 Key Idea

> “Mark on access, evict later”

---

## ⚙️ SIEVE Algorithm

### 🔹 Data Structures

* List (to store elements)
* Visited bit (0/1)
* Hand pointer (iterator)

---

### 🔹 Working

#### 1. On Cache Hit

```
visited = 1
```

#### 2. On Cache Miss

* If space available → insert
* If full → perform eviction

---

### 🔹 Eviction Process

```
while true:
   if visited == 0:
       evict element
       break
   else:
       visited = 0
       move hand forward
```

---

### 🔹 Insertion

* Insert new element at front

---

## 🔄 Key Differences (LRU vs SIEVE)

| Feature        | LRU Cache     | SIEVE Cache      |
| -------------- | ------------- | ---------------- |
| Ordering       | Strict        | Approximate      |
| Movement       | Required      | Not required     |
| Data Structure | DLL + HashMap | List + Pointer   |
| Overhead       | High          | Low              |
| Performance    | Moderate      | High             |
| Complexity     | O(1)          | O(1) (amortized) |

---

## 🔥 Why SIEVE is Better

* ✅ No constant reordering
* ✅ Fewer pointer operations
* ✅ Faster in real-world systems
* ✅ Better scalability
* ✅ Simpler logic

---

## 🧪 Example

Access sequence:

```
1, 2, 3, 1, 4, 5
```

* **LRU removes:** 3
* **SIEVE removes:** 1 (depends on hand pointer)

---

## 🧠 Key Insight

> LRU is precise but expensive
> SIEVE is approximate but efficient

---

## 🎯 Conclusion

* LRU is widely used and easy to understand
* SIEVE is a modern improvement for high-performance systems
* Choosing the right algorithm depends on system requirements

---

## 📌 Author Note

This project was created to explore cache optimization techniques and understand real-world system design concepts.
