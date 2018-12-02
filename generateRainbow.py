rainbow = []
for i in range(256):
  rainbow += [[1, i / 255, 0]]
for i in range(256):
  rainbow += [[1 - i / 255, 1, 0]]
for i in range(256):
  rainbow += [[0, 1, i / 255]]
for i in range(256):
  rainbow += [[0, 1 - i / 255, 1]]
for i in range(256):
  rainbow += [[i / 255, 0, 1]]

print(len(rainbow))
print("{")
for r in rainbow:
  print("{%.3g, %.3g, %.3g}" % (r[0], r[1], r[2]), sep='', end=', ')
print("}")