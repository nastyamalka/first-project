# first-project
Euler exercise 1
m=1
z=0
n=0
while m<354295:
    q=0
    z=0
    m+=1
    y=str(m)
    l=len(y)
    for n in range(l):
       q=int(y[n])**5
       z=z+q
    if m==z:
      print (m) 
