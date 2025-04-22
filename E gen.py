from sympy import isprime
primes = []
i = 2
while len(primes) < 10000:
    if isprime(i):
        primes.append(i)
    i += 1
#print(primes)
prevrow = []
count = []
for i in range(1000):
    if (i+1) % 100 == 0:
        print('processed:', i)
    row = []
    row.append(primes[i])
    if i > 0:
        for j in range(i-1):
            row.append(prevrow[j]+prevrow[j+1])
        row.append(primes[i])
    count.append(sum([1 if isprime(x) else 0 for x in row]))
    prevrow = row

#print(max([len(str(x)) for x in prevrow]))
with open("output.txt", "w") as f:
    for x in count:
        f.write(f"{x}\n")
